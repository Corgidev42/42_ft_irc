#include "impl/NickCommand.hpp"
#include <iostream>

NickCommand::NickCommand(){};
NickCommand::~NickCommand(){};

static bool isNicknameValid(const std::string& nick){
	if (nick.empty() || nick.size() > 9)
		return (false);
	if (isdigit(nick[0]))
		return (false);

	cout << "'" << nick << "'" << endl;

	std::string special = "[]\\`_^{|}";
	for (size_t i = 0; i < nick.size(); i++){
		if (!isalnum(nick[i]) && special.find(nick[i]) == std::string::npos)
			return (false);
	}
	return (true);
}

void NickCommand::execute(Server& server, Client& client, const Message& message){
	std::map<string, string> args = MakeVars()("server", server.getName());

	if (message.params.empty()){
		client.enqueueMessage(ircReplies.formatReply(
			ERR_NONICKNAMEGIVEN, args));
		server.handleWrite(client);
		return ;
	}

	std::string newNick = message.params[0];
	if (!isNicknameValid(newNick)){
		client.enqueueMessage(ircReplies.formatReply(
			ERR_ERRONEUSNICKNAME, MakeVars(args)("nick", newNick)("target", newNick)));
		server.handleWrite(client);
		return ;
	}

	if (server.getClientByNickname(newNick)){
		std::string currentNick = client.getNickname();
		if (currentNick.empty()) {
			currentNick = "*";

			cout << "NEW NICK " << newNick << endl;
			client.enqueueMessage(ircReplies.formatReply(
				ERR_NICKNAMEINUSE, MakeVars(args)("nick", currentNick)("target", newNick)));
			server.handleWrite(client);
			return;
		}
	}

	std::string oldNick = client.getNickname();
	client.setNickname(newNick);
	cout << "New Nickname : " << client.getNickname() << endl;

	if (client.isRegistered()) {
		// @TODO : host en dynamique
		std::string reply = ":" + oldNick + "!" + client.getUsername() + "@" + "localhost" +
                    " NICK :" + newNick + "\r\n";
		client.enqueueMessage(reply);
		server.handleWrite(client);
	}
}
