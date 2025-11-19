#pragma once

#include "common.hpp"

class Client {
    private:
        string _username;
        string _nickname;
        int _fd;
    public:
        Client(int fd);

        // Getters / Setters
        string getUsername() const;
        string getNickname() const;
        int getFd() const;

        Client& setUsername(string username);
        Client& setNickname(string nickname);
        Client& setFd(int fd);
};