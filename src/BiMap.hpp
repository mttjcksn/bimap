#pragma once

#include <unordered_map>
#include <functional>
#include <utility>
#include "Serialiser.hpp"

template <typename K, typename V>
class BiMap : Serialiser {
public:

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const K, V>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit iterator(typename std::unordered_map<K, V>::iterator it) : iter(it) {}

        reference operator*() const { return *iter; }
        pointer operator->() { return &(*iter); }

        iterator& operator++() { ++iter; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const iterator& other) const { return iter == other.iter; }
        bool operator!=(const iterator& other) const { return iter != other.iter; }

    private:
        typename std::unordered_map<K, V>::iterator iter;
    };

    iterator begin() { return iterator(keyToValue.begin()); }
    iterator end() { return iterator(keyToValue.end()); }

    void insert(const K& key, const V& value)
    {
        keyToValue[key] = value;
        valueToKey[value] = key;
    }

    V getValue(const K& key)
    {
        return keyToValue.at(key);
    }

    K getKey(V& value)
    {
        return valueToKey.at(value);
    }

    bool keyExists(K& key)
    {
        return (keyToValue.find( key ) != keyToValue.end());
    }    

    bool valueExists(V& value)
    {
        return (valueToKey.find( value ) != valueToKey.end());
    }    

    bool getValue(K& key, V& value)
    {
        auto iter = keyToValue.find(key);
        if (iter != keyToValue.end()) {
            value = iter->second;
            return true; // Key found
        }
        return false; // Key not found
    }

    bool getKey(V& value, K& key)
    {
        auto iter = valueToKey.find(value);
        if (iter != valueToKey.end()) {
            key = iter->second;
            return true; // Value found
        }
        return false; // Value not found
    }

    bool removeKey(const K& key)
    {
        auto valueIter = keyToValue.find(key);
        if (valueIter != keyToValue.end())
        {
            V value = valueIter->second;
            valueToKey.erase(value);
            keyToValue.erase(key);
            return true;
        }
        return false;
    }

    bool removeValue(const V& value)
    {
        auto keyIter = valueToKey.find(value);
        if (keyIter != valueToKey.end())
        {
            K key = keyIter->second;
            keyToValue.erase(key);
            valueToKey.erase(value);
            return true;
        }
        return false;
    }

    void clear()
    {
        keyToValue.clear();
        valueToKey.clear();
    }

    static std::vector<char> serialise(const BiMap& obj)
    {
        std::vector<char> ret;
        Serialiser::appendVector(ret, Serialiser::serialise(obj.keyToValue));
        Serialiser::appendVector(ret, Serialiser::serialise(obj.valueToKey));
        return ret;
    }

    static size_t deserialise(const char* serialisedData, BiMap& objOut)
    {
        char* readHead = (char*)serialisedData;
        readHead += Serialiser::deserialise(readHead, objOut.keyToValue);
        readHead += Serialiser::deserialise(readHead, objOut.valueToKey);
        return readHead-serialisedData;
    }

private:
    std::unordered_map<K, V> keyToValue;
    std::unordered_map<V, K> valueToKey;
};