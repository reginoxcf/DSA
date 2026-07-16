int gauss(vector<vector<mint>> &a, vector<mint> &ans){
  //0 = no soln, 1 = unique soln, 2 = multiple soln
  int n = a.size(), m = a[0].size() - 1;
  int rnk = 0;
  vector<int> pivot(m); ans.assign(m, 0);
  for(int i = 0; i < m; i++){
    if(rnk >= n) break;
    if(a[rnk][i] == 0){
      int sel = rnk;
      while(sel < n && a[sel][i] == 0) sel++;
      if(sel < n)
        for(int j = 0; j <= m; j++) swap(a[sel][j], a[rnk][j]);
      else
        continue;
    }
    pivot[rnk] = i;
    mint inv = a[rnk][i].inv();
    for(int j = m; j >= i; j--) a[rnk][j] *= inv;
    for(int j = rnk+1; j < n; j++){
      mint d = a[j][i];
      for(int k = m; k >= i; k--) a[j][k] -= a[rnk][k] * d;
    }
    rnk++;
  }

  for(int i = rnk; i < n; i++){
    if(a[i][m] != 0) return 0;
  }
  
  for(int i = rnk - 1; i >= 0; i--){
    ans[pivot[i]] = a[i][m];
    for(int j = pivot[i] + 1; j < m; j++){
      ans[pivot[i]] -= a[i][j] * ans[j];
    }
  }
  if(rnk < m) return 2;
  return 1;
}
