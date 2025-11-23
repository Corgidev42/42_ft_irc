#include "Server.hpp"
#include <sstream>

Server::Server(const string& port, const string& password) : _password(password) {
	// Create serverSocket for listenng
	//_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//if (_sockfd == -1)
	//   cerr << "Error: Socket init" << endl;

	istringstream(port) >> _port;

	memset(&_sin, 0, sizeof(_sin));
	_sin.ai_family = AF_INET;
	_sin.ai_socktype = SOCK_STREAM;
	_sin.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, "6667", &_sin, &_res))
		cerr << "getaddrinfo error" << endl;

	fcntl(_sockfd, F_SETFL, O_NONBLOCK);

	_sockfd = -1;

	// Loop through all possible addresses
	for (_p = _res; _p != NULL; _p = _p->ai_next) {
		_sockfd = socket(_p->ai_family, _p->ai_socktype, _p->ai_protocol);
		if (_sockfd < 0) continue;

		int opt = 1;
		setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		if (bind(_sockfd, _p->ai_addr, _p->ai_addrlen) == 0) {
			cout << "Bind success!\n";
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
		int num_events = epoll_wait(_epfd, _rev, 1028, -1);
		if (num_events > 0)
			for (int i = 0; i < num_events; ++i)
				handle_event(_rev[i]);
	}
}

void Server::sclose() {
	close(_sockfd);
}

int cfd;
char buf[1028];

void Server::handle_event(struct epoll_event ev) {
	int fd = ev.data.fd;

    if (fd == _sockfd) {
        // Authentication
        addNewClient(fd);
    } else if (fd == STDIN_FILENO) {
        // If "quit" close server
    } else if (ev.events & EPOLLIN) {

        int nbr = read(fd, &buf, sizeof(buf));
        if (nbr > 0) {
            cout << buf << endl;
        }

        string nick = "ezeppa";
        string welcome =
            ":myserver 001 " + nick + " :Welcome to my IRC server\r\n";
            // ":myserver 002 " + nick + " :Your host is myserver\r\n";

        send(fd, welcome.c_str(), welcome.size(), 0);

        // Set a Nickname
        // Set an Username
        // Join a Channel

		// Set a Nickname
		// Set an Username
		// Join a Channel

		// Send/Received a message (client<->client and client<->channel)

		// Kick command
		// Invite command
		// Topic command
		// Mode command (i, t, k, o, l)
	}
}

void Server::addNewClient(int fd) {
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(peer_addr);

    cfd = accept(fd, (struct sockaddr *)&peer_addr, &peer_addr_size);

    struct epoll_event nev;
    nev.events = EPOLLIN;
    nev.data.fd = cfd;
    epoll_ctl(_epfd, EPOLL_CTL_ADD, cfd, &nev);

	std::map<int, Client>::value_type pair(cfd, Client(cfd));
	_clients.insert(pair);	
}
