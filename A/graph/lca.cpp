//lca using binary lifting

#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(v) begin(v), end(v)
#define pi pair<int, int>
#define vi vector<int>
using namespace std;
const int LOG = 20, N = 1e6+3;
int n, q;
vector<int> g[N];
int depth[N], par[N][LOG+2];

void dfs(int u, int p){
	depth[u] = depth[p]+1;
	par[u][0] = p;
	for(int i = 1; i <= LOG; i++) par[u][i] = par[par[u][i-1]][i-1];
    for(auto v:g[u]){
        if(v == p) continue;
        dfs(v, u);
    }
	return ;
}

int lca(int u, int v){
	if(depth[u] < depth[v]) swap(u, v);
	int diff = depth[u] - depth[v];
	for(int i = LOG; i >= 0; i--){
        if((diff >> i) & 1) u = par[u][i];
    }
	if(u == v) return u;
	for(int i = LOG; i >= 0; i--){
		if(par[u][i] != par[v][i]){
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for(int i = n-1; i; i--){
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
	dfs(1,0);
	cin >> q;
	while(q--){
		int u, v; cin >> u >> v;
        cout << lca(u, v) << "\n";
	}
	return 0;
}