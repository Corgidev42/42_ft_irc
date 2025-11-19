#include "Client.hpp"

Client::Client(int fd) : _fd(fd) {}


string Client::getUsername() const {
    return _username;
}

string Client::getNickname() const {
    return _username;
}

int Client::getFd() const {
    return _fd;
}

Client& Client::setUsername(string username) {
    _username = username;
    return *this;
}

Client& Client::setNickname(string nickname) {
    _nickname = nickname;
    return *this;
}

Client& Client::setFd(int fd) {
    _fd = fd;
    return *this;
}