//
// Created by Rafał Jan Trybus on 22/12/2020.
//

#ifndef UNTITLED1_SSHCONNECTOR_H
#define UNTITLED1_SSHCONNECTOR_H

#include <iostream>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <fcntl.h>
#include "File.h"
#include <stdio.h>
#include <sys/stat.h>


///Klasa implementująca operacje odpowiedzialne za połączenie SSH
class SshConnector {
public:
    std::string _serverName;
    std::string _password;
    std::string _sshFilePath;

    SshConnector(std::string serverName, std::string password, std::string filePath, Dir* dir) : _serverName(serverName), _password(password),
    _sshFilePath(filePath), dir_(dir){
        my_ssh_session = ssh_new();
    }
    ////Obiekt klasy sesja ssh
    ssh_session my_ssh_session;
    ////Obiekt klasy sesja sftp
    sftp_session my_sftp_session;
    ///Funkcja autoryzuje sesje użytkownika na serwerze ssh, otwiera połączenie
    ///@param session obiekt sesji ssh.
    int verify_knownhosts(ssh_session session);
    ///Funkcja zwraca listę plików i katalogów znajdujących się na serwerze ssh
    sftp_session fetchFiles();
    ////Funkcja zwraca wartość logiczną: TRUE gdy plik jest katalogiem oraz FALSE gdy nim nie jest.
    int checkIfDir(ssh_session session, sftp_session sftp, std::string path);
    ////Funkcja wyświetla zawartość lokazlicaji na serwerze SSH
    ////@param files wektor obiektów klasy file
    int sftp_list_dir(ssh_session session, sftp_session sftp, std::string rootDir,std::vector<std::shared_ptr<File>> &files, std::shared_ptr<File> prev);
    //// Funkcja kopiuje zadany plik z lokalizacji maszyny lokalnej na serwer do zadanej lokalizacji
    void copyLS(std::string source, std::string target);
    //// Funkcja kopiuje zadany plik z lokalizacji serwera na maszynę lokalną do zadanej lokalizacji
    void copySL(std::string source, std::string target);
    //// Funkcja usuwa katalog na serwerze SSH
    void removeSshDir(std::string target);
    //// Funkcja kopiuje pusty katalog w kierunku z maszyny lokalnej na serwer
    void copyDirLS(std::string target);
    //// Funkcja kopiuje pusty katalog w kierunku z serwera na maszynę lokalną
    void copyDirSL(std::string target);
private:
    Dir* dir_;
};


#endif //UNTITLED1_SSHCONNECTOR_H
