#pragma once
#include <string>
#include "Account.h"
#include "HrSystem.h"

class Application {
private:
    static const int MAX_FAILS = 3;

    bool login(std::string& accountName, Role& role);

    HrSystem m_system;

public:
    int run();
};
