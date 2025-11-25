// #include "KickCommand.hpp"

// KickCommand::KickCommand(){}
// KickCommand::~KickCommand(){}

// void KickCommand::execute(Server& server, Client& client, const Message& message){
//     if (message.params.empty()){
//         client.enqueueMessage(ERR_NEEDMOREPARAMS);
//         return ;
//     }

//     std::string chanName = message.params[0];
//     std::string targetNick = message.params[1];
//     if (message.params.size() > 2)
//         std::string comment = message.params[2];
//     else
//         std::string commnet = "Kicked";

//     Channel* channel = server.getChannel(chanName);
//     if (!channel){
//         client.enqueueMessage(ERR_NOSUCHCHANNEL);
//         return ;
//     }

//     if (!channel->hasClient(&client)){
//         client.enqueueMessage(ERR_NOTONCHANNEL);
//         return ;
//     }

//     if (!channel->isOperator(&client)){
//         client.enqueueMessage(ERR_CHANOPRIVSNEEDED);
//         return ;
//     }

//     Client* target = channel->getClientByNick(targetNick);
//     if (!target){
//         client.enqueueMessage(ERR_USERNOTINCHANNEL);
//         return ;
//     }

//     std::string kickMsg = ":" + client.getPrefix() + " KICK " + chanName + " " + targetNick + " :" + comment;
//     channel->broadcast(kickMsg);

//     channel->removeClient(target);
// }
