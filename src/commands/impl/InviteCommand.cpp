#include "impl/InviteCommand.hpp"
#include "network/Client.hpp"
#include "Channel.hpp"

InviteCommand::InviteCommand(){}
InviteCommand::~InviteCommand(){}

void InviteCommand::execute(Server& server, Client& client, const Message& message){
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());

    if (message.params.empty()){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NEEDMOREPARAMS, MakeVars(args)("command", "INVITE")));
        server.handleWrite(client);
        return ;
    }

    std::string targetNick = message.params[0];
    std::string chanName = message.params[1];

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

    if (channel->hasMode('i') && !channel->isOperator(&client)){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_CHANOPRIVSNEEDED, MakeVars(args)("channel", chanName)));
        server.handleWrite(client);
        return ;
    }

    Client* target = server.getClientByNickname(targetNick);
    if (!target){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NOSUCHNICK, MakeVars(args)("target", target->getNickname())));
        server.handleWrite(client);
        return ;
    }

    if (channel->hasClient(target)){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_USERONCHANNEL, MakeVars(args)("target", target->getNickname())("channel", chanName)));
        server.handleWrite(client);
        return ;
    }

    channel->addInvited(target);

    client.enqueueMessage(ircReplies.formatReply(
        RPL_INVITING, MakeVars(args)("target", target->getNickname())("channel", chanName)));
    server.handleWrite(client);
}
