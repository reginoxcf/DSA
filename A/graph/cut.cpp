int timer = 0;
vector<int> tin, low;
vector<bool> cut;

void is_cut(int u){
    
}

void dfs(int u, int p){
    tin[u] = low[u] = ++timer;
    int children = 0;
    for(auto v:g[u]){
        if(v == p) continue;
        if(tin[v] > 0){
            low[u] = min(tin[v], low[u]);
        }
        else{
            children++;
            dfs(v, u);
            low[u] = min(low[v], low[u]);
            if(low[v] >= tin[u] && p != 0){
                is_cut(u);
            }
        }
    }
    if(p == 0 && children > 1) is_cut(u);
}

void find_cutpoints(){
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    cut.assign(n+1, false);
    timer = 0;
    for(int i = 1; i <= n; i++){
        if(tin[i] == -1) dfs(i, 0);
    }
}
