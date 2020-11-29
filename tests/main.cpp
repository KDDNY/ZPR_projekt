#include <iostream>
#include <gtest/gtest.h>
#include "../classes/Application.h"

TEST(test, test1){
   EXPECT_EQ(nullptr,Application::getProfiles());
}

TEST(test , test2){
    EXPECT_EQ(1,0);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

