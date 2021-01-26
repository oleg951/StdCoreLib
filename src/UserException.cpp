#include "UserException.h"

UserException::UserException() noexcept: std::exception()
{
}

UserException::UserException(const std::string_view _usrMsg,
                                 const std::string_view _dbMsg,
                                 const std::string_view _funcInfo,
                                 const std::exception &_exception) noexcept: std::exception(), 
m_usrMsg(_usrMsg), m_dbMsg(_dbMsg), m_funcInfo(_funcInfo), m_nestedException(_exception)
{

}

const std::string_view UserException::usrMsg() const noexcept
{
    return m_usrMsg;
}

const std::string_view UserException::dbMsg() const noexcept
{
    return m_dbMsg;
}

const std::string_view UserException::timeStamp() const noexcept
{
    return m_timeStamp;
}

const std::string_view UserException::funcInfo() const noexcept
{
    return m_funcInfo;
}

std::exception UserException::nestedException() const noexcept
{
     return m_nestedException;
}