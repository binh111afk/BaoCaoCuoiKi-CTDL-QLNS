#pragma once
#include <string>

class Console {
public:
    static const int COLOR_NORMAL  = 7;
    static const int COLOR_TITLE   = 14;
    static const int COLOR_LABEL   = 10;
    static const int COLOR_SUCCESS = 11;
    static const int COLOR_ERROR   = 12;

    static void setColor(int color);

    static void printLine(const std::string& text, int color = COLOR_NORMAL);

    static void printTitle(const std::string& title);

    static void printSuccess(const std::string& message);

    static void printError(const std::string& message);

    static std::string readLine(const std::string& prompt);

    static std::string readPassword(const std::string& prompt);

    static int readChoice(int maxChoice);

    static bool confirm(const std::string& question);

    static void pause();

    static void clearScreen();
};
