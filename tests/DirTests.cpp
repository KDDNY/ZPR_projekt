//
// Created by Marcin Piotrowski on 01.12.2020.
//

#include <gtest/gtest.h>
#include "../classes/Dir.h"

class LocalDirTests : public ::testing::Test{
public:
    std::unique_ptr<LocalDir> dir;
    LocalDirTests(){
        dir = std::make_unique<LocalDir>();
        dir->assignPath("/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut");
        dir->search(FIRST);
    }
};

TEST_F(LocalDirTests, searchTest) {
    vector v = dir->getFiles();
    std::string myString = "tekst.txt";
    auto it = find_if(v.begin(), v.end(), [&myString](const shared_ptr<File>& obj) {return obj->getName() == myString;});
    if (it != v.end())
    {
        EXPECT_EQ(it->get()->getName(),myString);;
    } else FAIL();
}

TEST_F(LocalDirTests, getPathTests){
    vector v = dir->getFiles();
    std::string myString = "tekst.txt";
    std::string path = "/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut";
    auto it = find_if(v.begin(), v.end(), [&myString](const shared_ptr<File>& obj) {return obj->getName() == myString;});
    if (it != v.end())
    {
        EXPECT_EQ(it->get()->getPath()+"/"+it->get()->getName(),path + "/tekst.txt");

    } else FAIL();
}

TEST_F(LocalDirTests, checkIfNotEmpty){
    EXPECT_FALSE(dir->getFiles().empty());
}

TEST_F(LocalDirTests, isDirectoryTest){
    vector v = dir->getFiles();
    string myString = "test";
    auto it = find_if(v.begin(), v.end(), [&myString](const shared_ptr<File>& obj) {return obj->getName() == myString;});
    if (it != v.end())
    {
        EXPECT_TRUE(it->get()->isDirectory());
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
