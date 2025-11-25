// #include "InviteCommand.hpp"
// #include "network/Client.hpp"

// InviteCommand::InviteCommand(){}
// InviteCommand::~InviteCommand(){}

// void execute(Server& server, Client& client, const Message& message){
//     std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname())("command", "INVITE");

//     if (message.params.empty()){
//         client.enqueueMessage(ircReplies.formatReply(
//             ERR_NEEDMOREPARAMS, args));
//         return ;
//     }

//     std::string targetNick = message.params[0];
//     std::string chanName = message.params[1];

//     Channel* channel = server.getChannel(chanName);
//     if (!channel){
//         client.enqueueMessage(ircReplies.formatReply(
//             ERR_NOSUCHCHANNEL, args));
//         return ;
//     }

//     if (!channel->hasClient(&client)){
//         client.enqueueMessage(ERR_NOTONCHANNEL);
//         return ;
//     }

//     if (channel->hasMode('i') && !channel->isOperator(&client)){
//         client.enqueueMessage(ERR_CHANOPRIVSNEEDED);
//         return ;
//     }

//     Client* target = server.getClientByNick(targetNick);
//     if (!target){
//         client.enqueueMessage(ERR_NOSUCHNICK);
//         return ;
//     }

//     if (channel->hasClient(target)){
//         client.enqueueMessage(ERR_USERONCHANNEL);
//         return ;
//     }

//     channel->addInvited(target);

//     client.enqueueMessage(RPL_INVITING);

//     target->reply(":" + client.getPrefix() + " INVITE " + targetNick + " :" + chanName);
// }
