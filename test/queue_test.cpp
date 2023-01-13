/**
 * @file queue_test.cpp
 * @author Ricardo Cardoso
 * 
 * @brief Testing file for Queue class.
 * This file contains the tests for the Queue class. 
 * It tests the constructor and the methods of the class.
 * The methods that are tested are: Push, Pop, Count and Size. 
 * 
 * @version 0.1
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <queue.h>
#include "gtest/gtest.h"

using namespace testing;

/**
 * @brief Test class for the Queue class
 * This class is used to create instances of the Queue class to be used in the tests.
 * 
 */
class QueueTest : public Test {
public:
    Queue<int> *int_queue;              /**< pointer to Queue of ints */
    Queue<std::string> *string_queue;   /**< pointer to Queue of stings */
    Queue<double> *double_queue;        /**< pointer to Queue of doubles */

    /**
     * @brief Setup of the tests.
     * This method is called before each of the tests.
     * Creates Queue objects to be used in the tests.
     * 
     */
    void SetUp() {
        int_queue = new Queue<int>(2);
        string_queue = new Queue<std::string>(2);
        double_queue = new Queue<double>(2);
    }
};

/**
 * @brief Tests the constructor of Queue.
 * 
 * Asserts that the constructor throws an exception when the queue 
 * size is negative and that the size and count of the Queue are
 * the expected ones.
 * 
 */
TEST_F(QueueTest, TestConstructor) {
    EXPECT_THROW(Queue<int>(-1), QueueNegativeSizeException);

    EXPECT_EQ(2, int_queue->Size());
    EXPECT_EQ(0, int_queue->Count());

    EXPECT_EQ(2, string_queue->Size());
    EXPECT_EQ(0, string_queue->Count());

    EXPECT_EQ(2, double_queue->Size());
    EXPECT_EQ(0, double_queue->Count());
}

/**
 * @brief Tests push method to Queue of ints
 * 
 * Asserts that the count of elements is the expected after pushing
 * some elements to the Queue until it gets full. Then assert that
 * QueueFullException is thrown when pushing to a full queue and that 
 * the count remains unchanged.
 * 
 */
TEST_F(QueueTest, TestIntPush) {
    int_queue->Push(1);
    int_queue->Push(2);
    EXPECT_EQ(int_queue->Count(), 2);
    EXPECT_THROW(int_queue->Push(3), QueueFullException);
    EXPECT_EQ(int_queue->Count(), 2);
}

/**
 * @brief Test pop method from Queue of ints
 * 
 * Push some elements to a Queue of ints and then assert that
 * pop method returns the expected object, including std::nullopt
 * when the Queue is empty.
 * 
 */
TEST_F(QueueTest, TestIntPop) {
    int_queue->Push(1);
    int_queue->Push(2);
    EXPECT_EQ(int_queue->Pop(), 1);
    EXPECT_EQ(int_queue->Pop(), 2);
    EXPECT_EQ(int_queue->Pop(), std::nullopt);
}

/**
 * @brief Tests push method to Queue of strings
 * 
 * Asserts that the count of elements is the expected after pushing
 * some elements to the Queue until it gets full. Then assert that
 * QueueFullException is thrown when pushing to a full queue and that 
 * the count remains unchanged.
 * 
 */
TEST_F(QueueTest, TestStringPush) {
    string_queue->Push("hello");
    string_queue->Push("world");
    EXPECT_EQ(string_queue->Count(), 2);
    EXPECT_THROW(string_queue->Push("!"), QueueFullException);
    EXPECT_EQ(string_queue->Count(), 2);
}

/**
 * @brief Test pop method from Queue of strings
 * 
 * Push some elements to a Queue of strings and then assert that
 * pop method returns the expected object, including std::nullopt
 * when the Queue is empty.
 * 
 */
TEST_F(QueueTest, TestStringPop) {
    string_queue->Push("hello");
    string_queue->Push("world");
    EXPECT_EQ(string_queue->Pop(), "hello");
    EXPECT_EQ(string_queue->Pop(), "world");
    EXPECT_EQ(string_queue->Pop(), std::nullopt);
}

/**
 * @brief Tests push method to Queue of doubles
 * 
 * Asserts that the count of elements is the expected after pushing
 * some elements to the Queue until it gets full. Then assert that
 * QueueFullException is thrown when pushing to a full queue and that 
 * the count remains unchanged.
 * 
 */
TEST_F(QueueTest, TestDoublePush) {
  double_queue->Push(1.1);
  double_queue->Push(2.2);
  EXPECT_EQ(double_queue->Count(), 2);
  EXPECT_THROW(double_queue->Push(3.3), QueueFullException);
  EXPECT_EQ(double_queue->Count(), 2);
}

/**
 * @brief Test pop method from Queue of doubles
 * 
 * Push some elements to a Queue of doubles and then assert that
 * pop method returns the expected object, including std::nullopt
 * when the Queue is empty.
 * 
 */
TEST_F(QueueTest, TestDoublePop) {
    double_queue->Push(1.1);
    double_queue->Push(2.2);
    EXPECT_DOUBLE_EQ(double_queue->Pop().value(), 1.1);
    EXPECT_DOUBLE_EQ(double_queue->Pop().value(), 2.2);
    EXPECT_EQ(double_queue->Pop(), std::nullopt);
}

/**
 * @brief Test size method of Queue of ints
 * 
 * Asserts that size remains unchanged and with the correct value 
 * after pushing and popping elements to the Queue.
 * 
 */
TEST_F(QueueTest, TestSize) {
    EXPECT_EQ(int_queue->Size(), 2);
    int_queue->Push(1);
    EXPECT_EQ(int_queue->Size(), 2);
    int_queue->Push(2);
    EXPECT_EQ(int_queue->Size(), 2);
    int_queue->Pop();
    EXPECT_EQ(int_queue->Size(), 2);
    int_queue->Pop();
    EXPECT_EQ(int_queue->Size(), 2);
}

/**
 * @brief Test count method of Queue of ints
 * 
 * Asserts that count is updated with the correct value 
 * after pushing and popping elements to the Queue.
 * 
 */
TEST_F(QueueTest, TestCount) {
    EXPECT_EQ(int_queue->Count(), 0);
    int_queue->Push(1);
    EXPECT_EQ(int_queue->Count(), 1);
    int_queue->Push(2);
    EXPECT_EQ(int_queue->Count(), 2);
    int_queue->Pop();
    EXPECT_EQ(int_queue->Count(), 1);
    int_queue->Pop();
    EXPECT_EQ(int_queue->Count(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}