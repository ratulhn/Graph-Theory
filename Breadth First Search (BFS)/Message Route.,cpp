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








void solve() {

    int n,m; cin>>n>>m;
    vector<int>g[n+1];
    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<int>q;
    vector<int>par(n+1);

    vector<bool>vis(n+1);

    q.push(1);
    vis[1]=true;
    bool ans=false;
    while(!q.empty()) {
        auto u=q.front();
        q.pop();
        if(u==n) {
            ans=true;break;
        }
        for(auto &v:g[u]) {
            if(!vis[v]) {
                vis[v]=true;
                q.push(v);
                par[v]=u;
            }
        }
    }
    if(!ans) {
        cout << "IMPOSSIBLE\n";return;
    }
    stack<int>res;
    int x=n;
    while(par[x]!=x) {
        res.push(x);
        x=par[x];
    }
    cout << res.size() << "\n";
    while(!res.empty()) {
        cout << res.top() << " ";
        res.pop();
    }

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
