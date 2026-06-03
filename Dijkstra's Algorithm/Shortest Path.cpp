#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 9, mod = 998244353;
const long long inf = 1e18+7;
int n, m;
vector<pair<int, int>> g[N];
vector<long long> dijkstra(int s, vector<int>&par) {
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
  vector<long long> d(n + 1, inf);
  vector<bool> vis(n + 1, 0);
  q.push({0, s});
  d[s] = 0;
  par[s]=s;
  while(!q.empty()) {
    auto x = q.top();
    q.pop();
    int u = x.second;
    if(vis[u]) continue;
    vis[u] = 1;
    for(auto y: g[u]) {
      int v = y.first;
      long long w = y.second;
      if(d[u] + w < d[v]) {
        d[v] = d[u] + w;
        q.push({d[v], v});
        par[v]=u;
      }
    }
  }
  return d;
}

int u[N], v[N], w[N];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
    int s,t;
  cin >> n >> m>>s>>t;
  for(int i = 1; i <= m; i++) {
    cin >> u[i] >> v[i] >> w[i];
    g[u[i]].push_back({v[i], w[i]});
  }
  vector<int>par(n+1,-1);
  auto d = dijkstra(s,par);
  
  if(d[t]==inf) cout << "-1\n";
  else {
    cout << d[t] << " ";
    vector<int>path;
    int cur=t;
    while(cur!=s) {
        path.push_back(cur);
        cur=par[cur];
    }
    path.push_back(s);
    cout << path.size()-1 << "\n";
    for(int i=path.size()-1; i>0; i--) cout << path[i] << " " << path[i-1] << "\n";
  }
  
  return 0;
}
