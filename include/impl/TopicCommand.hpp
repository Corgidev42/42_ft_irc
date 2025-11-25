#pragma once

#include "ICommand.hpp"

class TopicCommand : public ICommand{
    public:
        TopicCommand();
        ~TopicCommand();

        void execute(Server& server, Client& client, const Message& message);
};
