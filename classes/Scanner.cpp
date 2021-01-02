//
// Created by kddny on 29.12.2020.
//

#include "Scanner.h"


void Scanner::synchronize(const std::vector<std::shared_ptr<File>>& diff) {
    for(const auto& el : diff){
        el->generateCommand()->execute();
    }
}
