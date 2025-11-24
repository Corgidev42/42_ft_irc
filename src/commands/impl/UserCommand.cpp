#include "UserCommand.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

UserCommand::UserCommand(){};
UserCommand::~UserCommand(){};

void UserCommand::execute(Server& server, Client& client, const Message& message){
    if (message.params.size() < 4){
        // client.reply(ERR_NEEDMOREPARAMS)
        return ;
    }

    if (client.isRegistered()){
        // client.reply(ERR_ALREADYREGISTRED)
        return ;
    }

    std::string username = message.params[0];
    std::string realname = message.params[3];

    client.setUsername(username);
    client.setRealName(realname);

    if (!client.getNickname().empty()){
        client.setRegistered(true);
        client.reply("001" + client.getNickname() + " :Welcome to the FT_IRC Network");
        std::cout << "Client " << client.getFd() << "is now fully registered!" << std::endl;
    }
}
