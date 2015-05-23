#include <bits/stdc++.h>

using namespace std;

void initialize(int node, int b, int e, int M[], int A[], int N)
  {
      if (b == e)
          M[node] = b;
      else
       {
  //compute the values in the left and right subtrees
          initialize(2 * node, b, (b + e) / 2, M, A, N);
          initialize(2 * node + 1, (b + e) / 2 + 1, e, M, A, N);
  //search for the minimum value in the first and 
  //second half of the interval
          if (A[M[2 * node]] <= A[M[2 * node + 1]])
              M[node] = M[2 * node];
          else
              M[node] = M[2 * node + 1]; 
      }
 }

int query(int node, int b, int e, int M[], int A[], int i, int j)
  {
      int p1, p2;

  //if the current interval doesn't intersect 
  //the query interval return -1
      if (i > e || j < b)
          return -1;
   
  //if the current interval is included in 
  //the query interval return M[node]
      if (b >= i && e <= j)
          return M[node];
   
  //compute the minimum position in the 
  //left and right part of the interval
      p1 = query(2 * node, b, (b + e) / 2, M, A, i, j);
      p2 = query(2 * node + 1, (b + e) / 2 + 1, e, M, A, i, j);
      printf ("Range is %d  %d %d\n", b, (b + e)/2, p1);
      printf ("Range is %d  %d %d\n", (b + e)/2 + 1 , e, p2);
  //return the position where the overall 
  //minimum is
      if (p1 == -1)
          return M[node] = p2;
      if (p2 == -1)
          return M[node] = p1;
      if (A[p1] <= A[p2])
          return M[node] = p1;
      return M[node] = p2;


  }

int main() {
	int n, i, ans;
	scanf ("%d", &n);
	
	int aray[n];
	for (i = 0; i < n; i++) {
		scanf ("%d", &aray[i]);
	}

	int k = 2* pow(2,(int)log2(n)) - 1;

	int m[k];
//	cout << k;
	initialize( 1, 0 , n - 1, m, aray, n); 
	for (i = 0; i < k; i++) {
//		cout << "hi ";
//		cout << m[i] << endl;
	}
	ans = query(1,0,n - 1, m, aray, 2,7 );
	cout << ans << endl;
	return 0;
}
