//
// Created by Rafał Jan Trybus on 27/11/2020.
//

#ifndef UNTITLED1_DIR_H
#define UNTITLED1_DIR_H

#include <filesystem>
#include <iostream>
#include "Command.h"

using namespace std;

class Dir {
public:
    Dir(){}
    Dir(std::string path) : path_(path) {}
    virtual ~Dir() = default;
    virtual void printInfo() = 0;
    virtual void assignPath(string path) = 0;
    virtual void assignFactory(std::shared_ptr<AbstractFactory>) = 0;
    virtual void addFile() = 0;
    virtual void removeFile() = 0;
    virtual void renameFile() = 0;
    static Dir *make_dir(int choice);
    virtual void printTree() = 0;
private:
    string path_;
    std::shared_ptr<AbstractFactory> creator_;
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
    void DisplayFileInfo(const filesystem::directory_entry & entry, string & lead, filesystem::path& file_name);
    void DisplayDirTree(const filesystem::path& pathToShow, int level);
private:
    string path_;
    std::shared_ptr<AbstractFactory> creator_;
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

        cout << "--> WILL PRINT SSH DIR TREE" << endl;

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
private:
    string path_;
    std::shared_ptr<AbstractFactory> creator_;
};




#endif //UNTITLED1_DIR_H
