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


int n,m,r,c;
bool ans=false;

void dfs(int i, int j,vector<vector<bool>>&vis) {
    if(i<0||i>=n||j<0||j>=m) return;
    if(vis[i][j]) {
        return;
    }
    if(i==r&&j==c) {
        ans=true; return;
    }
    vis[i][j]=true;
    dfs(i+1,j,vis);
    dfs(i-1,j,vis);
    dfs(i,j+1,vis);
    dfs(i,j-1,vis);
}




void solve() {

    cin>>n>>m;
    vector<vector<bool>>vis(n+1,vector<bool>(m+1));
    vector<vector<char>>v(n+1,vector<char>(m+1));
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            char ch; cin>>ch;
            v[i][j]=ch;
            if(ch=='.') vis[i][j]=0;
            else vis[i][j]=1;
        }
    }
    int i,j; cin>>i>>j>>r>>c;
    i--,j--,r--,c--;
    vis[r][c]=vis[i][j]=false;
    dfs(i,j,vis);
    v[i][j]='.';
    auto good=[&](int i, int j) {
        if(i<0||i>=n||j<0||j>=m||v[i][j]=='X') return false;
        return true;
    };
    int cnt=0;
    if(good(r+1,c)) cnt++;
    if(good(r-1,c)) cnt++;
    if(good(r,c+1)) cnt++;
    if(good(r,c-1)) cnt++;
    
    if(i==r&&j==c) {
        if(cnt>0) cout << "YES\n";
        else cout << "NO\n";
    }
    else if(v[r][c]=='X') {
        if(ans) cout << "YES\n";
        else cout << "NO\n";
    }
    else {
        
        if(cnt>=2&&ans) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
