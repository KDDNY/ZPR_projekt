//
// Created by kddny on 10.12.2020.
//
#ifndef UNTITLED1_FILE_H
#define UNTITLED1_FILE_H

#include <string>
#include <vector>
#include <memory>
//#include <openssl/sha.h>
#include <fstream>
#include "FileCommandFactory.h"

enum WhichDir{
    FIRST, SECOND
};

enum Action{
    COPY, REMOVE, SKIP
};

class File{
public:
    File() = default;
    File(const std::string &name, bool directory, WhichDir whichDir);
    File(const std::string &name, bool directory, WhichDir whichDir, std::string home_dir_path);
    WhichDir which_dir_;
    std::vector<std::shared_ptr<File>> files_;

    void genHash();
    void setParentDir(WhichDir parentDir);
    void setPath(const std::string &path);
    void setAction(Action action);
    void setCreator(std::shared_ptr<LocalFileCommandFactory> creator);
    bool isDirectory() const;

    const std::string &getName() const;
    const std::vector<std::shared_ptr<File>> &getFiles() const;
    const std::string &getPath() const;
    std::string getRelPath();
    WhichDir getWhichDir() const;
    const std::string &getHash() const;
    Action getAction() const;
    std::shared_ptr<FileCommand> generateCommand();
private:
    std::string name_;
    std::string path_;
    std::string home_dir_path_;
    bool directory_;
    std::string hash_;
    Action action = COPY;
    std::shared_ptr<FileCommandFactory> creator_;
};

#endif //UNTITLED1_FILE_H
