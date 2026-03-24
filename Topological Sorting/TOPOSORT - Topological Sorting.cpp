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








void solve() {

    int n,m; cin>>n>>m;
    vector<int>adj[n+1];
    vector<int>indeg(n+1);
    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        indeg[v]++;
    }

    priority_queue<int,vector<int>,greater<int>>q;

    for(int i=1; i<=n; i++) {
        if(indeg[i]==0) q.push(i);
    }
    vector<int>res;
    while(!q.empty()) {
        auto u=q.top(); q.pop();
        for(auto &v:adj[u]) {
            indeg[v]--;
            if(indeg[v]==0) {
                q.push(v);
            }
        }
        res.push_back(u);
    }
    if(res.size()!=n) cout << "Sandro fails.\n";
    else {
        for(auto &x:res) cout << x << " "; nl;
    }
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
