//
// Created by kddny on 09.11.2020.
//

#include <iostream>
#include "LocalDirectory.h"

using namespace std;

void LocalDirectory::accept(Visitor &visitor) const {
    visitor.visit(*this);
}

LocalDirectory::LocalDirectory() {
    cout << "Local Directory constructor" << endl;
}
