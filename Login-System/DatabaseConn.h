#pragma once
#include "sqlite3.h"

class DatabaseConn
{
public:
    DatabaseConn(std::string user, std::string pass = "");
    bool CheckData(std::string PassKey);
    void InsertData();
    void DeleteData();
    void ModifyData(std::string PassKey, std::string NewValue);
    void CloseConn();

protected:
private:
    std::string usernameDB;
    std::string passwordDB;
    sqlite3* DB;
    char* zErrMsg = 0;
    sqlite3_stmt* stmt;
    int re;
};
