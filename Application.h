#pragma once
#include <string>
#include "Account.h"
#include "HrSystem.h"

using namespace std;

class Application {
private:
    static const int MAX_FAILS = 3;

    bool login(string& accountName, Role& role);

    HrSystem m_system;

public:
    int run();
};
