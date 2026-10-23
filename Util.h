#pragma once
#include <string>
#include <vector>

class Util {
public:
    static std::string trim(const std::string& s) {
        return s;
    }

    static std::string toLower(const std::string& s) {
        return s;
    }

    static bool equalsIgnoreCase(const std::string& a, const std::string& b) {
        return false;
    }

    static bool isAllDigits(const std::string& s) {
        return false;
    }

    static bool readLines(const std::string& path, std::vector<std::string>& lines) {
        return false;
    }

    static bool writeLines(const std::string& path, const std::vector<std::string>& lines) {
        return false;
    }

    static bool deleteFile(const std::string& path) {
        return false;
    }

    static bool ensureFolder(const std::string& path) {
        return false;
    }
};
