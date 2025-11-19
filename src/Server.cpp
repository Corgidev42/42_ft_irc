#include "Server.hpp"

Server::Server(const string& port, const string& password) : _port(stoi(port)), _password(password) {
    // Create serverSocket for listenng
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1)
        cerr << "Error: Socket init" << endl;

    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(_port);
    _sin.sin_addr.s_addr = htonl(INADDR_ANY);

    fcntl(_sockfd, F_SETFL, O_NONBLOCK);

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
        if (num_events > 0) {
            for (int i = 0; i < num_events; ++i)
            {
                handle_event(_rev[i]);
            }
        }
    }
}

void Server::sclose() {
    close(_sockfd);
}

void Server::handle_event(struct epoll_event ev) {
    int fd = ev.data.fd;

    if (fd == _sockfd) {
        // Authentication
        // Set a Nickname
        // Set an Username
    } else if (ev.events & EPOLLIN) {
        // Join a Channel

        // Send/Received a message (client<->client and client<->channel)

        // Kick command
        // Invite command
        // Topic command
        // Mode command (i, t, k, o, l)
    }
}

