#include "NickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>

NickCommand::NickCommand(){};
NickCommand::~NickCommand(){};

void NickCommand::execute(Server& server, Client& client, const Message& messge){
    if (message.params.empty()){
        // client.reply(ERR_NONICKNAMEGIVEN);
        return ;
    }

    std::string nickname = message.params[0];

    // TODO : check si pseudo deja pris
    client.setNickname(nickname);
    // TODO : envoeyr un message au client pour lui dire : poto c'e'st bon ton nickname est valide.

    // debug
    std::cout << "client fd :" << client.getFd() << " nick set to : " << nickname << std::endl;
}
