
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



int farthest(int s, int n, vector<int>&dis, vector<int>adj[]) {
    dis.resize(n+1);
    dis.assign(n+1,1e9);
    queue<int>q;
    dis[s]=0;
    q.push(s);
    int last=s;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(auto &v:adj[u]) {
            if(dis[u]+1<dis[v]) {
                dis[v]=dis[u]+1;
                q.push(v);
            }
        }
        last=u;
    }
    
    return last;
}




void solve() {

    int n; cin>>n;
    vector<int>adj[n+1];
    vector<int>dx,dy;
    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int x=farthest(1,n,dx,adj);
    int y=farthest(x,n,dy,adj);
    cout << dy[y] << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
