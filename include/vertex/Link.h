#pragma once
#include <memory>

namespace vertex
{

/** A link contains a key with which an object may be looked up, plus some
 * additional metadata */
template <typename Key, typename T = void>
class Link
{
public:
    using key_type = Key;
    using value_type = T;

    explicit Link(key_type key = key_type(), value_type data = value_type());
    Link(Link&&) = default;
    Link& operator=(const Link&) = default;
    Link& operator=(Link&&) = default;

    const key_type& key() const;
    const value_type& data() const;
    void key(const key_type& data);
    void data(const value_type& value);

    bool operator==(const Link& rhs) const;
    bool operator!=(const Link& rhs) const;

private:
    key_type key_;
    value_type data_;
};

template <typename Key, typename T>
Link<Key, T>::Link(Key key, T data)
    : key_(std::move(key)), data_(std::move(data))
{
}

template <typename Key, typename T>
const Key& Link<Key, T>::key() const
{
    return key_;
}

template <typename Key, typename T>
const T& Link<Key, T>::data() const
{
    return data_;
}

template <typename Key, typename T>
void Link<Key, T>::key(const Key& data)
{
    return key_ = data;
}

template <typename Key, typename T>
void Link<Key, T>::data(const T& value)
{
    return data_ = value;
}

template <typename Key, typename T>
bool Link<Key, T>::operator==(const Link<Key, T>& rhs) const
{
    return key_ == rhs.key_ && data_ == rhs.data_;
}

template <typename Key, typename T>
bool Link<Key, T>::operator!=(const Link<Key, T>& rhs) const
{
    return !(*this == rhs);
}

} // namespace