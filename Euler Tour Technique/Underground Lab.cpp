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

vector<int>path;

void dfs(int u, vector<int>adj[], vector<bool>&vis) {
    vis[u]=true;
    path.push_back(u);
    for(auto &v:adj[u]) {
        if(!vis[v]) {
            dfs(v,adj,vis);
            if(path.back()!=u) path.push_back(u);
        }
    }
}




void solve() {

    int n,m,k; cin>>n>>m>>k;
    vector<int>adj[n+1];
    lp(i,0,m) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool>vis(n+1);
    dfs(1,adj,vis);
    int cnt=(2*n+k-1)/k;
    int tot=0;
    vector<int>res;
    for(int i=0; i<path.size(); i++) {
        res.push_back(path[i]);
        if(i==path.size()-1||res.size()==cnt) {
            cout << res.size() << " ";
            for(auto &x:res) cout << x << " ";
            nl;
            res.clear();
            tot++;
        }
    }

    while(tot<k) {
        cout << "1 1\n";tot++;
    }

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
