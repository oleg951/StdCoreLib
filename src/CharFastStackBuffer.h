#ifndef CHARFASTSTACKBUFFER_H
#define CHARFASTSTACKBUFFER_H

#include "FastStackBuffer.h"

#include "UserException.h"

#include <iosfwd>
#include <iterator>

/**
 * @brief CharFastStackBuffer is class is stack of chars;
 *
 * @tparam N - stack size.
 */
template <size_t N = 1024>
class CharFastStackBuffer : public FastStackBuffer<wchar_t, N> {
   private:
    /**
     * @brief Write the values of this stack to the stream.
     * @param _os - output stream.
     * @param _buff - instace of the CharFastStackBuffer.
     */
    template <size_t Size>
    friend std::wostream &operator<<(std::wostream &_os, const CharFastStackBuffer<Size> &_buff);
};

template <size_t N>
CharFastStackBuffer<N> &operator<<(CharFastStackBuffer<N> &_buffer, const std::exception &_exception) {
    _buffer << _exception.what();

    return _buffer;
}

template <size_t Size>
std::wostream &operator<<(std::wostream &_os, const CharFastStackBuffer<Size> &_buff) {
    std::copy(_buff.m_buffer.cbegin(), _buff.m_buffer.cend(), std::ostreambuf_iterator<wchar_t>(_os));

    return _os;
}

template <size_t N>
CharFastStackBuffer<N> &operator<<(CharFastStackBuffer<N> &_buffer, const std::string_view &_value) {
    std::copy(_value.cbegin(), _value.cend(), FastStackBufferOutputIterator(_buffer));

    return _buffer;
}

template <size_t N, class V,
          typename = typename std::enable_if_t<
              std::is_integral_v<V> ||
              std::is_floating_point_v<V>>>
CharFastStackBuffer<N> &operator<<(CharFastStackBuffer<N> &_buffer, V _val) {
    _buffer << std::to_string(_val);

    return _buffer;
}

#endif  // CHARFASTSTACKBUFFER_H
