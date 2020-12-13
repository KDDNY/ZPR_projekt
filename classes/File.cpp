//
// Created by kddny on 10.12.2020.
//

#include "File.h"

const std::string &File::getName() const {
    return name_;
}

File::File(const std::string &name, bool directory) : name_(name) ,  directory_(directory){}

const std::vector<std::shared_ptr<File>> &File::getFiles() const {
    return files_;
}

bool File::isDirectory() const {
    return directory_;
}
