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




void dfs(vector<int>adj[],vector<bool>&vis,int u, vector<int>&res) {
    vis[u]=true;
    for(auto &v:adj[u]) {
        if(!vis[v]) dfs(adj,vis,v,res);
    }
    res.push_back(u);
}



void solve() {

    int n,m; cin>>n>>m;
    vector<int>adj[n+1];
    vector<bool>vis(n+1);
    vector<int>res;
    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
    }

    for(int i=1; i<=n; i++) {
        if(!vis[i]) {
            dfs(adj,vis,i,res);
        }
    }

    reverse(res.begin(),res.end());

    // check is feasible (cycle)

    vector<int>pos(n+1);
    for(int i=0; i<res.size(); i++) {
        pos[res[i]]=i;
    }

    for(int u=1; u<=n; u++) {
        for(auto &v:adj[u]) {
            if(pos[v]<=pos[u]) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }

    for(auto &x:res) cout << x << " ";nl;

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
