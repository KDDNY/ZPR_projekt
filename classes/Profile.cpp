//
// Created by kddny on 09.11.2020.
//

#include <iostream>
#include "Profile.h"
#include <vector>





void Profile::addDirectories(std::string path1, std::string path2,Choice flag1, Choice flag2){
    dir1_ = Dir::make_dir(flag1);
    dir1_->assignPath(path1);
    dir1_->search(FIRST);
    dir2_ = Dir::make_dir(flag2);
    dir2_->assignPath(path2);
    dir2_->search(SECOND);
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

/*
const vector<std::string> &Profile::getDifferences() const {
    return differences;
}
*/

const vector<shared_ptr<File>> &Profile::getDif() const{
    return differences_;
}

void Profile::scan() {
    dir1_->search(FIRST);
    dir2_->search(SECOND);
    differences_.clear();
    lookForDifference(dir1_->getFiles(),dir2_->getFiles());
    lookForDifference(dir2_->getFiles(),dir1_->getFiles());
}

void Profile::lookForDifference(std::vector<std::shared_ptr<File>> vector1, std::vector<std::shared_ptr<File>> vector2) {
    int index;
    for(const auto& el : vector1){
        index = getIndex(vector2, el);
        if(index >= 0 &&el->isDirectory()){
            lookForDifference(el->getFiles(), vector2.at(index)->getFiles());
        } else if (index==-1){
            string name = el->getName();
 //           differences.emplace_back(el->getName() + " in dir" + to_string(el->which_dir_));
            differences_.emplace_back(el);
        }
    }
}

int Profile::getIndex(std::vector<std::shared_ptr<File>> vector1, std::shared_ptr<File> file) {
    for(int i=0; i<vector1.size(); i++){
        string name = file->getName();
        string name2 = vector1.at(i)->getName();
        int xd = vector1.size();
        if(vector1.at(i)->getName() ==file->getName()){
            return i;
        }
    }
    return -1;
}

bool Profile::findInVector(std::vector<std::shared_ptr<File>> vector1, std::shared_ptr<File> file) {
    for(const auto& el : vector1){
        if(el->getName()==file->getName()){
            return true;
        }
    }
    return false;
}


Dir *Profile::getDir1() const {
    return dir1_;
}

Dir *Profile::getDir2() const {
    return dir2_;
}


