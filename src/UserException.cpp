#include "UserException.h"

#include <ctime>

UserException::UserException(const std::string_view &_usrMsg,
                             const std::string_view &_dbMsg,
                             const std::string_view &_funcInfo,
                             std::exception *_exception) noexcept : std::exception(),
                                                                    m_usrMsg(_usrMsg),
                                                                    m_dbMsg(_dbMsg),
                                                                    m_funcInfo(_funcInfo),
                                                                    m_nestedException(_exception) {
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
const std::string_view UserException::usrMsg() const noexcept {
    return m_usrMsg;
}

const std::string_view UserException::dbMsg() const noexcept {
    return m_dbMsg;
}

const std::string_view UserException::funcInfo() const noexcept {
    return m_funcInfo;
}

std::exception *UserException::nestedException() const noexcept {
    return m_nestedException;
}

std::string UserException::toString(int _level) const {
    std::string indent;
    indent.resize(_level);
    std::fill(indent.begin(), indent.begin() + _level, ' ');

    std::string str;

    str.append(indent).append("The exception in function ").append(m_funcInfo).append("\n");
    str.append(indent).append("User message: ").append(m_usrMsg).append("\n");
    str.append(indent).append("Debug message: ").append(m_dbMsg).append("\n");

    if (m_nestedException != NULL) {
        const UserException *except = dynamic_cast<const UserException *>(m_nestedException);
        if (except != NULL) {
            str.append(except->toString(_level + 1));
        } else {
            indent.append(" ");

            str.append(indent).append(m_nestedException->what());
        }

        if (m_nestedException != nullptr) {
            m_what.append(m_nestedException->what()).append("\n");
        }
    }
    return str;
}