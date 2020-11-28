//
// Created by Rafał Jan Trybus on 22/11/2020.
//

#ifndef UNTITLED1_COMMAND_H
#define UNTITLED1_COMMAND_H
#include <iostream>
#include <memory>

class Command {
public:
    virtual void execute() = 0;

};

class AbstractFactory{
public:
    virtual std::shared_ptr<Command> createAdd() = 0;
    virtual std::shared_ptr<Command> createRemove() = 0;
    virtual std::shared_ptr<Command> createRename() = 0;
};


#endif //UNTITLED1_COMMAND_H
