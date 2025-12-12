#include "CommandFactory.hpp"
#include <iostream>

CommandFactory::CommandFactory(){
    _commands["CAP"] = new CapCommand();
    _commands["INVITE"] = new InviteCommand();
    _commands["JOIN"] = new JoinCommand();
    _commands["KICK"] = new KickCommand();
    _commands["MODE"] = new ModeCommand();
    _commands["NICK"] = new NickCommand();
    _commands["PING"] = new PingCommand();
    _commands["PRIVMSG"] = new PrivMsgCommand();
    _commands["TOPIC"] = new TopicCommand();
    _commands["USER"] = new UserCommand();
    _commands["WHO"] = new WhoCommand();
}

CommandFactory::~CommandFactory(){
    std::map<std::string, ICommand*>::iterator it;
    for (it = _commands.begin(); it != _commands.end(); it++){
        delete it->second;
    }

    _commands.clear();
}

ICommand* CommandFactory::getCommand(const std::string& commandName){
    std::string upperName = _toUpper(commandName);

    std::map<std::string, ICommand*>::iterator it = _commands.find(upperName);

    if (it != _commands.end())
        return (it->second);

    return (NULL);
}

std::string CommandFactory::_toUpper(const std::string& str){
    std::string upper = str;
    for (size_t i = 0; i < upper.length() ; ++i)
        upper[i] = std::toupper(upper[i]);
    return (upper);
}
