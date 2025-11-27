#include "impl/PingCommand.hpp"

PingCommand::PingCommand(){};
PingCommand::~PingCommand(){};

void PingCommand::execute(Server& server, Client& client, const Message& message){
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());
    if (message.params.empty()){
        // client.enqueueMessage(ERR_NOORIGIN);
        return ;
    }

    std::string token = message.params[0];
    std::string pong = "PONG :" + token + "\r\n";

    client.enqueueMessage(pong);
    server.handleWrite(client);
}
