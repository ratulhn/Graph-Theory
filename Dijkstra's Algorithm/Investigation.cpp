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







void solve() {

    int n,m; cin>>n>>m;
    vector<pair<int,int>>adj[n+1];
    lp(i,0,m) {
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    vector<ll>cnt(n+1,0),dist(n+1,inf),mx(n+1,-1),mn(n+1,inf);

    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>>pq;
    pq.push({0,1});
    dist[1]=0;
    cnt[1]=1;
    mx[1]=0;
    mn[1]=0;

    while(!pq.empty()) {
        auto [w,u]=pq.top(); pq.pop();
        if(w>dist[u]) continue;
        for(auto [v,d]:adj[u]) {
            if(dist[u]+d<dist[v]) {
                dist[v]=dist[u]+d;
                cnt[v]=cnt[u];
                mx[v]=mx[u]+1;
                mn[v]=mn[u]+1;
                pq.push({dist[v],v});
            } else if(dist[u]+d==dist[v]) {
                cnt[v]=(cnt[v]+cnt[u])%M;
                mx[v]=max(mx[v],mx[u]+1);
                mn[v]=min(mn[v],mn[u]+1);
            }
        }
    }
    cout << dist[n] << " " << cnt[n] << " " << mn[n] << " " << mx[n] << "\n";
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
