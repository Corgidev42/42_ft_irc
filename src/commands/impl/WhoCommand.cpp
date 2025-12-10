#include "impl/WhoCommand.hpp"
#include <iostream>

WhoCommand::WhoCommand(){};
WhoCommand::~WhoCommand(){};

void WhoCommand::execute(Server& server, Client& client, const Message& message){
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());
	string query = message.params.empty() ? "*" : message.params[0];

    // m[RPL_WHOREPLY] = "{server} 352 {nick} {channel} {user} {host} {server2} {nick2} {flags} :{hopcount} {realname}";

	Channel* channel = server.getChannel(query);
	if (channel) {
		map<string, Client*> clients = channel->getClients();
		for (map<string, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
			Client* c = it->second;
			client.enqueueMessage(ircReplies.formatReply(
				RPL_WHOREPLY, MakeVars(args)
					("channel", channel->getName())
					("user", c->getUsername())
					("host", "localhost") // @TODO : host en dynamique
					("server2", server.getName())
					("nick2", c->getNickname())
					("flags", "H") // @TODO : ajouter les flags corrects
					("hopcount", "0") // @TODO : hopcount en dynamique
					("realname", c->getRealname())
				)
			);
		}
		client.enqueueMessage(ircReplies.formatReply(
			RPL_ENDOFWHO, MakeVars(args)("channel", query)
		));
		server.handleWrite(client);
		return;
	}

	server.handleWrite(client);
}
