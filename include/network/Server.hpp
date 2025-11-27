#pragma once

#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <map>
#include "common.hpp"
#include "network/Client.hpp"
#include "Channel.hpp"

class Channel;

// @TODO : Fonctions generales a faire en pointeurs de fonctions pour les differences entre les clients

class Server {
    private:
        int _port;
        string _password;

        string _name;

        int _sockfd;
        int _epfd;
        struct addrinfo _sin, *_res, *_p;
        struct epoll_event _rev[1028];

        map<int, Client> _clients;
        map<string, Channel> _channels;

        void handle_event(struct epoll_event ev);
        void addNewClient(int fd);
    public:
        Server(const string& port, const string& password);

        void run();
        void sclose();
        Client* getClientByNickname(const string& nickname);

        void handleWrite(Client& c);
        void handleRead(Client& c);

        Channel* getChannel(const string& chanName);
        Channel* addChannel(const string& chanName, Client *client);
        void removeChannel(const string& chanName);

        string getName() const;
        Server& setName(string name);
};
