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


vector<string>adj;
int n,m,k; 

void dfs(int i, int j, vector<vector<bool>>&vis) {
    if(i<0||i>=n||j<0||j>=m) return;
    if(adj[i][j]=='#'||vis[i][j]) return;
    vis[i][j]=true;
    dfs(i+1,j,vis);
    dfs(i-1,j,vis);
    dfs(i,j+1,vis);
    dfs(i,j-1,vis);
    if(k>0) {
        adj[i][j]='X';
        k--;
    }
}



void solve() {

    cin>>n>>m>>k;
    adj.resize(n);
    for(int i=0; i<n; i++) cin>>adj[i];
    vector<vector<bool>>vis(n+1,vector<bool>(m));
    for(int i=0; i<n; i++) {
        bool ok=false;
        for(int j=0; j<m; j++) {
            if(adj[i][j]=='.') {
                ok=true;
                dfs(i,j,vis);break;
            }
        }
        if(ok)break;
    }

    for(int i=0; i<n; i++) cout << adj[i] << "\n";

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
