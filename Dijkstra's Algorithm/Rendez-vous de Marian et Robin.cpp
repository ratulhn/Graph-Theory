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
const ll inf=1e18;

struct State {
    ll w;
    int u,h;
    bool operator>(const State &s) const {
        return w>s.w;
    }
};

auto F(vector<pair<int,int>>adj[],vector<int>&horse, int n, int s) {
    vector<vector<ll>>dist(n+1,vector<ll>(2,inf));
    priority_queue<State,vector<State>,greater<State>>pq;
    pq.push({0,s,horse[s]});
    dist[s][horse[s]]=0;
    while(!pq.empty()) {
        auto [w,u,h]=pq.top(); pq.pop();
        if(w>dist[u][h]) continue;
        for(auto [v,d]:adj[u]) {
            int next=h|horse[v];
            if(h) d=d/2;
            if(dist[u][h]+d<dist[v][next]) {
                dist[v][next]=dist[u][h]+d;
                pq.push({dist[v][next],v,next});
            }
        }
    }

    return dist;
}




void solve() {

    int n,m,h; cin>>n>>m>>h;
    vector<pair<int,int>>adj[n+1];
    vector<int>horse(n+1);
    for(int i=0; i<h; i++) {
        int x; cin>>x;
        horse[x]=1;
    }
    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w}); 
        adj[v].push_back({u,w}); 
    }

    auto x = F(adj,horse,n,1);
    auto y = F(adj,horse,n,n);

    ll res=inf;

    for(int i=1; i<=n; i++) {
        ll dx = min(x[i][0],x[i][1]);
        ll dy = min(y[i][0],y[i][1]);
        if(dx!=inf&&dy!=inf)
        res=min(res,max(dx,dy));
    }

    if(res==inf) cout << "-1\n";
    else cout << res << "\n";

}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
