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
                tree[node] = val;
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

        int n,q; cin>>n;
        Segment<long double>seg(n);
        EularTour G(n);
        for(int i=0; i<n-1; i++) {
            int u,v; cin>>u>>v;
            G.ae(u,v);
        }
        G.dfs(1);

        for(int i=1; i<=n; i++) {
            seg.update(G.in[i],0);
        }
        cin>>q;
        while(q--) {
            int t; cin>>t;
            ll x,y; cin>>x>>y;
            if(t==1) {
                seg.update(G.in[x],logl(y));
            } else {
                long double a= seg.query(G.in[x],G.out[x]);
                long double b= seg.query(G.in[y],G.out[y]);
                long double ans = a-b;
                if(ans>=logl(1e9)) {
                    ans=1e9;
                } else ans=expl(ans);
                cout << fixed << setprecision(10) << ans << "\n";
            }
        }
    
    }

    int main() {
        FastIO


        //int TT=1; cin>>TT; while(TT--)
        solve();

        return 0;
    }
