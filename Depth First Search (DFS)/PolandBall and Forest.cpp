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


void dfs(vector<int>adj[], int u, vector<bool>&vis) {
    vis[u]=true;
    for(auto &v:adj[u]) {
        if(!vis[v]) dfs(adj,v,vis);
    }
}




void solve() {

    int n; cin>>n;
    vector<int>adj[n+1];
    for(int u=1; u<=n; u++) {
        int v; cin>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool>vis(n+1);
    int res=0;

    for(int i=1; i<=n; i++) {
        if(!vis[i]) {
            res++;dfs(adj,i,vis);
        }
    }
    cout << res << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
