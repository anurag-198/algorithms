#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <cassert>
 
using namespace std;
 
const int md = 1000000007;
 
inline void add(int &a, int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
}
 
inline int mul(int a, int b) {
  return (long long)a * b % md;
}
 
inline int get_sq(int x) {
  int y = x + 1;
  int z = 2 * x + 1;
  int res = mul(x, mul(y, z));
  res = mul(res, 166666668);
  return res;
}
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int real_n = n;
    vector <int> p;
    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        p.push_back(i);
        while (n % i == 0) {
          n /= i;
        }
      }
    }

    if (n > 1) {
      p.push_back(n);
    }

    int cnt = p.size();
    int ans = 0;
    
    for (int t = 0; t < (1 << cnt); t++) {
      int num = 1;
      int w = 1;
      
      for (int i = 0; i < cnt; i++) {
        if (t & (1 << i)) {
          num *= p[i];
          w *= -1;
        }
      }
   //   cout <<num<<" "<< md + w <<" " << get_sq(real_n/num) <<" "<< mul(mul(num, num), get_sq(real_n / num))<<endl;
      add(ans, mul(md + w, mul(mul(num, num), get_sq(real_n / num))));
     // cout << ans << endl;
    }

   
    if (real_n == 1) {
      ans = 0;
    }
    printf("%d\n", ans);
  }
  return 0;
}