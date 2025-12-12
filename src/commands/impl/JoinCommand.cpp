#include "impl/JoinCommand.hpp"

JoinCommand::JoinCommand(){}
JoinCommand::~JoinCommand(){}

void JoinCommand::execute(Server& server, Client& client, const Message& message){
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());

    if (message.params.empty()){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NEEDMOREPARAMS, MakeVars(args)("command", "JOIN")));
        server.handleWrite(client);
        return ;
    }

    // @TODO Checker le nom '#'
    std::string chanName = message.params[0];
    string key;
    if (message.params.size() > 1)
        key = message.params[1];
    else
        key = "";

    if (chanName[0] != '#'){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NOSUCHCHANNEL, MakeVars(args)("channel", chanName)));
        server.handleWrite(client);
        return ;
    }

    // TODO : faire une methode getChannel
    Channel* channel = server.getChannel(chanName);

    // cas 1 : on creer si ca existe pas :
    if (!channel){
        //TODO : faireu ne methode createChannel
        channel = server.addChannel(chanName, &client);
    }
    // cas 2 : le channel existe :
    else {
        if (channel->hasClient(&client))
            return ; //client deja dedans)

        if (channel->hasMode('i') && !channel->isInvited(&client)){
            client.enqueueMessage(ircReplies.formatReply(
                ERR_INVITEONLYCHAN, MakeVars(args)("channel", chanName)));
            server.handleWrite(client);
            return ;
        }

        if (channel->hasMode('k') && channel->getKey() != key){
            client.enqueueMessage(ircReplies.formatReply(
                ERR_BADCHANNELKEY, MakeVars(args)("channel", chanName)));
            server.handleWrite(client);
            return ;
        }

        if (channel->hasMode('l') && channel->getUserCount() >= channel->getLimit()){
            client.enqueueMessage(ircReplies.formatReply(
                ERR_CHANNELISFULL, MakeVars(args)("channel", chanName)));
            server.handleWrite(client);
            return ;
        }

        channel->addClient(&client);
    }

    // Succes : broadcast join a tous le monde
    std::string joinMsg = ":" + client.getNickname() + " Join: " + chanName;
    channel->broadcast(joinMsg, server);

    if (!channel->getTopic().empty()) {
        client.enqueueMessage(ircReplies.formatReply(
            RPL_TOPIC, MakeVars(args)("channel", chanName)("topic", channel->getTopic())));
    }

    std::string names = channel->buildNamesList();
    // @TODO: Ajouter les modes de visibilite (si on veut)
    std::string symbol = "=";

    client.enqueueMessage(ircReplies.formatReply(
        RPL_NAMREPLY, MakeVars(args)("symbol", symbol)("channel", chanName)("names", names)));

    client.enqueueMessage(ircReplies.formatReply(
        RPL_ENDOFNAMES, MakeVars(args)("channel", chanName)));

    server.handleWrite(client);
}
