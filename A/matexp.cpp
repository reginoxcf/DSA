const ll mod = 1e9+7;

vector<vector<int>> mmul(const vector<vector<int>> &a, const vector<vector<int>> &b){
  vector<vector<int>> c;
  c.resize(a.size(), vector<int>(b[0].size()));
  for(int i = 0; i < a.size(); i++){
    for(int j = 0; j < b[0].size(); j++){
      for(int k = 0; k < a[0].size(); k++){
        c[i][j] = (1ll * a[i][k] * b[k][j] + 1ll * c[i][j]) % mod;
      }
    }
  }
  return c;
}

vector<vector<int>> mpow(vector<vector<int>> b, ll m){
  vector<vector<int>> res(b.size(), vector<int>(b[0].size(), 0));
  for(int i = 0; i < res.size(); i++) res[i][i] = 1;
  while(m){
    if(m & 1) res = mmul(res, b);
    b = mmul(b, b);
    m >>= 1;
  }
  return res;
}
