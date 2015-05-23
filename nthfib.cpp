#include <bits/stdc++.h>
#define ll long long

using namespace std;

/*int getpow(int a, int b, int mod) {
	int t;
	if (b == 0) 
		return 1;	
	else {
		int t = getpow(a,b/2);
		if ((b % 2) == 0) {
			return t * t;
		}
		else 
			return t * t * a;
	}
}
*/
void multiply (ll a[2][2], ll b[2][2], ll mod) {
	ll res[2][2];
	memset(res, 0, sizeof(res));

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				res[i][j] = (res[i][j] % mod + (a[i][k] % mod) * (b[k][j] % mod)) % mod;
			}
		}
	}
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			a[i][j] = res[i][j];
		}
	}
}

void matr(ll b[2][2], ll key, ll mod) {
	int t;
	long long int temp[2][2];
	memset(temp, 0, sizeof(temp));

	if (key == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				temp[i][j] = b[i][j];
				if (i == j) {
					b[i][j] = 1;
				}
				else {
					b[i][j] = 0;
				}
			}
		}
	return;		
	}
	else {
		matr(b, key/2, mod);
		if ((key % 2) == 0) {
			multiply(b,b,mod);
		}
		else {
			multiply(b,b,mod);
			multiply(b,temp,mod);
		}
	}

}

long long int arr[2][2];
int main() {
	int d, e, c,i,j;
	int a[2][2];
	arr[0][0] = 1;
	arr[0][1] = 1;
   	arr[1][0] = 1;
   	arr[1][1] = 0;
//	memset(res,0, sizeof(res));
//	memset(a, 0, sizeof(a));
	matr(arr,2, 100);
	for (int i = 0; i  < 2; i++) {	
		for (j = 0; j < 2; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

/*	cin >> d >>  e;
	c = getpow(d, e);
	cout << c << endl;*/
	return 0;
}
