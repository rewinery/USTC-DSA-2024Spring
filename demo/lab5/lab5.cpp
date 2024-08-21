#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;



class Graph {
    vector<vector<pair<int, float>>> adj;

    vector<vector<pair<int, float>>> mst;

    vector<vector<pair<int, float>>> res;

    size_t root;
public:
    Graph(fstream &fin) {
        // TODO: 读取文件，构造图
    }

    void writeGraph(fstream &fout) {
        size_t vertex_num = res.size();
        for (size_t i = 0; i < vertex_num; ++i) {
            fout << "{source: '" << i << "', target: '" << i << "', 'rela': '', type: 'resolved'}," << endl;
        }

        for (size_t i = 0; i < vertex_num; ++i) {
            for (size_t j = 0; j < res[i].size(); ++j)
            fout << "{source: '" << i << "', target: '" << res[i][j].first << "', 'rela': '" << res[i][j].second << "', type: 'resolved'}," << endl;
        }
    }

    void saveGraph(const string &filename) {
        fstream fout(filename, ios::out);
        if (!fout) {
            cout << "Failed to open file " << filename << "!" << endl;
            exit(0);
        }
        fstream fh("head.txt", ios::in);
        if (!fh) {
            cout << "Failed to open file head.txt!" << endl;
            exit(0);
        }
        string line;
        while (getline(fh, line)) {
            fout << line << endl;
        }
        fh.close();
        fout << endl << endl << "var links = " << endl << "[" << endl;
        writeGraph(fout);
        fout << endl << "];";

        fstream ft("tail.txt", ios::in);
        if (!ft) {
            cout << "Failed to open file tail.txt!" << endl;
            exit(0);
        }
        while (getline(ft, line)) {
            fout << line << endl;
        }
        ft.close();
        fout.close();
        cout << "Save graph to " << filename << " successfully!" << endl;
    };

    void prim() {
        // TODO: Prim算法
    }
    void kruskal() {
        // TODO: Kruskal算法
    }

    void process() {
        // TODO: 处理图，将 mst 转化为 res
    }
};

int main() {
    fstream fin("graph.txt");
    Graph g(fin);
    fin.close();

    return 0;
}

  