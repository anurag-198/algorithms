#include <bits/stdc++.h>
#include <math.h>
#define ll long long
using namespace std;

void mul(ll a[2][2], ll b[2][2], ll mod)
{
    ll c[2][2];
    int i;
    int j;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            c[i][j] = 0;
        }
    }
    int k;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            for(k = 0; k < 2; k++) {
                c[i][j] = (c[i][j]%mod + (a[i][k] % mod* b[k][j]%mod) % mod)%mod;
            }
        }
    }
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            a[i][j] = c[i][j];
        }
    }
}  
void mat_mul(ll mat[2][2], ll n,ll mod)
{
    if(n == 0 || n == 1) {
        return;
    }
    mat_mul(mat,n/2,mod);
    ll m[2][2] = {{1,1},{1,0}};
    mul(mat,mat,mod);
    if(n % 2 != 0) {
        mul(mat,m,mod);
    }
}

ll fibo(ll a, ll b, ll n, ll m)
{
    ll mod = pow(10,m);
    ll mat[2][2] = {{1,1},{1,0}};
    mat_mul(mat,n,mod);
    int i;
    int j;
   
   
    return (b * mat[0][0] + a * mat[0][1])  % mod;
   
}
       
int main()
{
   std::ios::sync_with_stdio(false);
    int t;
    cin >> t;
    int k;
   
   
    for(k  = 1; k <= t; k++) {
       
        int i;
       
        ll a,b,c,n,m;
        cin >> a >> b >> n >> m ;
        cout << "Case " << k << ": ";
        if(n == 0) {
            cout << a << endl;
            continue;
        }
	if (n == 1) {
		cout << b << endl;
		continue;
	}

        ll ans1 = fibo(a,b,n - 1,m);
       
        cout << ans1 << endl;
    }
   
	return 0;
}
