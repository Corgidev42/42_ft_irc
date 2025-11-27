#include "impl/KickCommand.hpp"

KickCommand::KickCommand(){}
KickCommand::~KickCommand(){}

void KickCommand::execute(Server& server, Client& client, const Message& message){
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());
    
    if (message.params.empty()){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NEEDMOREPARAMS, MakeVars(args)("command", "KICK")));
        server.handleWrite(client);
        return ;
    }

    std::string chanName = message.params[0];
    std::string targetNick = message.params[1];
    std::string comment;
    if (message.params.size() > 2)
        comment = message.params[2];
    else
        comment = "Kicked";

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

    if (!channel->isOperator(&client)){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_CHANOPRIVSNEEDED, MakeVars(args)("channel", chanName)));
        server.handleWrite(client);
        return ;
    }

    Client* target = channel->getClientByNick(targetNick);
    if (!target){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_USERNOTINCHANNEL, MakeVars(args)("target", target->getNickname())("channel", chanName)));
        server.handleWrite(client);
        return ;
    }

    std::string kickMsg = ":" + client.getNickname() + " KICK " + chanName + " " + targetNick + " :" + comment + "\r\n";
    channel->broadcast(kickMsg, server);

    channel->removeClient(target);
}
