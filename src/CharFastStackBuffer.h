#ifndef CHARFASTSTACKBUFFER_H
#define CHARFASTSTACKBUFFER_H

#include <iosfwd>

#include "FastStackBuffer.h"
#include "UserException.h"

/**
 * @brief CharFastStackBuffer is class is stack of chars;
 * 
 * @tparam N - stack size.
 */
template <size_t N = 1024>
class CharFastStackBuffer : public FastStackBuffer<wchar_t, N> {
   public:
   /**
    * @brief Construct a new Char Fast Stack Buffer object.
    * 
    */
    explicit CharFastStackBuffer() noexcept;

   private:
    /**
     * @brief Write the values of this stack to the stream.
     *
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
    for (auto &&begin = _buff.m_buffer.cbegin(); begin != _buff.m_nextIt; ++begin) {
        _os << *begin;
    }
    return _os;
}

template <size_t N>
CharFastStackBuffer<N> &operator<<(CharFastStackBuffer<N> &_buffer, const std::string_view &_value) {
    for (auto cit = _value.cbegin(); cit != _value.cend(); ++cit) {
        _buffer.push(*cit);
    }

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

template <size_t N>
CharFastStackBuffer<N>::CharFastStackBuffer() noexcept : FastStackBuffer<wchar_t, N>() {
}

#endif  // CHARFASTSTACKBUFFER_H
