#pragma once

#include "ICommand.hpp"

class NickCommand : public ICommand {

    public:
        NickCommand();
        ~NickCommand();

        void execute(Server& server, Client& client, const Message& message);
};
