#pragma once

#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "common.hpp"


// @TODO : Fonctions generales a faire en pointeurs de fonctions pour les differences entre les clients

class Server {
    private:
        int _port;
        string _password;

        int _sockfd;
        int _epfd;
        struct sockaddr_in _sin;
        struct epoll_event _ev, rev[1028];
    public:
        Server(const string& port, const string& password);
        
        void run();
        
        void sclose();
};