#include <bits/stdc++.h>
using namespace std;

int partition(int arr[], int l, int r)
{
    swap(arr[r], arr[l + rand() % (r - l + 1)]);
    int pivot = arr[r], k = l - 1;
    for (int j = l; j < r; j++)
        if (arr[j] >= pivot)
            swap(arr[++k], arr[j]);
    swap(arr[++k], arr[r]);
    return k;
}
int Kth(int arr[], int l, int r, int k)
{
    int ind = partition(arr, l, r);
    if (ind == k - 1)
        return arr[ind];
    return (ind < k - 1) ? Kth(arr, ind + 1, r, k) : Kth(arr, l, ind - 1, k);
}
int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int k;
    cin >> k;
    cout << Kth(arr, 0, n - 1, k) << endl;
}