 #include <bits/stdc++.h>

using namespace std;

int main() {
	int ans1;
	int i, j,tc, n, po,pos, maxi = 0;
	int a[10001];
	int lis[10001];

	vector<int> vc[10001];

	scanf ("%d", &tc);
	while (tc--) {
		scanf ("%d", &n);
		for (i = 0; i < n; i++) {
			scanf ("%d", &a[i]);
			lis[i] = 1;
		}

		for (i = 1; i < n; i++) {
			for (j = 0; j < i; j++) {
				if ((a[i] > a[j]) && (lis[i] < lis[j] + 1)) {
					lis[i] = lis[j] + 1;
					vc[i].push_back(a[j]);		
					cout << a[j] <<" ";	
				}
			}
			cout << a[i] << endl;
			vc[i].push_back(a[i]);
		}

		for (i = 0; i < n; i++ ) {
			cout << lis[i] << endl;
			if (maxi < lis[i]) {
				maxi = lis[i];
				pos = i;
			}
//			maxi = max(maxi, lis[i]); 
		}

//		cout << maxi << endl;

		ans1 = vc[pos][vc[pos].size()-1] - vc[pos][0];
		for (i = 0; i < vc[pos].size(); i++) {
			cout << vc[pos][i] <<" ";
		}
		cout << endl;

		for (i = pos + 1; i < n; i++) {
			if (lis[i] == maxi) {
				po = i;
			ans1 = max(ans1, vc[pos][vc[po].size() - 1] - vc[po][0]);	
			for (j = 0; j < vc[po].size(); j++) {
                        		cout << vc[po][j] <<" ";
                		}
				cout << endl;
			}
		}		
	}
	return 0;

}
