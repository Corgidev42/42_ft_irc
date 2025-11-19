#include "Server.hpp"

Server::Server(const string& port, const string& password) {
    // Create serverSocket

    // Bind to port

    // Listen command

    // Epoll create instance
}

void Server::run() {
    while(true) {
        if (epoll_wait() > 0) {
            // Authentication
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
}

void Server::close() {
    close(_fd);
}
