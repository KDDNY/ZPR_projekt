//
// Created by kddny on 13.11.2020.
//

#ifndef UNTITLED1_VISITOR_H
#define UNTITLED1_VISITOR_H

class LocalDirectory;

class Visitor {
public:
   virtual void visit(const LocalDirectory& localDirectory) = 0;
};


#endif //UNTITLED1_VISITOR_H
