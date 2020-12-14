//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_PROFILE_H
#define UNTITLED1_PROFILE_H



#include "Dir.h"

class Profile {
public:
    Profile(Dir* directory1, Dir* directory2, std::string name);
    void scan();
    void addDirectories(std::string path1, std::string path2,Choice flag1, Choice flag2);
    void summary();
    void printTree1();
    void printTree2();
    ~Profile(){delete dir1_; delete dir2_;}
    std::string getName();
    const vector<std::string> &getDifferences() const;
    Dir *getDir1() const;
    Dir *getDir2() const;
    bool findInVector(std::vector<std::shared_ptr<File>> vector1, std::shared_ptr<File> file);
    int getIndex(std::vector<std::shared_ptr<File>> vector1, std::shared_ptr<File> file);
private:
    std::vector<std::string> differences;
    std::string name_;
    Dir* dir1_;
    Dir* dir2_;
    void lookForDifference(std::vector<std::shared_ptr<File>> vector1, std::vector<std::shared_ptr<File>> vector2, int x);
};


#endif //UNTITLED1_PROFILE_H
