//
// Created by Marcin Piotrowski on 01.12.2020.
//

#include <gtest/gtest.h>
#include "../classes/Application.h"


TEST(ApplicationTests, ApplicationStartsEmpty){
    EXPECT_TRUE(Application::getProfiles().empty());
}


TEST(ApplicationTests, AddProfile){
    Profile* prof1 = new Profile(nullptr, nullptr,"___TEST PROFILE___");
    Application::addProfile(prof1);
    EXPECT_FALSE(Application::getProfiles().empty());
}

