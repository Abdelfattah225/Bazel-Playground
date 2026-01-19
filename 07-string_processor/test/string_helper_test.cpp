// test/string_helper_test.cpp
#include <gtest/gtest.h>
#include "utils/string_helper.hpp"

TEST(StringHelperTest, EmptyStringReturnsTrue) {
    StringHelper helper;
    EXPECT_TRUE(helper.isEmpty(""));
}

TEST(StringHelperTest, NonEmptyStringReturnsFalse) {
    StringHelper helper;
    EXPECT_FALSE(helper.isEmpty("hello"));
}

TEST(StringHelperTest, LengthReturnsCorrectValue) {
    StringHelper helper;
    EXPECT_EQ(helper.length("hello"), 5);
    EXPECT_EQ(helper.length(""), 0);
}

TEST(StringHelperTest, ToUpperConvertsCorrectly) {
    StringHelper helper;
    EXPECT_EQ(helper.toUpper("hello"), "HELLO");
    EXPECT_EQ(helper.toUpper("World"), "WORLD");
}