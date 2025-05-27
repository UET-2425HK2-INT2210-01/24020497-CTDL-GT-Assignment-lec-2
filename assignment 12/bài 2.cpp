#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Cấu trúc cạnh gồm 2 đỉnh u, v và trọng số d
struct Edge {
    int u, v, d;
};

// So sánh cạnh theo trọng số tăng dần
bool compareEdges(const Edge& a, const Edge& b) {
    return a.d < b.d;
}

// Union-Find (Disjoint Set) để phát hiện chu trình
class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n + 1);  // Đánh số từ 1 tới n
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            parent[i] = i;
    }

    // Tìm gốc đại diện của tập chứa u
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // nén đường
        return parent[u];
    }

    // Hợp hai tập u và v, trả về true nếu hợp thành công
    bool unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return false; // đã cùng tập → tạo chu trình

        // Hợp bằng rank
        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        } else {
            parent[pv] = pu;
            if (rank[pu] == rank[pv])
                rank[pu]++;
        }
        return true;
    }
};

int main() {
    ifstream fin("connection.txt");
    ofstream fout("connection.out");

    int n, m;
    fin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        fin >> edges[i].u >> edges[i].v >> edges[i].d;
    }

    // Sắp xếp các cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind uf(n); // Khởi tạo Union-Find

    int totalCost = 0;
    vector<Edge> result; // Lưu các cạnh được chọn

    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            totalCost += e.d;
            result.push_back(e);
        }
    }

    // Ghi kết quả ra file
    fout << totalCost << endl;
    for (const Edge& e : result) {
        fout << e.u << " " << e.v << " " << e.d << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
