#include <iostream>
#include <vector>

using namespace std;

const long long mod = 1000000007;
const long long mult = 11173;

int main() {
    long long N, Q, basenumber;
    cin >> N;
    vector<long long> data(N + 1);
    data[0] = 0;
    for (long long i = 0; i < N; i++) {
        long long now;
        cin >> now;
        data[i + 1] = data[i] + now;
        data[i + 1] %= mod;
    }
    cin >> Q;
    cin >> basenumber;
    long long leftnow, rightnow, sum;
    sum = 0;
    leftnow = basenumber;
    long long l, r;
    rightnow = (mult * leftnow + 1) % mod;
    for (long long i = 0; i < Q; i++) {
        l = min(leftnow % N, rightnow % N);
        r = max(leftnow % N, rightnow % N);
        sum += (data[r + 1] - data[l]);
        sum = sum % mod;
        leftnow = (mult * rightnow + 1) % mod;
        rightnow = (mult * leftnow + 1) % mod;
    }
    cout << sum % mod;
    return 0;
}