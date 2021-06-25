#include "LogHelper.h"

#include <chrono>
#include <ctime>
#include <iostream>

LogHelper::LogHelper(LogLevel _logLevel): m_logLevel(_logLevel) {
    m_buffer << timestamp() << " ";
}

LogHelper::~LogHelper() {
    std::cerr << m_buffer << std::endl;
}

std::string LogHelper::timestamp() const noexcept {
    auto time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeStr(std::ctime(&time));
    // remove line feed.
    timeStr.resize(timeStr.size() - 1);

    return timeStr;
}

std::basic_ostream<char> &LogHelper::stream() {
    if (!m_ostream.has_value()) {
        m_ostream.emplace(m_buffer);
    }

    return m_ostream->ostream;
}
