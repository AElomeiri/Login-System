#include <iostream>
#include "Screens.h"
#include "DatabaseConn.h"
#include <cstdlib>  // For system()
using namespace std;

// Clearing the screen using system-specific command.
void Screens::CleanScreen()
{
    #ifdef _WIN32
        system("cls");  // For Windows
    #else
        system("clear");  // For Unix/Linux/Mac
    #endif

}

// To leat the user enter his/her data (username, password).
void Screens::userDetails()
{
    cout << "Enter your username: "; cin >> username;
    cout << "Enter your password: "; cin >> password;
}

// The first screen apper to the user.
void Screens::MainScreen()
{
    cout << "-----Welcome-----" << endl;
    cout << "1. Rigster\n" << "2. Login\n" << "3. Exit\n";
    cout << "Your choice: "; cin >> choice;
    if (choice == 1) {
        CleanScreen();
        RegistrationScreen();
    }
    else if (choice == 2) {
        CleanScreen();
        LoginScreen();
    }
    else if (choice == 3) {
        exit(0);
    }
    else
    { 
        CleanScreen();
        printf("<--- INVALID INPUT!! --->");
        MainScreen(); 
    }
}

//Registration screen.
void Screens::RegistrationScreen()
{
    cout << "(---- REGISTRATION SCREEN ----)" << endl;
    userDetails();
    DatabaseConn connection(username, password);
    if (connection.CheckData(REGISTRATION)) {
        connection.InsertData();
        connection.CloseConn();
        CleanScreen();
        printf("<--- THE PROCCESS HAVE DONE SUCCESSFULLY!! --->\n");
        MainScreen();
    }
    else {
        connection.CloseConn();
        CleanScreen();
        printf("<--- THE USERNAME IS ALREADY USED!! --->\n");
        RegistrationScreen();
    }

}

//Login screen.
void Screens::LoginScreen()
{
    cout << "(---- LOGIN SCREEN ----)" << endl;
    userDetails();
    DatabaseConn connention(username, password);
    if (connention.CheckData(LOGIN)) {
        connention.CloseConn();
        CleanScreen();
        ActivityScreen();
    }
    else {
        connention.CloseConn();
        CleanScreen();
        printf("<--- THE USERNAME OR PASSWOED OR BOUTH OF THEM ARE WRONG!! --->\n");
        LoginScreen();
    }
}

// The next screen after successful login.
void Screens::ActivityScreen()
{
    cout << "(---- ACTIVITY SCREEN ----)" << endl;
    printf("----- Welcome Back %s -----\n", username.c_str());
    cout << "1. Modfiy your account\n" << "2. Delete your account\n" << "3. Logout\n";
    cout << "Your choice: "; cin >> choice;
    if (choice == 1) {
        CleanScreen();
        ConfirmationScreen(&Screens::ModifyScreen);
    }
    else if (choice == 2) {
        CleanScreen();
        ConfirmationScreen(&Screens::DeleteScreen);
    }
    else if (choice == 3) {
        CleanScreen();
        cout << "----- Goodbye -----" << endl;
        MainScreen();
    }
    else
    {
        CleanScreen();
        cout << "<--- INVALID INPUT!! --->" << endl;
        ActivityScreen();
    }
}

//
void Screens::ConfirmationScreen(void (Screens::*screen)())
{
    cout << "*Are you sure:(y/n) "; cin >> choice2;
    if (choice2 == 'y') {
        CleanScreen();
        (this->*screen)();
    }
    else if (choice2 == 'n') {
        CleanScreen();
        ActivityScreen();
    }
    else {
        CleanScreen();
        cout << "<--- INVALID INPUT!! --->" << endl;
        ConfirmationScreen(screen);
    }
}

//Modify Screen
void Screens::ModifyScreen()
{
    cout << "What do you want to modify:" << endl;
    cout << "1. usrname\n" << "2. password\n" << endl;
    cout << "Your choise >>> "; cin >> choice;
    if (choice == 1) {
        CleanScreen();
        UsernameModificationScreen();
    }
    else if (choice == 2) {
        CleanScreen();
        PasswordModificationScreen();
    }
    else {
        CleanScreen();
        cout << "<--- INVALID INPUT!! --->" << endl;
        ModifyScreen();
    }
}

//
void Screens::UsernameModificationScreen()
{
    cout << "Enter the new username: "; cin >> newUsername;
    DatabaseConn connection(username, password);
    if (connection.CheckData(REGISTRATION)) {
        connection.ModifyData(USERNAME, newUsername);
        connection.CloseConn();
        username = newUsername;
        CleanScreen();
        printf("<--- THE PROCCESS HAVE DONE SUCCESSFULLY!! --->\n");
        ActivityScreen();
    }
    else {
        connection.CloseConn();
        CleanScreen();
        printf("<--- THE USERNAME IS ALREAD USED!! --->\n");
        UsernameModificationScreen();
    }
}

//
void Screens::PasswordModificationScreen()
{
    cout << "Enter the new password: "; cin >> newPassword;
    DatabaseConn connection(username, password);
    connection.ModifyData(PASSWORD, newPassword);
    connection.CloseConn();
    password = newPassword;
    CleanScreen();
    printf("--- THE PROCCESS HAVE DONE SUCCESSFULLY!! ---\n");
    ActivityScreen();
}

//Delete Screen
void Screens::DeleteScreen()
{
    DatabaseConn connection(username, password);
    connection.DeleteData();
    connection.CloseConn();
    CleanScreen();
    printf("<--- YOUR ACCOUNT HAVE BEEN DELETED SUCCESSFULLY!! --->\n");
    MainScreen();
}
