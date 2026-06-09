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
const ll inf=1e18+7;







void solve() {

    int n,m; cin>>n>>m;
    vector<pair<int,int>>adj[n+1];
    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    priority_queue<array<ll,3>,vector<array<ll,3>>,greater<>>pq;
    vector<vector<ll>>dist(n+1,vector<ll>(2,inf));

    dist[1][0]=0;
    pq.push({0,1,0});

    while(!pq.empty()) {
        auto [w,u,f]=pq.top(); pq.pop();
        if(w>dist[u][f]) continue;
        for(auto [v,d]:adj[u]) {

            if(dist[u][f]+d<dist[v][f]) {
                dist[v][f]=dist[u][f]+d;
                pq.push({dist[v][f],v,f});
            }
            if(f==0) {
                if(dist[u][f]+(d/2)<dist[v][1]) {
                    dist[v][1]=dist[u][f]+(d/2);
                    pq.push({dist[v][1],v,1});
                }
            }
        }
    }

    cout << min(dist[n][0],dist[n][1]) << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
