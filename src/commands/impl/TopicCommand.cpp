#include "TopicCommand.hpp"

TopicCommand::TopicCommand(){}
TopicCommand::~TopicCommand(){}

void TopicCommand::execute(Server& server, Client& client, const Message& message){
    if (message.params.empty()){
        client.reply(ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string chanName = message.params[0];
    Channel* channel = server.getChannel(chanName);

    if (!channel){
        client.reply(ERR_NOSUCHCHANNEL);
        return ;
    }

    if (!channel->hasClient(&client)){
        client.reply(ERR_NOTONCHANNEL);
        return ;
    }

    // cas 1 : voir le topic (pas de 2eme arg)
    if (message.params.size() == 1){
        if (channel.getTopic().empty())
            client.reply(RPL_NOTOPIC);
        else {
            client.reply(RPL_TOPIC);
        return ;
    }

    //cas 2 : changer le topic :
    // check du mode t : topic proteger par les utilisateurs :
    if (channel->hasMode('t') && !channel->isOperator(&client)){
        client.reply(ERR_CHANOPRIVSNEEDED);
        return ;
    }

    std::string newTopic = message.params[1];
    channel->setTopic(newTopic);

    // notif a tous le channel
    channel->broadcast(":" + client.getPrefix() + " TOPIC " + chanName + " :" + newTopic);
}
