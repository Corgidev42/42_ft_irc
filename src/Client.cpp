#include "Client.hpp"

Client::Client() : _fd(-1) {
    cout << "test0" << endl;

}

Client::Client(int fd) : _fd(fd) {
    cout << "test" << endl;
}

string Client::getUsername() const {
    return _username;
}

string Client::getNickname() const {
    return _username;
}

string Client::getRealname() const {
    return _realname;
}

string Client::getBuffer() const {
    return _buffer;
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

Client& Client::setRealname(string realname) {
    _realname = realname;
    return *this;
}

Client& Client::setBuffer(string buffer) {
    _buffer = buffer;
    return *this;
}

Client& Client::setFd(int fd) {
    _fd = fd;
    return *this;
}