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
	std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());

	if (message.params.empty()){
		client.enqueueMessage(ircReplies.formatReply(
			ERR_NONICKNAMEGIVEN, args));
		return ;
	}

	std::string newNick = message.params[0];
	if (!isNicknameValid(newNick)){
		client.enqueueMessage(ircReplies.formatReply(
			ERR_ERRONEUSNICKNAME, MakeVars(args)("target", newNick)));
		return ;
	}

	if (server.getClientByNickname(newNick)){
		std::string currentNick = client.getNickname();
		if (currentNick.empty()) {
			currentNick = "*";

			cout << "NEW NICK " << newNick << endl;
			client.enqueueMessage(ircReplies.formatReply(
				ERR_NICKNAMEINUSE, MakeVars(args)("target", newNick)));
			return;
		}
	}

	std::string oldNick = client.getNickname();
	client.setNickname(newNick);

	if (client.isRegistered()) {
		// @TODO Even: host en dynamique
		client.enqueueMessage(ircReplies.formatReply(
			RPL_WELCOME, MakeVars(args)("user", client.getUsername())("host", "localhost")));
	}
}
