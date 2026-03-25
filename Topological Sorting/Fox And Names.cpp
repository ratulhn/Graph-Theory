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

    int n; cin>>n;
    vector<string>adj(n);
    vector<int>ord[26];
    vector<int>indeg(26);
    for(int i=0; i<n; i++) {
        cin>>adj[i];
    }

    for(int i=0; i<n-1; i++) {
        int idx=-1;
        for(int j=0; j<min(adj[i].size(),adj[i+1].size()); j++) {
            if(adj[i][j]!=adj[i+1][j]) {
                idx=j;break;
            }
        }
        if(idx==-1) {
            if(adj[i]>adj[i+1]) {
                cout << "Impossible\n"; return;
            }
        } else {
            int u=adj[i][idx]-'a';
            int v=adj[i+1][idx]-'a';
            indeg[v]++;
            ord[u].push_back(v);
        }
    }

    priority_queue<int,vector<int>,greater<int>>q;

    for(int i=0; i<26; i++) if(indeg[i]==0) q.push(i);
    vector<int>res;
    while(!q.empty()) {
        auto u=q.top(); q.pop();
        for(auto &v:ord[u]) {
            indeg[v]--;
            if(indeg[v]==0) {
                q.push(v);
            }
        }
        res.push_back(u);
    }
    
    if(res.size()!=26) cout << "Impossible\n";
    else {
        for(auto &x:res) cout << (char)('a'+x);nl;
    }

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
