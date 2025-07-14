#ifndef INDEXEDSET_HPP
#define INDEXEDSET_HPP

#include <QHash>
#include <QStack>
#include <QDebug>
#include <optional>
#include <functional>

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
class IndexedMap
{
public:
    using Index = qsizetype;

    using OptionalRef = std::optional<std::reference_wrapper<_Type>>;
    using OptionalConstRef = std::optional
        <std::reference_wrapper<const _Type>>;

public:
    IndexedMap() = default;
    IndexedMap(const IndexedMap&) = default;
    IndexedMap(IndexedMap&&) = default;

    ~IndexedMap() = default;

    bool Insert(_Type&& element) noexcept;
    bool Remove(const _KeyType& key) noexcept;

    const _Type& Unpack(OptionalConstRef value) const noexcept;
    _Type& Unpack(OptionalRef value) noexcept;

    OptionalConstRef GetElement(const _KeyType& key) const noexcept;
    OptionalRef GetElement(const _KeyType& key) noexcept;

    OptionalConstRef GetElement(const Index index) const noexcept;
    OptionalRef GetElement(const Index index) noexcept;

    Index GetIndex(const _KeyType& key) const noexcept;

    bool DoesContain(const _KeyType& key) const noexcept;

    IndexedMap& operator = (const IndexedMap&) = default;
    IndexedMap& operator = (IndexedMap&&) = default;

private:
    QHash<_KeyType, _Type> m_Data{};

    QHash<Index, _KeyType> m_IndicesToKeys{};
    QHash<_KeyType, Index> m_KeysToIndices{};

    QStack<Index> m_FreeIndices{};
};

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
bool IndexedMap<_Type, _KeyType, _KeyName>::Insert(_Type&& element)
    noexcept
{
    const _KeyType& key = element.*_KeyName;

    if (DoesContain(key))
    {
        return false;
    }

    m_Data.insert(key, std::move(element));

    if (m_FreeIndices.isEmpty())
    {
        m_FreeIndices.push(m_IndicesToKeys.size());
    }

    const Index nextIndex = m_FreeIndices.top();
    m_FreeIndices.pop();

    m_IndicesToKeys.insert(nextIndex, key);
    m_KeysToIndices.insert(key, nextIndex);

    return true;
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
bool IndexedMap<_Type, _KeyType, _KeyName>::Remove
    (const _KeyType& key) noexcept
{
    if (!m_Data.remove(key))
    {
        qDebug() << "[Error] No value with key " << key;

        return false;
    }

    const Index index = m_KeysToIndices[key];

    if (!m_KeysToIndices.remove(key) || m_IndicesToKeys.remove(index))
    {
        return false;
    }

    m_FreeIndices.push(index);

    return true;
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
const _Type& IndexedMap<_Type, _KeyType, _KeyName>::Unpack
    (OptionalConstRef value) const noexcept
{
    return value.value().get();
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
_Type& IndexedMap<_Type, _KeyType, _KeyName>::Unpack
    (OptionalRef value) noexcept
{
    return value.value().get();
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
typename IndexedMap<_Type, _KeyType, _KeyName>::OptionalConstRef
IndexedMap<_Type, _KeyType, _KeyName>::GetElement
    (const _KeyType& key) const noexcept
{
    if (const auto iter = m_Data.find(key);
        iter != m_Data.end())
    {
        return iter.value();
    }

    qDebug() << "[Error] The value with key: " << key
        << "was not found";

    return std::nullopt;
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
typename IndexedMap<_Type, _KeyType, _KeyName>::OptionalRef
IndexedMap<_Type, _KeyType, _KeyName>::GetElement
    (const _KeyType& key) noexcept
{
    const auto& constThis = static_cast<const IndexedMap*>(this);
    const auto& result = constThis->GetElement(key);

    if (result.has_value())
    {
        return std::ref(const_cast<_Type&>(result.value().get()));
    }

    return std::nullopt;
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
typename IndexedMap<_Type, _KeyType, _KeyName>::OptionalConstRef
IndexedMap<_Type, _KeyType, _KeyName>::GetElement
    (const Index index) const noexcept
{
    if (index >= 0 && index < m_Data.size())
    {
        return GetElement(m_IndicesToKeys[index]);
    }

    qDebug() << "[Error] The index " << index << " is invalid";

    return std::nullopt;
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
typename IndexedMap<_Type, _KeyType, _KeyName>::OptionalRef
IndexedMap<_Type, _KeyType, _KeyName>::GetElement
    (const Index index) noexcept
{
    const auto& constThis = static_cast<const IndexedMap*>(this);
    const auto& result = constThis->GetElement(index);

    if (result.has_value())
    {
        return std::ref(const_cast<_Type&>(result.value().get()));
    }

    return std::nullopt;
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
typename IndexedMap<_Type, _KeyType, _KeyName>::Index
IndexedMap<_Type, _KeyType, _KeyName>::GetIndex(const _KeyType& key)
    const noexcept
{
    if (const auto iter = m_KeysToIndices.find(key);
        iter != m_KeysToIndices.end())
    {
        return iter.value();
    }

    qDebug() << "[Error] No index by key " << key;

    return {};
}

template <class _Type, class _KeyType, _KeyType _Type::* _KeyName>
bool IndexedMap<_Type, _KeyType, _KeyName>::DoesContain
    (const _KeyType& key) const noexcept
{
    return m_Data.contains(key);
}

#endif
