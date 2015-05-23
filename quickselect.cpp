#include <bits/stdc++.h>

using namespace std;

int partition (int a[], int p, int r) {
        int x = a[r];
        int i = p - 1;
        int j;

        for (j = p; j < r; j++) {
                if (a[j] <= x) {
                        i++;
                        swap(a[j],a[i]);
                }
        }
        swap(a[i + 1], a[r]);
        return (i + 1);
}

int quickselect(int a[], int p, int r, int k) {
        int q;
        if (p < r) {
                q = partition(a, p, r);
		
		if (q == k) {
			return a[q];
		}
		 if (k < q) {
                	quickselect(a, p, q - 1,k);
		}
		if (k > q)
                	quickselect(a, q + 1, r,k);
        }
}

int main() {
        int i,a[] = {2,6,3,8,12,1,0};
        int k = quickselect(a,0,6,5);
        cout << k;
        return 0;
}

