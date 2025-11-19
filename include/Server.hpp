#pragma once

#include <sys/epoll.h>
#include "common.hpp"

// @TODO : Fonctions generales a faire en pointeurs de fonctions pour les differences entre les clients

class Server {
    public:
        Server(const string& port, const string& password);
        
        void run();
        
        void close();
};