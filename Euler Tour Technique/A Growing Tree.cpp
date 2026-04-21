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


struct EularTour {
    int N, timer = 0;
    vector<int> in, out;
    vector<vector<int>> adj;
    EularTour(int _N) {
        N = _N+1;
        adj.resize(N);
        in.resize(N), out.resize(N);
    }
    void ae(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int u, int p = -1) {
        in[u] = ++timer;
        for (auto& v: adj[u]) if (v != p) { 
        dfs(v, u);
        }
        out[u] = timer; 
    }
};


template<typename T>
class Segment {

public:
    int n;
    vector<T> tree;

    T merge_val(T a, T b) {
        return a+b;
    }

    void maintain(int node) {
        tree[node] = merge_val(tree[node*2], tree[node*2+1]);
    }

    void update(int node, int l, int r, int i, T val) {
        if (l == r) {
            tree[node] += val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) update(node*2, l, m, i, val);
        else update(node*2+1, m+1, r, i, val);
        maintain(node);
    }

    T query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int m = (l + r) / 2;
        if (qr <= m) return query(node*2, l, m, ql, qr);
        if (ql > m) return query(node*2+1, m+1, r, ql, qr);
        T l_res = query(node*2, l, m, ql, qr);
        T r_res = query(node*2+1, m+1, r, ql, qr);
        return merge_val(l_res, r_res);
    }

public:

    Segment(int n) : n(n), tree(4 * n) {}

    void update(int i, T val) {
        update(1, 1, n, i, val);
    }

    T query(int ql, int qr) {
        return query(1, 1, n, ql, qr);
    }

    T get(int i) {
        return query(1, 1, n, i, i);
    }
};





void solve() {

    int n; cin>>n;
    vector<array<int,3>>qr(n+1);
    vector<int>adj[n+2];
    int id=2;
    lp(i,0,n) {
        cin>>qr[i][0];
        if(qr[i][0]==1) {
            cin>>qr[i][1];
            qr[i][2]=id++;
            int u=qr[i][1],v=qr[i][2];
            adj[u].push_back(v);
        } else {
            cin>>qr[i][1]>>qr[i][2];
        }
    }



    EularTour G(id);
    Segment<ll>seg(id+5);

    for(int i=1; i<id; i++) {
        if(adj[i].size()) {
            for(auto &v:adj[i]) {
                G.ae(i,v);
            }
        }
    }
    G.dfs(1);

    for(int i=1; i<id; i++) {
        seg.update(G.in[i],0);
    }

    for(int i=0; i<n; i++) {
        if(qr[i][0]==1) {
            int s=qr[i][2];
            ll sum = seg.query(1,G.in[s]);
            seg.update(G.in[s],-sum);
            seg.update(G.out[s]+1,sum);
        } else {
            int s=qr[i][1];
            ll sum =qr[i][2];
            seg.update(G.in[s],sum);
            seg.update(G.out[s]+1,-sum);
        }
    }

    for(int i=1; i<id; i++) {
        cout << seg.query(1,G.in[i]) << " ";
    }nl;

}

int main() {
    FastIO


    int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
