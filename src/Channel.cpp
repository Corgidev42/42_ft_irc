#include "../include/Channel.hpp"


Channel::Channel(const std::string& name, Client* creator){
    _name = name;

}
Channel::~Channel();

string Channel::getName(){
    return (_name);
}

string Channel::getTopic(){
    return (_topic);
}

string Channel::getKey(){
    return (_key);
}

size_t Channel::getLimit(){
    return (_limit);
}

size_t Channel::getUserCount(){
    return (_clients.size());
}

string Channel::getModeStr() const {
    string modes = "+";
    if (_isInvitedOnly)
        modes += "i";
    if (_isTopicRestricted)
        modes += "t';
    if (_isKeyMode)
        modes += "k";
    if (_isLimitMode)
        modes += "l";
    return (modes);
}

void Channel::setTopic(const string& topic){
    _topic = topic;
}

void Channel::setKey(const string& key){
    _key = key;
}

void Channel::setLimit(size_t limit){
    _limit = limit;
}

void Channel::setMode(char mode, bool active){
    switch (mode):
        case 'i' : _isInvitedOnly = active; break;
        case 't' : _isTopicRestricted = active; break;
        case 'k' : _isKeyMode = active; break;
        case 'l' : _isLimitMode = active; break;
}

bool Channel::hasMode(char mode) const{
    switch(mode):
        case 'i' : return (_isInvitedOnly);
        case 't' : return (_isTopicRestricted);
        case 'k' : return (_isKeyMode);
        case 'l' : return (_isLimitMode);
}

void Channel::addClient(Client* client){
    if (!hasClient(client)){
        _clients.insert(std::make_pair(client->getNickname(), client));
    }
}

void Channel::removeClient(Client* client){
    if (hasClient(client)){
        _clients.erase(std::make_pair(client->getNickname(), client));
    }
}

bool Channel::hasClient(Client* client){
    for (std::map<std::string, Client*>::iterator it = _clients.begin() ; it != _clients.end() ; ++it){
        if (it == client)
            return (true);
        else {
            return (false);
        }
    }
}

Client* Channel::getClientByNick(const string& msg){
    std::map<std::string, Client*>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it){
        if((*it)->getNickname() == nick)
            return (*it);
    }
    return (NULL);
}

void Channel::addOperator(Client* client){
    if (!isOperator(client)){
        _operators.pushback(client);
    }
}

void Channel::removeOperator(Client* client){
    if (isOperator(client)){
        _operators.erase(client);
    }
}

bool Channel::isOperator(Client* client){
    std::vector<Client*>::iterator it;
    for(it = _operators.begin(); it != _operators.end(); ++it){
        if (it == client)
            return (true);
        else
            return (false);
    }
}

void Channel::addInvited(Client* client){
    if (!isInvited(client)){
        _invited.pushback(client);
    }
}

void Channel::removeInvited(Client* client){
    if (isInvited(client)){
        _invited.erase(client);
    }
}

bool Channel::isInvited(Client* client){
    std::vector<Client*>::iterator it;
    for (it = _invited.begin(); it != _invited.end() ; ++it){
        if (it == client)
            return (true);
        else
            return (false);
    }
}

void Channel::broadcast(const string& msg){
    std::map<std::string, Client*>::iterator it;

    for (it = _clients.begin(); it != _clients.end() ; ++it)
        it->second->reply(msg);
}
