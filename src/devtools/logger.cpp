#include "logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace giLog
{
    std::shared_ptr<spdlog::logger> consoleLog;

    void initLogger()
    {
        consoleLog = spdlog::stdout_color_mt("console");
        consoleLog->set_level(spdlog::level::debug);
    }

}


