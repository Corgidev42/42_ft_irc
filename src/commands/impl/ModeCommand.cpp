#include "impl/ModeCommand.hpp"
#include <cstdlib>
#include <sstream>

void ModeCommand::execute(Server& server, Client& client, const Message& message) {
    std::map<string, string> args = MakeVars()("server", server.getName())("nick", client.getNickname());

    if (message.params.size() < 1) {
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NEEDMOREPARAMS, MakeVars(args)("command", "MODE")));
        server.handleWrite(client);
        return;
    }

    std::string target = message.params[0];

    Channel* channel = server.getChannel(target);
    // On ne gère que les modes de Channel pour l'instant (commence par #)
    if (target[0] != '#' || !channel) {
        client.enqueueMessage(ircReplies.formatReply(
            ERR_NOSUCHCHANNEL, MakeVars(args)("channel", target)));
        server.handleWrite(client);
        return;
    }

    // 2. Si l'utilisateur demande juste les modes actuels "MODE #chan"
    if (message.params.size() == 1) {
        std::string modes = channel->getModeStr();
        // std::string args = channel->getModeArgs();
        client.enqueueMessage(ircReplies.formatReply(
            RPL_CHANNELMODEIS, MakeVars(args)("channel", target)("modes", modes)));
        server.handleWrite(client);
        return;
    }

    // 3. Vérification des droits (Seul un opérateur peut CHANGER un mode)
    if (!channel->isOperator(&client)) {
        client.enqueueMessage(ircReplies.formatReply(
            ERR_CHANOPRIVSNEEDED, MakeVars(args)("channel", target)));
        server.handleWrite(client);
        return;
    }

    // --- DÉBUT DU PARSING ET APPLICATION ---

    std::string modeString = message.params[1]; // ex: "+o-l"
    std::string modeParamsResult = "";
    std::string modeStrResult = "";
    size_t paramIdx = 2;
    bool adding = true;
    char currentSign = '+';

    for (size_t i = 0; i < modeString.length(); ++i) {
        char mode = modeString[i];

        if (mode == '+') {
            adding = true;
            currentSign = '+';
            continue;
        }
        if (mode == '-') {
            adding = false;
            currentSign = '-';
            continue;
        }

        bool success = false;
        std::string argAdded = "";

        switch (mode) {
            case 'i':
                if (channel->hasMode('i') != adding) {
                    channel->setMode('i', adding);
                    success = true;
                }
                break;

            case 't':
                if (channel->hasMode('t') != adding) {
                    channel->setMode('t', adding);
                    success = true;
                }
                break;

            case 'k':
                if (adding) {
                    if (paramIdx < message.params.size()) {
                        std::string key = message.params[paramIdx++];
                        channel->setKey(key);
                        channel->setMode('k', true);
                        success = true;
                        argAdded = key;
                    }
                } else {
                    if (channel->hasMode('k')) {
                        channel->setKey("");
                        channel->setMode('k', false);
                        success = true;
                    }
                }
                break;

            case 'o':
                if (paramIdx < message.params.size()) {
                    std::string targetNick = message.params[paramIdx++];
                    Client* targetClient = channel->getClientByNick(targetNick);

                    if (targetClient) {
                        if (adding) {
                            if (!channel->isOperator(targetClient)) {
                                channel->addOperator(targetClient);
                                success = true;
                            }
                        } else {
                            if (channel->isOperator(targetClient)) {
                                channel->removeOperator(targetClient);
                                success = true;
                            }
                        }
                        argAdded = targetNick;
                    } else {
                        client.enqueueMessage(ircReplies.formatReply(
                            ERR_CHANOPRIVSNEEDED, MakeVars(args)("target", targetNick)));
                    }
                }
                break;

            case 'l':
                if (adding) {
                    if (paramIdx < message.params.size()) {
                        std::string limitStr = message.params[paramIdx++];
                        int limit = std::atoi(limitStr.c_str());

                        channel->setLimit(limit);
                        channel->setMode('l', true);
                        success = true;
                        argAdded = limitStr;
                    }
                } else {
                    if (channel->hasMode('l')) {
                        channel->setMode('l', false);
                        channel->setLimit(0);
                        success = true;
                    }
                }
                break;

            default:
                std::string unknownMode(1, mode);
                client.enqueueMessage(ircReplies.formatReply(
                    ERR_CHANOPRIVSNEEDED, MakeVars(args)("char", unknownMode)));
                break;
        }

        if (success) {
            modeStrResult += currentSign;
            modeStrResult += mode;

            if (!argAdded.empty()) {
                modeParamsResult += " " + argAdded;
            }
        }
    }

    if (!modeStrResult.empty()) {
        std::string finalMsg = ":" + client.getNickname() + " MODE " + target + " " + modeStrResult + modeParamsResult;

        channel->broadcast(finalMsg, server);
    }
    server.handleWrite(client);
}
