#pragma once

#include <ostream>
#include <string>

#include "CharFastStackBuffer.h"

/**
 * @brief FastStackStreamBuffer is stream stack based buffer.
 * 
 * @tparam N - the buffer size.
 */
template <size_t N>
class FastStackStreamBuffer final : public std::basic_streambuf<wchar_t> {
   public:
    using w_char_traits = std::char_traits<wchar_t>;

    /**
     * @brief Construct a new Fast Stack Stream Buffer object
     * 
     * @param _impl - instance of CharFastStackBuffer.
     * @param _freeze - is ownership mark. If _freeze is true, the buffer does not control the object's lifetime.
     */
    explicit FastStackStreamBuffer(CharFastStackBuffer<N> &_impl, bool _freeze = true);
    
    /**
     * @brief Destroy the FastStackStreamBuffer object
     * 
     */
    ~FastStackStreamBuffer();

    /**
     * @brief 
     * 
     * @return CharFastStackBuffer<N>* 
     */
    CharFastStackBuffer<N> *buffer();
    /**
     * @brief Set the Buffer object
     * 
     * @param _impl - instance of CharFastStackBuffer.
     * @param _freeze - is ownership mark. If _freeze is true, the buffer does not control the object's lifetime.
     */
    void setBuffer(CharFastStackBuffer<N> &_impl, bool _freeze = true);
    /**
     * @brief Set the Freeze object
     * 
     * @param _freeze is ownership mark. If _freeze is true, the buffer does not control the object's lifetime
     */
    void setFreeze(bool _freeze);

   protected:
   /**
    * @brief Ensures that there is space at the put area for at least one character by saving some initial subsequence of characters starting at pbase() to the output sequence 
    * and updating the pointers to the put area (if needed). If ch is not Traits::eof() (i.e. Traits::eq_int_type(ch, Traits::eof()) != true), it is either put to the put area or directly saved to the output sequence.
    * The function may update pptr, epptr and pbase pointers to define the location to write more data. On failure, the function ensures that either pptr() == nullptr or pptr() == epptr.
    * The base class version of the function does nothing. The derived classes may override this function to allow updates to the put area in the case of exhaustion.
    * 
    * @param _c is symbol.
    * @return w_char_traits::int_type - returns unspecified value not equal to Traits::eof() on success, Traits::eof() on failure. 
    * The base class version of the function returns Traits::eof(). 
    */
    typename w_char_traits::int_type overflow(typename w_char_traits::int_type _c = w_char_traits::eof()) override;
    /**
     * @brief Writes count characters to the output sequence from the character array whose first element is pointed to by s. The characters are written as if by repeated calls to sputc(). 
     * Writing stops when either count characters are written or a call to sputc() would have returned Traits::eof().
     * 
     * @param _s - characters.
     * @param _count - number of characters.
     * @return std::streamsize - the number of characters successfully written.
     */
    virtual std::streamsize xputn(const typename w_char_traits::char_type *_s, std::streamsize _count);

   private:
   /**
    * @brief The Stack buffer.
    * 
    */
    CharFastStackBuffer<N> *m_impl;
    /**
     * @brief The ownership mark.
     * 
     */
    bool m_freeze;
};

template <size_t N>
FastStackStreamBuffer<N>::FastStackStreamBuffer(CharFastStackBuffer<N> &_impl, bool _freeze) : m_impl(&_impl), m_freeze(_freeze) {
}

template <size_t N>
FastStackStreamBuffer<N>::~FastStackStreamBuffer() {
    if (!m_freeze) {
        delete m_impl;
    }
}

template <size_t N>
CharFastStackBuffer<N> *FastStackStreamBuffer<N>::buffer() {
    m_freeze = true;
    return m_impl;
}

template <size_t N>
void FastStackStreamBuffer<N>::setBuffer(CharFastStackBuffer<N> &_impl, bool _freeze) {
    m_impl = _impl;
    m_freeze = _freeze;
}

template <size_t N>
inline void FastStackStreamBuffer<N>::setFreeze(bool _freeze) {
    m_freeze = _freeze;
}

template <size_t N>
std::streamsize FastStackStreamBuffer<N>::xputn(const typename w_char_traits::char_type *_s, std::streamsize _count) {
    for (int i = 0; i < _count; ++i) {
        w_char_traits::char_type c = _s[i];
        if (c == w_char_traits::eof()) {
            return i;
        }

        m_impl->push(c);
    }

    return _count;
}

template <size_t N>
typename FastStackStreamBuffer<N>::w_char_traits::int_type FastStackStreamBuffer<N>::overflow(typename w_char_traits::int_type _c) {
    if (m_impl == NULL || m_impl->isFull() || w_char_traits::eq_int_type(_c, w_char_traits::eof())) {
        return w_char_traits::eof();
    }

    std::char_traits<wchar_t>::char_type ch = w_char_traits::to_char_type(_c);
    if (!m_impl->push(ch)) {
        return w_char_traits::eof();
    }

    return w_char_traits::not_eof(_c);
}
