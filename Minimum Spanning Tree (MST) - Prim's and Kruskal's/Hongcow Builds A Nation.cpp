#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> 
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // find_by_order, order_of_key

#define FastIO ios::sync_with_stdio(false);cin.tie(nullptr);
#define dbg(v) cout << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << "\n";
//#include "dbgtest.h"
#define ll long long
#define all(v) v.begin(),v.end()
#define nl cout<<'\n'
#define lp(i,a,n) for(int i=a; i<n; i++)

const int M = 1e9+7;



struct dsu {
  vector<int> par, rnk, size; int c;
  dsu(int n) : par(n+1), rnk(n+1,0), size(n+1,1), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
  bool same(int i, int j) { return find(i) == find(j); }
  int get_size(int i) { return size[find(i)]; }
  int count() { return c; } //connected components
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1; else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j; size[j] += size[i];
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};




void solve() {

    int n,m,k; cin>>n>>m>>k;
    dsu d(n);

    vector<int>c(k); lp(i,0,k) cin>>c[i];

    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        d.merge(u,v);
    }

    ll tot_gov=0;
    ll mx_comp=0;

    vector<ll>comp;

    for(int i=0; i<k; i++) {
        int p = d.find(c[i]);
        int sz= d.get_size(p);
        tot_gov+=sz;
        comp.push_back(sz);
        mx_comp=max((ll)sz,mx_comp);
    }

    ll cur = n-tot_gov;
    bool flag=true;
    ll res=0;
    for(auto x:comp) {
        if(x==mx_comp&&flag) {
            flag=false;
            ll s = x+cur;
            res+=s*1ll*(s-1)/2ll;
        } else res+=x*1ll*(x-1)/2ll;
    }

    cout << res-m << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
