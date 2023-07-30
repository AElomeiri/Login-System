#pragma once
#include "DatabaseConn.h"
#include <string>

class Screens
{
    public:
        void CleanScreen(); // To clean the screen for the new one.
        void userDetails(); // To take the username and password.
        void MainScreen(); // The first screen will apper whin the user run the program.
        void RegistrationScreen();
        void LoginScreen();
        void ActivityScreen();
        void ConfirmationScreen(void (Screens::* screen)());
        void DeleteScreen();
        void ModifyScreen();
        void UsernameModificationScreen();
        void PasswordModificationScreen();
    private:
        const std::string LOGIN = "LOGIN";
        const std::string REGISTRATION = "REGISTRATION";
        const std::string USERNAME = "USERNAME";
        const std::string PASSWORD = "PASSWORD";
        std::string username;
        std::string newUsername;
        std::string password;
        std::string newPassword;
        int choice;
        char choice2;
    protected:
};

