#include <bits/stdc++.h>

using namespace std;

int getMid(int a, int b) {
	return (a + (b - a) / 2);
}
int getSumUtil (int *st, int ss, int se, int qs, int qe, int index) {
	if (qs <= ss && qe >= se)
		return st[index];

	if (se < qs || ss > qe) 	
		return 0;

	int mid = getMid(ss, se);
	return getSumUtil(st, ss, mid, qs, qe, 2*index + 1) + getSumUtil(st, mid + 1, se, qs, qe, 2 * index + 2);
}

int getSum(int *st, int n, int qs, int qe) {
	if (qs < 0 || qe > n - 1 || qs > qe) {
		printf ("Invalid input\n");
		return -1;
	}

	return getSumUtil(st, 0, n - 1, qs, qe, 0);
}

int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
	if (ss == se) {
		st[si] = arr[ss];
		return arr[ss];
	}

	int mid = getMid(ss, se);
	st[si] = constructSTUtil(arr, ss, mid, st, si * 2 + 1) + constructSTUtil(arr, mid + 1, se, st, si * 2 + 2);
	return st[si];
}

int *construct(int arr[], int n) {
	int x = (int)(ceil(log2(n))); 
	cout <<" log2(n) is "<< x << endl;// height
	int max_size = 2*(int)pow(2,x+1) - 1; // max elements in m
	int *st = new int[max_size];	
	
	int k = constructSTUtil(arr, 0, n - 1, st, 0);
	cout << "Total sum is "<< k << endl;

	return st;
}

int main() {
	int arr[] = {1, 3, 5, 7, 9, 11};
	int n = sizeof(arr)/sizeof(int);

	int *st = construct(arr, n);	

	printf ("Sum of range = %d\n", getSum(st, n, 2, 5));
	return 0;
}
