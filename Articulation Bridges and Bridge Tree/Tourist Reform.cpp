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



struct Edge {
    int u,v;
};




struct TECC {

    int n,k;
    vector<vector<pair<int,int>>>g;
    vector<bool>used,is_bridge;
    vector<int>comp,ord,low;
   

    void dfs(int x, int prv_edge, int &c) {
        used[x]=1; ord[x]=c++; low[x]=n;
        for(auto &edge:g[x]) {
            int y=edge.first;
            int id=edge.second;
            if(id==prv_edge) continue;
            if(used[y]) {
                low[x]=min(low[x],ord[y]);
                continue;
            }
            dfs(y,id,c);
            low[x]=min(low[x],low[y]);

            if(ord[x]<low[y]) {
                is_bridge[id]=true;
            }
        }
    }

    void dfs2(int x, int num) {
        comp[x]=num;
        for(auto &edge:g[x]) {
            int y=edge.first;
            int id=edge.second;
            if(comp[y]!=-1) continue;
            if(is_bridge[id]) {
                k++;
                dfs2(y,k);
            } else dfs2(y,num);
        }
    }

    TECC(int n, int m, const vector<Edge>&edges): n(n),k(0), used(n), comp(n,-1), ord(n), low(n), is_bridge(m,false) {
        int c=0;
        g.resize(n);
        for(int i=0; i<m; i++) {
            g[edges[i].u].push_back({edges[i].v,i});
            g[edges[i].v].push_back({edges[i].u,i});
        }
        for(int i=0; i<n; i++) {
            if(used[i]) continue;
            dfs(i,-1,c);
            dfs2(i,k);
            k++;
        }
    }
};


vector<pair<int,int>>oriented_edges;
vector<bool>edge_oriented;
vector<bool>vis;

void oriented_dfs(int x, const TECC&tecc) {
    vis[x]=true;
    for(auto &edge:tecc.g[x]) {
        int y=edge.first;
        int id=edge.second;
        if(edge_oriented[id]) continue;
        edge_oriented[id]=true;
        if(tecc.is_bridge[id]) {
            oriented_edges[id]={y,x};
        } else {
            oriented_edges[id]={x,y};
        }

        if(!vis[y]) oriented_dfs(y,tecc);
    }
}



void solve() {

    int n,m; cin>>n>>m;
    vector<Edge>edges(m);
    for(int i=0; i<m; i++) {
        cin>>edges[i].u>>edges[i].v;
        edges[i].u--;edges[i].v--;
    }

    TECC tecc(n,m,edges);

    vector<int>comp_size(tecc.k,0);
    for(int i=0; i<n; i++) {
        comp_size[tecc.comp[i]]++;
    }

    int max_comp_id=0;
    for(int i=0; i<tecc.k; i++) {
        if(comp_size[i]>comp_size[max_comp_id]) {
            max_comp_id=i;
            
        }
    }

    int root = -1;
    for(int i = 0; i < n; i++) {
        if(tecc.comp[i] == max_comp_id) {
            root = i;
            break;
        }
    }

    edge_oriented.assign(m,false);
    oriented_edges.resize(m);
    vis.assign(n,false);

    oriented_dfs(root,tecc);

    cout << comp_size[max_comp_id] << "\n";
    for(int i=0; i<m; i++) {
        cout << oriented_edges[i].first+1 << " " << oriented_edges[i].second+1 << "\n";
    }

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
