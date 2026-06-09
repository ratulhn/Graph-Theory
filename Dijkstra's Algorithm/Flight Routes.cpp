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

    int n,m,k; cin>>n>>m>>k;
    vector<pair<int,int>>adj[n+1];

    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    priority_queue<array<ll,2>,vector<array<ll,2>>,greater<>>pq;
    vector<vector<ll>>dist(n+1);
    pq.push({0,1});

    while(!pq.empty()) {
        auto [w,u]=pq.top(); pq.pop();
        if(dist[u].size()==k) continue;
        dist[u].push_back(w);
        for(auto [v,d]:adj[u]) {
            pq.push({d+w,v});
        }
    }
    for(int i=0; i<k; i++) cout << dist[n][i] << " ";
    nl;
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
