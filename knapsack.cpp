#include <bits/stdc++.h>

using namespace std;
//int k[100001][200001];

int knapsack (int W, int wt[], int val[], int n) {
	int i, w;
	int k[n+1][w+1];

//	memset(k, 0, sizeof(k));

	for (i = 0; i <= n; i++) {
		for (w = 0; w <= W; w++) {
			if (i == 0 || w == 0) {
				k[i][w] = 0;
			}
			else if (wt[i - 1] <= w) {
				k[i][w] = max((val[i - 1] + k[i - 1][w - wt[i - 1]]),k[i - 1][w]);
			}
			else {
				k[i][w] = k[i - 1][w];
			}
		} 
	}
	for (i = 1; i <= W; i++) {
		cout << k[n][i] << " ";
	}
	cout << endl;
}

int main() {
	int n, i;
	scanf ("%d", &n);
	int w,wt[n], val[n];
	w = 0;
	for (i = 0; i < n; i++) {
		scanf ("%d%d", &wt[i], &val[i]);
		w += wt[i];
	}

	knapsack(w,wt,val,n);
	return 0;
}
