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
       profile->addDirectories("/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut","/home/kddny/Desktop/ZPR/ZPR_projekt/tests/cmake-build-debug/dut2",LOCAL,LOCAL);
    }
};

TEST_F(ProfileTests, dir1Test){
    vector v = profile->getDir1()->getFiles();
    string myString = "test";
    auto it = find_if(v.begin(), v.end(), [&myString](const shared_ptr<File>& obj) {return obj->getName() == myString;});
    if (it != v.end())
    {
        EXPECT_EQ(it->get()->getName(),myString);
        //    cout << "znaleziono: " << it->get()->getName() << endl;
        //   auto index = std::distance(v.begin(), it);
    } else FAIL();
}

TEST_F(ProfileTests, dir2Test){
    if(!profile->getDir2()->getFiles().empty()){
        EXPECT_EQ("difference",profile->getDir2()->getFiles().back()->getName());
    } else FAIL();
}

TEST_F(ProfileTests, findInVectorTest){
    profile->scan();
    std::vector<std::shared_ptr<File>> vector1;
    std::vector<std::shared_ptr<File>> vector2;
    vector1 = profile->getDir1()->getFiles();
    vector2 = profile->getDir2()->getFiles();
    EXPECT_TRUE(profile->findInVector(vector1,vector2.at(0)));
}

/*
TEST_F(ProfileTests, scanTest1){
    profile->scan();
    if(!profile->getDifferences().empty()) {
        EXPECT_EQ(profile->getDifferences().back(), "difference in dir1");
    } else FAIL();
}

TEST_F(ProfileTests, scanTest2){
    profile->scan();
    for(const auto& diff : profile->getDifferences()){
        cout << diff << endl;
    }
    EXPECT_EQ(profile->getDifferences().size(),6);
}
*/

TEST_F(ProfileTests, betterscanTest1){
    profile->scan();
    if(!profile->getDif().empty()) {
        EXPECT_EQ(profile->getDif().back()->getName(), "difference");
    } else FAIL();
}

/*
TEST_F(ProfileTests, betterscanTest2){
    profile->scan();

    EXPECT_EQ(profile->getDif().size(),7);
    if(HasFailure()){
    for(const auto& diff : profile->getDif()){
        cout << diff->getName() << " in dir" <<diff->which_dir_ <<endl;
    }}
}
*/

TEST_F(ProfileTests, hashCompareTest){
    profile->scan();

}

/*
TEST_F(ProfileTests, addTest){
    testing::internal::CaptureStdout();
    profile->addDirectories("path","path",LOCAL,LOCAL);
    profile->summary();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("\n---------------------------\n#PROFILE SUMMARY:\n#name: \n#LOCAL DIR PATH: path\n#LOCAL DIR PATH: path\n",output);
}
*/
