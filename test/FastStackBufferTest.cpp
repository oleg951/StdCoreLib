#include "gtest/gtest.h"

#include "FastStackBuffer.h"

class Fixture: public ::testing::Test {
protected:
    FastStackBuffer<int, 100> stackBuffer {};
};

TEST_F(Fixture, stack_overflow_test) {
    ASSERT_THROW(stackBuffer.pop(), UserException);
    ASSERT_THROW(stackBuffer.top(), UserException);

    for (int i = 0; i < 100; ++i) {
        stackBuffer.push(i);
    }

    ASSERT_THROW(stackBuffer.push(100), UserException);
}

TEST_F(Fixture, fill_stack_buffer_test) {
    stackBuffer.push(0);
    stackBuffer.push(1);
    stackBuffer.push(2);

    ASSERT_EQ(stackBuffer.pop(), 2);
    ASSERT_EQ(stackBuffer.pop(), 1);
    ASSERT_EQ(stackBuffer.pop(), 0);
}

TEST_F(Fixture, stack_buffer_is_empty_test) {
    ASSERT_TRUE(stackBuffer.isEmpty());
}

TEST_F(Fixture, stack_buffer_is_full_test) {
    for (int i = 0; i < 100; ++i) {
        stackBuffer.push(i);
    }

    ASSERT_TRUE(stackBuffer.isFull());
}
