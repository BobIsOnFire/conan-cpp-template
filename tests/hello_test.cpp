#include "hello.h"

#include <gtest/gtest.h>

TEST(HelloTest, simple)
{
    EXPECT_EQ(get_hello_string(), "This is a hello from library!");
}
