#include "network/Client.hpp"

Client::Client() : _fd(-1) {}

Client::Client(int fd) : _fd(fd) {}

string Client::getUsername() const {
    return _username;
}

string Client::getNickname() const {
    return _username;
}

string Client::getRealname() const {
    return _realname;
}

string& Client::getReadBuffer() {
    return _readBuffer;
}

string& Client::getWriteBuffer() {
    return _writeBuffer;
}

int Client::getFd() const {
    return _fd;
}

int Client::getEPollServerFd() const {
    return _ePollServerFd;
}

bool Client::isRegistered() const {
    return _isRegistered;
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

Client& Client::setFd(int fd) {
    _fd = fd;
    return *this;
}

Client& Client::setEPollServerFd(int ePollServerFd) {
    _ePollServerFd = ePollServerFd;
    return *this;
}

void Client::setRegistered(bool status){
    _isRegistered = status;
}

void Client::enableWriteEvents() {
    epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT;
    ev.data.ptr = this;

    epoll_ctl(_ePollServerFd, EPOLL_CTL_MOD, _fd, &ev);
}

void Client::disableWriteEvents() {
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.ptr = this;

    epoll_ctl(_ePollServerFd, EPOLL_CTL_MOD, _fd, &ev);
}

void Client::enqueueMessage(const std::string& message){
    getWriteBuffer() += message;
    cout << "enqueueMessage : " << getWriteBuffer() << endl;
    enableWriteEvents();
}
