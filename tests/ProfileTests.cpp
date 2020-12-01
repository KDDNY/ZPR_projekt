//
// Created by kddny on 01.12.2020.
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
    profile->addDirectories("path","path",1,1);
}

