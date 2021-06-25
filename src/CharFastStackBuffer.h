#ifndef CHARFASTSTACKBUFFER_H
#define CHARFASTSTACKBUFFER_H

#include "FastStackBuffer.h"

#include "UserException.h"

#include <iosfwd>
#include <iterator>

/*!
 * @brief CharFastStackBuffer is class is stack of chars;
 * @tparam N - stack size.
 */
template<class Char_t = char, size_t N = 1024>
class CharFastStackBuffer : public FastStackBuffer<Char_t, N> {
private:
    /*!
     * @brief Write the values of this stack to the stream.
     * @param _os - output stream.
     * @param _buff - instace of the CharFastStackBuffer.
     */
    template<class OS_t, class Buffer_t>
    friend OS_t &operator<<(OS_t &_os, const Buffer_t &_buff);
};

template<class Char_t = char, size_t N = 1024>
CharFastStackBuffer<Char_t, N> &operator<<(CharFastStackBuffer<Char_t, N> &_buffer, const std::exception &_exception) {
    _buffer << _exception.what();

    return _buffer;
}

template<class OS_t, class Buffer_t>
OS_t &operator<<(OS_t &_os, const Buffer_t &_buff) {
    std::copy(_buff.m_buffer.cbegin(), _buff.m_buffer.cend(), std::ostreambuf_iterator(_os));

    return _os;
}

template<class Char_t = char, size_t N = 1024, class CharSeq_t>
CharFastStackBuffer<Char_t, N> &
operator<<(CharFastStackBuffer<Char_t, N> &_buffer, const CharSeq_t &_value) {
    std::copy(std::cbegin(_value), std::cend(_value), FastStackBufferOutputIterator(_buffer));

    return _buffer;
}

template<class Char_t = char, size_t N, class V,
        typename = typename std::enable_if_t<
                std::is_integral_v<V> ||
                std::is_floating_point_v<V>>>
CharFastStackBuffer<Char_t, N> &operator<<(CharFastStackBuffer<Char_t, N> &_buffer, V _val) {
    _buffer << std::to_string(_val);

    return _buffer;
}

#endif  // CHARFASTSTACKBUFFER_H
