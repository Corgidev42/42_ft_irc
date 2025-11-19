#include "Server.hpp"

Server::Server(const string& port, const string& password) : _port(stoi(port)), _password(password) {
    // Create serverSocket for listenng
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1)
        cerr << "Error: Socket init" << endl;

    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(_port);
    _sin.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind to port
    if (bind(_sockfd, (struct sockaddr *)&_sin, sizeof(struct sockaddr)) == -1)
        cerr << "Error: Socket bind" << endl;

    // Listen command
    if (listen(_sockfd, 5) == -1)
        cerr << "Error: Socket listen" << endl;

    // Epoll create instance
    _epfd = epoll_create1(0);
    if (_epfd == -1)
        cerr << "Error: Epoll create" << endl;
    
    _ev.events = EPOLLIN;
    _ev.data.fd = STDIN_FILENO;

    if (epoll_ctl(_epfd, EPOLL_CTL_ADD, STDIN_FILENO, &_ev) == -1)
        cerr << "Error: Epoll ctl for quit" << endl;

    _ev.data.fd = _sockfd;
    if (epoll_ctl(_epfd, EPOLL_CTL_ADD, _sockfd, &_ev))
        cerr << "Error: Epoll ctl for listen server" << endl;
}

void Server::run() {
    // while(true) {
        // if (epoll_wait() > 0) {
            // Authentication
            // Set a Nickname
            // Set an Username
            // Join a Channel

            // Send/Received a message (client<->client and client<->channel)

            // Kick command
            // Invite command
            // Topic command
            // Mode command (i, t, k, o, l)
        // }
    // }
}

void Server::sclose() {
    close(_sockfd);
}
