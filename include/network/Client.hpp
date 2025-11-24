#pragma once

#include "common.hpp"

class Client {
    private:
        string _username;
        string _nickname;
        string _realname;
        string _buffer;
        int _fd;
        int _ePollServerFd;
    public:
        Client();
        Client(int fd);

        // Getters / Setters
        string getUsername() const;
        string getNickname() const;
        string getRealname() const;
        string& getBuffer();
        int getFd() const;
        int getEPollServerFd() const;

        Client& setUsername(string username);
        Client& setNickname(string nickname);
        Client& setRealname(string realname);
        Client& setFd(int fd);
        Client& setEPollServerFd(int epsfd);

        void enableWriteEvents();
        void disableWriteEvents();
};