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
  ll tot;
  dsu(int n) : par(n+1), rnk(n+1,0), size(n+1,1), c(n),tot(0) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
  bool same(int i, int j) { return find(i) == find(j); }
  int get_size(int i) { return size[find(i)]; }
  int count() { return c; } //connected components
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1; else --c;
    tot+=size[i]*1ll*size[j];
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j; size[j] += size[i];
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};




void solve() {

    int n,m; cin>>n>>m;
    vector<array<int,3>>edges;

    for(int i=0; i<n-1; i++) {
        int u,v,w; cin>>u>>v>>w;
        edges.push_back({w,u,v});
    }

    vector<pair<int,int>>query(m);
    for(int i=0; i<m; i++) cin>>query[i].first,query[i].second=i;

    vector<ll>res(m);

    dsu d(n);
    int cnt=0;

    sort(edges.begin(),edges.end());
    sort(query.begin(),query.end());

    for(int i=0; i<m; i++) {
        while(cnt<n-1 && edges[cnt][0]<=query[i].first) {
            auto &[w,u,v] = edges[cnt];
            d.merge(u,v);
            cnt++;
        }
        res[query[i].second]=d.tot;
    }
    for(auto i:res) cout << i <<" ";nl;
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
