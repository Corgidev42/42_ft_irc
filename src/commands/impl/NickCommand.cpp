#include "NickCommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>

NickCommand::NickCommand(){};
NickCommand::~NickCommand(){};

static bool isNicknameValid(const std::string& nick){
  if (nick.empty() || nick.size() > 9)
    return (false);
  if (isdigit(nick[0]))
    return (false);

  std::string special = "[]\\`_^{|}";
  for (size_t i = 0; i < nick.size(); i++){
    if (!isalnum(nick[i]) && special.find(nick[i]) == std::string::npos)
      return (false);
  }
  return (true);
}



void NickCommand::execute(Server& server, Client& client, const Message& messge){
    if (message.params.empty()){
        client.reply(ERR_NONICKNAMEGIVEN);
        return ;
    }

    std::string newNick = message.params[0];
    if (!isNicknameValid(newNick)){
      client.reply(ERR_ERRONEUSNICKNAME)
      return ;
    }

    if (server.getClientByNickname(newNick)){
      std::string currentNick = client.getNickname();
      if (currentNick.empty())
        currentNick = "*";

      client.reply();
      return;
    }

    std::string oldNick = client.getNickname();
    client.setNickname(newNick);

    if (client.isRegistered()) {
        // std::string oldPrefix = oldNick + "!" + client.getUsername() + "@" + client.getHostname();
        // std::string msg = ":" + oldPrefix + " NICK :" + newNick;
        // client.reply(msg);

        // map<string, string>args;
        // args["nick"] = oldNick;
        // args["newnick"] = newNick;

        // enqueueMessage(client, CMD_NICK, args);

        client.addMessage(CMD_NICK(oldNick, newNick));


    }

}
