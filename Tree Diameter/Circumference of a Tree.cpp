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



int farthest(vector<int>adj[],int s, int n, vector<int>&dis) {
    dis.resize(n+1);
    dis.assign(n+1,1e9);
    queue<int>q;
    q.push(s);
    int last=s;
    dis[s]=0;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(auto &v:adj[u]) {
            if(dis[u]+1<dis[v]) {
                dis[v]=dis[u]+1;
                q.push(v);
                last=v;
            }
        }
    }
    return last;
}




void solve() {

    int n; cin>>n;
    vector<int>adj[n+1];
    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int>dx,dy;

    int x = farthest(adj, 1, n, dx);
    int y = farthest(adj, x, n, dx);
    farthest(adj, y, n, dy);

    cout << 3*dy[x] << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
