// #include "ModeCommand.hpp"
// #include <cstdlib>
// #include <sstream>

// void ModeCommand::execute(Server& server, Client& client, const Message& message) {
//     if (message.params.size() < 1) {
//         client.enqueueMessage(ERR_NEEDMOREPARAMS);
//         return;
//     }

//     std::string target = message.params[0];

//     // On ne gère que les modes de Channel pour l'instant (commence par #)
//     if (target[0] != '#') {
//         client.enqueueMessage(ERR_NOSUCHCHANNEL);
//         return;
//     }

//     Channel* channel = server.getChannel(target);
//     if (!channel) {
//         client.enqueueMessage(ERR_NOSUCHCHANNEL);
//         return;
//     }

//     // 2. Si l'utilisateur demande juste les modes actuels "MODE #chan"
//     if (message.params.size() == 1) {
//         std::string modes = channel->getModesStr();
//         std::string args = channel->getModeArgs();
//         client.enqueueMessage(RPL_CHANNELMODEIS);
//         return;
//     }

//     // 3. Vérification des droits (Seul un opérateur peut CHANGER un mode)
//     if (!channel->isOperator(&client)) {
//         client.enqueueMessage(ERR_CHANOPRIVSNEEDED);
//         return;
//     }

//     // --- DÉBUT DU PARSING ET APPLICATION ---

//     std::string modeString = message.params[1]; // ex: "+o-l"
//     std::string modeParamsResult = "";
//     std::string modeStrResult = "";
//     size_t paramIdx = 2;
//     bool adding = true;
//     char currentSign = '+';

//     for (size_t i = 0; i < modeString.length(); ++i) {
//         char mode = modeString[i];

//         if (mode == '+') {
//             adding = true;
//             currentSign = '+';
//             continue;
//         }
//         if (mode == '-') {
//             adding = false;
//             currentSign = '-';
//             continue;
//         }

//         bool success = false;
//         std::string argAdded = "";

//         switch (mode) {
//             case 'i':
//                 if (channel->hasMode('i') != adding) {
//                     channel->setMode('i', adding);
//                     success = true;
//                 }
//                 break;

//             case 't':
//                 if (channel->hasMode('t') != adding) {
//                     channel->setMode('t', adding);
//                     success = true;
//                 }
//                 break;

//             case 'k':
//                 if (adding) {
//                     if (paramIdx < message.params.size()) {
//                         std::string key = message.params[paramIdx++];
//                         channel->setKey(key);
//                         channel->setMode('k', true);
//                         success = true;
//                         argAdded = key;
//                     }
//                 } else {
//                     if (channel->hasMode('k')) {
//                         channel->setKey("");
//                         channel->setMode('k', false);
//                         success = true;
//                     }
//                 }
//                 break;

//             case 'o':
//                 if (paramIdx < message.params.size()) {
//                     std::string targetNick = message.params[paramIdx++];
//                     Client* targetClient = channel->getClientByNick(targetNick);

//                     if (targetClient) {
//                         if (adding) {
//                             if (!channel->isOperator(targetClient)) {
//                                 channel->addOperator(targetClient);
//                                 success = true;
//                             }
//                         } else {
//                             if (channel->isOperator(targetClient)) {
//                                 channel->removeOperator(targetClient);
//                                 success = true;
//                             }
//                         }
//                         argAdded = targetNick;
//                     } else {
//                         client.enqueueMessage("401 " + targetNick + " :No such nick/channel");
//                     }
//                 }
//                 break;

//             case 'l':
//                 if (adding) {
//                     if (paramIdx < message.params.size()) {
//                         std::string limitStr = message.params[paramIdx++];
//                         int limit = std::atoi(limitStr.c_str());

//                         channel->setLimit(limit);
//                         channel->setMode('l', true);
//                         success = true;
//                         argAdded = limitStr;
//                     }
//                 } else {
//                     if (channel->hasMode('l')) {
//                         channel->setMode('l', false);
//                         channel->setLimit(0);
//                         success = true;
//                     }
//                 }
//                 break;

//             default:
//                 std::string unknownMode(1, mode);
//                 client.enqueueMessage("472 " + unknownMode + " :is unknown mode char to me");
//                 break;
//         }

//         if (success) {
//             modeStrResult += currentSign;
//             modeStrResult += mode;

//             if (!argAdded.empty()) {
//                 modeParamsResult += " " + argAdded;
//             }
//         }
//     }

//     if (!modeStrResult.empty()) {
//         std::string finalMsg = ":" + client.getPrefix() + " MODE " + target + " " + modeStrResult + modeParamsResult;

//         channel->broadcast(finalMsg);
//     }
// }
