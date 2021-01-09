//
// Created by kddny on 10.12.2020.
//

#include <array>
#include "File.h"

using namespace std;

const std::string &File::getName() const {
    return name_;
}

File::File(const std::string &name, bool directory, WhichDir whichDir)
: name_(name) , directory_(directory), which_dir_(whichDir){

}

File::File(const string &name, bool directory, WhichDir whichDir, std::string home_dir_path)
: name_(name) , directory_(directory), which_dir_(whichDir) , home_dir_path_(home_dir_path) {
}

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

Action File::getAction() const {
    return action;
}

void File::setAction(Action action) {
    File::action = action;
}

void File::genHash() {
//    std::string *buffer = new std::string;
//    buffer->reserve(1024);
//    std::fstream fp;
//
//    fp.open(path_ + "/" + name_,std::ios::in);
//    if(!(fp.is_open())){
//        fprintf(stderr,"Unable to open the file\n");
//        exit(EXIT_FAILURE);
//    }
//    else {
//        std::string line;
//        while(fp >> line){
//            buffer->append(line);
//        }
//    }
//    fp.close();
//
//    std::array<unsigned char,SHA_DIGEST_LENGTH> digest;
//    SHA_CTX ctx;
//    SHA1_Init(&ctx);
//    SHA1_Update(&ctx, buffer->c_str(), buffer->size());
//    SHA1_Final(digest.data(),&ctx);
//    delete buffer;
//    std::array<char,SHA_DIGEST_LENGTH * 2 +1> mdString;
//    for(int i = 0 ; i < SHA_DIGEST_LENGTH ; ++i) {
//        sprintf(&(mdString[i*2]),"%02x",(unsigned int)digest[i]);
//    }
//    hash_ = mdString.data();
}

void File::setCreator(shared_ptr<LocalFileCommandFactory> creator) {
    creator_ = creator;
}

void File::setCreatorSSH(shared_ptr<SSHFileCommandFactory> creator) {
    creator_ = creator;
}

std::shared_ptr<FileCommand> File::generateCommand() {
    return creator_->createAction(*this);
}

string File::getRelPath(){
    string out = path_.substr(home_dir_path_.length(), path_.length());
    return out;
}

