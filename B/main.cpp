#include <iostream>
#include <vector>

using namespace std;

int64_t ComputeMax(int64_t l, int64_t r, const vector<vector<int64_t>>& data, const vector<int64_t> &logs) {
    int64_t N = r - l + 1;
    N = logs[N];
    int64_t k = 1 << N;
    return max(data[N][l], data[N][r - k + 1]);
}

const int64_t mod = 1000000007;
const int64_t mult = 11173;

int main() {
    int64_t N, Q, basenumber, deg;
    cin >> N;
    vector<int64_t> logs(N + 1);
    logs[0] = 0;
    logs[1] = 0;
    int64_t x = 2;
    for (int i = 2; i < N + 1; i++) {
        if (i <= x) logs[i] = logs[i - 1];
        else {
            logs[i] = logs[i - 1] + 1;
            x *= 2;
        }
    }
    deg = logs[N] + 1;
    vector<vector<int64_t>> data(deg);
    for (int i = 0; i < deg; i++) {
        data[i].resize(N - i);
    }
    for (int64_t i = 0; i < N; i++) {
        int64_t now;
        cin >> now;
        data[0][i] = now;
    }
    for (int i = 1; i < deg; i++) {
        for (int j = 0; j < data[i].size(); j++) {
            int64_t k = 1 << i;
            k /= 2;
            data[i][j] = max(data[i - 1][j], data[i - 1][j + k]);
        }
    }
    cin >> Q;
    cin >> basenumber;
    int64_t leftnow, rightnow, sum;
    sum = 0;
    leftnow = basenumber;
    int64_t l, r;
    rightnow = (mult * leftnow + 1) % mod;
    for (int64_t i = 0; i < Q; i++) {
        l = min(leftnow % N, rightnow % N);
        r = max(leftnow % N, rightnow % N);
        //cout << l << " " << r << ComputeMax(l, r, data, logs) << endl;
        sum += ComputeMax(l, r, data, logs);
        sum = sum % mod;
        leftnow = (mult * rightnow + 1) % mod;
        rightnow = (mult * leftnow + 1) % mod;
    }
    cout << sum % mod;
    return 0;
}