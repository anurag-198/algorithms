#include <bits/stdc++.h>

using namespace std;

int merge(int a[], int p, int q, int r) {
	int countinv = 0;
	int i,j,n1 = q - p + 1;
	int n2 = r - q;

	int L[n1 + 1];
	int R[n2 + 1];
	for (i = 0; i < n1; i++) {
		L[i] = a[p + i];
	}

	for (j = 0; j < n2; j++) {
		R[j] = a[q + j + 1];
	}
	
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	
	int k;
	i = 0;
	j = 0;

	for (k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		}
		else {
			a[k] = R[j];
			j++;
			countinv += (n1 - i);
		}
	}
	return countinv;
}

int mergesort(int a[], int p, int r) {
	int q;
	int countinv = 0;
	if (p < r) {
		q = (p + r) / 2;
		countinv += mergesort(a,p,q); //counting inversions in left part
		countinv += mergesort(a, q + 1, r);
		countinv += merge(a,p,q,r);
	}
	return countinv;
}

int main() {
	int i,a[] = {3,2,1};
	int k = mergesort(a, 0 ,2);
	cout << k << endl;	
	return 0;
}
