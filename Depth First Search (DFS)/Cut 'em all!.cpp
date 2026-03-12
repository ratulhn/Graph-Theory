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




void dfs(int u, int p, vector<int>g[], vector<int>&sub, int &res) {
    sub[u]=1;
    for(auto &v:g[u]) {
        if(v!=p) {
            dfs(v,u,g,sub,res);
            sub[u]+=sub[v];
        }
    }
    if(sub[u]>0&&sub[u]%2==0) {
        sub[u]=0;
        res++;
    }
}



void solve() {

    int n; cin>>n;
    vector<int>g[n+1];
    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>sub(n+1);
    int res=0;
    dfs(1,0,g,sub,res);
    if(n%2) cout << "-1\n";
    else cout << res-1 << "\n";
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
