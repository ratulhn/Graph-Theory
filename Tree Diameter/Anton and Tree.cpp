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


const int N=2e5+10;
int n; 
int color[N],com[N];
vector<int>adj[N],compressed[N];
bool vis[N];

void dfs(int u, int id) {
    vis[u]=true;
    com[u]=id;
    for(auto &v:adj[u]) {
        if(!vis[v]&&color[u]==color[v]) dfs(v,id);
    }
}

int farthest(int s,vector<int>&dis) {
    dis.resize(n+1);
    dis.assign(n+1,1e9);
    dis[s]=0;
    queue<int>q;
    q.push(s);
    int last=s;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(auto &v:compressed[u]) {
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

    cin>>n;
    for(int i=1; i<=n; i++) cin>>color[i];
    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int id=1;
    for(int i=1; i<=n; i++) {
        if(!vis[i]) {
            dfs(i,id);
            id++;
        }
    }

    set<pair<int,int>>list;

    for(int u=1; u<=n; u++) {
        for(auto &v:adj[u]) {
            int par=com[u];
            int child=com[v];
            if(child!=par&&!list.count({par,child})&&!list.count({child,par})) {
                compressed[par].push_back(child);
                compressed[child].push_back(par);
                list.insert({par,child});
            }
        }
    }

    vector<int>dx;

    int x=farthest(1,dx);
    int y=farthest(x,dx);
    int len=dx[y];
    cout << (len+1)/2 << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
