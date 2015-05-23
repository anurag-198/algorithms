#include <bits/stdc++.h>

using namespace std;

int c[10000];
void countingsort(int a[], int n) {
}

int main () {
	int n,maxi, i;
	cout << "enter the no \n";
	cin >> n;
	int a[n];
	int b[n];

	maxi = -1;

	memset(c, 0, sizeof(c));
	
	for (i = 0; i < n; i++) {
		scanf ("%d", &a[i]);
		c[a[i]]++;
		maxi = max(maxi, a[i]);
	}

	for (i = 1; i <= maxi; i++) {
		c[i] = c[i] + c[i - 1];
	}

	for (i = n - 1; i >= 0; i--) {
		b[c[a[i]]] = a[i];
		c[a[i]]--;		
	}

	for (i = 1; i <= n; i++) {
		cout << b[i] << " ";
	}
	return 0;		
}
