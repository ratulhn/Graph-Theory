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
const int inf=1e9+7;







void solve() {

    string s,t; cin>>s>>t;
    int dist[26][26];

    for(int i=0; i<26; i++) {
        for(int j=0; j<26; j++) {
            if(i==j) dist[i][j]=0;
            else dist[i][j]=inf;
        }
    }

    int m; cin>>m;
    for(int i=0; i<m; i++) {
        char a,b; cin>>a>>b;
        int w; cin>>w;
        int u=a-'a';
        int v=b-'a';
        dist[u][v]=min(dist[u][v],w);
    }

    for(int k=0; k<26; k++) {
        for(int i=0; i<26; i++) {
            for(int j=0; j<26; j++) {
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }


    if(s.size()!=t.size()) {
        cout << "-1\n"; return;
    }
    ll res=0;
    for(int i=0; i<s.size(); i++) {
        int u = s[i]-'a';
        int v = t[i]-'a';
        if(u==v) continue;

        int id=-1;
        ll d=inf;
        for(int k=0; k<26; k++) {
            if(dist[u][k]!=inf && dist[v][k]!=inf && dist[u][k]+dist[v][k]<d) {
                d=dist[u][k]+dist[v][k];
                id=k;
            }
        }

        if(id==-1) {
            cout << "-1\n"; return;
        }

        res+=d;
        s[i]=t[i]=id+'a';

    }

    cout << res << "\n";
    cout << s << "\n";


}

int main() {
    FastIO


    //int TT=1; cin>>TT; while(TT--)
    solve();

    return 0;
}
