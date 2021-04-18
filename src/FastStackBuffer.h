#pragma once

#include "UserException.h"

#include <array>
#include <string_view>

/**
 * @brief The FastStackBuffer class is a simple stack implementation.
 *
 * @tparam T - stack element type.
 * @tparam N - the stack size.
 */
template <class T, std::size_t N = 1024>
class FastStackBuffer {
   public:
    /**
     * @brief Construct a new FastStackBuffer object
     *
     */
    explicit FastStackBuffer() noexcept;
    /**
     * @brief Destroy the FastStackBuffer object
     *
     */
    ~FastStackBuffer() noexcept = default;

    /**
     * @brief Construct a new FastStackBuffer object
     *
     */
    FastStackBuffer(const FastStackBuffer &_stack) = default;
    /**
     * @brief Assigns _stack to this stack and returns a reference to this stack.
     *
     */
    FastStackBuffer &operator=(const FastStackBuffer &_stack) = default;

    /**
     * @brief Construct a new Fast Stack Buffer object
     *
     */
    FastStackBuffer(FastStackBuffer &&_stack) = default;
    /**
     * @brief Move-assigns _stack to this stack and returns a reference to this stack.
     *
     */
    FastStackBuffer &operator=(FastStackBuffer &&_stack) = default;

    /**
     * @brief Push a value onto the stack. Returns true if the operation is successful; otherwise returns false.
     *
     */
    bool push(const T &_val) noexcept;
    /**
     * @brief Push a value onto the stack. Returns true if the operation is successful; otherwise returns false.
     *
     */
    bool push(T &&_val) noexcept;
    /**
     * @brief Removes the top item from the stack and returns it.
     * @throw UserException - if stack is empty;
     */
    T pop();

    /**
     * @brief Return top item of the stack.
     * @throw UserException - if stack is empty;
     */
    T &top() const;


    /**
     * @brief Returns true if the stack contains no items; otherwise returns false.
     *
     */
    constexpr bool isEmpty() const noexcept;
    /**
     * @brief Returns the size of this stack.
     *
     */
    constexpr size_t size() const noexcept;
    /**
     * @brief Returns the capacity of this stack.
     *
     */
    constexpr size_t capacity() const noexcept;
    /**
     * @brief Returns true if the stack is full; otherwise returns false.
     *
     */
    constexpr bool isFull() const noexcept;

   protected:
   /**
    * @brief Underlying array.
    *
    */
    std::array<T, N> m_buffer;
   /**
    * @brief End of stack iterator.
    *
    */                    
    typename std::array<T, N>::iterator m_nextIt;
};

template <class T, size_t N>
FastStackBuffer<T, N>::FastStackBuffer() noexcept {
    m_nextIt = m_buffer.begin();
}

template <class T, size_t N>
bool FastStackBuffer<T, N>::push(const T &_val) noexcept {
    if (m_nextIt == m_buffer.cend()) {
        return false;
    }

    *m_nextIt = _val;

    ++m_nextIt;

    return true;
}

template <class T, size_t N>
bool FastStackBuffer<T, N>::push(T &&_val) noexcept {
    if (m_nextIt == m_buffer.cend()) {
        return false;
    }

    *m_nextIt = std::move(_val);

    ++m_nextIt;

    return true;
}

template <class T, size_t N>
T FastStackBuffer<T, N>::pop() {
    if (m_nextIt == m_buffer.begin()) {
         throw UserException("Stack is empty", "isEmpty()", __PRETTY_FUNCTION__);
    }

    return std::move(*(--m_nextIt));
}

template <class T, size_t N>
T& FastStackBuffer<T, N>::top() const
{
    if (isEmpty()) {
        throw UserException("Stack is empty", "isEmpty()", __PRETTY_FUNCTION__);
    }

    auto prevIt = m_nextIt;
    return *(--prevIt);
}

template <class T, size_t N>
constexpr bool FastStackBuffer<T, N>::isEmpty() const noexcept {
    return m_nextIt == m_buffer.begin();
}

template <class T, size_t N>
constexpr size_t FastStackBuffer<T, N>::size() const noexcept {
    return m_nextIt - m_buffer.begin();
}

template <class T, size_t N>
constexpr size_t FastStackBuffer<T, N>::capacity() const noexcept {
    return N;
}

template <class T, size_t N>
constexpr bool FastStackBuffer<T, N>::isFull() const noexcept {
    return size() == N;
}
