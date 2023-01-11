#include "queue.h"
#include "gtest/gtest.h"




TEST(QueueTests, DummyTest) {
    Queue<int> queue(3);
    EXPECT_EQ(queue.Count(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}