#include <iostream>
#include <gtest/gtest.h>
#include "../classes/Application.h"
#include "../GUI classes/StartFrame.h"
#include "wx/wx.h"


TEST(ApplicationTest, ApplicationStartsEmpty){
    EXPECT_TRUE(Application::getProfiles().empty());
}

TEST(ApplicationTest, AddProfile){
    Profile* prof1 = new Profile(nullptr, nullptr,"___TEST PROFILE___");
    Application::add_profile(prof1);
    EXPECT_FALSE(Application::getProfiles().empty());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

