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



void dfs(vector<int>adj[],int u, int p, int t, vector<int>&v) {
    v[u]=t;
    for(auto &x:adj[u]) {
        if(x!=p) {
            dfs(adj,x,u,t+1,v);
        }
    }
}


void depth(vector<int>adj[], int u, int p, vector<int>&dep) {
    bool leaf=true;
    for(auto &x:adj[u]) {
        if(x!=p) {
            leaf=false;
            depth(adj,x,u,dep);
            dep[u]=max(dep[u],dep[x]+1);
        }
    }
    if(leaf) dep[u]=0;
    
}




void solve() {

    int n,m; cin>>n>>m;
    vector<int>adj[n+1];

    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int>a(n+1),b(n+1);
    dfs(adj,1,0,0,a);
    dfs(adj,m,0,0,b);
    vector<int>dep(n+1);
    int res=0;

    depth(adj,1,0,dep);
    for(int i=1; i<=n; i++) {
        if(b[i]<a[i]) res=max(res,dep[i]+a[i]);
    }

    cout << 2*res << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
