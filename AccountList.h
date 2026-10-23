#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "Util.h"

using namespace std;

template <typename T>
class AccountList {
private:
    static bool lessByUsername(const T& a, const T& b) {
        return false;
    }

    vector<T> m_items;
    string m_filePath;

public:
    AccountList(const string& filePath) {}

    bool load() {
        return false;
    }

    bool save() const {
        return false;
    }

    int size() const {
        return 0;
    }

    T& at(int index) {
        static T item;
        return item;
    }

    int indexOf(const string& username) const {
        return -1;
    }

    void add(const T& item) {}

    void removeAt(int index) {}

    void sortByUsername() {}
};
