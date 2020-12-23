//
// Created by kddny on 10.12.2020.
//

#include <string>
#include <vector>
#include <memory>
#include <openssl/sha.h> //For genrating Hash function
#include <fstream> // for reading file


#ifndef UNTITLED1_FILE_H
#define UNTITLED1_FILE_H

#endif //UNTITLED1_FILE_H

enum WhichDir{
    FIRST, SECOND
};

class File{
public:
    File() = default;
    File(const std::string &name, bool directory, WhichDir whichDir);
    WhichDir which_dir_;
    std::vector<std::shared_ptr<File>> files_;

    void setParentDir(WhichDir parentDir);
    void setPath(const std::string &path);
    void genHash();

    bool isDirectory() const;
    const std::string &getName() const;
    const std::vector<std::shared_ptr<File>> &getFiles() const;
    const std::string &getPath() const;
    WhichDir getWhichDir() const;
    const std::string &getHash() const;
private:
    std::string name_;
    std::string path_;
    bool directory_;
    std::string hash_;
};

