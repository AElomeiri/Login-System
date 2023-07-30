#include <iostream>
#include "DatabaseConn.h"
#include "sqlite3.h"
using namespace std;

//
DatabaseConn::DatabaseConn(std::string user, std::string pass)
{
    usernameDB = user;
    passwordDB = pass;
    sqlite3_open("database.db", &DB);
    const string sql = "CREATE TABLE IF NOT EXISTS USERS (ID INTEGER PRIMARY KEY AUTOINCREMENT, USERNAME TEXT, PASSWORD TEXT);";
    sqlite3_exec(DB, sql.c_str(), NULL, NULL, &zErrMsg);
}

// Check if the data is already exist or not.
bool DatabaseConn::CheckData(std::string PassKey)
{
    if (PassKey == "REGISTRATION") {
        const string sql = "SELECT * FROM USERS WHERE USERNAME = '" + usernameDB + "' ;";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
        re = sqlite3_step(stmt);
        if (re == SQLITE_ROW) {
            sqlite3_finalize(stmt);
            return false;
        }
        else {
            sqlite3_finalize(stmt);
            return true;
        }
    }
    else if (PassKey == "LOGIN") {
        const string sql = "SELECT * FROM USERS WHERE USERNAME='" + usernameDB + "' AND PASSWORD='" + passwordDB + "' ;";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
        re = sqlite3_step(stmt);
        if (re == SQLITE_ROW) {
            sqlite3_finalize(stmt);
            return true;
        }
        else {
            sqlite3_finalize(stmt);
            return false;
        }
    }
}

// Function to indert new user's account data.
void DatabaseConn::InsertData()
{
    const string sql = "INSERT INTO USERS( USERNAME, PASSWORD) VALUES( '" + usernameDB + "', '" + passwordDB + "');";
    sqlite3_exec(DB, sql.c_str(), NULL, NULL, &zErrMsg);
}

// Function to delete user's account.
void DatabaseConn::DeleteData()
{
    const string sql = "DELETE FROM USERS WHERE USERNAME = '"+usernameDB+"' ;";
    sqlite3_exec(DB, sql.c_str(), NULL, NULL, &zErrMsg);
}

//
void DatabaseConn::ModifyData(std::string PassKey, std::string NewValue)
{
    if (PassKey == "USERNAME") {
        const string sql = "UPDATE USERS SET USERNAME = '" + NewValue + "' WHERE USERNAME = '"+usernameDB+"';";
        sqlite3_exec(DB, sql.c_str(), NULL, NULL, &zErrMsg);
    }
    else if (PassKey == "PASSWORD") {
        const string sql = "UPDATE USERS SET PASSWORD = '" + NewValue + "' WHERE USERNAME = '"+usernameDB+"';";
        sqlite3_exec(DB, sql.c_str(), NULL, NULL, &zErrMsg);
    }
}

//Close the connection to the database.
void DatabaseConn::CloseConn()
{
    sqlite3_close_v2(DB);
}