//
// Created by Marcin Piotrowski on 01.12.2020.
//

#include <gtest/gtest.h>
#include "../classes/Dir.h"

TEST(DirTests, AddLocal){
    auto dir = Dir::make_dir(LOCAL);
    EXPECT_TRUE(dynamic_cast<LocalDir*>(dir));
}

TEST(DirTests, AddSSH){
    auto dir = Dir::make_dir(SSH);
    EXPECT_TRUE(dynamic_cast<SshDir*>(dir));
}

TEST(DirTests, Assign){
    auto dir = Dir::make_dir(LOCAL);
    dir->assignPath("path");
    testing::internal::CaptureStdout();
    dir->printInfo();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("#LOCAL DIR PATH: path\n",output);
}

TEST(DirTests, LocalAddCommand){
    auto dir = Dir::make_dir(LOCAL);
    testing::internal::CaptureStdout();
    dir->addFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Local add\n",output);
}

TEST(DirTests, LocalRemoveCommand){
    auto dir = Dir::make_dir(LOCAL);
    testing::internal::CaptureStdout();
    dir->removeFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Local delete\n",output);
}

TEST(DirTests, LocalRenameCommand){
    auto dir = Dir::make_dir(LOCAL);
    testing::internal::CaptureStdout();
    dir->renameFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Local rename\n",output);
}

TEST(DirTests, SSHRenameCommand){
    auto dir = Dir::make_dir(SSH);
    testing::internal::CaptureStdout();
    dir->renameFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("SSH rename\n",output);
}

TEST(DirTests, SSHRemoveCommand){
    auto dir = Dir::make_dir(SSH);
    testing::internal::CaptureStdout();
    dir->removeFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("SSH delete\n",output);
}

TEST(DirTests, SSHaddCommand){
    auto dir = Dir::make_dir(SSH);
    testing::internal::CaptureStdout();
    dir->addFile();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("SSH add\n",output);
}