int timer;
vector<int> low, tin;

void is_bridge(int u, int v){
    
}

void dfs(int u, int p){
    low[u] = tin[u] = ++timer;
    for(auto v:g[u]){
        if(v == p) continue;
        if(tin[v] != -1){
            low[u] = min(low[u], tin[v]);
        }
        else{
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u]){
                is_bridge(u, v);
            }
        }
    }
}

void find_bridges(){
    timer = 0;
    low.assign(n+1, -1);
    tin.assign(n+1, -1);
    for(int i = 1; i <= n; i++){
        if(tin[i] == -1) dfs(i, 0);
    }
}