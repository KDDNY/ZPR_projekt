//
// Created by Rafał Jan Trybus on 22/11/2020.
//

#include "Command.h"

class LocalAdd : public Command{
public:
    void execute() override{
        std::cout << "Local add" << std::endl;
    }
};

class LocalDelete : public Command{
public:
    void execute() override{
        std::cout << "Local delete" << std::endl;
    }
};

class LocalRename : public Command{
public:
    void execute() override{
        std::cout << "Local rename" << std::endl;
    }
};

class SshAdd : public Command{
public:
    void execute() override{
        std::cout << "SSH add" << std::endl;
    }
};

class SshDelete : public Command{
public:
    void execute() override{
        std::cout << "SSH delete" << std::endl;
    }
};

class SshRename : public Command{
public:
    void execute() override{
        std::cout << "SSH rename" << std::endl;
    }
};

class LocalFactory : public AbstractFactory{
public:
    std::shared_ptr<Command> createAdd(){
        return std::make_shared<LocalAdd>();
    }
    std::shared_ptr<Command> createRemove(){
        return std::make_shared<LocalDelete>();
    }
    std::shared_ptr<Command> createRename(){
        return std::make_shared<LocalRename>();
    }
};

class SshFactory : public AbstractFactory{
public:
    std::shared_ptr<Command> createAdd(){
        return std::make_shared<SshAdd>();
    }
    std::shared_ptr<Command> createRemove(){
        return std::make_shared<SshDelete>();
    }
    std::shared_ptr<Command> createRename(){
        return std::make_shared<SshRename>();
    }
};

