//
// Created by kddny on 09.11.2020.
//

#include <iostream>
#include "Profile.h"
#include <vector>
#include <bits/stdc++.h>



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
    vector<shared_ptr<File>> v(getDir1()->getFiles().size() + getDir2()->getFiles().size());
    vector<shared_ptr<File>>::iterator it, st;
    //finding the common elements
    it = set_intersection(getDir1()->getFiles().begin(), getDir1()->getFiles().end(), getDir2()->getFiles().begin(), getDir2()->getFiles().end(), v.begin());
    for (st = v.begin(); st != it; ++st) {
        differences.push_back(st->get()->getName());
    }
}

Dir *Profile::getDir1() const {
    return dir1_;
}

Dir *Profile::getDir2() const {
    return dir2_;
}
