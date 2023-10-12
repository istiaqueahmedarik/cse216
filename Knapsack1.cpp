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
int ans(int lastInd, int w)
{
    if (w <= 0 || lastInd < 0)
        return 0;
    if (dp[lastInd][w] != -1)
        return dp[lastInd][w];
    int noTake = ans(lastInd - 1, w);
    int take = LLONG_MIN;
    if (w - v[lastInd].first >= 0)
        take = ans(lastInd - 1, w - v[lastInd].first) + v[lastInd].second;
    return dp[lastInd][w] = max(noTake, take);
}
int32_t main()
{
    IOS;
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }
    cout << ans(n - 1, k) << endl;
    return 0;
}