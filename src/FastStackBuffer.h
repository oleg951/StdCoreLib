#pragma once

#include "UserException.h"

#include <array>
#include <string_view>

template<class T, std::size_t N>
class FastStackBuffer;

#warning TODO
//TODO Не делать приватным
template<class T, std::size_t N = 1024>
class OutputIterator {
private:
    FastStackBuffer<T, N> *m_instance;

    struct Proxy {
        explicit Proxy(OutputIterator<T, N> *_it) : m_oIt(_it) {}

        template<class Value_t>
        void operator=(Value_t &&_lvalue) { m_oIt->m_instance->push(std::forward<Value_t>(_lvalue)); }

    private:
        OutputIterator *m_oIt;
    };

    friend class FastStackBuffer<T, N>;

public:
    using iterator_category = std::output_iterator_tag;
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using difference_type = std::ptrdiff_t;
    [[nodiscard]]
    Proxy operator*() noexcept { return Proxy{this}; }

    OutputIterator &operator++() noexcept { return *this; }

    OutputIterator &operator++(int) noexcept { return *this; }

    bool operator==([[maybe_unused]]const OutputIterator &_outIt) const noexcept { return false; }

    bool operator!=([[maybe_unused]]const OutputIterator &_outIt) const noexcept { return true; }
};

/**
 * @brief The FastStackBuffer class is a simple stack implementation.
 * @tparam T - stack element type.
 * @tparam N - the stack size.
 */
template<class T, std::size_t N = 1024>
class FastStackBuffer {
public:
    /*!
     * @brief The array iterator type.
     */
    using array_iterator_t = typename std::array<T, N>::iterator;
    /*!
     * @brief The iterator distance type.
     */
    using Distance_t = typename std::iterator_traits<array_iterator_t>::difference_type;

    /**
     * @brief Push a value onto the stack. Returns true if the operation is successful; otherwise returns false.
     * @throw UserException - if stack is full.
     */
    bool push(const T &_val);

    /**
     * @brief Push a value onto the stack. Returns true if the operation is successful; otherwise returns false.
     * @throw UserException - if stack is full.
     */
    bool push(T &&_val);

    /**
     * @brief Removes the top item from the stack and returns it.
     * @throw UserException - if stack is empty;
     */
    [[nodiscard]]
    T pop();

    /**
     * @brief Return top item of the stack.
     * @throw UserException - if stack is empty;
     */
    [[nodiscard]]
    T &top() const;


    /**
     * @brief Returns true if the stack contains no items; otherwise returns false.
     *
     */
    [[nodiscard]]
    inline constexpr bool isEmpty() const noexcept;

    /**
     * @brief Returns the size of this stack.
     *
     */
    [[nodiscard]]
    inline constexpr Distance_t size() const noexcept;

    /**
     * @brief Returns the capacity of this stack.
     *
     */
    [[nodiscard]]
    inline constexpr size_t capacity() const noexcept;

    /**
     * @brief Returns true if the stack is full; otherwise returns false.
     *
     */
    [[nodiscard]]
    inline constexpr bool isFull() const noexcept;

    OutputIterator<T, N> outputIt() const noexcept;

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
    array_iterator_t m_nextIt{m_buffer.begin()};
};

template<class T, size_t N>
bool FastStackBuffer<T, N>::push(const T &_val) {
    if (isFull()) {
        throw UserException("Stack is full", "isFull()", __PRETTY_FUNCTION__);
    }

    *m_nextIt = _val;

    ++m_nextIt;

    return true;

}

template<class T, size_t N>
bool FastStackBuffer<T, N>::push(T &&_val) {
    if (isFull()) {
        throw UserException("Stack is full", "isFull()", __PRETTY_FUNCTION__);
    }

    *m_nextIt = std::move(_val);

    ++m_nextIt;

    return true;
}

template<class T, size_t N>
T FastStackBuffer<T, N>::pop() {
    if (isEmpty()) {
        throw UserException("Stack is empty", "isEmpty()", __PRETTY_FUNCTION__);
    }

    return std::move(*(--m_nextIt));
}

template<class T, size_t N>
T &FastStackBuffer<T, N>::top() const {
    if (isEmpty()) {
        throw UserException("Stack is empty", "isEmpty()", __PRETTY_FUNCTION__);
    }

    auto prevIt = m_nextIt;
    return *(--prevIt);
}

template<class T, size_t N>
inline constexpr bool FastStackBuffer<T, N>::isEmpty() const noexcept {
    return m_nextIt == m_buffer.begin();
}

template<class T, size_t N>
inline constexpr typename FastStackBuffer<T, N>::Distance_t FastStackBuffer<T, N>::size() const noexcept {
    return m_nextIt - m_buffer.begin();
}

template<class T, size_t N>
inline constexpr size_t FastStackBuffer<T, N>::capacity() const noexcept {
    return N;
}

template<class T, size_t N>
inline constexpr bool FastStackBuffer<T, N>::isFull() const noexcept {
    return size() == N;
}
