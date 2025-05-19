const ll MOD = 1e9+7;

vector<vector<ll>> mmul(vector<vector<ll>> a, vector<vector<ll>> b){
    vector<vector<ll>> c;
    c.resize(a.size(), vector<ll>(b[0].size()));
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b[0].size(); j++){
            for(int k = 0; k < a[0].size(); k++){
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

vector<vector<ll>> mpow(vector<vector<ll>> b, ll m){
    vector<vector<ll>> res = b;
    for(int i = 0; i < res.size(); i++){
        for(int j = 0; j < res[i].size(); j++){
            if(i == j) res[i][j] = 1;
            else res[i][j] = 0;
        }
    }
    while(m){
        if(m & 1) res = mmul(res, b);
        b = mmul(b, b);
        m >>= 1;
    }
    return res;
}