// #include "JoinCommand.hpp"

// JoinCommand::JoinCommand(){}
// JoinCommand::~JoinCommand(){}

// void JoinCommand::execute(Server& server, Client& client, const Message& message){
//     if (message.params.empty()){
//         client.enqueueMessage(ERR_NEEDMOREPARAMS);
//         return ;
//     }

//     std::string chanName = message.params[0];
//     if (message.params.size() > 1)
//         key = message.params[1];
//     else
//         key = "";

//     if (chanName[0] != '#'){
//         client.enqueueMessage(ERR_NOSUCHCHANNEL);
//         return ;
//     }

//     // TODO : faire une methode getChannel
//     Channel* channel = server.getChannel(chanName);

//     // cas 1 : on creer si ca existe pas :
//     if (!channel){
//         //TODO : faireu ne methode createChannel
//         channel = server.createChannel(chanName, client);

//         std::cout << "Channel " << chanName << " created by " << client.getNickname() << std::endl;
//     }

//     // cas 2 : le channel existe :
//     else {
//         if (channel->hasClient(&client)
//             return ; //client deja dedans)

//         if (channel->hasMode('i') && !channel->isInvited(&client)){
//             client.enqueueMessage(ERR_INVITEONLYCHAN);
//             return ;
//         }

//         if (channel->hasMode('k') && channel->getKey() != key){
//             client.enqueueMessage(ERR_BADCHANNELKEY);
//             return ;
//         }

//         if (channel->hasMode('l') && channel->getUserCount() >= channel->getLimit()){
//             client.enqueueMessage(ERR_CHANNELISFULL);
//             return ;
//         }

//         channel->addClient(&client);
//     }

//     // Succes : broadcast join a tous le monde
//     std::string joinMsg = ":" + client.getPrefix() + " Join: " + chanName;
//     channel->broadcast(joinMsg);

//     if (!channel->getTopic().empty())
//         client.enqueueMessage(RPL_TOPIC);

//     client.enqueueMessage(RPL_NAMREPLY);
//     client.enqueueMessage(RPL_ENDOFNAMES);
// }
