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
const ll inf=-1e18;


struct Edge{
    int u,v;
    ll w;
};




void solve() {

    int n,m; cin>>n>>m;
    
    vector<Edge>adj;

    for(int i=0; i<m; i++) {
        int u,v,w; cin>>u>>v>>w;
        adj.push_back({u,v,w});
    }

    vector<ll>dist(n+1,inf);
    dist[1]=0;

    for(int i=0; i<n-1; i++) {
        for(auto [u,v,w]:adj) {
            if(dist[u]!=inf) {
                if(dist[u]+w>dist[v]) {
                    dist[v]=dist[u]+w;
                }
            }
        }
    }

    vector<bool>neg(n+1,0);
    queue<int>qn;
    
    for(auto [u,v,w]:adj) {
        if(dist[u]!=inf) {
            if(dist[u]+w>dist[v]&&neg[v]==0) {
                dist[v]=dist[u]+w;
                neg[v]=true;
                qn.push(v);
            }
        }
    }

    while(!qn.empty()) {
        auto u=qn.front(); qn.pop();
        for(auto [un,v,w]:adj) {
            if(un==u&&neg[v]==0) {
                qn.push(v);
                neg[v]=true;
            }
        }
    }


    if(neg[n]) cout << "-1\n";
    else cout << dist[n] << "\n";

    
    
    nl;

}

int main() {
    FastIO


    //while(TT)
    solve();

    return 0;
}
