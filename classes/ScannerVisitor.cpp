//
// Created by kddny on 13.11.2020.
//

#include "ScannerVisitor.h"
#include <iostream>

using namespace std;


void ScannerVisitor::visit(const LocalDirectory &) {
    cout << "Scanner visitor local directory" << endl;
}
