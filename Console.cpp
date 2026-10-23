#include "Console.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Util.h"

void Console::setColor(int color) {}

void Console::printLine(const std::string& text, int color) {}

void Console::printTitle(const std::string& title) {}

void Console::printSuccess(const std::string& message) {}

void Console::printError(const std::string& message) {}

std::string Console::readLine(const std::string& prompt) {
    return "";
}

std::string Console::readPassword(const std::string& prompt) {
    return "";
}

int Console::readChoice(int maxChoice) {
    return -1;
}

bool Console::confirm(const std::string& question) {
    return false;
}

void Console::pause() {}

void Console::clearScreen() {}
