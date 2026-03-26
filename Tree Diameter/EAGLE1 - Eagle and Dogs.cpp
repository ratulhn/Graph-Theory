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



int farthest(vector<pair<int,int>>adj[],int s,int n, vector<ll>&dis) {
    dis.resize(n+1);
    dis.assign(n+1,1e18);
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>q;
    q.push({0,s});
    dis[s]=0;
    int last=s;
    while(!q.empty()) {
        auto [w,u]=q.top(); q.pop();
        if(w > dis[u]) continue;
        for(auto &[v,d]:adj[u]) {
            if(dis[u]+d<dis[v]) {
                dis[v]=dis[u]+d;
                q.push({dis[v],v});
            }
        }
        last=u;
    }
    return last;
}   




void solve() {

    int n; cin>>n;
    vector<pair<int,int>>adj[n+1];
    vector<ll>dx,dy;

    for(int i=0; i<n-1; i++) {
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    int x = farthest(adj,1,n,dx);
    int y = farthest(adj,x,n,dx);
    farthest(adj,y,n,dy);
    for(int i=1; i<=n; i++) {
        cout << max(dx[i],dy[i]) << " ";
    }nl;
}   

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
