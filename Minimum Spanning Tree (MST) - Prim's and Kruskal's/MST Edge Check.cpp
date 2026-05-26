#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9;

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

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  vector<array<int, 4>> ed;
  for(int i = 1; i <= m; i++){
    int u, v, w; cin >> u >> v >> w;
    ed.push_back({w, u , v,i});
  }
  sort(ed.begin(), ed.end());
  vector<string>res(m+1);
  dsu d(n);
  
  for (int i=0;i<m;){
    int u = ed[i][1], v = ed[i][2], w = ed[i][0];
    int j=i;
    while(j<m&&ed[j][0]==w) j++;
    for(int k=i; k<j; k++) {
        if (d.same( ed[k][1],ed[k][2])) res[ed[k][3]]="NO";
        else res[ed[k][3]]="YES";
    }
    for(int k=i; k<j; k++) {
        d.merge( ed[k][1],ed[k][2]);
    }
    i=j;
  }

  for(int i=1; i<=m; i++) cout << res[i] << "\n";
  
  return 0;
}
