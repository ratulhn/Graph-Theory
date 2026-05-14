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


const int N = 5e5 + 9;

bool vis[N];
vector<int> g[N], r[N], G[N], vec; //G is the condensed graph
void dfs1(int u) {
  vis[u] = 1;
  for(auto v: g[u]) if(!vis[v]) dfs1(v);
  vec.push_back(u);
}

vector<int> comp;
void dfs2(int u) {
  comp.push_back(u);
  vis[u] = 1;
  for(auto v: r[u]) if(!vis[v]) dfs2(v);
}





void solve() {

    int n,m; cin>>n>>m;

    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        r[v].push_back(u);
    }

    for(int i=1; i<=n; i++) {
        if(!vis[i]) dfs1(i);
    }
    reverse(vec.begin(),vec.end());
    memset(vis,0,sizeof vis);

    int scc=0;

    vector<int>res(n+1);

    for(auto u:vec) {
        if(!vis[u]) {
            comp.clear();
            dfs2(u);
            scc++;
            for(auto x:comp) res[x]=scc;
        }
    }
    cout << scc << "\n";
    for(int i=1; i<=n; i++) cout << res[i] << " ";nl;
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
