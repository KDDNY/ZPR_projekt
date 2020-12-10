//
// Created by Marcin Piotrowski on 01.12.2020.
//

#include <gtest/gtest.h>
#include "../classes/Dir.h"
#include "../classes/Command.cpp"

class LocalDirTests : public ::testing::Test{
public:
    std::unique_ptr<LocalDir> dir;
    LocalDirTests(){
        dir = std::make_unique<LocalDir>();
        dir->assignFactory(std::make_shared<LocalFactory>());
        dir->assignPath("/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut");
    }
};

TEST_F(LocalDirTests, treeTest){
    testing::internal::CaptureStdout();
    dir->printTree();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("[+] \"test\"\n[+] \"test (copy)\"\n",output);
}

TEST_F(LocalDirTests, checkIfNotEmpty){
    dir->search();
    EXPECT_FALSE(dir->getFiles().empty());
}

TEST_F(LocalDirTests, checkIfFileExist){
    dir->search();

    if(!dir->getFiles().empty()){
        std::vector files = dir->getFiles();
        EXPECT_EQ("test (copy)",dir->getFiles().back());
    } else FAIL();
}


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
