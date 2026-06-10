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

struct Edge {
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

    vector<int>par(n+1,-1);
    vector<ll>dist(n+1,0);
    int last=-1;
    
    
    for(int i=0; i<n; i++) {
        last=-1;
        for(auto [u,v,w]:adj) {
            if(dist[u]+w<dist[v]) {
                dist[v]=max(-inf,dist[u]+w);
                last=v;
                par[v]=u;
            }
        }
    }

    if(last==-1) cout << "NO\n";
    else {
        cout << "YES\n";
        vector<int>res;
        int cyl=last;
        for(int i=0; i<n; i++) cyl=par[cyl];

        for(int cur=cyl;;cur=par[cur]) {
            res.push_back(cur);
            if(cur==cyl&&res.size()>1) break;
        }

        reverse(res.begin(),res.end());
        for(auto x:res) cout << x << " ";
        nl;
    }

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
