#include "Account.h"
#include "Util.h"

using namespace std;

Account::Account(const string& username, const string& password)
    : m_strUsername(username), m_strPassword(password) {
}

string Account::getUsername() const {
    return this->m_strUsername;
}

string Account::getPassword() const {
    return this->m_strPassword;
}

bool Account::matchesUsername(const string& name) const {
    return Util::equalsIgnoreCase(this->m_strUsername, name);
}

bool Account::checkPassword(const string& password) const {
    return this->m_strPassword == password;
}

void Account::setPassword(const string& newPassword) {
    this->m_strPassword = newPassword;
}
