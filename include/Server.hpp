#pragma once

#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include "common.hpp"


// @TODO : Fonctions generales a faire en pointeurs de fonctions pour les differences entre les clients

class Server {
    private:
        int _port;
        string _password;

        int _sockfd;
        int _epfd;
        struct addrinfo _sin, *_res, *_p;
        struct epoll_event _rev[1028];

        void handle_event(struct epoll_event ev);
    public:
        Server(const string& port, const string& password);
        
        void run();
        void sclose();

};