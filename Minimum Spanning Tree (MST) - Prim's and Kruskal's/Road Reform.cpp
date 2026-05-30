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
    vector<array<int,3>>edges(m);
    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        edges[i][0]=w;
        edges[i][1]=u;
        edges[i][2]=v;
    }
    sort(edges.begin(),edges.end());
    dsu d(n);   

    vector<int>ed;

    for(int i=0; i<m; i++) {
        if(!d.same(edges[i][2],edges[i][1])) {
            ed.push_back(edges[i][0]);
            d.merge(edges[i][2],edges[i][1]);
        }
    }

    if(ed.back()<=k) {
        ll res=1e18;
        for(int i=0; i<m; i++) {
            res=min(res,(ll)abs(edges[i][0]-k));
        }
        cout << res << "\n";
    } else {
        ll res=0;
        for(auto &e:ed) {
            if(e>k) res+=e-k;
        }
        cout << res << "\n";
    }


}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
