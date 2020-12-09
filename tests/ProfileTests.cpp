//
// Created by Marcin Piotrowski on 01.12.2020.
//

#include <gtest/gtest.h>
#include "../classes/Profile.h"

class ProfileTests : public ::testing::Test {
public:
    std::unique_ptr<Profile> profile;
    ProfileTests(){
       profile = std::make_unique<Profile>(nullptr, nullptr, "");
    }
};

TEST_F(ProfileTests, addTest){
    testing::internal::CaptureStdout();
    profile->addDirectories("path","path",LOCAL,LOCAL);
    profile->summary();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("\n---------------------------\n#PROFILE SUMMARY:\n#name: \n#LOCAL DIR PATH: path\n#LOCAL DIR PATH: path\n",output);
}

