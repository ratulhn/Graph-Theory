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


const int N = 3e5 + 9, LG = 18;

bool vis[N];
int par[N][LG + 1], dep[N], arr[N];
void dfs(int u) {
    if(vis[u]) return;
    vis[u]=true;
    dfs(arr[u]);
    int p=arr[u];
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  
}

int kth(int u, int k) {
    if(k < 0) return -1;
    for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
    return u;
}






void solve() {

    int n,q; cin>>n>>q;
    for(int i=1; i<=n; i++) {
        cin>>arr[i];
    }

    for(int i=1; i<=n; i++) {
        if(!vis[i]) dfs(i);
    }

    while(q--) {
        int a,b; cin>>a>>b;
        int cycle_entry_a = kth(a,dep[a]);
        int ans=-1;
        if(kth(a,dep[a]-dep[b])==b) {
            ans=dep[a]-dep[b];
        } else if(kth(cycle_entry_a,dep[cycle_entry_a]-dep[b])==b) {
            ans=dep[cycle_entry_a]-dep[b]+dep[a];
        } else ans=-1;

        cout << ans << "\n";
    }


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
