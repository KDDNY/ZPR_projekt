//
// Created by Marcin Piotrowski on 29.12.2020.
//
#ifndef UNTITLED1_FILECOMMANDFACTORY_H
#define UNTITLED1_FILECOMMANDFACTORY_H
#include <memory>
#include "FileCommand.h"

class File;
///Klasa abstrakcyjna będąca fabryką obiektów klasy Command służących do synchronizacji. Na podstawie
///enum ACTION w obiekcie klasy FILE określa jaka akcja ma zostać wykonana.
class FileCommandFactory {
public:
    ///Na podstawie enum ACTION w obiekcie klasy FILE określa jaka akcja ma zostać wykonana.
    ///@param file obiekt na rzecz, którego ma być wykonana akcja.
    ///@return wskaźnik na obiekt klasy Command
    virtual std::shared_ptr<FileCommand> createAction(const File& file) = 0;
    ///Tworzy obiekt klasy Command, który ma na celu skopiowanie pliku.
    ///@param file obiekt na rzecz, którego ma być wykonana akcja.
    ///@return wskaźnik na obiekt klasy Command
    virtual std::shared_ptr<FileCommand> createCopy(const File& file) = 0;
    ///Tworzy obiekt klasy Command, który ma na celu usunięcie pliku.
    ///@param file obiekt na rzecz, którego ma być wykonana akcja.
    ///@return wskaźnik na obiekt klasy Command
    virtual std::shared_ptr<FileCommand> createRemove(const File& file) = 0;
    virtual std::shared_ptr<FileCommand> createSkip(const File& file) = 0;
};
///Implementacja klasy abstrakcyjnej FileCommandFactory dla lokalnych katalogów.
class LocalFileCommandFactory : public FileCommandFactory{
public:
    std::shared_ptr<FileCommand> createAction(const File& file) override;
    std::shared_ptr<FileCommand> createCopy(const File& file) override;
    std::shared_ptr<FileCommand> createRemove(const File& file) override;
    std::shared_ptr<FileCommand> createSkip(const File& file) override;
};


#endif //UNTITLED1_FILECOMMANDFACTORY_H
