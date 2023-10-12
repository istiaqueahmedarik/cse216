#include <bits/stdc++.h>
#define int long long
#define float double
#define endl '\n'
#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

using namespace std;
int n, k;
int dp[150][100005];
vector<pair<int, int>> v;
int ans(int lastInd, int val)
{
    if (!val)
        return 0;
    if (lastInd < 0)
        return 1e16;
    if (dp[lastInd][val] != -1)
        return dp[lastInd][val];
    int noTake = ans(lastInd - 1, val);
    int take = LLONG_MAX;
    if (val - v[lastInd].second >= 0)
        take = ans(lastInd - 1, val - v[lastInd].second) + v[lastInd].first;
    return dp[lastInd][val] = min(take, noTake);
}
int32_t main()
{
    IOS;
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    int mx = LLONG_MIN;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        mx = max(mx, y);
        v.push_back({x, y});
    }
    for (int i = 1e5; i >= 0; i--)
    {
        if (ans(n - 1, i) <= k)
        {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}