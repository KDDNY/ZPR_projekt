//
// Created by kddny on 09.11.2020.
//

#include <iostream>
#include "Profile.h"
#include <vector>


void Profile::addDirectories(std::string path1, std::string path2,unsigned int flag1, unsigned int flag2){
    dir1_ = Dir::make_dir(flag1);
    dir1_->assignPath(path1);

    dir2_ = Dir::make_dir(flag2);
    dir2_->assignPath(path2);
}

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
