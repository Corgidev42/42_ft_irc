#include "Channel.hpp"

Channel::Channel(const std::string& name, Client* client) {
    _name = name;
    addOperator(client);
}

Channel::~Channel() {}

string Channel::getName() const {
    return (_name);
}

string Channel::getTopic() const {
    return (_topic);
}

string Channel::getKey() const {
    return (_key);
}

size_t Channel::getLimit() const {
    return (_limit);
}

size_t Channel::getUserCount() const {
    return (_clients.size());
}

string Channel::getModeStr() const {
    string modes = "+";
    if (_isInviteOnly)
        modes += "i";
    if (_isTopicRestricted)
        modes += "t";
    if (_isKeyMode)
        modes += "k";
    if (_isLimitMode)
        modes += "l";
    return (modes);
}

Channel& Channel::setTopic(const string& topic){
    _topic = topic;
    return *this;
}

Channel& Channel::setKey(const string& key){
    _key = key;
    return *this;
}

Channel& Channel::setLimit(size_t limit){
    _limit = limit;
    return *this;
}

Channel& Channel::setMode(char mode, bool active){
    switch (mode) {
        case 'i' : _isInviteOnly = active; break;
        case 't' : _isTopicRestricted = active; break;
        case 'k' : _isKeyMode = active; break;
        case 'l' : _isLimitMode = active; break;
    }
    return *this;
}

bool Channel::hasMode(char mode) const{
    switch(mode) {
        case 'i' : return (_isInviteOnly);
        case 't' : return (_isTopicRestricted);
        case 'k' : return (_isKeyMode);
        case 'l' : return (_isLimitMode);
    }
    return 0;
}

void Channel::addClient(Client* client){
    if (!hasClient(client)){
        _clients.insert(std::make_pair(client->getNickname(), client));
    }
}

void Channel::removeClient(Client* client){
    if (hasClient(client)){
        _clients.erase(client->getNickname());
    }
}

bool Channel::hasClient(Client* client){
    std::map<std::string, Client*>::iterator it;

    for (it = _clients.begin() ; it != _clients.end() ; ++it)
        if (it->second == client) return (true);
    return (false);
}

Client* Channel::getClientByNick(const string& nick){
    std::map<std::string, Client*>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it){
        if((it->second)->getNickname() == nick)
            return (it->second);
    }
    return (NULL);
}

void Channel::addOperator(Client* client){
    if (!isOperator(client)){
        _operators.push_back(client);
    }
}

void Channel::removeOperator(Client* client){
    if (!isOperator(client)) return;

    std::vector<Client*>::iterator it;
    for (it = _operators.begin(); it != _operators.end(); ++it) {
        if (*it == client) {
            _operators.erase(it);
            return;
        }
    }
}

bool Channel::isOperator(Client* client){
    std::vector<Client*>::iterator it;
    for(it = _operators.begin(); it != _operators.end(); ++it)
        if (*it == client) return (true);
    return (false);
}

void Channel::addInvited(Client* client){
    if (!isInvited(client)){
        _invited.push_back(client);
    }
}

void Channel::removeInvited(Client* client){
    if (!isInvited(client)) return;

    std::vector<Client*>::iterator it;
    for (it = _invited.begin(); it != _invited.end(); ++it) {
        if (*it == client) {
            _invited.erase(it);
            return;
        }
    }
}

bool Channel::isInvited(Client* client){
    std::vector<Client*>::iterator it;
    for (it = _invited.begin(); it != _invited.end() ; ++it)
        if (*it == client) return (true);
    return (false);
}

void Channel::broadcast(const string& msg, Server& server){
    std::map<std::string, Client*>::iterator it;

    for (it = _clients.begin(); it != _clients.end() ; ++it) {
        Client* cli = it->second;

        cli->enqueueMessage(msg);
        server.handleWrite(*cli);
    }
}

void Channel::broadcastExcept(const string& msg, Server& server, Client* sender) {
    std::map<std::string, Client*>::iterator it;

    for (it = _clients.begin(); it != _clients.end() ; ++it) {
        Client* cli = it->second;

        if (cli != sender) {
            cli->enqueueMessage(msg);
            server.handleWrite(*cli);
        }
    }
}

string Channel::buildNamesList() {
    string names;
    std::map<std::string, Client*>::iterator it;

    for (it = _clients.begin(); it != _clients.end() ; ++it) {
        Client* cli = it->second;
        
        if (isOperator(cli))
            names += "@";
        
        names += cli->getNickname();
        
        std::map<std::string, Client*>::iterator next = it;
        ++next;
        if (next != _clients.end())
            names += " ";
    }
    return names;
}
