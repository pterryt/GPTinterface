#ifndef GPTINTERFACE_LOGGER_H
#define GPTINTERFACE_LOGGER_H
#include <spdlog/spdlog.h>

namespace giLog
{
    extern std::shared_ptr<spdlog::logger> consoleLog;
    void initLogger();
}

#endif //GPTINTERFACE_LOGGER_H