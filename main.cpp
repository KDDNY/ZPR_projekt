#include <iostream>
#include <filesystem>
// #include <gtest/gtest.h>
// #include "tests/Tests.cpp"


#include "classes/Application.h"

int main(int argc, char *argv[]) {
    Application application;
    //auto local1 = std::make_shared<LocalDirectory>();
    //auto local2 = std::make_shared<LocalDirectory>();
    //ScannerVisitor scannerVisitor;
    //local1->accept(scannerVisitor);

    //Profile profile(local1, local2, "fist profile");

    /* sposób na wylistyowanie zawartości katalogu
    std::string path = "/home/kddny/CLionProjects/untitled1/test_dir";
    for(const auto & entry : std::filesystem::directory_iterator(path)){
        std::cout << entry.path().string().substr(path.length()+1) << std::endl;
    }
    */

   // ::testing::InitGoogleTest(&argc, argv);
 //   return RUN_ALL_TESTS();


 Profile* prof1 = new Profile(nullptr, nullptr,"___TEST PROFILE___");
 prof1->addDirectories("/Users/raftry/Desktop/[ZPR]/testFolder1", "/Users/raftry/Desktop/[ZPR]/testFolder2",1,2);
 prof1->summary();

 delete prof1;

}
