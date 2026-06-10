#include <bits/stdc++.h>
using namespace std;

#define FastIO ios::sync_with_stdio(false); cin.tie(nullptr);

// Fully encapsulated Bellman-Ford Negative Cycle Detector (1-indexed)
struct BellmanFord {
    int n;
    const int INF = 2e9; // Safe infinity to prevent overflow when adding costs

    struct Edge {
        int u, v, cost;
    };
    vector<Edge> edges;
    vector<int> dist;
    vector<int> parent;

    // Constructor
    BellmanFord(int n) : n(n) {}

    // Adds a directed edge to the graph
    void add_edge(int u, int v, int cost) {
        edges.push_back({u, v, cost});
    }

    /**
     * Finds a negative cycle in the graph.
     * 
     * @param s        The starting source vertex.
     * @param find_any If true, searches the entire graph for any negative cycle.
                   If false, only searches for cycles reachable from 's'.
     * @return         A vector containing the node IDs in the negative cycle in 
     *                 chronological order. Returns an empty vector if no cycle exists.
     */
    vector<int> get_negative_cycle(int s, bool find_any = false) {
        dist.assign(n + 1, INF);
        parent.assign(n + 1, -1);

        if (find_any) {
            // To find ANY negative cycle, we initialize all starting distances to 0
            for (int i = 1; i <= n; i++) {
                dist[i] = 0;
            }
        } else {
            dist[s] = 0;
        }

        int last_relaxed_node = -1;

        // Relax edges exactly N times
        for (int i = 0; i < n; i++) {
            last_relaxed_node = -1;
            for (auto& edge : edges) {
                if (dist[edge.u] < INF) {
                    if (dist[edge.v] > dist[edge.u] + edge.cost) {
                        // Guard against underflow with large negative weights
                        dist[edge.v] = max(-INF, dist[edge.u] + edge.cost);
                        parent[edge.v] = edge.u;
                        last_relaxed_node = edge.v; // Record the node that was relaxed
                    }
                }
            }
        }

        vector<int> cycle;
        // If no relaxation occurred on the N-th iteration, there is no negative cycle
        if (last_relaxed_node == -1) {
            return cycle; 
        }

        // Backtrack N times starting from the last relaxed node.
        // This guarantees that we enter the negative cycle loop itself.
        int cycle_node = last_relaxed_node;
        for (int i = 0; i < n; i++) {
            cycle_node = parent[cycle_node];
        }

        // Reconstruct the cycle by backtracking until we loop back to cycle_node
        for (int cur = cycle_node; ; cur = parent[cur]) {
            cycle.push_back(cur);
            if (cur == cycle_node && cycle.size() > 1) {
                break;
            }
        }
        
        // Reverse the backtracked path to get the correct chronological order
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
};

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    BellmanFord bf(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        bf.add_edge(u, v, w);
    }

    int s; 
    cin >> s;

    // Run the cycle detector
    vector<int> cycle = bf.get_negative_cycle(s, false);

    if (cycle.empty()) {
        cout << "No negative cycle from " << s << "\n";
    } else {
        cout << "Negative cycle: ";
        for (int u : cycle) {
            cout << u << " ";
        }
        cout << "\n";
    }
}

int main() {
    FastIO
    solve();
    return 0;
}
