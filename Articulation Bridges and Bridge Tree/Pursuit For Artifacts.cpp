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
    int u,v,w;
};

struct TECC {

    int n,k;
    vector<vector<int>>g;
    vector<vector<pair<int,int>>>t; 
    vector<bool>used;
    vector<int>comp,ord,low;
    using pair_edge = pair<int,int>;
    vector<pair_edge>br;
    vector<bool> has_artifact;

    void dfs(int x, int prv, int &c) {
        used[x]=1; ord[x]=c++; low[x]=n;
        bool mul = 0;
        for(auto y:g[x]) {
            if(used[y]) {
                if(y!=prv||mul) low[x]=min(low[x],ord[y]);
                else mul=1;
                continue;
            }
            dfs(y,x,c);
            low[x]=min(low[x],low[y]);
        }
    }

    void dfs2(int x, int num) {
        comp[x]=num;
        for(auto y:g[x]) {
            if(comp[y]!=-1) continue;
            if(ord[x]<low[y]) {
                br.push_back({x,y});
                k++;
                dfs2(y,k);
            } else dfs2(y,num);
        }
    }

    TECC(int n,const vector<Edge>&edges): n(n), used(n), comp(n,-1), ord(n), low(n), k(0) {
        
        g.resize(n);

        for(auto &e:edges) {
            g[e.u].push_back(e.v);
            g[e.v].push_back(e.u);
        }
        
        int c=0;
        for(int i=0; i<n; i++) {
            if(used[i]) continue;
            dfs(i,-1,c);
            dfs2(i,k);
            k++;
        }

        has_artifact.assign(k,false);
    }

    void build_tree(const vector<Edge>& edges) {
        t.resize(k);
        for(auto e:edges) {
            int x = comp[e.u], y=comp[e.v];
            if(x==y) {
                if(e.w==1) has_artifact[x]=true;
            } else {
                t[x].push_back({y,e.w});
                t[y].push_back({x,e.w});
            }
            
        }
    }


};


bool dfs_path(int u, int p, int target, bool any_art, const TECC&tecc) {
    any_art=any_art||tecc.has_artifact[u];

    if(u==target) {
        return any_art;
    }

    for(auto &edge:tecc.t[u]) {
        int v=edge.first;
        int w=edge.second;

        if(v==p) continue;

        if(dfs_path(v,u,target,any_art||(w==1),tecc)) {
            return true;
        }
    }
    return false;
}




void solve() {

    int n,m; cin>>n>>m;
    vector<Edge>edges(m);

    for(int i=0; i<m; i++) {
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
        edges[i].u--;
        edges[i].v--;
    }

    int start,target; cin>>start>>target;
    start--;target--;

    TECC tecc(n,edges);

    tecc.build_tree(edges);

    int start_comp = tecc.comp[start];
    int target_comp = tecc.comp[target];

    if(dfs_path(start_comp,-1,target_comp,0,tecc)) {
        cout << "YES\n";
    } else cout << "NO\n";


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
