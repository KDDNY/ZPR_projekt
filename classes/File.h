//
// Created by kddny on 10.12.2020.
//

#include <string>
#include <vector>
#include <memory>

#ifndef UNTITLED1_FILE_H
#define UNTITLED1_FILE_H

#endif //UNTITLED1_FILE_H

class File{
public:
    File() = default;
    File(const std::string &name, bool directory);
    const std::string &getName() const;
    const std::vector<std::shared_ptr<File>> &getFiles() const;
    std::string name_;

    bool isDirectory() const;

    std::string path_;
    std::vector<std::shared_ptr<File>> files_;
    bool directory_;
};
