#include <filesystem>
#include <fstream>
#include "Util.h"

using namespace std;

const char* const Util::WHITESPACE = " \t\r\n";

string Util::trim(const string& text) {
    const size_t iFirst = text.find_first_not_of(Util::WHITESPACE);
    if (iFirst == string::npos) {
        return "";
    }

    const size_t iLast = text.find_last_not_of(Util::WHITESPACE);
    return text.substr(iFirst, iLast - iFirst + 1);
}

string Util::toLower(const string& text) {
    string strResult = text;
    for (size_t iIndex = 0; iIndex < strResult.size(); iIndex++) {
        if (strResult[iIndex] >= 'A' && strResult[iIndex] <= 'Z') {
            strResult[iIndex] = static_cast<char>(strResult[iIndex] - 'A' + 'a');
        }
    }
    return strResult;
}

bool Util::equalsIgnoreCase(const string& first, const string& second) {
    return Util::toLower(first) == Util::toLower(second);
}

bool Util::isAllDigits(const string& text) {
    if (text.empty()) {
        return false;
    }

    for (size_t iIndex = 0; iIndex < text.size(); iIndex++) {
        if (text[iIndex] < '0' || text[iIndex] > '9') {
            return false;
        }
    }
    return true;
}

bool Util::readLines(const string& path, vector<string>& lines) {
    lines.clear();
    ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    string strLine;
    while (getline(file, strLine)) {
        lines.push_back(Util::trim(strLine));
    }
    file.close();
    return true;
}

bool Util::writeLines(const string& path, const vector<string>& lines) {
    ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    for (size_t iIndex = 0; iIndex < lines.size(); iIndex++) {
        file << lines[iIndex] << "\n";
    }
    file.close();
    return !file.fail();
}

bool Util::deleteFile(const string& path) {
    error_code errorCode;
    return filesystem::remove(path, errorCode);
}

bool Util::ensureFolder(const string& path) {
    error_code errorCode;
    filesystem::create_directories(path, errorCode);
    return filesystem::is_directory(path, errorCode);
}
