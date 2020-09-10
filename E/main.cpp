#include <iostream>
#include <vector>

using namespace std;

class CutTree {
public:
    vector<int64_t> tree;
    int64_t treesize;
    vector<int64_t> startdata;
public:
    int64_t parent(int64_t v) { return (v - 1) / 2; }
    int64_t rightchild(int64_t v) { return (v + 1) * 2; }
    int64_t leftchild(int64_t v) { return v * 2 + 1; }
    CutTree(const vector<int64_t> &data, int x) : treesize(x), startdata(data){
        tree.resize(2 * x - 1);
        for (int64_t i = x - 1; i < 2 * x - 1; i++) {
            if (data[i - x + 1] % 2 == 0)tree[i] = 1;
            else tree[i] = 0;
        }
        for (int64_t i = x - 2; i >= 0; i--) {
            tree[i] = tree[rightchild(i)] + tree[leftchild(i)];
        }
    }
    void Update(int64_t vertex, int64_t n) {
        startdata[vertex] = n;
        vertex += treesize - 1;
        n += 1;
        n %= 2;
        n = abs(n);
        tree[vertex] = n;
        if (treesize == 1) return;
        while(parent(vertex) > 0) {
            vertex = parent(vertex);
            tree[vertex] = tree[rightchild(vertex)] + tree[leftchild(vertex)];
        }
        tree[0] = tree[1] + tree[2];
    }
    int64_t Sum(int64_t vertex, int64_t ql, int64_t qr, int64_t vl, int64_t vr) {
        if (vr <= ql || vl >= qr) return 0;
        if(ql <= vl && vr <= qr) return tree[vertex];
        int64_t vm = (vl + vr) / 2;
        return Sum(leftchild(vertex), ql, qr, vl, vm) +
               Sum(rightchild(vertex), ql, qr, vm, vr);
    }
    int64_t Search (int64_t number, int64_t vertex) {
        if (vertex == 0 && tree[vertex] < number) return -1;
        if (vertex >= treesize - 1) return vertex - treesize + 1;
        if (tree[leftchild(vertex)] < number) {
            number -= tree[leftchild(vertex)];
            vertex = rightchild(vertex);
            return Search(number, vertex);
        } else {
            vertex = leftchild(vertex);
            return Search(number, vertex);
        }
    }
};

int main() {
    int N, Q;
    cin >> N;
    int x = 1;
    while(x < N) {
        x *= 2;
    }
    vector<int64_t> data(x);
    for (int i = 1; i < x + 1; i++) {
        if (i <= N) {
            int64_t j;
            cin >> j;
            data[i - 1] = j;
        } else {
            data[i - 1] = 1;
        }
    }
    cin >> Q;
    CutTree tr(data, x);
    /*for (int i = 0; i < 2 * x - 1; i++) {
        cout << tr.tree[i] << endl;
    }*/
    for (int i = 0; i < Q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int64_t k, index;
            cin >> k;
            index = tr.Search(k, 0);
            if (index == -1) cout << "NONE" << endl;
            else {
                cout << data[index] << endl;
            }
        } else {
            int index, value;
            cin >> index >> value;
            data[index] = value;
            tr.Update(index, value);
        }
    }

    return 0;
}
