struct dsu{
  vector<int> lab;
  vector<pair<int&, int>> history;
  dsu(int n) : lab(n+1, -1) {}
  int find(int u){
    if(lab[u] < 0) return u;
    return find(lab[u]);
  }
  void join(int u, int v){
    u = find(u), v = find(v);
    if(u == v) return ;
    if(lab[u] > lab[v]) swap(u, v);
    history.push_back({lab[u], lab[u]});
    history.push_back({lab[v], lab[v]});
    lab[u] += lab[v];
    lab[v] = u;
    return ;
  }
  int ver(){
    return history.size();
  }
  void rb(int id){
    while(ver() > id){
      (history.back()).first = (history.back()).second;
      history.pop_back();
    }
  }
} ;
