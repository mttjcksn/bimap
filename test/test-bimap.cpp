#include "gtest/gtest.h"
#include "BiMap.hpp"  // Adjust the path according to your project structure

class BiMapTest : public ::testing::Test {
protected:
    BiMap<int, std::string> biMap;
};

// Test insert and retrieve value by key
TEST_F(BiMapTest, InsertAndRetrieveByKey) {
    biMap.insert(1, "one");
    int key = 1;
    ASSERT_TRUE(biMap.keyExists(key));
    EXPECT_EQ(biMap.getValue(key), "one");
}

// Test retrieve key by value
TEST_F(BiMapTest, RetrieveKeyByValue) {
    biMap.insert(2, "two");
    std::string value = "two";
    ASSERT_TRUE(biMap.valueExists(value));
    EXPECT_EQ(biMap.getKey(value), 2);
}

// Test non-existent key and value lookup
TEST_F(BiMapTest, NonExistentKeyAndValue) {
    int key = 3;
    std::string value = "three";
    EXPECT_FALSE(biMap.keyExists(key));
    EXPECT_FALSE(biMap.valueExists(value));
}

// Test getValue with reference
TEST_F(BiMapTest, GetValueWithReference) {
    biMap.insert(4, "four");
    int key = 4;
    std::string value;
    ASSERT_TRUE(biMap.getValue(key, value));
    EXPECT_EQ(value, "four");
}

// Test getKey with reference
TEST_F(BiMapTest, GetKeyWithReference) {
    biMap.insert(5, "five");
    std::string value = "five";
    int key;
    ASSERT_TRUE(biMap.getKey(value, key));
    EXPECT_EQ(key, 5);
}

// Test removing by key
TEST_F(BiMapTest, RemoveByKey) {
    biMap.insert(6, "six");
    int key = 6;
    ASSERT_TRUE(biMap.removeKey(key));
    EXPECT_FALSE(biMap.keyExists(key));
    std::string value = "six";
    EXPECT_FALSE(biMap.valueExists(value));
}

// Test removing by value
TEST_F(BiMapTest, RemoveByValue) {
    biMap.insert(7, "seven");
    std::string value = "seven";
    ASSERT_TRUE(biMap.removeValue(value));
    int key = 7;
    EXPECT_FALSE(biMap.keyExists(key));
    EXPECT_FALSE(biMap.valueExists(value));
}

// Test clear functionality
TEST_F(BiMapTest, Clear) {
    biMap.insert(8, "eight");
    biMap.insert(9, "nine");
    biMap.clear();
    int key1 = 8;
    int key2 = 9;
    std::string value1 = "eight";
    std::string value2 = "nine";
    EXPECT_FALSE(biMap.keyExists(key1));
    EXPECT_FALSE(biMap.keyExists(key2));
    EXPECT_FALSE(biMap.valueExists(value1));
    EXPECT_FALSE(biMap.valueExists(value2));
}

// Test iterator functionality
TEST_F(BiMapTest, Iterator) {
    biMap.insert(10, "ten");
    biMap.insert(11, "eleven");

    std::unordered_map<int, std::string> expected = { {10, "ten"}, {11, "eleven"} };
    
    for (auto it = biMap.begin(); it != biMap.end(); ++it) {
        EXPECT_EQ(expected[it->first], it->second);
    }
}

// Test serialization and deserialization
TEST_F(BiMapTest, SerializationAndDeserialization) {
    biMap.insert(12, "twelve");
    biMap.insert(13, "thirteen");

    std::vector<char> serializedData = BiMap<int, std::string>::serialise(biMap);
    
    BiMap<int, std::string> deserializedBiMap;
    BiMap<int, std::string>::deserialise(serializedData.data(), deserializedBiMap);

    int key1 = 12;
    int key2 = 13;
    EXPECT_TRUE(deserializedBiMap.keyExists(key1));
    EXPECT_TRUE(deserializedBiMap.keyExists(key2));
    EXPECT_EQ(deserializedBiMap.getValue(key1), "twelve");
    EXPECT_EQ(deserializedBiMap.getValue(key2), "thirteen");
}
