//
// Created by Marcin Piotrowski on 01.12.2020.
//

#include <gtest/gtest.h>
#include "../classes/Profile.h"
#include "../classes/Command.cpp"

class ProfileTests : public ::testing::Test {
public:
    std::unique_ptr<Profile> profile;

    ProfileTests(){
       profile = std::make_unique<Profile>(nullptr, nullptr, "");
       profile->addDirectories("/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut","/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut2",LOCAL,LOCAL);
    }
};

TEST_F(ProfileTests, dir1Test){
    if(!profile->getDir1()->getFiles().empty()){
        EXPECT_EQ("test (copy)",profile->getDir1()->getFiles().back()->getName());
    } else FAIL();
}

TEST_F(ProfileTests, dir2Test){
    if(!profile->getDir2()->getFiles().empty()){
        EXPECT_EQ("difference",profile->getDir2()->getFiles().back()->getName());
    } else FAIL();
}

TEST_F(ProfileTests, scanTest1){
    profile->scan();
    if(!profile->getDifferences().empty()) {
        EXPECT_EQ(profile->getDifferences().back(), "difference in dir2");
    } else FAIL();
}

TEST_F(ProfileTests, scanTest2){
    profile->scan();
    EXPECT_EQ(profile->getDifferences().size(),1);
}

TEST_F(ProfileTests, addTest){
    testing::internal::CaptureStdout();
    profile->addDirectories("path","path",LOCAL,LOCAL);
    profile->summary();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("\n---------------------------\n#PROFILE SUMMARY:\n#name: \n#LOCAL DIR PATH: path\n#LOCAL DIR PATH: path\n",output);
}

