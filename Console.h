#pragma once
#include <string>
#include <vector>

using namespace std;

class Console {
public:
    static const int COLOR_NORMAL   = 7;
    static const int COLOR_TITLE    = 14;
    static const int COLOR_LABEL    = 10;
    static const int COLOR_SUCCESS  = 11;
    static const int COLOR_ERROR    = 12;
    static const int COLOR_SELECTED = 112;

    static void setColor(int color);

    static void printLine(const string& text, int color = COLOR_NORMAL);

    static void printTitle(const string& title);

    static void printSuccess(const string& message);

    static void printError(const string& message);

    static string readLine(const string& prompt);

    static string readPassword(const string& prompt);

    static int chooseOption(const vector<string>& items, int startAt = 1);

    static bool confirm(const string& question);

    static void pause();

    static void clearScreen();
};
