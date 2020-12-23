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
        dir->search(FIRST);
    }
};

TEST_F(LocalDirTests, searchTest) {
    vector v = dir->getFiles();
    std::string myString = "tekst.txt";
    auto it = find_if(v.begin(), v.end(), [&myString](const shared_ptr<File>& obj) {return obj->getName() == myString;});
    if (it != v.end())
    {
        EXPECT_EQ(it->get()->getName(),myString);
    //    cout << "znaleziono: " << it->get()->getName() << endl;
     //   auto index = std::distance(v.begin(), it);
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
        //    cout << "znaleziono: " << it->get()->getName() << endl;
        //   auto index = std::distance(v.begin(), it);
    } else FAIL();
}

TEST_F(LocalDirTests, getDeeperPathTest) {
    vector v = dir->getFiles().back()->getFiles();
    std::string myString = "WeNeedToGoDeeper";
    std::string path = "/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut/test (copy)";
    auto it = find_if(v.begin(), v.end(),[&myString](const shared_ptr<File> &obj) { return obj->getName() == myString; });
    if (it != v.end()) {
        EXPECT_EQ(it->get()->getPath() + "/" + it->get()->getName(), path + "/" + myString);
        //    cout << "znaleziono: " << it->get()->getName() << endl;
        //   auto index = std::distance(v.begin(), it);
    } else FAIL();
}

TEST_F(LocalDirTests, getDeeperPathTest2) {
    vector v = dir->getFiles().back()->getFiles().back()->getFiles().back()->getFiles();
    std::string myString = "20z_Harmonogram_laboratorium_TWCz.pdf";
    std::string path = "/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut/test (copy)/WeNeedToGoDeeper/muchDeeper";
    auto it = find_if(v.begin(), v.end(),[&myString](const shared_ptr<File> &obj) { return obj->getName() == myString; });
    if (it != v.end()) {
        EXPECT_EQ(it->get()->getPath() + "/" + it->get()->getName(), path + "/" + myString);
        //    cout << "znaleziono: " << it->get()->getName() << endl;
        //   auto index = std::distance(v.begin(), it);
    } else FAIL();
}

TEST_F(LocalDirTests, TWCzhashGenTest){
    vector v = dir->getFiles().back()->getFiles().back()->getFiles().back()->getFiles();
    v.at(2)->genHash();
    string hash = v.back()->getHash();
    EXPECT_EQ("99577fc6825a6e791dec315070da55d501d809f7", hash);
    if(HasFailure()){
        for(const auto el : v){
            cout << el->getName() << endl;
            cout << el->getPath() << endl;
        }
    }
}

/*
TEST_F(LocalDirTests, treeTest){
    testing::internal::CaptureStdout();
    dir->printTree();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("[+] \"test\"\n[+] \"test (copy)\"\n   [+] \"WeNeedToGoDeeper\"\n",output);
}
*/

TEST_F(LocalDirTests, checkIfNotEmpty){
    EXPECT_FALSE(dir->getFiles().empty());
}

TEST_F(LocalDirTests, checkIfFileExist){
    if(!dir->getFiles().empty()){
        EXPECT_EQ("test (copy)",dir->getFiles().back()->getName());
    } else FAIL();
}

TEST_F(LocalDirTests, weNeedToGoDeeperTest){
    if(!dir->getFiles().back()->files_.empty()){
        EXPECT_EQ("WeNeedToGoDeeper",dir->getFiles().back()->getFiles().back()->getName());
    } else FAIL();
}

TEST_F(LocalDirTests, isDirectoryTest){
    if(!dir->getFiles().back()->files_.empty()){
        EXPECT_TRUE(dir->getFiles().back()->getFiles().back());
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
