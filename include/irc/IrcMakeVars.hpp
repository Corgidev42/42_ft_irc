#ifndef IRC_MAKEVARS_HPP
#define IRC_MAKEVARS_HPP

#include <map>
#include <string>

class MakeVars
{
public:
    MakeVars() {}
    MakeVars(std::map<std::string, std::string> nvars) {
        vars = nvars;
    }

    // Méthode permettant d’enchaîner les appels
    MakeVars& operator()(const std::string& key, const std::string& value)
    {
        vars[key] = value;
        return *this;
    }

    // Conversion implicite vers std::map<string,string>
    operator std::map<std::string, std::string>() const
    {
        return vars;
    }

private:
    std::map<std::string, std::string> vars;
};

#endif
