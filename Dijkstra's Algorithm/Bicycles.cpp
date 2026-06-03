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



 const long long inf = 1e18;

 struct State {
    ll time;
    ll u,bike;

    bool operator>(const State &s) const {
        return time>s.time;
    }
 };




void solve() {

    int n,m; cin>>n>>m;
    vector<pair<int,ll>>adj[n+1];
    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<ll>cost(n+1);
    lp(i,0,n) cin>>cost[i+1];

    vector<vector<ll>>dist(n+1,vector<ll>(1005,inf));
    priority_queue<State,vector<State>,greater<State>>pq;

    ll bike = cost[1];
    pq.push({0,1,bike});
    dist[1][bike]=0;
    
    while(!pq.empty()) {
        auto [time,u,bike]=pq.top(); pq.pop();
        if(time>dist[u][bike]) continue;
        
        for(auto &[v,d]:adj[u]) {
            int next_bike = min(bike,cost[v]);

            if((bike*d)+dist[u][bike]<dist[v][next_bike]) {
                dist[v][next_bike]=(bike*d)+dist[u][bike];
                pq.push({dist[v][next_bike],v,next_bike});
            }
        }
    }
    
    ll res=inf;
    for(int i=1; i<=1000; i++) res=min(res,dist[n][i]);
    cout << res << "\n";

}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
