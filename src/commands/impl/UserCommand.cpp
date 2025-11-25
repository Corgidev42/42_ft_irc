#include "impl/UserCommand.hpp"
#include <iostream>

UserCommand::UserCommand(){};
UserCommand::~UserCommand(){};

void UserCommand::execute(Server& server, Client& client, const Message& message){
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());
    if (message.params.size() < 4){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NEEDMOREPARAMS, MakeVars(args)("command", "USER")));
        server.handleWrite(client);
        return ;
    }

    if (client.isRegistered()){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NICKNAMEINUSE, args));
        server.handleWrite(client);
        return ;
    }

    std::string username = message.params[0];
    std::string realname = message.params[3];

    client.setUsername(username);
    client.setRealname(realname);

    if (!client.getNickname().empty()){
        client.setRegistered(true);
        client.enqueueMessage(ircReplies.formatReply(
            RPL_WELCOME, MakeVars(args)("user", client.getUsername())("host", "localhost")));
        client.enqueueMessage(ircReplies.formatReply(
            RPL_YOURHOST, MakeVars(args)("version", "1.0")));
        server.handleWrite(client);
    }
}
