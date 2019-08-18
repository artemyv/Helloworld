#include "details.v1.h"
#include "details.v2.h"
#include "details.v3.h"

#include <iostream>

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#define LOG_STREAM_CALL(logger, level)                                                                                 \
    logger && logger->should_log(level) &&                                                                             \
        logger_stream::detail::LogStream() ==                                                                          \
            logger_stream::detail::make_forwarder([a_logger = logger, a_level = level](const char *pattern,            \
                                                                                       auto &&... a) {                 \
                [[gsl::supress("lifetime.3")]] a_logger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},  \
                                                             a_level,                                                  \
                                                             pattern,                                                  \
                                                             std::forward<decltype(a)>(a)...);                         \
                return true;                                                                                           \
            })

#define LOG_STREAM_INFO(logger) LOG_STREAM_CALL(logger, spdlog::level::info)

int
main()
{
    auto logger = spdlog::default_logger();
    LOG_STREAM_INFO(logger) << "Welcome to spdlog version " << SPDLOG_VER_MAJOR << '.' << SPDLOG_VER_MINOR << '.'
                            << SPDLOG_VER_PATCH;

    LOG_STREAM_INFO(logger) << "test hex" << std::hex << 123;
    // std::cout << logger_stream::detail::v2::make_pattern<0, 1, 0, 0>() << '\n';
}
