#include <windows.h>
#include <conio.h>
#include <iostream>
#include "Console.h"
#include "Util.h"

void Console::setColor(int color) {}

void Console::printLine(const string& text, int color) {}

void Console::printTitle(const string& title) {}

void Console::printSuccess(const string& message) {}

void Console::printError(const string& message) {}

string Console::readLine(const string& prompt) {
    return "";
}

string Console::readPassword(const string& prompt) {
    return "";
}

int Console::chooseOption(const vector<string>& items, int startAt) {
    return startAt;
}

bool Console::confirm(const string& question) {
    return false;
}

void Console::pause() {}

void Console::clearScreen() {}
