#include "impl/PrivMsgCommand.hpp"
#include "network/Client.hpp"
#include "Channel.hpp"

PrivMsgCommand::PrivMsgCommand(){}
PrivMsgCommand::~PrivMsgCommand(){}

void PrivMsgCommand::execute(Server& server, Client& client, const Message& message){
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());

    if (message.params.empty()){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NORECIPIENT, MakeVars(args)));
        server.handleWrite(client);
        return ;
    }

    if (message.params.size() != 2){
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NOTEXTTOSEND, MakeVars(args)));
        server.handleWrite(client);
        return ;
    }

    // @TODO : faire la decoupe sur ','
    std::string receiverNames = message.params[0];
    std::string msg = message.params[1] + "\r\n";

    Channel* targetChannel = server.getChannel(receiverNames);
    Client* targetClient = server.getClientByNickname(receiverNames);

    if (!targetClient && !targetChannel) {
        client.enqueueMessage(ircReplies.formatReply(
            ERR_CANNOTSENDTOCHAN, MakeVars(args)("channel", receiverNames)));
        server.handleWrite(client);
        return ;
    }

    // @TODO Check si mask doivent etre pris en compte 'ERR_NOTOPLEVEL' 'ERR_WILDTOPLEVEL'

    // @TODO Apres decoupe des recipients checker les spams 'ERR_TOOMANYTARGETS'

    // @TODO Gerer le cas de 'ERR_NOSUCHNICK' car confusion avec receivers

    // @TODO 'RPL_AWAY'

    targetChannel->broadcastExcept(msg, server, &client);
    server.handleWrite(client);
}
