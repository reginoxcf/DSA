const int mod = 998244353, root = 15311432, root_1 = 469870224, root_pw = 1LL<<23;
 
int binpow(int a, int b){
    int res = 1;
    while(b > 0){
        if(b & 1){
            res = 1LL * res * a % mod;
        }
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return res;
}
 
void ntt(vector<int>& a, bool invert){
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++){
        int bit = (n >> 1);
        for (; j & bit; bit >>= 1){
            j ^= bit;
        } 
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }
    for (int l = 2; l <= n; l <<= 1){
        int wl = invert ? root_1 : root;
        for(int i = l; i < root_pw; i <<= 1) wl = 1LL * wl * wl % mod;
        for(int i = 0; i < n; i += l){
            int w = 1;
            for (int j = 0; j < l / 2; j++){
                int u = a[i + j], v = 1LL * a[i + j + l / 2] * w % mod;
                a[i + j] = ((u + v) < mod) ? (u+v) : (u+v-mod);
                a[i + j + l / 2] = ((u - v) >= 0) ? (u - v) : (u - v + mod);
                w = 1LL * w * wl % mod;
            }
        }
    }
    if(invert){
        int n_1 = binpow(n, mod - 2);
        for(int& i : a) i = (1LL * i * n_1) % mod;
    }
}
 
vector<int> multiply(vector<int> const& a, vector<int> const& b){
    int sus = a.size() + b.size() - 1;
    vector<int> fa(a.begin(),a.end()), fb(b.begin(),b.end());
    int n = 1;
    while (n < a.size() + b.size()){
        n <<= 1;
    }
    fa.resize(n); fb.resize(n);
    ntt(fa, 0); ntt(fb, 0);
    for(int i = 0; i < n; i++){
        fa[i] = 1LL * fa[i] * fb[i] % mod;
    }
    ntt(fa, 1);

    while(fa.size() > sus) fa.pop_back();
 
    return fa;
}
