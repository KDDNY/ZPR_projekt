//
// Created by kddny on 09.11.2020.
//

#include <iostream>
#include "Profile.h"
#include <vector>





void Profile::addDirectories(std::string path1, std::string path2,Choice flag1, Choice flag2){
    dir1_ = Dir::make_dir(flag1);
    dir1_->assignPath(path1);
    dir1_->search();
    dir2_ = Dir::make_dir(flag2);
    dir2_->assignPath(path2);
    dir2_->search();
}

Profile::Profile(Dir* directory1, Dir* directory2, std::string name):
        dir1_(directory1), dir2_(directory2), name_(name) { }

void Profile::summary(){

    std::cout << endl << "---------------------------" <<std::endl;
    std::cout << "#PROFILE SUMMARY:" <<std::endl;
    std::cout << "#name: "<< name_ <<std::endl;


    dir1_->printInfo();
    dir1_->printTree();

    dir2_->printInfo();
    dir2_->printTree();
}

std::string Profile::getName() {
    return name_;
}

void Profile::printTree1() {
    dir1_->printTree();
}

void Profile::printTree2() {
    dir2_->printTree();
}

const vector<std::string> &Profile::getDifferences() const {
    return differences;
}

void Profile::scan() {
    lookForDifference(dir1_->getFiles(),dir2_->getFiles());
}

void Profile::lookForDifference(std::vector<std::shared_ptr<File>> vector1, std::vector<std::shared_ptr<File>> vector2) {
    int counter = 0;
    for(const auto& el : vector1){
        if(find(vector2.begin(), vector2.end(), el) != vector2.end()&&el->isDirectory()){
            lookForDifference(el->getFiles(), vector2.at(counter)->getFiles());
            cout << "DUPA" << endl;
        } else {
            differences.emplace_back(el->getName() + " in dir1");
        }
        counter++;
    }
    counter = 0;
    for(const auto& el : vector2){
        if(find(vector1.begin(), vector1.end(), el) != vector1.end()&&el->isDirectory()){
            lookForDifference(el->getFiles(), vector1.at(counter)->getFiles());
        } else {
            differences.emplace_back(el->getName() + " in dir2");
        }
        counter++;
    }
}

Dir *Profile::getDir1() const {
    return dir1_;
}

Dir *Profile::getDir2() const {
    return dir2_;
}

