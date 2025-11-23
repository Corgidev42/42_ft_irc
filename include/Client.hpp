#pragma once

#include "common.hpp"

class Client {
    private:
        string _username;
        string _nickname;
        string _realname;
        string _buffer;
        int _fd;
    public:
        Client();
        Client(int fd);

        // Getters / Setters
        string getUsername() const;
        string getNickname() const;
        string getRealname() const;
        string getBuffer() const;
        int getFd() const;

        Client& setUsername(string username);
        Client& setNickname(string nickname);
        Client& setRealname(string realname);
        Client& setBuffer(string buffer);
        Client& setFd(int fd);
};