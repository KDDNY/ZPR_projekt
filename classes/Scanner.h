//
// Created by kddny on 29.12.2020.
//

#ifndef UNTITLED1_SCANNER_H
#define UNTITLED1_SCANNER_H

#include <vector>
#include <memory>
#include "File.h"
#include "FileCommandFactory.h"

class Scanner {
public:
    static void synchronize(const std::vector<std::shared_ptr<File>>& diff);
};


#endif //UNTITLED1_SCANNER_H