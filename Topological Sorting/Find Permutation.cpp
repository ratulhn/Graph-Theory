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
    vector<int>indeg(n+1);
    for(int i=0; i<m; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        indeg[v]++;
    }
    vector<int>indegt=indeg;
    vector<int>ord;
    priority_queue<int>q;


    for(int i=1; i<=n; i++) if(indeg[i]==0) q.push(i);

    while(!q.empty()) {
        int u=q.top(); q.pop();
        for(auto &v:adj[u]) {
            indeg[v]--;
            if(indeg[v]==0) q.push(v);
        }
        ord.push_back(u);
    }
    vector<int>ordm;
    priority_queue<int,vector<int>,greater<int>>qm;


    for(int i=1; i<=n; i++) if(indegt[i]==0) qm.push(i);

    while(!qm.empty()) {
        int u=qm.top(); qm.pop();
        for(auto &v:adj[u]) {
            indegt[v]--;
            if(indegt[v]==0) qm.push(v);
        }
        ordm.push_back(u);
    }

    if(ord.size()!=n||ordm.size()!=n) cout << "No\n";
    else {
        int id=1;
        vector<int>res(n+1);
        for(auto &x:ord) res[x]=id++;
        for(int i=0; i<n; i++) {
            if(ord[i]!=ordm[i]) {
                cout << "No\n"; return;
            }
        }
        cout << "Yes\n";
        for(int i=1; i<=n; i++) cout << res[i] << " ";nl;
    }

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
