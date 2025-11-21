#pragma once

#include "common.hpp"

class Client {
    private:
        string _username;
        string _nickname;
        string _realname;
        int _fd;
    public:
        Client(int fd);

        // Getters / Setters
        string getUsername() const;
        string getNickname() const;
        string getRealname() const;
        int getFd() const;

        Client& setUsername(string username);
        Client& setNickname(string nickname);
        Client& setRealname(string realname);
        Client& setFd(int fd);
};