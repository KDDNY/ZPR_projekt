//
// Created by Rafał Jan Trybus on 27/11/2020.
//

#ifndef UNTITLED1_DIR_H
#define UNTITLED1_DIR_H

#include <filesystem>
#include <iostream>
#include "Command.h"

using namespace std;

enum Choice{
    LOCAL, SSH
};

class Dir {
public:
    Dir(){}
    Dir(std::string path) : path_(path) {}
    virtual ~Dir() = default;
    virtual void printInfo() = 0;
    void assignPath(string path){
        path_ = path;

    }
    void assignFactory(std::shared_ptr<AbstractFactory> factory) {
        creator_ = factory;
    }
    void addFile(){
        std::shared_ptr<Command> command = creator_->createAdd();
        command->execute();
    }
    void removeFile(){
        std::shared_ptr<Command> command = creator_->createRemove();
        command->execute();
    }
    void renameFile(){
        std::shared_ptr<Command> command = creator_->createRename();
        command->execute();
    }
    static Dir *make_dir(Choice flag);
    virtual void printTree() = 0;
protected:
    string path_;
    std::shared_ptr<AbstractFactory> creator_;
};

class LocalDir : public Dir{
public:
    void printInfo(){
        std::cout << "#LOCAL DIR PATH: " << path_ <<std::endl;
    }
    void printTree(){

        std::filesystem::path pathToShow(path_);
        DisplayDirTree(pathToShow,0);

    }
    void DisplayFileInfo(const filesystem::directory_entry & entry, string & lead, filesystem::path& file_name);
    void DisplayDirTree(const filesystem::path& pathToShow, int level);
};


class SshDir: public Dir{
public:
    void printInfo(){
        std::cout << "#SSH DIR PATH: " << path_ <<std::endl;
    }
    void printTree(){

        cout << "--> WILL PRINT SSH DIR TREE" << endl;

    }
};




#endif //UNTITLED1_DIR_H
