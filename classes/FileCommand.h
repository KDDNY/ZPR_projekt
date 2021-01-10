//
// Created by Marcin Piotrowski on 30.12.2020.
//

#ifndef UNTITLED1_FILECOMMAND_H
#define UNTITLED1_FILECOMMAND_H
#include <filesystem>

class File;

///Klasa abstrakcyjna ze wzorca projektowego komendy, reprezentująca operacje na pliku wykonywaną w celu synchronizacji.
class FileCommand {
public:
    ///Konstruktor
    ///@param file wskaźnik do pliku na którym będą wykonywane operacje.
    FileCommand(const File& file) : file_(file) {};
    ///Wywołuje daną akcje.
    virtual void execute() = 0;
    const File& file_;
};

///Implementuje wykonanie kopii dla lokalnego katalogu.
class LocalCopyFileCommand : public FileCommand{
public:
    LocalCopyFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
private:
    void CopyRecursive(const std::filesystem::path& src, const std::filesystem::path& target) noexcept;
};

class LocalSkipFileCommand : public FileCommand{
public:
    LocalSkipFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

///Implementuje usunięcie lokalnego katalogu.
class LocalRemoveFileCommand : public FileCommand{
public:
    LocalRemoveFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

// SSH definitions

class SSHCopyFileCommand : public FileCommand{
public:
    SSHCopyFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

class SSHSkipFileCommand : public FileCommand{
public:
    SSHSkipFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

class SSHRemoveFileCommand : public FileCommand{
public:
    SSHRemoveFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

#endif //UNTITLED1_FILECOMMAND_H