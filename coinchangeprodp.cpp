#include <bits/stdc++.h>

using namespace std;

int main() {
	int tc,i,j, sum, n;
	scanf ("%d", &tc);

	while (tc--) {
		scanf ("%d%d", &sum, &n);
		
		int v[n];
		for (i = 0; i < n; i++) {
			scanf ("%d", &v[i]);
		}
		
		int dp[sum + 1];

		for (i = 1; i <= sum; i++) {
			dp[i] = INT_MAX;
		}

		dp[0] = 0;	

		for (i = 1; i <= sum; i++) {
			for (j = 0; j < n; j++) {
				if ((v[j] <= i) && ((dp[i - v[j]] + 1) < dp[i])) { 
					dp[i] = dp[i - v[j]] + 1;
				}			
			}
		}
		
		cout << dp[sum] << endl;
	}

	return 0;

}
