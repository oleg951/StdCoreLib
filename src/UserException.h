#pragma once

#include <exception>
#include <string_view>
#include <string>

class UserException : public std::exception
{
public:
    UserException() noexcept;
    explicit UserException(const std::string_view _usrMsg,
                             const std::string_view _dbMsg,
                             const std::string_view _funcInfo,
                             const std::exception &_exception = std::exception()) noexcept;

    virtual ~UserException() noexcept = default;

    UserException(const UserException &_exception) noexcept = default;
    UserException &operator=(const UserException &_exception) noexcept = default;

    UserException(UserException &&_exception) noexcept = default;
    UserException &operator=(UserException &&_exception) noexcept = default;

    const std::string_view usrMsg() const noexcept;
    const std::string_view dbMsg() const noexcept;
    const std::string_view timeStamp() const noexcept;
    const std::string_view funcInfo() const noexcept;
    std::exception nestedException() const noexcept;

private:
    std::string m_usrMsg;
    std::string m_dbMsg;
    std::string m_timeStamp;
    std::string m_funcInfo;
    std::exception m_nestedException;
};