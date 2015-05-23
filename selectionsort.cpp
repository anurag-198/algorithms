#include <bits/stdc++.h>

using namespace std;

void selectionsort(int a[], int n, int st, int end) {
	int i,j,min;
	for (i = st; i <= end - 1; i++) {
		min = i;
		for (j = i + 1; j <= end; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		swap(a[min], a[i]);
	}
}

void insertionsort(int a[], int n, int st, int end) {
	int i, key, j;
	for (i = st + 1; i < n; i++) {
		key = a[i];
		j = i - 1;
		while (j >= st && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

void bubblesort(int a[], int n, int st, int end) {
	int i,j;
	int k = 0;
	for (i = st; i <= end; i++) {
		for (j = st; j <= end - k; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j],a[j + 1]);
			}
			k++;
		}
	}
}

int main() {
	int i,a[] = {5,4,3,2,1};
	selectionsort(a,5, 2, 4);
//	insertionsort(a,5, 2 , 4);
//	bubblesort(a,5,2,4);
	for (i = 0; i < 5; i++) {
		cout << a[i] << " ";
	}
	return 0;
}
