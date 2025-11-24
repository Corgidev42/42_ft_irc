#pragma once

#include <string>
#include <map>

class Client;

std::string formatMessage(
    const std::string& fmt,
    const std::map<std::string, std::string>& args);

void enqueueMessage(
    Client& client,
    int messageId,
    const std::map<std::string, std::string>& args);
