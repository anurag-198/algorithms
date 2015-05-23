#include <bits/stdc++.h>

using namespace std;

void merge(int a[], int p, int q, int r) {
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
	
	L[n1 + 1] = INT_MAX;
	R[n2 + 1] = INT_MAX;
	
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
		}
	}

	for (i = p; i <= r; i++) {
		cout << a[i] <<" ";
	}		
	cout << endl;
}

void mergesort(int a[], int p, int r) {
	int q;
	if (p < r) {
		q = (p + r) / 2;
		mergesort(a,p,q);
		mergesort(a, q + 1, r);
		merge(a,p,q,r);
	}
}

int main() {
	int i,a[] = {3,2,6,1,9,0,4};
	mergesort(a,0,6);
	for (i = 0; i < 7; i++) {
		cout << a[i] <<" ";
	}
	return 0;
}
