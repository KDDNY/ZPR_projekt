//
// Created by kddny on 10.12.2020.
//

#include "File.h"

const std::string &File::getName() const {
    return name_;
}

File::File(const std::string &name, bool directory, WhichDir whichDir)
: name_(name) , directory_(directory), which_dir_(whichDir){}

const std::vector<std::shared_ptr<File>> &File::getFiles() const {
    return files_;
}

bool File::isDirectory() const {
    return directory_;
}

void File::setParentDir(WhichDir parentDir) {
    which_dir_ = parentDir;
}

const std::string &File::getPath() const {
    return path_;
}

void File::setPath(const std::string &path) {
    File::path_ = path;
}

WhichDir File::getWhichDir() const {
    return which_dir_;
}

const std::string &File::getHash() const {
    return hash_;
}

void File::genHash() {

}
