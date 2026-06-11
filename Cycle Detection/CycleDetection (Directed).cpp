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
const int N=1e5+10;

int par[N],vis[N];
vector<int>cycle;


bool dfs(vector<int>adj[], int u) {
    if(!cycle.empty()) return true;
    vis[u]=1;
    for(auto v:adj[u]) {
        if(vis[v]==0) {
            par[v]=u;
            if(dfs(adj,v)) return true;
        } else if(vis[v]==1) {
            cycle.push_back(v);
            for(int cur=u; cur!=v; cur=par[cur]) {
                cycle.push_back(cur);
            }
            cycle.push_back(v);
            reverse(cycle.begin(),cycle.end());
            return true;
        }
    }
    vis[u]=2;
    return false;
}




void solve() {

    int n,m; cin>>n>>m;
    vector<int>adj[n+1];
    lp(i,0,m) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
    }

    for(int i=1; i<=n; i++) {
        if(!vis[i]&&dfs(adj,i)) {
            cout << cycle.size() << "\n";
            for(auto x:cycle) cout << x << ' ';nl;
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
