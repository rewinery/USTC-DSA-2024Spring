#include"search.h"

using namespace std;


int main() {
    fstream file = fstream("./data/testcase.txt", ios::in);
    string s;           // string to search in
    string t;           // string to search
    vector<string> res; // result
    getline(file, t);
    cout << "\033[32mString to search\033[0m: " << t << endl;
    cout << "\033[32mResult\033[0m:" << endl;
    while (getline(file, s)) {
        search(s,t,kmp,res);
    }
    file.close();   // Do not forget to close the file
    return 0;
}
