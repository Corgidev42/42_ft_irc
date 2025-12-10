#include "network/Server.hpp"
#include "Message.hpp"
#include "CommandFactory.hpp"
#include <sstream>
#include <cstdlib>

Server::Server(const string& port, const string& password) : _password(password), _name("localhost") {
	// Create serverSocket for listenng
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd == -1)
		cerr << "Error: Socket init" << endl;

	istringstream(port) >> _port;

	memset(&_sin, 0, sizeof(_sin));
	_sin.ai_family = AF_INET;
	_sin.ai_socktype = SOCK_STREAM;
	_sin.ai_flags = AI_PASSIVE;

	// @TODO Vincent : port en dynamique
	if (getaddrinfo(NULL, port.c_str(), &_sin, &_res))
		cerr << "getaddrinfo error" << endl;

	fcntl(_sockfd, F_SETFL, O_NONBLOCK);

	// Loop through all possible addresses
	for (_p = _res; _p != NULL; _p = _p->ai_next) {
		_sockfd = socket(_p->ai_family, _p->ai_socktype, _p->ai_protocol);
		if (_sockfd < 0) continue;

		int opt = 1;
		setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		if (bind(_sockfd, _p->ai_addr, _p->ai_addrlen) == 0) {
			spdlog::info("Socket bound to port {}", port);
			break;
		}

		close(_sockfd);
		_sockfd = -1;
	}

	freeaddrinfo(_res);

	// Listen command
	if (listen(_sockfd, 5) == -1)
		cerr << "Error: Socket listen" << endl;

	// Epoll create instance
	_epfd = epoll_create1(0);
	if (_epfd == -1)
		cerr << "Error: Epoll create" << endl;

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = STDIN_FILENO;

	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1)
		cerr << "Error: Epoll ctl for quit" << endl;

	ev.data.fd = _sockfd;
	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, _sockfd, &ev))
		cerr << "Error: Epoll ctl for listen server" << endl;
}

void Server::run() {
	while(true) {
		int num_events = epoll_wait	(_epfd, _rev, 1028, -1);
		if (num_events > 0)
			for (int i = 0; i < num_events; ++i)
				handle_event(_rev[i]);
	}
}

void Server::sclose()
{
	for (std::map<int, Client>::iterator it = _clients.begin();
		it != _clients.end(); ++it)
	{
		int fd = it->second.getFd();
		if (fd >= 0) close(fd);
	}
	_clients.clear();

	if (_sockfd >= 0) close(_sockfd);
	if (_epfd >= 0) close(_epfd);

	spdlog::info("Server closed");
}

void Server::handle_event(struct epoll_event ev) {
	int fd = ev.data.fd;

	if (fd == _sockfd) {
		// Authentication
		addNewClient(fd);
	} else if (fd == STDIN_FILENO) {
		std::string line;
		std::getline(std::cin, line);
		if (line == "quit") {
			sclose();
			exit(0);
		}
	} else {
		std::map<int, Client>::iterator it = _clients.find(fd);
		if (it != _clients.end()) {
			Client& c = it->second;
			if (ev.events & EPOLLOUT) {
				handleWrite(c);
			}
			if (ev.events & EPOLLIN) {
				handleRead(c);
			}
		}
	}
}

void Server::addNewClient(int fd) {
	struct sockaddr_in peer_addr;
	socklen_t peer_addr_size = sizeof(peer_addr);

	int cfd = accept(fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
	spdlog::info("New client connected: FD {}", cfd);

	// @TODO : Verifier si on peut l'utiliser pour le client
	fcntl(cfd, F_SETFL, O_NONBLOCK);

	struct epoll_event nev;
	nev.events = EPOLLIN;
	nev.data.fd = cfd;
	epoll_ctl(_epfd, EPOLL_CTL_ADD, cfd, &nev);

	Client client(cfd);
	client.setEPollServerFd(_epfd);

	_clients.insert(std::make_pair(cfd, client));
}

void Server::handleWrite(Client& c)
{
	if (c.getWriteBuffer().empty())
	{
		c.disableWriteEvents();
		return;
	}

	ssize_t sent = send(c.getFd(),
						c.getWriteBuffer().c_str(),
						c.getWriteBuffer().size(),
						0);

	if (sent > 0)
	{
		spdlog::debug("Sent to client FD {} buffer '{}'", c.getFd(), c.getWriteBuffer());
		c.getWriteBuffer().erase(0, sent);

		if (c.getWriteBuffer().empty())
			c.disableWriteEvents();
	}
	// Gerer le cas de sent < 0
}

void Server::handleRead(Client& c)
{
	char buf[512];
	ssize_t n = recv(c.getFd(), buf, sizeof(buf), 0);

	if (n == 0)
	{
		// Le client a fermé la connexion
		close(c.getFd());
		return;
	}
	// Gerer le cas de n < 0

	c.getReadBuffer().append(buf, n);
	spdlog::debug("Received from client FD {} buffer '{}'", c.getFd(), c.getReadBuffer());

	size_t pos = c.getReadBuffer().find("\r\n") + 2;
	while (pos > 2) {
		string msg = c.getReadBuffer().substr(0, pos);
		struct Message parsedMessage;

		parserIRC.ast = parserIRC.parser.parse("<message>", msg, parserIRC.consumed);
		if (parserIRC.ast == 0) {
			spdlog::warn("Failed to parse message from client FD {}: '{}'", c.getFd(), msg);
		}
		else if (parserIRC.consumed > 0) {
			DataExtractor extractor;
			ExtractedData data = extractor.extract(parserIRC.ast);

			parsedMessage.prefix = data.first("<prefix>");
			parsedMessage.command = data.first("<command>");
			parsedMessage.params = data.all("<middle>");
			for (size_t i = 0; i < data.all("<trailing>").size(); i++)
				parsedMessage.params.push_back(data.all("<trailing>")[i]);

			delete parserIRC.ast;
		}
		c.getReadBuffer().erase(0, pos);
		CommandFactory cf;

		if (cf.getCommand(parsedMessage.command)) {
			spdlog::debug("Executing command '{}' from client FD {}", parsedMessage.command, c.getFd());
			cf.getCommand(parsedMessage.command)->execute(*this, c, parsedMessage);
		}

		if (c.getReadBuffer().empty())
			break;

		pos = c.getReadBuffer().find("\r\n") + 2;
	}
}

Channel* Server::getChannel(const string& chanName) {
	map<string, Channel>::iterator it;

	for (it = _channels.begin(); it != _channels.end(); ++it) {
		if (it->second.getName() == chanName)
			return &it->second;
	}
	return (NULL);
}


Channel* Server::addChannel(const string& chanName, Client* client) {
	map<string, Channel>::iterator it = _channels.find(chanName);
	if (it != _channels.end())
		return NULL;

	std::pair<std::map<std::string, Channel>::iterator, bool> res =
        _channels.insert(std::make_pair(chanName, Channel(chanName, client)));
	res.first->second.addOperator(client);
	spdlog::info("Channel {} created by client FD {}", chanName, client->getFd());

	return &(res.first->second);
}

void Server::removeChannel(const string& chanName) {
	map<string, Channel>::iterator it;

	for (it = _channels.begin(); it != _channels.end(); ++it) {
		if ((it->second).getName() == chanName)
			_channels.erase(chanName);
	}
	spdlog::info("Channel {} removed", chanName);
}

Client* Server::getClientByNickname(const string& nickname){
	map<int, Client>::iterator it;

	for (it = _clients.begin(); it != _clients.end(); ++it){
		if (it->second.getNickname() == nickname)
			return &it->second;
	}
	return (NULL);
}

string Server::getName() const {
	return _name;
}

Server& Server::setName(string name) {
	_name = name;
	return *this;
}