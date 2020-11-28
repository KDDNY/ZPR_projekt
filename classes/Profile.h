//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_PROFILE_H
#define UNTITLED1_PROFILE_H



#include "Dir.h"

class Profile {
public:
    Profile(Dir* directory1, Dir* directory2, std::string name):
    dir1_(directory1), dir2_(directory2), name_(name) { }
    void scan();
    void addDirectories(std::string path1, std::string path2,unsigned int flag1, unsigned int flag2);
    void summary();
    ~Profile(){delete dir1_; delete dir2_;}
    std::string getName();
private:
    std::string name_;
    Dir* dir1_;
    Dir* dir2_;
};


#endif //UNTITLED1_PROFILE_H
