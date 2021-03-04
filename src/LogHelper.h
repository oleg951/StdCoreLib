#pragma once

#include <optional>

#include "CharFastStackBuffer.h"
#include "FastStackStreamBuffer.h"

/**
 * @brief LogHelper - class foк logging.
 * 
 */
class LogHelper {
   public:
   /**
    * @brief Logging level.
    * 
    */
    enum class LogLevel {
        Critical,
        Error,
        Warning,
        Information
    };

    /**
     * @brief Construct a new LogHelper object
     * 
     * @param _logLevel - login level.
     */
    LogHelper(LogLevel _logLevel = LogLevel::Warning);
    /**
     * @brief Destroy the LogHelper object
     * 
     */
    ~LogHelper();

   private:
   /**
    * @brief loging level.
    * 
    */
    LogLevel m_logLevel;
    
    /**
     * @brief Stack buffer.
     * 
     */
    CharFastStackBuffer<1024> m_buffer;

    /**
     * @brief Redirects the output stream.
     * 
     */
    struct LazyInitedStream {
        explicit LazyInitedStream(CharFastStackBuffer<1024> &_buff) : streamBuff(_buff), ostream(&streamBuff) {}

        FastStackStreamBuffer<1024> streamBuff;
        std::wostream ostream;
    };

    /**
     * @brief output stream.
     * 
     */
    std::optional<LazyInitedStream> m_ostream;

    /**
     * @brief Returns the current time stamp.
     * 
     */
    std::string timestamp() const noexcept;
    /**
     * @brief Returns the output stream reference.
     * 
     */
    std::wostream &stream();

    /**
     * @brief Streaming operator.
     * 
     */
    template <class T>
    friend LogHelper &operator<<(LogHelper &_lh, const T &_val);
};

template <class T>
LogHelper &operator<<(LogHelper &_lh, const T &_val) {
    if constexpr (std::is_convertible_v<T, std::string_view> || std::is_base_of_v<std::exception, T> || std::is_integral_v<T> || std::is_floating_point_v<T>) {
        _lh.m_buffer << _val;
    } else {
        _lh.stream() << _val;
    }

    return _lh;
}