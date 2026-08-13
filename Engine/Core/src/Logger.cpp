#include "Primitive/Core/Logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace primitive
{
    void Logger::Log(
        LogLevel level,
        std::string_view message)
    {
        Write(level, message);
    }

    void Logger::Trace(std::string_view message)
    {
        Write(LogLevel::Trace, message);
    }

    void Logger::Info(std::string_view message)
    {
        Write(LogLevel::Info, message);
    }

    void Logger::Warn(std::string_view message)
    {
        Write(LogLevel::Warn, message);
    }

    void Logger::Error(std::string_view message)
    {
        Write(LogLevel::Error, message);
    }

    void Logger::Critical(std::string_view message)
    {
        Write(LogLevel::Critical, message);
    }

    void Logger::Write(
        LogLevel level,
        std::string_view message)
    {
        const auto now = std::chrono::system_clock::now();

        const auto time = std::chrono::system_clock::to_time_t(now);

        const auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()
            ) % 1000;

        std::tm localTime{};

        localtime_s(&localTime, &time);

        std::ostringstream timestamp;

        timestamp
            << std::put_time(&localTime, "%H:%M:%S")
            << '.'
            << std::setfill('0')
            << std::setw(3)
            << milliseconds.count();

        std::ostream& output =
            (level == LogLevel::Error)
                ? std::cerr
                : std::cout;

        output
            << '['
            << timestamp.str()
            << "] ";

        switch (level)
        {
        case LogLevel::Trace:
            output << "[TRACE] ";
            break;

        case LogLevel::Info:
            output << "[INFO] ";
            break;

        case LogLevel::Warn:
            output << "[WARN] ";
            break;

        case LogLevel::Error:
            output << "[ERROR] ";
            break;

        case LogLevel::Critical:
            output << "[CRITICAL]";
            break;
        }

        output << message << '\n';
    }
}