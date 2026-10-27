#pragma once
#include <string>
#include "Account.h"
#include <sstream>

using namespace std;

class Employee : public Account {
private:
    bool m_needsPasswordChange;

public:
    Employee(const string& username = "", const string& password = "",
             bool needsPasswordChange = false) : 
             Account(username, password), m_needsPasswordChange(needsPasswordChange) {
             }

    static string defaultPassword() {
        return "111111";
    }

    static Employee createNew(const string& username) {
        return Employee(username, defaultPassword(), true);
    }

    // Nhập thông tin từ string line vào Employee out
    static bool fromLine(const string& line, Employee& out) {
      istringstream stream = istringstream(line);
      string username;
      string password;
      string flag;
      string extra;

      stream >> username >> password >> flag;
      if (!stream){ return false; }

      if (stream >> extra) {return false;}

      if (flag != "0" && flag != "1") {
        return false;
      }

      if (flag == "1") {
        out = Employee(username, password, true);
        return true;
      }

      out = Employee(username, password, false);

      return true;
    }

    string toLine() const override {
        string flag;
        if (m_needsPasswordChange) {flag = "1";}
        else {flag = "0";}

        return getUsername() + " " + getPassword() + " " + flag;
    }

    Role getRole() const override {
        return Role::EMPLOYEE;
    }

    bool needsPasswordChange() const {
        return m_needsPasswordChange;
    }

    void setNeedsPasswordChange(bool value) {
      m_needsPasswordChange  = value;
    }
};

