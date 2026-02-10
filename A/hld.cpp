struct HLD{
  vector<vector<int>> g;
  vector<int> sz, depth, anc;
  vector<pair<int, int>> hid;
  vector<vector<int>> sp;
  vector<int> tin, tout;
  int hsz = 0, timer = 0, n = 0, L = 0;

  void init(int n_){
    n = n_;
    L = __lg(n) + 1;
    g.assign(n + 1, vector<int>());
    sz.assign(n + 1, 0);
    depth = anc = tin = tout = sz;
    hid.assign(n + 1,{-1, -1});
    sp.assign(n + 1, vector<int>(L + 1, 0));
    hsz = 0;
    timer = 0;
  }

  void add_edge(int u, int v){
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void dfs_sz(int u = 1, int p = 0){
    depth[u] = depth[p] + 1;
    sz[u] = 1;
    for(int i = 1; i <= L; i++) sp[u][i] = sp[sp[u][i - 1]][i - 1];
    for(auto &v : g[u]){
      if(v == p) continue;
      sp[v][0] = u;
      dfs_sz(v, u);
      sz[u] += sz[v];
      if(sz[v] > sz[g[u][0]]) swap(g[u][0], v);
    }
  }

  void dfs_hld(int u = 1, int p = 0){
    if(hid[u].first == -1){
      hid[u].first = ++hsz;
      hid[u].second = 1;
      anc[u] = u;
    }
    tin[u] = ++timer;
    for(auto v : g[u]){
      if(v == p) continue;
      if(v == g[u][0]){
        hid[v].first = hid[u].first;
        hid[v].second = hid[u].second + 1;
        anc[v] = anc[u];
      }
      dfs_hld(v, u);
    }
    tout[u] = timer;
  }
  
    int LCA(int u, int v){
      if(depth[u] > depth[v]) swap(u, v);
      int diff = depth[v] - depth[u];
      for(int l = L; l >= 0; l--){
        if((diff >> l) & 1) v = sp[v][l];
      }
      if(u == v) return u;
      for(int l = L; l >= 0; l--){
        if(sp[u][l] != sp[v][l]){
          u = sp[u][l];
          v = sp[v][l];
        }
      }
      return sp[u][0];
    }

  void go(int u = 1){
    dfs_sz(u);
    dfs_hld(u);
  }
};
