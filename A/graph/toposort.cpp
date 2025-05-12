/*
Topological Sort - AC code to CSES Course Schedule
https://cses.fi/problemset/task/1679/
*/
#include<bits/stdc++.h>
#define task "test" //edit this line if file input
#define rep(i, a, b) for(int i = a; i <= (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ll long long 
#define pii pair<int, int>
#define vi vector<int>
using namespace std;
const int N = 1e5+3;
int n, m, in[N], l, topo[N];
vector<int> g[N];
queue<int> q;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	if(fopen(task".inp","r")){
		freopen(task".inp","r",stdin);
		freopen(task".out","w",stdout);
	}
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		in[y]++;
	}
	//topological sort starts here
	for(int i = 1; i <= n; i++){
		//finding roots
		if(!in[i]) q.push(i);
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		topo[++l] = u;
		for(auto v:g[u]){
			in[v]--;
			if(!in[v]) q.push(v);
		}
	}
	if(l < n){cout << "IMPOSSIBLE"; return 0;}
	for(int i = 1; i <= n; i++) cout << topo[i] << " ";
	return 0;
}