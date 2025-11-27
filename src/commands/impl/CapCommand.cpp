#include "impl/CapCommand.hpp"
#include <iostream>

CapCommand::CapCommand(){};
CapCommand::~CapCommand(){};

void CapCommand::execute(Server& server, Client& client, const Message& message){
	(void)message;
	
	client.enqueueMessage("CAP * LS :\r\n");
	server.handleWrite(client);
}
