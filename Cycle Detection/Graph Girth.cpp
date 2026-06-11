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
    vector<int>adj[n+1];
    lp(i,0,m) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int res=1e9;

    for(int i=1; i<=n; i++) {
        vector<int>d(n+1,0),used(n+1,0),par(n+1,0);
        queue<int>q;
        q.push(i);
        used[i]=1;
        par[i]=-1;
        while (!q.empty())
        {
            auto u=q.front(); q.pop();
            for(auto v:adj[u]) {
                if(used[v]&&par[u]!=v) {
                    res=min(res,d[u]+d[v]+1);
                }
                if(!used[v]) {
                    q.push(v);
                    d[v]=d[u]+1;
                    par[v]=u;
                    used[v]=1;
                }
            }
        }
    }

    if(res==1e9) cout << "-1\n";
    else cout << res << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
