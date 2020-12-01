//
// Created by kddny on 01.12.2020.
//

#include <gtest/gtest.h>
#include "../classes/Dir.h"

TEST(DirTests, AddLocal){
    auto dir = Dir::make_dir(1);
    EXPECT_TRUE(dynamic_cast<localDir*>(dir));
}

TEST(DirTests, AddSSH){
    auto dir = Dir::make_dir(2);
    EXPECT_TRUE(dynamic_cast<sshDir*>(dir));
}

TEST(DirTests, Assign){
    auto dir = Dir::make_dir(1);
    dir->assignPath("path");
    testing::internal::CaptureStdout();
    dir->printInfo();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("#LOCAL DIR PATH: path\n",output);
}

