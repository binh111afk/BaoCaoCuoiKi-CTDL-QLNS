#pragma once
#include <string>
#include <vector>

using namespace std;

class Util {
public:
    static string trim(const string& s) {
        return s;
    }

    static string toLower(const string& s) {
        return s;
    }

    static bool equalsIgnoreCase(const string& a, const string& b) {
        return false;
    }

    static bool isAllDigits(const string& s) {
        return false;
    }

    static bool readLines(const string& path, vector<string>& lines) {
        return false;
    }

    static bool writeLines(const string& path, const vector<string>& lines) {
        return false;
    }

    static bool deleteFile(const string& path) {
        return false;
    }

    static bool ensureFolder(const string& path) {
        return false;
    }
};
