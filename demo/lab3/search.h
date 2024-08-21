#ifndef __SEARCH_H
#define __SEARCH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief search the string t in s using search_algorithm
 * @param s the string to search in
 * @param t the string to search
 * @param search_algorithm the search algorithm
 * @return res the result
 */
void search(const string &s, const string &t, int (*search_algorithm)(const string &, const string &, const int), vector<string> &res) {
    int start = 0;
    vector<string> result;
    int index = 0;
    string ret;
    while (true) {
        int pos = search_algorithm(s, t, start);
        if (pos == -1) 
            break;
        ret += s.substr(start, pos-start) + "\033[31m" + t + "\033[0m";
        start = pos + t.size();
    }
    ret += s.substr(start);
    res.push_back(ret);
    cout << ret <<endl; 
}

/**
 * @brief search the string t in s using brute force algorithm
 * @return the position of the first occurrence of t in s, -1 if not found
 */
int bf(const string &s, const string &t, const int start) {
    int i = start;
    while (i <= (s.size() - t.size())) {
        int j = 0;
        while (j < t.size() && s[i + j] == t[j]) {
            j++;
        }
        if (j == t.size()) {
            return i;
        } 
        else {
            i++;
        }
    }
    return -1;
}

/**
 * @brief get the next array of the string t
 */
vector<int> get_next(const string &t) {
    int n = t.size();
    vector<int> next(n, 0);
    int j=0;
    int k=-1;
    next[0]=-1;
    while(j < n) {
        if(k == -1||t[j] == t[k]){
            next[++j] = ++k;
        }
        else{
            k = next[k];
        }
    }
    return next;
}


/**
 * @brief kmp algorithm
 */
int kmp(const string &s, const string &t, const int start) {
    static vector<int> next;    // next array
    if (next.empty()) {
        next = get_next(t);
        for (int i = 0; i < next.size(); ++i) {
            cout << next[i] << " ";
        }
        cout << endl;
    }
    int i = start, j = 0;
    while (i < s.size() && j < (int)t.size()) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } 
        else {
            j = next[j];
        }
    }
    if (j == t.size()) {
        return i - j;
    }
    else {
        return -1;
    }
}

#endif /* search.h */