#include <bits/stdc++.h>

using namespace std;
int a[100005];
int sum[100005];
int main() {
	int tc, n, i, sum2, maxi;
	int flag = 0;
	scanf ("%d", &tc);
	while (tc--) {
		flag = 0;
		scanf ("%d", &n);
		sum2 = 0;
		for (i = 0; i < n; i++) {
			scanf ("%d", &a[i]);
			if (a[i] > 0) {
				flag = 1;
				sum2 = sum2 + a[i];
			}
		}

		sum[0] = a[0];
		for (i = 1; i < n; i++) {
			sum[i] = max(sum[i - 1] + a[i], a[i]);
		
		}	

		maxi = INT_MIN;
		for (i = 0; i < n; i++) {
			maxi = max(maxi, sum[i]);
		}

		if (flag == 0) {
			cout << maxi << " "<< maxi << endl;
			continue;
		}
		cout << maxi <<" "<< sum2<<endl;
	}
	return 0;
}
