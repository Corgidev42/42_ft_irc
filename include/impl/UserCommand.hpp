#pragma once

#include "ICommand.hpp"

class UserCommand : public ICommand{

    public:
        UserCommand();
        ~UserCommand();

        void execute(Server& server, Client& client, const Message& message);
};
