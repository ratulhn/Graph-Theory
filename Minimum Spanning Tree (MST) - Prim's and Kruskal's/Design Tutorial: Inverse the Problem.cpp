#include<bits/stdc++.h>
using namespace std;

const int N = 2020;
int g[N][N], w[N], to[N], selected[N];
vector<pair<int,int>>adj[N];
long long Prims(int n) {
  long long ans = 0;
  for(int i = 1; i <= n; i++) w[i] = 2e9, selected[i] = 0, to[i] = -1;
  w[1] = 0;
  for(int i = 1; i <= n; i++) {
    int u = -1;
    for(int j = 1; j <= n; j++) if(!selected[j] && (u == -1 || w[j] < w[u])) u = j;
    if (w[u] == 2e9) return - 1; //NO MST
    selected[u] = 1;
    ans += w[u];
    if(to[u] != -1) {
        int v=to[u];
        adj[u].push_back({v,w[u]});
        adj[v].push_back({u,w[u]});
    } //order of the edges may be changed
    for(int v = 1; v <= n; v++) if(g[u][v] < w[v]) w[v] = g[u][v], to[v] = u;
  }
  return ans;
}


bool dfs(int root, int u, int p, long long dist) {
    if(dist!=g[root][u]) {
        return false;
    }
    for(auto &edge:adj[u]) {
        int v=edge.first;
        int w=edge.second;
        if(v!=p) {
            if(!dfs(root,v,u,dist+w)) return false;
        }
    }
    return true;
}


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n; cin>>n;

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++)
    cin>>g[i+1][j+1];
  }

  for(int i=1; i<=n; i++) {
    if(g[i][i]!=0) {
        cout << "NO\n"; return 0;
    }
    for(int j=1; j<=n; j++) {
        if(i!=j) {
            if(g[i][j]<=0||g[i][j]!=g[j][i]) {
                cout << "NO\n"; return 0;
            }
        }
    }
  }

  long long ans = Prims(n);

  for(int i=1; i<=n; i++) {
    if(!dfs(i,i,0,0)) {
        cout << "NO\n"; return 0;
    }
  }


  cout << "YES\n";

  return 0;
}
