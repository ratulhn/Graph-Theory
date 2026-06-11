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

    int n; cin>>n;
    vector<pair<int,int>>adj[n+1];

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            int x; cin>>x;
            if(i==j||x==-1) continue;
            adj[i].push_back({j,x});
        }
    }

    for(int s=1; s<=n; s++) {
        vector<ll>dist(n+1,inf);
        priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>>pq;
        vector<int>first(n+1,-1),par(n+1,-1);
        for(auto [v,w]:adj[s]) {
            dist[v]=w;
            par[v]=s;
            first[v]=v;
            pq.push({w,v});
        }
        dist[s]=0;
        first[s]=s;
        ll ans=inf;
        while(!pq.empty()) {
            auto [w,u]=pq.top(); pq.pop();
            if(w>dist[u]) continue;
            for(auto [v,d]:adj[u]) {

                if(v==s) {
                    if(u!=first[u]) ans=min(ans,dist[u]+d);
                }

                if(dist[u]+d<dist[v]) {
                    dist[v]=dist[u]+d;
                    par[v]=u;
                    first[v]=first[u];
                    pq.push({dist[v],v});
                }
            }
        }

        for(int u=1; u<=n; u++) {
            for(auto [v,d]:adj[u]) {
                if(v==s||u==s) continue;
                if(first[u]!=first[v]&&first[u]!=-1&&first[v]!=-1)
                ans=min(ans,dist[u]+dist[v]+d);
            }
        }

        if(ans==inf) cout << "-1\n";
        else cout << ans << "\n";
    }


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
