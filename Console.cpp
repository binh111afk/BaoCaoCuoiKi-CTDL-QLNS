#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "Console.h"
#include "Util.h"

using namespace std;

void Console::setColor(const int color) {
    cout.flush();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void Console::printLine(const string& text, const int color) {
    Console::setColor(color);
    cout << text << endl;
    Console::setColor(Console::COLOR_NORMAL);
}

void Console::printTitle(const string& title) {
    size_t iPadding = 0;
    if (title.length() < Console::TITLE_WIDTH) {
        iPadding = Console::TITLE_WIDTH - title.length();
    }
    const size_t iLeft = iPadding / 2;
    const size_t iRight = iPadding - iLeft;

    const string strBorder(Console::TITLE_WIDTH + Console::TITLE_BORDER_SIDES, Console::TITLE_BORDER);
    const string strMiddle = string(1, Console::TITLE_BORDER) + string(iLeft, ' ') + title
        + string(iRight, ' ') + string(1, Console::TITLE_BORDER);

    Console::printLine(strBorder, Console::COLOR_TITLE);
    Console::printLine(strMiddle, Console::COLOR_TITLE);
    Console::printLine(strBorder, Console::COLOR_TITLE);
}

void Console::printSuccess(const string& message) {
    Console::printLine(message, Console::COLOR_SUCCESS);
}

void Console::printError(const string& message) {
    Console::printLine(message, Console::COLOR_ERROR);
}

string Console::readLine(const string& prompt) {
    Console::setColor(Console::COLOR_LABEL);
    cout << prompt;
    Console::setColor(Console::COLOR_NORMAL);

    string strLine;
    if (!getline(cin, strLine)) {
        cin.clear();
        return "";
    }
    return Util::trim(strLine);
}

string Console::readPassword(const string& prompt) {
    Console::setColor(Console::COLOR_LABEL);
    cout << prompt;
    Console::setColor(Console::COLOR_NORMAL);
    cout.flush();

    string strPassword;
    int iKey = _getch();
    while (iKey != Console::KEY_ENTER) {
        Console::applyPasswordKey(iKey, strPassword);
        iKey = _getch();
    }
    cout << endl;
    return strPassword;
}

int Console::chooseOption(const vector<string>& items, const int startAt) {
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO oldCursor = {};
    GetConsoleCursorInfo(hOutput, &oldCursor);
    CONSOLE_CURSOR_INFO hiddenCursor = oldCursor;
    hiddenCursor.bVisible = FALSE;
    SetConsoleCursorInfo(hOutput, &hiddenCursor);

    const int iCount = static_cast<int>(items.size());
    Console::printLine("(Mui ten len/xuong de chon, Enter de xac nhan)", Console::COLOR_LABEL);
    for (int iLine = 0; iLine < iCount; iLine++) {
        cout << endl;
    }

    CONSOLE_SCREEN_BUFFER_INFO info = {};
    GetConsoleScreenBufferInfo(hOutput, &info);
    COORD listStart = info.dwCursorPosition;
    listStart.Y = static_cast<SHORT>(listStart.Y - iCount);

    int iSelected = startAt;
    bool bConfirmed = false;
    while (!bConfirmed) {
        SetConsoleCursorPosition(hOutput, listStart);
        Console::printOptions(items, iSelected);
        bConfirmed = Console::readSelectionKey(iSelected, iCount);
    }

    SetConsoleCursorInfo(hOutput, &oldCursor);
    return iSelected;
}

bool Console::confirm(const string& question) {
    const string strAnswer = Console::readLine(question + " (y/n): ");
    return strAnswer == "y" || strAnswer == "Y";
}

void Console::pause() {
    Console::printLine("Nhan phim bat ky de tiep tuc...");
    const int iKey = _getch();
    if (iKey == Console::KEY_EXTENDED_ZERO || iKey == Console::KEY_EXTENDED_E0) {
        _getch();
    }
}

void Console::clearScreen() {
    cout.flush();
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info = {};
    GetConsoleScreenBufferInfo(hOutput, &info);

    const DWORD dwCells = static_cast<DWORD>(info.dwSize.X) * static_cast<DWORD>(info.dwSize.Y);
    const COORD origin = {0, 0};
    DWORD dwWritten = 0;
    FillConsoleOutputCharacterA(hOutput, ' ', dwCells, origin, &dwWritten);
    FillConsoleOutputAttribute(hOutput, static_cast<WORD>(Console::COLOR_NORMAL), dwCells, origin, &dwWritten);
    SetConsoleCursorPosition(hOutput, origin);
}

void Console::printOptions(const vector<string>& items, const int selected) {
    for (size_t iIndex = 0; iIndex < items.size(); iIndex++) {
        const int iOption = static_cast<int>(iIndex) + Console::FIRST_OPTION;
        if (iOption == selected) {
            Console::setColor(Console::COLOR_SELECTED);
            cout << "> " << items[iIndex];
            Console::setColor(Console::COLOR_NORMAL);
            cout << endl;
        } else {
            cout << "  " << items[iIndex] << endl;
        }
    }
}

bool Console::readSelectionKey(int& selected, const int count) {
    const int iKey = _getch();
    if (iKey == Console::KEY_ENTER) {
        return true;
    }

    if (iKey == Console::KEY_EXTENDED_ZERO || iKey == Console::KEY_EXTENDED_E0) {
        Console::moveSelection(_getch(), selected, count);
    }
    return false;
}

void Console::moveSelection(const int arrowKey, int& selected, const int count) {
    switch (arrowKey) {
        case Console::KEY_UP:
            selected = (selected <= Console::FIRST_OPTION) ? count : selected - 1;
            break;

        case Console::KEY_DOWN:
            selected = (selected >= count) ? Console::FIRST_OPTION : selected + 1;
            break;

        default:
            break;
    }
}

void Console::applyPasswordKey(const int key, string& password) {
    if (key == Console::KEY_EXTENDED_ZERO || key == Console::KEY_EXTENDED_E0) {
        _getch();
        return;
    }

    if (key == Console::KEY_BACKSPACE) {
        Console::removeLastPasswordChar(password);
        return;
    }

    if (key >= Console::KEY_FIRST_PRINTABLE) {
        password += static_cast<char>(key);
        cout << Console::PASSWORD_MASK;
        cout.flush();
    }
}

void Console::removeLastPasswordChar(string& password) {
    if (password.empty()) {
        return;
    }

    password.pop_back();
    cout << "\b \b";
    cout.flush();
}
