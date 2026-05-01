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



const int N = 3e5 + 9, LG = 18;

vector<pair<int,int>> g[N];
int par[N][LG + 1], dep[N], sz[N],vmin[N][LG+1];
void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  for (auto v: g[u]) if (v.first != p) {
    vmin[v.first][0]=v.second;
    dfs(v.first, u);
    sz[u] += sz[v.first];
  }
}
void prepare(int n){
    for(int j=1;j<=LG;j++)for(int i=1;i<=n;i++){
        vmin[i][j] = min(vmin[i][j - 1], vmin[par[i][j - 1]][j - 1]);
    }
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int kth(int u, int k) {
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
  return u;
}
int lift(int u, int k,int &res) {
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) res=min(res,vmin[u][i]), u = par[u][i];
  return u;
}
int dist(int u, int v) {
  int l = lca(u, v);
  int res=1e9;
  lift(u,dep[u]-dep[l],res);
  lift(v,dep[v]-dep[l],res);
  return res;
}
//kth node from u to v, 0th node is u
int go(int u, int v, int k) {
  int l = lca(u, v);
  int d = dep[u] + dep[v] - (dep[l] << 1);
  assert(k <= d);
  if (dep[l] + k <= dep[u]) return kth(u, k);
  k -= dep[u] - dep[l];
  return kth(v, dep[v] - dep[l] - k);
}




void solve() {

    int n,m; cin>>n>>m;
    

    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    dfs(1);
    prepare(n);
    int q; cin>>q;
    while(q--) {
        int u,v; cin>>u>>v;
        cout << dist(u,v) << "\n";
    }
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
