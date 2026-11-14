#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "Console.h"
#include "Util.h"

void Console::setColor(int color) {
    cout.flush();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void Console::printLine(const string& text, int color) {
    setColor(color);
    cout << text << endl;
    setColor(COLOR_NORMAL);
}

void Console::printTitle(const string& title) {
    size_t width = 36;
    size_t left = (width - title.length()) / 2;
    size_t right = width - title.length() - left;

    string stars = string(width + 2, '*');
    string middle = "*" + string(left, ' ') + title + string(right, ' ') + "*";

    printLine(stars, COLOR_TITLE);
    printLine(middle, COLOR_TITLE);
    printLine(stars, COLOR_TITLE);
}

void Console::printSuccess(const string& message) {
    printLine(message, COLOR_SUCCESS);
}

void Console::printError(const string& message) {
    printLine(message, COLOR_ERROR);
}

string Console::readLine(const string& prompt) {
    setColor(COLOR_LABEL);
    cout << prompt;
    setColor(COLOR_NORMAL);

    string line;
    if (!getline(cin, line)) {
        cin.clear();
        return "";
    }
    return Util::trim(line);
}

string Console::readPassword(const string& prompt) {
    setColor(COLOR_LABEL);
    cout << prompt;
    setColor(COLOR_NORMAL);
    cout.flush();

    string password;
    while (true) {
        int key = _getch();
        if (key == 13) {
            break;
        }

        if (key == 0 || key == 224) {
            _getch();
        } else if (key == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
                cout.flush();
            }
        } else if (key >= 32) {
            password += static_cast<char>(key);
            cout << '*';
            cout.flush();
        }
    }
    cout << endl;
    return password;
}

int Console::chooseOption(const vector<string>& items, int startAt) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO oldCursor;
    GetConsoleCursorInfo(handle, &oldCursor);
    CONSOLE_CURSOR_INFO hiddenCursor = oldCursor;
    hiddenCursor.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &hiddenCursor);

    size_t size = items.size();
    int count = static_cast<int>(size);
    printLine("(Mui ten len/xuong de chon, Enter de xac nhan)", COLOR_LABEL);
    for (size_t i = 0; i < size; i++) {
        cout << endl;
    }

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD listStart = info.dwCursorPosition;
    listStart.Y = static_cast<SHORT>(listStart.Y - count);

    int selected = startAt;
    while (true) {
        SetConsoleCursorPosition(handle, listStart);
        for (size_t i = 0; i < size; i++) {
            if (static_cast<int>(i) + 1 == selected) {
                setColor(COLOR_SELECTED);
                cout << "> " << items[i];
                setColor(COLOR_NORMAL);
                cout << endl;
            } else {
                cout << "  " << items[i] << endl;
            }
        }

        int key = _getch();
        if (key == 13) {
            break;
        }

        if (key == 0 || key == 224) {
            key = _getch();
            if (key == 72) {
                selected--;
                if (selected < 1) {
                    selected = count;
                }
            } else if (key == 80) {
                selected++;
                if (selected > count) {
                    selected = 1;
                }
            }
        }
    }

    SetConsoleCursorInfo(handle, &oldCursor);
    return selected;
}

bool Console::confirm(const string& question) {
    string answer = readLine(question + " (y/n): ");
    return answer == "y" || answer == "Y";
}

void Console::pause() {
    printLine("Nhan phim bat ky de tiep tuc...");
    int key = _getch();
    if (key == 0 || key == 224) {
        _getch();
    }
}

void Console::clearScreen() {
    cout.flush();
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);

    DWORD cells = static_cast<DWORD>(info.dwSize.X) * static_cast<DWORD>(info.dwSize.Y);
    COORD origin = {0, 0};
    DWORD written;
    FillConsoleOutputCharacterA(handle, ' ', cells, origin, &written);
    FillConsoleOutputAttribute(handle, static_cast<WORD>(COLOR_NORMAL), cells, origin, &written);
    SetConsoleCursorPosition(handle, origin);
}
