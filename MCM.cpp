#include <bits/stdc++.h>
using namespace std;

void printParenthesis(int i, int j, vector<vector<int>> &bracket, vector<char> &name)
{
    if (i == j)
    {
        cout << name[i];
        return;
    }

    cout << "(";
    printParenthesis(i, bracket[i][j], bracket, name);
    printParenthesis(bracket[i][j] + 1, j, bracket, name);
    cout << ")";
}

int mcm(vector<int> &arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> bracket(n, vector<int>(n, 0));
    vector<char> name(n);

    for (int i = 0; i < n; i++)
    {
        name[i] = 'A' + i;
    }

    for (int len = 2; len < n; len++)
    {
        for (int i = 1; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    printParenthesis(1, n - 1, bracket, name);
    cout << endl;

    return dp[1][n - 1];
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << mcm(arr) << endl;
    return 0;
}
