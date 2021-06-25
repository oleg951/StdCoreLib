#pragma once

#include <exception>
#include <string>
#include <string_view>

/**
 * @brief UserException is the user exception. It contains the name of function that threw exception, the user message, the debug message and
 * it can store a nested exception.
 * 
 */
class UserException : public std::exception {
public:
    /**
    * @brief Construct a new UserException object.
    * 
    * @param _usrMsg - user message.
    * @param _dbMsg - debug message. 
    * @param _funcInfo - function name.
    */
    explicit UserException(const std::string_view &_usrMsg,
                           const std::string_view &_dbMsg,
                           const std::string_view &_funcInfo) noexcept;

    /**
    * @brief Construct a new UserException object.
    * 
    * @param _usrMsg - user message.
    * @param _dbMsg - debug message. 
    * @param _funcInfo - function name.
    * @param _exception - nested exception.
    */
    template<class T,
            typename = typename std::enable_if_t<std::is_base_of_v<std::exception, std::decay_t<T>>>>
    explicit UserException(const std::string_view &_usrMsg,
                           const std::string_view &_dbMsg,
                           const std::string_view &_funcInfo,
                           T &&_exception) noexcept;

    /**
     * @brief Destroy the UserException object
     * 
     */
    virtual ~UserException() noexcept;

    /**
     * @brief Returns information about the exception.
     * 
     */
    [[nodiscard]] const char *what() const noexcept override;

    /**
     * @brief Construct a new UserException object
     * 
     */
    UserException(const UserException &_exception) = default;

    /**
     * @brief Copy operator.
     * 
     */
    UserException &operator=(const UserException &_exception) = default;

    /**
     * @brief Move construct a new UserException object.
     * 
     */
    UserException(UserException &&_exception) noexcept = default;

    /**
     * @brief Move operator.
     * 
     */
    UserException &operator=(UserException &&_exception) noexcept = default;

    /**
     * @brief Return the user message.
     * 
     */
    std::string_view usrMsg() const noexcept;

    /**
     * @brief Return the debug message.
     * 
     */
    std::string_view dbMsg() const noexcept;

    /**
     * @brief Return the function name.
     * 
     */
    std::string_view funcInfo() const noexcept;

    /**
     * @brief Return the nested exception.
     * 
     */
    std::exception *nestedException() const noexcept;

private:
    /**
    * @brief Information about the exception.
    * 
    */
    mutable std::string m_what;

    /**
     * @brief The user message.
     * 
     */
    std::string m_usrMsg;
    /**
     * @brief The debug message.
     * 
     */
    std::string m_dbMsg;
    /**
     * @brief The function name.
     * 
     */
    std::string m_funcInfo;
    /**
     * @brief The nested exception.
     * 
     */
    std::exception *m_nestedException;

    /**
     * @brief Returns information about the exception, taking into account the nested level.
     * 
     */
    std::string toString() const;
};

template<class T, typename>
UserException::UserException(const std::string_view &_usrMsg,
                             const std::string_view &_dbMsg,
                             const std::string_view &_funcInfo,
                             T &&_exception) noexcept : std::exception(),
                                                        m_usrMsg(_usrMsg),
                                                        m_dbMsg(_dbMsg),
                                                        m_funcInfo(_funcInfo) {
    m_nestedException = new std::decay_t<T>(std::forward<T>(_exception));
}
