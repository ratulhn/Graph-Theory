#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9;

struct dsu {
  vector<int> par, rnk, size; int c;
  dsu(int n) : par(n+1), rnk(n+1,0), size(n+1,0), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
  bool same(int i, int j) { return find(i) == find(j); }
  int get_size(int i) { return size[find(i)]; }
  int count() { return c; } //connected components
  bool merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return false; else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j; size[j] += size[i];
    if (rnk[i] == rnk[j]) rnk[j]++;
    return true;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m,k; cin >> n >> m>>k;
  vector<string> s(n+1);
  for(int i = 0; i <n; i++){
    cin>>s[i];
  }

  int cnt=1;
  int node[n+1][m+1];

  for(int i=0; i<n; i++) for(int j=0; j<m; j++) node[i][j]=cnt++;

  dsu d(cnt);

  auto good=[&](int i, int j) {
    if(i<0||i>=n||j<0||j>=m) return false;
    return true;
  };

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
        if(s[i][j]=='*') continue;
        int cur=node[i][j];
        if(good(i-1,j)) d.size[cur]+=(s[i-1][j]=='*');
        if(good(i+1,j)) d.size[cur]+=(s[i+1][j]=='*');
        if(good(i,j-1)) d.size[cur]+=(s[i][j-1]=='*');
        if(good(i,j+1)) d.size[cur]+=(s[i][j+1]=='*');
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
        if(s[i][j]=='*') continue;
        int cur=node[i][j];
        if(good(i-1,j)&&s[i-1][j]=='.') d.merge(cur,node[i-1][j]); 
        if(good(i+1,j)&&s[i+1][j]=='.') d.merge(cur,node[i+1][j]); 
        if(good(i,j+1)&&s[i][j+1]=='.') d.merge(cur,node[i][j+1]); 
        if(good(i,j-1)&&s[i][j-1]=='.') d.merge(cur,node[i][j-1]); 
    }
  }

  while(k--) {
    int x,y; cin>>x>>y;
    x--;y--;
    int cur=node[x][y];
    int par = d.find(cur);
    cout << d.size[par] << "\n";
  }


  
  return 0;
}
