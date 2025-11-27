#include "impl/TopicCommand.hpp"

TopicCommand::TopicCommand(){}
TopicCommand::~TopicCommand(){}

void TopicCommand::execute(Server& server, Client& client, const Message& message) {
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());

    if (message.params.empty()){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NEEDMOREPARAMS, MakeVars(args)("command", "TOPIC")));
        server.handleWrite(client);
        return ;
    }

    std::string chanName = message.params[0];
    Channel* channel = server.getChannel(chanName);

    if (!channel){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NOSUCHCHANNEL, MakeVars(args)("channel", chanName)));
        server.handleWrite(client);
        return ;
    }

    if (!channel->hasClient(&client)){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NOTONCHANNEL, MakeVars(args)("channel", chanName)));
        server.handleWrite(client);
        return ;
    }

    // cas 1 : voir le topic (pas de 2eme arg)
    if (message.params.size() == 1){
        if (channel->getTopic().empty()) {
            client.enqueueMessage(ircReplies.formatReply(
                RPL_NOTOPIC, MakeVars(args)("channel", chanName)));
            server.handleWrite(client);
        }
        else {
            client.enqueueMessage(ircReplies.formatReply(
                RPL_TOPIC, MakeVars(args)("channel", chanName)("topic", channel->getTopic())));
            server.handleWrite(client);
        }
        return ;
    }

    //cas 2 : changer le topic :
    // check du mode t : topic proteger par les utilisateurs :
    if (channel->hasMode('t') && !channel->isOperator(&client)){
            client.enqueueMessage(ircReplies.formatReply(
                ERR_CHANOPRIVSNEEDED, MakeVars(args)("channel", chanName)));
            server.handleWrite(client);
        return ;
    }

    std::string newTopic = message.params[1];
    channel->setTopic(newTopic);

    std::string msg = ":" + client.getNickname() + " TOPIC " + chanName + " :" + newTopic + "\r\n";
    // notif a tous le channel
    channel->broadcast(msg, server);
}
