#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

/**
 * s[0]: 1 
 * s[1]: 3 
 * s[2]: 9 
 * s[3]: 0 5 
 * s[4]: 5 6 
 * s[5]: 0 1 5 6 
 * s[6]: 0 1 2 3 7 8 9 
 * s[7], s[8], s[9], s[10]: 0 1 2 3 4 5 6 7 8 9 
 * 从而可以构建 size = 2 * 2 * 4 * 7 * 10000 = 1120000 的哈希表，从而没有冲突
 */

class hashTable {
private:
    int size;
    struct info {
        string phone;
        int cost;
        info(string p, int c=0) : phone(p), cost(c) {}
    };
    vector<info *> table;
    size_t hash(string phone) {
        return (phone[0] == '5' ? 560000 : 0)
             + (phone[1] == '6' ? 280000 : 0)
             + (phone[2]  > '1' ? phone[2]-'3' : phone[2] - '0') * 70000
             + (phone[3]  > '3' ? phone[3]-'7' : phone[3] - '0') * 10000
             + (phone[4] - '0') * 1000
             + (phone[5] - '0') * 100
             + (phone[6] - '0') * 10
             + (phone[7] - '0');
    }

    unsigned long time_minute(string time) {
        // time 共 4 位，以秒为单位，返回向上取整的分钟数
        return (stoul(time) + 59) / 60;
    }
public:
    hashTable() {
        size = 1120000;
        table = vector<info *>(size, nullptr);
    }

    void insert(string phone, string type, string time) {
        size_t index = hash(phone);
        if (table[index] == nullptr) {
            table[index] = new info(phone);
        }
        table[index]->cost += (type == "01" ? 1 : 2) * time_minute(time);
    }

    void output(fstream &fout) {
        for (int i = 0; i < size; i++) {
            if (table[i] != nullptr) {
                fout << "139" << table[i]->phone << " " << table[i]->cost << endl;
            }
        }
    }
};


int main() {
    clock_t start, end;
    start = clock();
    fstream fin("./data/gsm.dat", ios::in);
    string record;
    // int cnt = 0;
    int i = 0;
    hashTable table;
    while (fin >> record) {
        // cout << record << endl;
        string phone = record.substr(3, 8);
        string type = record.substr(11, 2);
        string time = record.substr(13, 4);
        table.insert(phone, type, time);
    }
    fin.close();
    // 输出到 out.txt
    fstream fout("./out.txt", ios::out);
    table.output(fout);
    fout.close();
    end = clock();
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}