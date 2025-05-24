struct LazyST{
  int n;
  vector<pair<int,int>> t;
  void resize(int n){
    this->n = n;
    t.resize(n*4+3);
    fill(all(t), make_pair(0, 0));
  }
  void push(int id){
    int &x = t[id].second;
    t[id*2].first += x;
    t[id*2+1].first += x;
    t[id*2].second += x;
    t[id*2+1].second += x;
    x = 0;
  }
  void update(int id, int l, int r, int L, int R, int v){
    if(L > r || R < l) return;
    if(L <= l && r <= R){
      t[id].first += v;
      t[id].second += v;
      return;
    }
    push(id);
    update(id*2, l, (l+r)/2, L, R, v);
    update(id*2+1, (l+r+2)/2, r, L, R, v);
    t[id].first = min(t[id*2].first, t[id*2+1].first);
  }
  int get(int id, int l, int r, int L, int R){
    if(L > r || R < l) return 1e9;
    if(L <= l && r <= R) return t[id].first;
    push(id);
    int mid = (l+r)/2;
    return min(get(id*2, l, mid, L, R), get(id*2+1, mid+1, r, L, R));
  }
  void print(int id, int L, int R){
    cout << L << " " << R << " " << t[id].first << "\n";
    if(L==R) return ;
    print(id*2, L, (L+R)/2);
    print(id*2+1, (L+R+2)/2, R);
  }
};