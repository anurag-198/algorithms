#include <bits/stdc++.h>
 
#define pb push_back
#define mp make_pair
 
using namespace std;
 
typedef long long LL;
 
LL Q=1e9 + 7;
 
LL gcd(LL a, LL b){
    if (b == 0) return a;
    return gcd(b, a%b);
}
 
void bru(LL n){
    LL ans = 0;
    for (int i=1;i<=n-1;i++){
        if (gcd(n, i) == 1){
            ans += i*i;
            ans %= Q;
        }
    }
    cout<<ans<<"\n";
}
 
LL f(LL n){
    vector<LL> r;
    r.pb(n);
    r.pb(n+1);
    r.pb(2*n + 1);
    for (LL i=0;i<3;i++){
        if (r[i]%2 == 0){
            r[i] /= 2;
            break;
        }
    }
    for (LL i=0;i<3;i++){
        if (r[i]%3 == 0){
            r[i] /= 3;
            break;
        }
    }
    LL ans = r[0];
    ans %= Q;
    ans = (ans * r[1] ) %Q;
    ans = (ans * r[2] ) %Q;
    return ans;
}
 
int main(){
    int test;
    cin>>test;
    while (test--){
        LL n;
        cin>>n;
       // bru(n);
        LL nn = n;
        LL ans = 0;
        vector<LL> p;
        p.clear();
        for (LL i=2;i*i<=n;i++){
            if (n%i == 0){
                p.pb(i);
                while (n%i == 0){
                    n /= i;
                }
            }
        }
        if (n != 1){
            p.pb(n);
        }
        n = nn;
        LL sz = p.size();
        ans = f(n-1);
        for (LL i=1;i<(1<<sz);i++){
            LL te = 1;
            LL cnt = 0;
            for (LL j=0;j<sz;j++){
                if ( (i&(1<<j)) != 0){
                    te = te*p[j];
                    cnt++;
                }
            }
            LL temp = te*te;
            temp %= Q;
            LL re = (n-1)/te;
            cout << temp <<" "<<re <<endl;
            temp = (temp*f(re))%Q;
            cout << temp <<endl;
          //  cout<<i<<" "<<temp<<"\n";
            if(cnt % 2 != 0){
                ans -= temp;
                ans  = (ans + Q)%Q;
            } else {
                ans += temp;
                ans %= Q;
            }
            cout << ans <<endl;
        }

        cout<<ans<<"\n";
    }
    return 0;
}
 