//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_PROFILE_H
#define UNTITLED1_PROFILE_H


#include "Directory.h"

class Profile {
public:
    Profile(std::shared_ptr<Directory> directory1, std::shared_ptr<Directory> directory2, std::string name):
    directory1_(directory1), directory2_(directory2), name_(name) { }
    void scan();
private:
    std::string name_;
    std::shared_ptr<Directory> directory1_;
    std::shared_ptr<Directory> directory2_;
};


#endif //UNTITLED1_PROFILE_H
