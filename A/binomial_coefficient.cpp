const ll mod = ;
vector<ll> fact, inv;
ll bpow(ll n, int k){
    ll res = 1;
    while(k){
        if(k & 1) res = (res * n) % mod;
        n = (n * n) % mod;
        k >>= 1;
    }
    return res;
}

ll C(int n, int k){
    return ((inv[n-k] * inv[k]) % mod * fact[n]) % mod;
}

ll P(int n, int k){
    return (fact[n] * inv[n-k]) % mod;
}

ll Pset(vector<int> n){
    ll ans = fact[accumulate(n.begin(), n.end(), 0)];
    for(int &x:n){
        ans = (ans * inv[x]) % mod;
    }
    return ans;
}

void init(int N){
    fact.resize(N+1), inv.resize(N+1);
    fact[0] = 1;
    for(int i = 1; i <= N; i++) fact[i] = (i * fact[i-1]) % mod;
    inv[N] = bpow(fact[N], mod - 2);
    for(int i = N-1; i >= 0; i--) inv[i] = ((i+1) * inv[i+1]) % mod;
}