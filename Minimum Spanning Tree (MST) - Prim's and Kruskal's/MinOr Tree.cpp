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

    int n,m; cin>>n>>m;
    vector<array<int,3>>edges;
    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        edges.push_back({w,u,v});
    }
    sort(edges.begin(),edges.end());

    auto good=[&](int tmp) {
        dsu d(n);
        int comp=n;
        for(auto &[w,u,v]:edges) {
            if((w|tmp)==tmp) {
                if(!d.same(u,v)) {
                    d.merge(u,v);
                    comp--;
                    if(comp==1) return true;
                }
            }
        }
        return comp==1;
    };

    int ans = (1<<30)-1;

    for(int i=29; i>=0; i--) {
        int tmp = ans^(1<<i);
        if(good(tmp)) {
            ans=tmp;
        }
    }
    cout << ans << "\n";
}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
