#include "InviteCommand.hpp"

InviteCommand::InviteCommand(){}
InviteCommand::~InviteCommand(){}

void execute(Server& server, Client& client, const Message& message){
    if (message.params.empty()){
        client.reply(ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string targetNick = message.params[0];
    std::string chanName = message.params[1];

    Channel* channel = server.getChannel(chanName);
    if (!channel){
        client.reply(ERR_NOSUCHCHANNEL);
        return ;
    }

    if (!channel->hasClient(&client)){
        client.reply(ERR_NOTONCHANNEL);
        return ;
    }

    if (channel->hasMode('i') && !channel->isOperator(&client)){
        client.reply(ERR_CHANOPRIVSNEEDED);
        return ;
    }

    Client* target = server.getClientByNick(targetNick);
    if (!target){
        client.reply(ERR_NOSUCHNICK);
        return ;
    }

    if (channel->hasClient(target)){
        client.reply(ERR_USERONCHANNEL);
        return ;
    }

    channel->addInvited(target);

    client.reply(RPL_INVITING);

    target->reply(":" + client.getPrefix() + " INVITE " + targetNick + " :" + chanName);
}
