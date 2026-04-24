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
class LazySegment {

public:
    int n;
    vector<T> tree, lazy;

    // merge function (sum)
    T merge_val(T a, T b) {
        return a | b;
    }

    // recalculate from children
    void maintain(int node) {
        tree[node] = merge_val(tree[node * 2], tree[node * 2 + 1]);
    }

    // push lazy value to current node
    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;

        // apply pending update
        tree[node] =  lazy[node];

        // propagate to children if not leaf
        if (l != r) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }

        lazy[node] = 0;
    }

    // range update
    void update(int node, int l, int r, int ql, int qr, T val) {
        push(node, l, r);

        // no overlap
        if (qr < l || r < ql) return;

        // complete overlap
        if (ql <= l && r <= qr) {
            lazy[node] = 1ll<<val;
            push(node, l, r);
            return;
        }

        int m = (l + r) / 2;

        update(node * 2, l, m, ql, qr, val);
        update(node * 2 + 1, m + 1, r, ql, qr, val);

        maintain(node);
    }

    // range query
    T query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);

        // no overlap
        if (qr < l || r < ql) return 0;

        // complete overlap
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int m = (l + r) / 2;

        T l_res = query(node * 2, l, m, ql, qr);
        T r_res = query(node * 2 + 1, m + 1, r, ql, qr);

        return merge_val(l_res, r_res);
    }

public:
    LazySegment(int n) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

    // user friendly update
    void update(int l, int r, T val) {
        update(1, 1, n, l, r, val);
    }

    // user friendly query
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }

    // point query
    T get(int i) {
        return query(1, 1, n, i, i);
    }
};






void solve() {

    int n,q; cin>>n>>q;
    vector<int>col(n+1);
    lp(i,0,n) cin>>col[i+1];
    EularTour G(n);
    for(int i=0; i<n-1; i++) {
        int u,v; cin>>u>>v;
        G.ae(u,v);
    }
    LazySegment<ll>seg(n);
    G.dfs(1);
    for(int i=1; i<=n; i++) {
        seg.update(G.in[i],G.in[i],col[i]);
    }
    while(q--) {
        int t; cin>>t;
        if(t==1) {
            int v,c; cin>>v>>c;
            seg.update(G.in[v],G.out[v],c);
        } else {
            int v; cin>>v;
            cout << __builtin_popcountll(seg.query(G.in[v],G.out[v])) << "\n";
        }
    }

}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
