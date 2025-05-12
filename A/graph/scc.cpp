/*
Strongly Connected Components in Directed Graph using Tarjan's algorithm
 */
#include<bits/stdc++.h>
#define task "test"
using namespace std;
const int N = 1e5+3;
int n, m, cnt, num[N], low[N], group[N], h;
bool a_in[N];
vector<int> g[N], g2[N], scc[N];
stack<int> st;
queue<int> qu;
 
void dfs(int u){
    num[u] = ++cnt, low[u] = num[u];
    st.push(u);
    for(auto v : g[u]){
        if(num[v]!=0) low[u] = min(low[u], num[v]);
        else{
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
    int v, in=0;
    if(low[u] == num[u]){
        ++h;
        do{
            v = st.top();
            group[v] = h;
            num[v] = 1e9;
            ++in, a_in[v] = true;
            st.pop();
        } while(v != u);	
    }
}
int main(){
	if(fopen(task".inp","r")){
		freopen(task".inp","r",stdin);
		freopen(task".out","w",stdout);
	}
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        if(num[i] == 0) dfs(i);
    }
    for(int i = 1; i <= n; i++) scc[group[i]].push_back(i);
    for(int i = 1; i <= h; i++){
    	for(auto x:scc[i]) cout << x << " ";
		cout << "\n";
    }
    return 0;
}
