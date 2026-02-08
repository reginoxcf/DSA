struct HLD {
  vector<vector<int>> g;
  vector<int> sz, depth, anc;
  vector<bool> hv;
  vector<pair<int, int>> hid;
  vector<vector<int>> sp;
  vector<int> tin;
  int hsz = 0, timer = 0, n = 0, L = 0;

  void init(int n_) {
    n = n_;
    L = __lg(n) + 1;
    g.assign(n + 1, vector<int>());
    sz.assign(n + 1, 0);
    depth.assign(n + 1, 0);
    anc.assign(n + 1, 0);
    hv.assign(n + 1, false);
    hid.assign(n + 1, {-1, -1});
    sp.assign(n + 1, vector<int>(L + 1, 0));
    tin.assign(n + 1, 0);
    hsz = 0;
    timer = 0;
  }

  void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void find_sz(int u = 1, int p = 0) {
    depth[u] = depth[p] + 1;
    sz[u] = 1;
    for (int i = 1; i <= L; i++) sp[u][i] = sp[sp[u][i - 1]][i - 1];
    int mx = -1;
    for (auto v : g[u]) {
      if (v == p) continue;
      sp[v][0] = u;
      find_sz(v, u);
      sz[u] += sz[v];
      if (mx == -1 || sz[mx] < sz[v]) mx = v;
    }
    if (mx != -1) hv[mx] = 1;
  }

  void find_hld(int u = 1, int p = 0) {
    if (hid[u].first == -1) {
      hid[u].first = ++hsz;
      hid[u].second = 1;
      anc[u] = u;
    }
    tin[u] = ++timer;
    for (auto v : g[u]) {
      if (v == p) continue;
      if (hv[v]) {
        hid[v].first = hid[u].first;
        hid[v].second = hid[u].second + 1;
        anc[v] = anc[u];
        find_hld(v, u);
      }
    }
    for (auto v : g[u]) {
      if (v == p) continue;
      if (!hv[v]) find_hld(v, u);
    }
  }

  int LCA(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int diff = depth[v] - depth[u];
    for (int l = L; l >= 0; l--) {
      if ((diff >> l) & 1) v = sp[v][l];
    }
    if (u == v) return u;
    for (int l = L; l >= 0; l--) {
      if (sp[u][l] != sp[v][l]) {
        u = sp[u][l];
        v = sp[v][l];
      }
    }
    return sp[u][0];
  }
};
