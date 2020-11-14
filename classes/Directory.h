//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_DIRECTORY_H
#define UNTITLED1_DIRECTORY_H


#include <vector>
#include <memory>
#include "File.h"
#include "Visitor.h"

class Directory {
public:
    virtual ~Directory() = default;
    virtual void addFile() = 0;
    virtual void removeFile() = 0;
    virtual void renameFile() = 0;
    virtual void accept(Visitor& visitor) const = 0;
    std::vector<std::shared_ptr<File>> files_;
};


#endif //UNTITLED1_DIRECTORY_H
