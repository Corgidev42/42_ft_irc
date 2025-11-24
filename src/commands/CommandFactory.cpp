// #include "CommandFactory.hpp"
// #include <iostream>

// CommandFactory::CommandFactory(){
//     // _commands["JOIN"] = new JoinCommand();
//     _commands["NICK"] = new NickCommand();
//     _commands["USER"] = new UserCommand();
//     _commands["PING"] = new PingCommand();
//    //...
// }

// CommandFactory::~CommandFactory(){
//     std::map<std::string, ICommand*>::iterator it;
//     for (it = _commands.begin(); it != _commands.end(); it++){
//         delete it->second;
//     }

//     _commands.clear();
// }

// ICommand* CommandFactory::getCommand(const std::string& commandName){
//     std::string upperName = _toUpper(commandName);

//     std::map<std::string, ICommand*>::iterator it = _commands.find(upperName);

//     if (it != _commands.end())
//         return (it->second);

//     return (NULL);
// }

// std::string CommandFactory::_toUpper(const std::string& str){
//     std::string upper = str;
//     for (size_t i; i < upper.length() ; ++i)
//         upper[i] = std::toupper(upper[i]);
//     return (upper);
// }
