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

    int n,m,k; cin>>n>>m>>k;
    vector<int>prod(n+1);
    lp(i,0,n) cin>>prod[i+1];
    vector<int>g[n+1];
    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>dis(n+1,1e9),cost(k+1);
    queue<int>q;
    q.push(1);
    dis[1]=0;

    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(auto &v:g[u]) {
            if(dis[u]+1<dis[v]) {
                dis[v]=dis[u]+1;
                q.push(v);
            }
        }
    }

    vector<int>res(k+1);

    for(int i=1; i<=n; i++) {
        res[prod[i]]=max(res[prod[i]],dis[i]);
    }

    for(int i=1; i<=k; i++) cout << res[i] << " ";nl;

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
