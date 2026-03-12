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


int n,m; 
void dfs(int i, int j,vector<string>&adj, vector<bool>&vis, vector<int>&node) {
    if(i<0||j<0||i>=n||j>=m) return;
    if(adj[i][j]=='.'||vis[i*m+j]) return;
    vis[i*m+j]=true;
    node.push_back(i*m+j);
    dfs(i+1,j,adj,vis,node);
    dfs(i-1,j,adj,vis,node);
    dfs(i,j+1,adj,vis,node);
    dfs(i,j-1,adj,vis,node);
}




void solve() {

    cin>>n>>m;
    vector<string>adj(n); lp(i,0,n) cin>>adj[i];

    vector<int>par(n*m+m),val(n*m+m);
    vector<bool>vis(n*m+m);
    int id=1;

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(adj[i][j]=='#' && !vis[i*m+j]) {
                vector<int>node;
                dfs(i,j,adj,vis,node);
                val[id]=node.size();
                for(auto &x:node) {
                    par[x]=id;  
                }
                id++;
            
            }
        }
    }

    auto good=[&](int i, int j) {
        if(i<0||j<0||i>=n||j>=m || adj[i][j]=='.') return false;
        return true;
    };

   

    ll ans=0;
    for(int i=0; i<n; i++) {
        set<int>st;
        ll res=m;
        for(int j=0; j<m; j++) {
            
            if(good(i+1,j)) {
                int p = par[(i+1)*m+j];
                
                if(!st.count(p)) {
                    res+=val[p];
                    st.insert(p);
                }
            }
            if(good(i-1,j)) {
                int p = par[(i-1)*m+j];
                
                if(!st.count(p)) {
                    res+=val[p];
                    st.insert(p);
                }
            }
        }
        for(int j=0; j<m; j++) {
            if(st.count(par[i*m+j])) res--;
        }
        ans=max(ans,res);
    }
    for(int i=0; i<m; i++) {
        set<int>st;
        ll res=n;
        for(int j=0; j<n; j++) {
            
            if(good(j,i+1)) {
                int p = par[j*m+(i+1)];
            
                if(!st.count(p)) {
                    res+=val[p];
                    st.insert(p);
                }
            }
            if(good(j,i-1)) {
                int p = par[j*m+(i-1)];
            
                if(!st.count(p)) {
                    res+=val[p];
                    st.insert(p);
                }
            }
        }
        for(int j=0; j<n; j++) {
            if(st.count(par[j*m+i])) res--;
        }
        ans=max(ans,res);
    }

    cout << ans << "\n";

}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
