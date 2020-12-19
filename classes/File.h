//
// Created by kddny on 10.12.2020.
//

#include <string>
#include <vector>
#include <memory>

#ifndef UNTITLED1_FILE_H
#define UNTITLED1_FILE_H

#endif //UNTITLED1_FILE_H

enum ParentDir{
    FIRST, SECOND
};

class File{
public:
    File() = default;
    File(const std::string &name, bool directory, ParentDir parentDir);
    const std::string &getName() const;
    const std::vector<std::shared_ptr<File>> &getFiles() const;
    std::string name_;
    bool isDirectory() const;

    void setParentDir(ParentDir parentDir);

    ParentDir parent_dir_;
    std::string path_;
    std::vector<std::shared_ptr<File>> files_;
    bool directory_;
};

