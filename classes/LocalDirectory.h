//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_LOCALDIRECTORY_H
#define UNTITLED1_LOCALDIRECTORY_H


#include "Directory.h"

class LocalDirectory : public Directory {
public:
    LocalDirectory();
    void addFile() override {}
    void removeFile() override {}
    void renameFile() override {}
    void accept(Visitor& visitor) const override;
    std::string path_;
};


#endif //UNTITLED1_LOCALDIRECTORY_H
