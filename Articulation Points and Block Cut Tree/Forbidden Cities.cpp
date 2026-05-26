#include <bits/stdc++.h>
using namespace std;

// Fully encapsulated Block-Cut Tree (BCT) Black Box
struct BlockCutTree {
    int n;                          // Number of vertices in the original graph
    int bct_size;                   // Total size of the constructed BCT
    int timer;                      // DFS entry timer
    int num_bccs;                   // Total count of Biconnected Components (Blocks)
    
    vector<vector<int>> g;          // Original graph adjacency list
    vector<vector<int>> bcc;        // bcc[u] stores list of BCC IDs containing vertex u
    vector<int> dis, low, st;       // Tarjan's helper arrays
    vector<vector<int>> bcc_members;// bcc_members[i] stores vertices inside BCC i
    
    vector<vector<int>> bt;         // Block-Cut Tree adjacency list
    vector<int> id;                 // id[u] maps original vertex u to BCT node ID
    vector<int> art;                // art[u] = 1 if BCT node u is an AP, 0 otherwise
    vector<int> dep;                // dep[u] stores depth of BCT node u
    vector<int> cnt;                // cnt[u] stores prefix sum of APs from root to BCT node u
    vector<vector<int>> par;        // par[u][k] stores 2^k-th ancestor of u in BCT
    
    // Phase 1 DFS: Tarjan's algorithm for finding BCCs
    void tarjan_dfs(int u, int pre = 0) {
        low[u] = dis[u] = ++timer;
        st.push_back(u);
        for (auto v : g[u]) {
            if (!dis[v]) {
                tarjan_dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dis[u]) {
                    bct_size++;
                    
                    if (bct_size >= bcc_members.size()) {
                        bcc_members.resize(bct_size + 1);
                    }
                    
                    int x;
                    do {
                        x = st.back();
                        st.pop_back();
                        bcc[x].push_back(bct_size);
                        bcc_members[bct_size].push_back(x);
                    } while (x != v);
                    
                    bcc[u].push_back(bct_size);
                    bcc_members[bct_size].push_back(u);
                }
            } else if (v != pre) {
                low[u] = min(low[u], dis[v]);
            }
        }
    }

    // Phase 3 DFS: Precomputations for LCA and prefix sums
    void bct_dfs(int u, int pre = 0) {
        dep[u] = dep[pre] + 1;
        cnt[u] = cnt[pre] + art[u];
        par[u][0] = pre;
        for (int k = 1; k <= 19; k++) {
            par[u][k] = par[par[u][k - 1]][k - 1];
        }
        for (auto v : bt[u]) {
            if (v != pre) {
                bct_dfs(v, u);
            }
        }
    }

    // Binary lifting LCA query on the BCT (supporting up to 2^19 nodes)
    int get_lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int k = 19; k >= 0; k--) {
            if (dep[par[u][k]] >= dep[v]) {
                u = par[u][k];
            }
        }
        if (u == v) return u;
        for (int k = 19; k >= 0; k--) {
            if (par[u][k] != par[v][k]) {
                u = par[u][k];
                v = par[v][k];
            }
        }
        return par[u][0];
    }

    // Counts APs on BCT path between u and v (inclusive)
    int get_ap_dist(int u, int v) {
        int lc = get_lca(u, v);
        return cnt[u] + cnt[v] - 2 * cnt[lc] + art[lc];
    }

    int dist(int u, int v) {
        int lc = get_lca(u, v);
        return dep[u] + dep[v] - 2 * dep[lc];
    }

    // Constructor: Builds the BCT from the original graph (1-indexed)
    BlockCutTree(int n, const vector<pair<int, int>>& edges) : n(n), bct_size(0), timer(0), num_bccs(0) {
        g.resize(n + 1);
        bcc.resize(n + 1);
        dis.assign(n + 1, 0);
        low.assign(n + 1, 0);
        bcc_members.resize(n + 1);
        
        for (auto& edge : edges) {
            g[edge.first].push_back(edge.second);
            g[edge.second].push_back(edge.first);
        }

        // Step 1: Compute BCCs
        for (int i = 1; i <= n; i++) {
            if (!dis[i]) {
                tarjan_dfs(i);
            }
        }

        num_bccs = bct_size; // Store total BCC count

        // Step 2: Build BCT nodes and bipartite edges
        id.assign(n + 1, 0);
        art.assign(n + 2 * n + 1, 0);
        bt.resize(n + 2 * n + 1);

        for (int u = 1; u <= n; u++) {
            if (bcc[u].size() > 1) { // u is an Articulation Point
                id[u] = ++bct_size;
                art[id[u]] = 1;
                for (auto v : bcc[u]) {
                    bt[id[u]].push_back(v);
                    bt[v].push_back(id[u]);
                }
            } else if (bcc[u].size() == 1) { // u is a regular node
                id[u] = bcc[u][0];
            }
        }

        // Step 3: LCA precomputations (using 20 levels for 2^19 safety bound)
        dep.assign(bct_size + 1, 0);
        cnt.assign(bct_size + 1, 0);
        par.assign(bct_size + 1, vector<int>(20, 0));
        
        for (int i = 1; i <= bct_size; i++) {
            if (dep[i] == 0) {
                bct_dfs(i);
            }
        }
    }

    // --- PUBLIC API METHODS ---

    // Query: Returns the number of APs strictly between u and v (excluding u and v)
    int query(int u, int v) {
        if (u == v) return 0;
        int tu = id[u], tv = id[v];
        return get_ap_dist(tu, tv) - art[tu] - art[tv];
    }
    
    // Returns the total count of Biconnected Components in the graph
    int get_num_bccs() const {
        return num_bccs;
    }

    // Returns the list of vertices in BCC 'bcc_id' (1-indexed: 1 to num_bccs)
    const vector<int>& get_bcc_vertices(int bcc_id) const {
        return bcc_members[bcc_id];
    }
};

// Driver solver function
void solve() {
    int n, m,q; cin>>n>>m>>q;

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    // Instantiate BCT Black Box
    BlockCutTree bct(n, edges);

   
    while (q--) {
        int a,b,c; cin>>a>>b>>c;

        if (a == c || b == c) {
            cout << "NO\n"; continue;
        } 

        a=bct.id[a];
        b=bct.id[b];
        c=bct.id[c];
        if(bct.art[c] == 1&&bct.dist(a,b)==bct.dist(a,c)+bct.dist(c,b)) {
            cout << "NO\n";
        } else cout << "YES\n";
    }
}

int main() {
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
