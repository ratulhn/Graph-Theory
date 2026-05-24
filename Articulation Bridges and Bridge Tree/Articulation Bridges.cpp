#include <bits/stdc++.h>
using namespace std;

// Header files for Policy-Based Data Structures (PBDS)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// Definition of an Ordered Set (oset) using PBDS.
// It acts like a standard std::set but allows two additional O(log N) operations:
// 1. find_by_order(k): Returns an iterator to the k-th smallest element (0-indexed).
// 2. order_of_key(x): Returns the number of elements strictly smaller than x.
template<class T> 
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Macros for optimization and convenience
#define FastIO ios::sync_with_stdio(false);cin.tie(nullptr); // Speeds up C++ input/output operations
#define dbg(v) cout << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << "\n"; // Basic debugging utility
#define ll long long
#define all(v) v.begin(),v.end() // Quick access to begin and end iterators of containers
#define nl cout<<'\n'            // Fast newline print
#define lp(i,a,n) for(int i=a; i<n; i++) // Standard loop macro

const int M = 1e9+7; // Commonly used modulo value for competitive programming tasks


// Two-Edge-Connected Components (TECC) solver structure (0-indexed)
struct TECC { 

    int n, k;                      // n: number of vertices, k: count of 2-edge-connected components
    vector<vector<int>> g, t;      // g: original graph, t: tree/forest of components (bridge-block tree)
    vector<bool> used;             // Visited array for the first DFS phase
    vector<int> comp, ord, low;    // comp: component assignments, ord: entry times, low: low-link values
    using edge = pair<int,int>;
    vector<edge> br;               // Stores all identified bridges (edges whose removal disconnects the graph)

    // First DFS Phase: Calculates entry times (ord) and low-link values (low)
    // - x: current vertex
    // - prv: parent vertex in the DFS tree
    // - c: global counter to track the order of node visits
    void dfs(int x, int prv, int &c) {
        used[x] = 1; 
        ord[x] = c++; 
        low[x] = n; // Initialize low value with a default upper bound
        bool mul = 0; // Tracks multiple edges between the same pair of nodes (multigraphs)
        
        for(auto y : g[x]) {
            if(used[y]) {
                // If y is already visited, check if it's a back-edge.
                // If y is the parent of x, we skip it *only once* (since duplicate edges are not bridges).
                if(y != prv || mul) {
                    low[x] = min(low[x], ord[y]);
                } else {
                    mul = 1; // Mark that we have seen the edge to the parent once
                }
                continue;
            }
            dfs(y, x, c); // Recursively visit unvisited neighbors
            low[x] = min(low[x], low[y]); // Update low value after returning from subtree
        }
    }

    // Second DFS Phase: Identifies bridges and assigns component labels (IDs)
    // - x: current vertex
    // - num: the current component ID to assign
    void dfs2(int x, int num) {
        comp[x] = num;
        for(auto y : g[x]) {
            if(comp[y] != -1) continue; // Skip if y is already assigned to a component
            
            // Bridge Condition: ord[parent] < low[child]
            // If true, the edge (x, y) is a bridge.
            if(ord[x] < low[y]) {
                br.push_back({x, y});
                k++;               // Create a new component ID
                dfs2(y, k);        // Assign the new component ID to the subtree
            } else {
                // Not a bridge; y belongs to the same component as x
                dfs2(y, num);
            }
        }
    }

    // Constructor: Automatically runs the TECC algorithm on the input graph 'g'
    TECC(const vector<vector<int>>& g) : 
        g(g), n(g.size()), used(n), comp(n, -1), ord(n), low(n), k(0) {
        
        int c = 0;
        // Iterate through all vertices to handle potentially disconnected graphs
        for(int i = 0; i < n; i++) {
            if(used[i]) continue;
            dfs(i, -1, c); // 1st DFS: compute traversal times and low-link values
            dfs2(i, k);    // 2nd DFS: assign components and extract bridges
            k++;           // Increment component count for the next disconnected graph segment
        }
    }

    // Optional utility: Constructs the "Bridge-Block Tree/Forest"
    // Each component is contracted into a single vertex, and components are connected by the bridges.
    void build_tree() {
        t.resize(k);
        for(auto e : br) {
            int x = comp[e.first], y = comp[e.second];
            t[x].push_back(y);
            t[y].push_back(x);
        }
    }
};


// Primary logic wrapper
void solve() {

    int n, m; cin >> n >> m; // Read number of vertices (n) and edges (m)
    vector<vector<int>> g(n); // Graph adjacency list
    
    // Read the undirected edges and populate the graph
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    TECC t(g); // Instantiate the TECC solver structure, triggering execution
    
    vector<vector<int>> ans(t.k); // 2D array to group vertices by component ID

    // Group the original vertices using their component assignments
    for(int i = 0; i < n; i++) {
        ans[t.comp[i]].push_back(i);
    }
    
    // Print the total number of components
    cout << ans.size() << "\n";
    
    // Print each component's size followed by its member vertices
    for(auto x : ans) {
        cout << x.size();
        for(auto y : x) cout << " " << y;
        nl;
    }
}

int main() {
    FastIO // Initialize fast I/O settings

    // int TT=1; cin>>TT; while(TT--) // Optional loop for handling multiple test cases
    solve();

    return 0;
}
