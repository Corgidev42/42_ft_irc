// #include "TopicCommand.hpp"

// TopicCommand::TopicCommand(){}
// TopicCommand::~TopicCommand(){}

// void TopicCommand::execute(Server& server, Client& client, const Message& message){
//     if (message.params.empty()){
//         client.enqueueMessage(ERR_NEEDMOREPARAMS);
//         return ;
//     }

//     std::string chanName = message.params[0];
//     Channel* channel = server.getChannel(chanName);

//     if (!channel){
//         client.enqueueMessage(ERR_NOSUCHCHANNEL);
//         return ;
//     }

//     if (!channel->hasClient(&client)){
//         client.enqueueMessage(ERR_NOTONCHANNEL);
//         return ;
//     }

//     // cas 1 : voir le topic (pas de 2eme arg)
//     if (message.params.size() == 1){
//         if (channel.getTopic().empty())
//             client.enqueueMessage(RPL_NOTOPIC);
//         else {
//             client.enqueueMessage(RPL_TOPIC);
//         return ;
//     }

//     //cas 2 : changer le topic :
//     // check du mode t : topic proteger par les utilisateurs :
//     if (channel->hasMode('t') && !channel->isOperator(&client)){
//         client.enqueueMessage(ERR_CHANOPRIVSNEEDED);
//         return ;
//     }

//     std::string newTopic = message.params[1];
//     channel->setTopic(newTopic);

//     // notif a tous le channel
//     channel->broadcast(":" + client.getPrefix() + " TOPIC " + chanName + " :" + newTopic);
// }
