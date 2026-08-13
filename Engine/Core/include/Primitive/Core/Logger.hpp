#pragma once

#include <string_view>

namespace primitive
{
    enum class LogLevel
    {
        Trace,
        Info,
        Warn,
        Error,
        Critical
    };

    class Logger
    {
    public:
        void Log(LogLevel level, std::string_view message);

        void Trace(std::string_view message);
        void Info(std::string_view message);
        void Warn(std::string_view message);
        void Error(std::string_view message);
        void Critical(std::string_view message);

    private:
        void Write(LogLevel level, std::string_view message);
    };
}