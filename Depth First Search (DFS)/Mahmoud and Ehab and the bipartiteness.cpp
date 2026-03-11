//The maximum number of edges that can exist is l * r in a bipartite graph


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



void dfs(vector<int>adj[],int u, int p, int c, vector<int>&col) {
    col[c]++;
    for(auto &v:adj[u]) {
        if(v!=p) {
            dfs(adj,v,u,c^1,col);
        }
    }
}




void solve() {

    int n; cin>>n;
    vector<int>adj[n+1];
    vector<int>col(2);
    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(adj,1,0,0,col);

    cout << col[0]*1ll*col[1]-n+1 << "\n";


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
