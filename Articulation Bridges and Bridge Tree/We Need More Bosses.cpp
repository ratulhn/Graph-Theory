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



struct TECC { // 0 indexed

    int n,k;
    vector<vector<int>>g,t;
    vector<bool>used;
    vector<int>comp,ord,low;
    using edge = pair<int,int>;
    vector<edge>br;

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

    TECC(const vector<vector<int>>&g): g(g), n(g.size()), used(n), comp(n,-1), ord(n), low(n), k(0) {
        int c=0;
        for(int i=0; i<n; i++) {
            if(used[i]) continue;
            dfs(i,-1,c);
            dfs2(i,k);
            k++;
        }
    }

    void build_tree() {
        t.resize(k);
        for(auto e:br) {
            int x = comp[e.first], y=comp[e.second];
            t[x].push_back(y);
            t[y].push_back(x);
        }
    }


};


int farthest(int s, int n, vector<int>&dis, vector<vector<int>>&adj) {
    dis.resize(n+1);
    dis.assign(n+1,1e9);
    queue<int>q;
    dis[s]=0;
    q.push(s);
    int last=s;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(auto &v:adj[u]) {
            if(dis[u]+1<dis[v]) {
                dis[v]=dis[u]+1;
                q.push(v);
            }
        }
        last=u;
    }
    
    return last;
}


void solve() {

    int n,m; cin>>n>>m;
    vector<vector<int>>g(n);
    for(int i=0; i<m; i++) {
        int a,b; cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    TECC t(g);
    t.build_tree();
    vector<int>dx,dy;
    int x = farthest(0,t.k,dx,t.t);
    int y = farthest(x,t.k,dx,t.t);

    cout << dx[y] << '\n';

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
