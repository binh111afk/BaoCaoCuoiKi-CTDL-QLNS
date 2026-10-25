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
             bool needsPasswordChange = false) : Account(username, password) {
                this -> m_needsPasswordChange = needsPasswordChange;
             }

    static string defaultPassword() {
        return "111111";
    }

    static Employee createNew(const string& username) {
        return Employee(username, Employee::defaultPassword(), true);
    }

    static bool fromLine(const string& line, Employee& out) {
      istringstream in = istringstream(line);
      string username;
      string password;
      bool flag;
      
      in >> username >> password >> flag;

      this -> m_username = username;
      this -> m_password = password;
      this -> m_needPasswordChange = flag;

      return true;

    }

    string toLine() const override {
        return "";
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

void test_Employe(){

  //
}