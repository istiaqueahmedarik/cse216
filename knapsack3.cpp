#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(int W, vector<int> &wt, vector<int> &val, int n)
{
    vector<int> dp(W + 1, 0);
    for (int i = 0; i <= W; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (wt[j] <= i)
            {
                dp[i] = max(dp[i], dp[i - wt[j]] + val[j]);
            }
        }
    }
    return dp[W];
}

int main()
{
    int n, W;
    cin >> n >> W;
    vector<int> wt(n), val(n);
    for (int i = 0; i < n; i++)
    {
        cin >> wt[i] >> val[i];
    }
    cout << knapsack(W, wt, val, n) << endl;
    return 0;
}
