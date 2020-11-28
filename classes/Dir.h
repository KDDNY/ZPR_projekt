//
// Created by Rafał Jan Trybus on 27/11/2020.
//

#ifndef UNTITLED1_DIR_H
#define UNTITLED1_DIR_H

#include <filesystem>
#include <iostream>

using namespace std;


class Dir {
public:

    Dir(){}
    Dir(std::string path) : path_(path) {}
    virtual ~Dir() = default;
    virtual void printInfo() = 0;
    virtual void assignPath(string path) = 0;
    static Dir *make_dir(int choice);
    virtual void printTree() = 0;



private:
    string path_;

};



class localDir : public Dir
{
public:
    void printInfo(){
        std::cout << "#LOCAL DIR PATH: " << path_ <<std::endl;
    }
    void assignPath(string path){
        path_ = path;

    }
    void printTree(){

        std::filesystem::path pathToShow(path_);
        DisplayDirTree(pathToShow,0);

    }
    void DisplayFileInfo(const filesystem::directory_entry & entry, string & lead, filesystem::path& file_name);
    void DisplayDirTree(const filesystem::path& pathToShow, int level);
private:
    string path_;
};


class sshDir: public Dir
{
public:
    void printInfo(){
        std::cout << "#SSH DIR PATH: " << path_ <<std::endl;
    }
    void assignPath(string path){

        path_ = path;

    }
    void printTree(){

        cout << "--> WILL PRINT SSH DIR TREE";

    }
private:
    string path_;
};




#endif //UNTITLED1_DIR_H
