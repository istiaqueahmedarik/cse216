/*******************************************
 @b |I|s|t|i|a|q|u|e| |A|h|m|e|d| |A|r|i|k|
********************************************/
#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
using namespace std;
void __print(int x) { cerr << x; }
#define int long long
#define pi acos(-1)
#define endl '\n'
#define set_bits __builtin_popcountll
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define FileIO                        \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout)

inline void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &i : arr)
        cin >> i;
    vector<int> dp(n + 1, 0);
    dp[0] = arr[0];
    int l = 0, r = 0, mx = dp[0];
    for (int i = 1; i < n; i++)
    {
        if (dp[i - 1] + arr[i] < arr[i])
        {
            dp[i] = arr[i];
            l = i;
        }
        else
        {
            dp[i] = dp[i - 1] + arr[i];
        }
        if (dp[i] > mx)
        {
            mx = dp[i];
            r = i;
        }
    }
    cout << mx << " " << l + 1 << " " << r + 1 << endl;
    cout << endl;
}

auto main() -> int32_t
{
    IOS;
    int t, cs = 1;
    cin >> t;
    while (t--)
    {
        cout << "Case " << cs++ << ":" << endl;
        solve();
    }

    return 0;
}