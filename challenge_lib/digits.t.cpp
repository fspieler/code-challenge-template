#include <debug.h>
#include <digits.h>
#include <gtest/gtest.h>

TEST(digits,zero_has_zero_decimal_digits)
{
    ASSERT_EQ(0, numDigitsDecimal(0));
}
TEST(digits,five_has_one_digits)
{
    ASSERT_EQ(1, numDigitsDecimal(5));
}
TEST(digits,twenty_three_has_two_decimal_digits)
{
    ASSERT_EQ(2, numDigitsDecimal(23));
}
TEST(digits,eleven_million_three_hundred_forty_six_thousand_two_hundred_forteen_has_eight_decimal_digits)
{
    ASSERT_EQ(8, numDigitsDecimal(11346214));
}
TEST(digits,zero_has_zero_binary_digits)
{
    ASSERT_EQ(0, numDigitsBinary(0));
}
TEST(digits,five_has_three_binary_digits)
{
    ASSERT_EQ(3, numDigitsBinary(5));
}
TEST(digits,twenty_three_has_four_binary_digits)
{
    ASSERT_EQ(5, numDigitsBinary(23));
}
TEST(digits,one_hundred_eleven_has_six_binary_digits)
{
    ASSERT_EQ(7, numDigitsBinary(111));
}
