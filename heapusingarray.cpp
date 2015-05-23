#include <bits/stdc++.h>

using namespace std;
int heapsize;
int size;

void maxheapify(int a[], int i) {
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int largest;
	if ((l <= heapsize) && (a[l] > a[i])) {
		largest = l;
	}
	else {
		largest = i;
	}
	if ((r <= heapsize) && (a[r] > a[largest])) {
		largest = r;
	}
	if (largest != i) {
		swap(a[i], a[largest]);
		maxheapify(a,largest);
	}
}

void buildmaxheap(int a[]) {
	int i;
	for (i = (size - 1)/2; i >= 0; i--) {
		maxheapify(a,i);
	}
}

void heapsort(int a[]) {
	buildmaxheap(a);
	cout << a[6] <<endl;
	int i;
	for (i = size; i > 0; i--) {
		swap(a[i], a[0]);
		heapsize--;
		maxheapify(a,0);
	}
}

int main() {
	int i,j,arr[] = {0,4,1,5,22,2,3,9};
	heapsize = 7;
	size = 7;
	heapsort(arr);
	for (i = 0; i <= 7; i++) {
		cout << arr[i] <<" ";
	}
	cout << endl;
	return 0;
}
