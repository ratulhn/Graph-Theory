#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, LG = 20;

struct dsu {
  vector<int> par, rnk, size; int c;
  dsu(int n) : par(n+1), rnk(n+1,0), size(n+1,1), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
  bool same(int i, int j) { return find(i) == find(j); }
  int get_size(int i) { return size[find(i)]; }
  int count() { return c; } //connected components
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1; else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j; size[j] += size[i];
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};

vector<pair<int,int>> g[N];
int par[N][LG + 1], dep[N], sz[N],vmx[N][LG+1];
void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  for (auto v: g[u]) if (v.first != p) {
    vmx[v.first][0]=v.second;
    dfs(v.first, u);
    sz[u] += sz[v.first];
  }
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
void precom(int n) {
    for (int i = 1; i <= LG; i++) 
        for(int j=1; j<=n; j++)
            vmx[j][i] =max(vmx[j][i-1],vmx[par[j][i - 1]][i - 1]);
}
int kth(int u, int k) {
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
  return u;
}
int lift(int u, int k, int &res) {
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) res=max(res,vmx[u][i]),u=par[u][i];
  return u;
}
int dist(int u, int v) {
  int l = lca(u, v);
  int res=0;
  lift(u,dep[u]-dep[l],res);
  lift(v,dep[v]-dep[l],res);
  return res;
}
//kth node from u to v, 0th node is u
int go(int u, int v, int k) {
  int l = lca(u, v);
  int d = dep[u] + dep[v] - (dep[l] << 1);
  assert(k <= d);
  if (dep[l] + k <= dep[u]) return kth(u, k);
  k -= dep[u] - dep[l];
  return kth(v, dep[v] - dep[l] - k);
}
int32_t main() {

  int n,m; cin >> n>>m;
  vector<array<int,4>>edges;
  for(int i=0; i<m; i++) {
    int u,v,w; cin>>u>>v>>w;
    edges.push_back({w,u,v,i});
  }

  sort(edges.begin(),edges.end());
  long long cur=0;
  vector<bool>done(m);

  dsu d(n);
  int comp=n;

  for(auto &[w,u,v,id]:edges) {
    if(!d.same(u,v)) {
        comp--;
        d.merge(u,v);
        cur+=w;
        done[id]=true;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
        if(comp==1) break;
    }
  }

  dfs(1);
  precom(n);
  vector<long long>res(m);

  for(auto &[w,u,v,id]:edges) {
    if(done[id]) {
        res[id]=cur;continue;
    } 
    res[id]=cur-dist(u,v)+w;

  }

  for(auto &x:res) cout << x << "\n";


  return 0;
}
