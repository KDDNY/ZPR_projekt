//
// Created by kddny on 10.12.2020.
//

#include <string>
#include <vector>
#include <memory>

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

    bool isDirectory() const;
    const std::string &getName() const;
    const std::vector<std::shared_ptr<File>> &getFiles() const;
    const std::string &getPath() const;
private:
    std::string name_;
    bool directory_;

};

