#include <bits/stdc++.h>

using namespace std;

int compare (const void *a, const void *b) {
	return ( *(char *)a - *(char *)b);
}

int findCeil (char str[], char first, int l, int h) {
	int ceilIndex = l;
	for (int i = l+1; i <= h; i++)
		if (str[i] > first && str[i] < str[ceilIndex])
			ceilIndex = i;

	return ceilIndex;
}

void sortperm(char str[], int k) {
	int size = strlen(str);
//	qsort(str, size, sizeof(str[0]),compare);

	bool isFinished = false;

	while (!isFinished) {
		cout << str << endl;
		k--;
		if (k == 0) 
			return;
		int i;
		for (i = size - 2; i >= 0; i--) {
			if (str[i] < str[i+1])
				break;
		}
		
		if (i == -1) {
			isFinished = true;
		}
		else {
			int ceilIndex = findCeil(str,str[i],i+1,size-1);
			swap(str[i],str[ceilIndex]);
			qsort(str+i+1, size-i-1,sizeof(str[0]),compare); 
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);

	char str[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char st[27];
	int i,tc, n, k;
	cin >> tc;
	for (i = 1; i <= tc; i++) {
		cin >> n >> k;
		strcpy(st,str);
		st[n] = '\0';
//		cout << st;
		cout <<"Case " << i <<":" << endl;
		sortperm(st,k);
	}
		
	return 0;
}
