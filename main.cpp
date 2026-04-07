#include <bits/stdc++.h>
using namespace std;

// Problem: Bounded knapsack (有限背包)
// Input:
// n, m then n lines: p_i, w_i, v_i
// Goal: maximize value under capacity m with up to p_i items of type i.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    struct Item { int p, w, v; };
    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        cin >> items[i].p >> items[i].w >> items[i].v;
    }

    // If weights are small relative to m, use monotone queue optimization per residue class.
    // General robust approach: for each item, do monotone deque DP in O(m).
    vector<long long> dp(m + 1, 0);

    for (const auto &it : items) {
        int p = it.p, w = it.w, v = it.v;
        if (w == 0) { // special case: zero weight, take up to p items
            long long add = 1LL * p * v;
            for (int j = 0; j <= m; ++j) dp[j] += add;
            continue;
        }
        // Optimize bounded knapsack using monotonic queue by residue modulo w
        int mod = w;
        for (int r = 0; r < mod; ++r) {
            deque<pair<int,long long>> dq; // pair: index t, value best
            // we consider states at positions j = r + t*w
            // define g[t] = dp[j] - t*v; we maintain max over t in sliding window size p
            for (int j = r, t = 0; j <= m; j += w, ++t) {
                long long g = dp[j] - 1LL * t * v;
                while (!dq.empty() && dq.back().second <= g) dq.pop_back();
                dq.emplace_back(t, g);
                // Remove elements out of window (t - dq.front().first > p)
                while (!dq.empty() && t - dq.front().first > p) dq.pop_front();
                dp[j] = dq.front().second + 1LL * t * v;
            }
        }
    }

    long long ans = 0;
    for (int j = 0; j <= m; ++j) ans = max(ans, dp[j]);
    cout << ans << '\n';
    return 0;
}

