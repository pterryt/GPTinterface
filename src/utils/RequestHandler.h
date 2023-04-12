#ifndef GPTINTERFACE_REQUESTHANDLER_H
#define GPTINTERFACE_REQUESTHANDLER_H

#include <curl/curl.h>
#include "openai.hpp"

class RequestHandler
{
public:
    static std::string qPTrequest(const std::string& input);
};


#endif //GPTINTERFACE_REQUESTHANDLER_H