/**
 * @file queue_test.cpp
 * @author Ricardo Cardoso
 * @brief Testing file for Queue class.
 * @version 0.1
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <queue.h>
#include "gtest/gtest.h"


TEST(QueueTests, Constructor) {
    Queue<int> queue1(-1);
    Queue<char> queue2(0);
    Queue<float> queue3(2);
    Queue<int> queue4(2);
    EXPECT_EQ(queue1.Count(), 0) << queue1.Count();
    EXPECT_EQ(queue1.Size(), 0);
}

TEST(QueueTests, Push) {
    Queue<int> queue(3);
    EXPECT_EQ(queue.Count(), 0);
}

TEST(QueueTests, Pop) {
    Queue<int> queue(3);
    EXPECT_EQ(queue.Count(), 0);
}

TEST(QueueTests, Count) {
    Queue<int> queue(3);
    EXPECT_EQ(queue.Count(), 0);
}

TEST(QueueTests, Size) {
    Queue<int> queue(3);
    EXPECT_EQ(queue.Count(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}