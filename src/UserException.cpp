#include "UserException.h"

UserException::UserException(const std::string_view &_usrMsg,
                             const std::string_view &_dbMsg,
                             const std::string_view &_funcInfo) noexcept : std::exception(),
                                                                           m_usrMsg(_usrMsg),
                                                                           m_dbMsg(_dbMsg),
                                                                           m_funcInfo(_funcInfo),
                                                                           m_nestedException(nullptr) {
}

UserException::~UserException() noexcept {
    m_what.clear();
    m_usrMsg.clear();
    m_dbMsg.clear();
    m_funcInfo.clear();

    delete m_nestedException;
    m_nestedException = nullptr;
}

const char *UserException::what() const noexcept {
    if (m_what.empty()) {
        m_what.append(toString());
    }

    return m_what.c_str();
}
std::string_view UserException::usrMsg() const noexcept {
    return m_usrMsg;
}

std::string_view UserException::dbMsg() const noexcept {
    return m_dbMsg;
}

std::string_view UserException::funcInfo() const noexcept {
    return m_funcInfo;
}

std::exception *UserException::nestedException() const noexcept {
    return m_nestedException;
}

std::string UserException::toString() const {
    std::string str;

    str.append("The exception in function ").append(m_funcInfo).append("\n");
    str.append("User message: ").append(m_usrMsg).append("\n");
    str.append("Debug message: ").append(m_dbMsg).append("\n");

    if (m_nestedException != nullptr) {
       str.append(m_nestedException->what()).append("\n");
    }
    str.append("\n");

    return str;
}