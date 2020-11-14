//
// Created by kddny on 13.11.2020.
//

#ifndef UNTITLED1_SCANNERVISITOR_H
#define UNTITLED1_SCANNERVISITOR_H


#include "Visitor.h"

class ScannerVisitor : public Visitor{
    void visit(const LocalDirectory&);
};


#endif //UNTITLED1_SCANNERVISITOR_H
