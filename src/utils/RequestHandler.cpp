#include "RequestHandler.h"
#include "openai.hpp"

std::string RequestHandler::qPTrequest(const std::string &input)
{
    openai::start();
    nlohmann::json requestPayload;

    requestPayload["model"] = "gpt-3.5-turbo";
    requestPayload["messages"] = {{{ "role", "user"}, { "content", input}}};
    requestPayload["max_tokens"] = 500;
    requestPayload["temperature"] = 0;

    auto chat = openai::chat().create(requestPayload);
    std::string response = chat["choices"][0]["message"]["content"];

    return response;
}
