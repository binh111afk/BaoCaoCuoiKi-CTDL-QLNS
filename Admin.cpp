#include <sstream>
#include "Admin.h"

using namespace std;

Admin::Admin(const string& username, const string& password)
    : Account(username, password) {
}

bool Admin::fromLine(const string& line, Admin& out) {
    istringstream stream = istringstream(line);
    string strUsername;
    string strPassword;
    string strExtra;

    stream >> strUsername >> strPassword;
    if (!stream) {
        return false;
    }

    if (stream >> strExtra) {
        return false;
    }

    out = Admin(strUsername, strPassword);
    return true;
}

string Admin::toLine() const {
    return this->getUsername() + " " + this->getPassword();
}

Role Admin::getRole() const {
    return Role::ADMIN;
}
