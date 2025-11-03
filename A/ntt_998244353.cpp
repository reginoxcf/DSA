const int ROOT = 3, mod = 998244353;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (r * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return r;
}

void ntt(vector<int> & a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = modpow(ROOT, (mod - 1) / len);
        if (invert) wlen = modpow(wlen, mod - 2);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            int half = len >> 1;
            for (int j = 0; j < half; ++j) {
                int u = a[i + j];
                int v = (int)((a[i + j + half] * w) % mod);
                int sum = u + v;
                if (sum >= mod) sum -= mod;
                int diff = u - v;
                if (diff < 0) diff += mod;
                a[i + j] = sum;
                a[i + j + half] = diff;
                w = (w * wlen) % mod;
            }
        }
    }

    if (invert) {
        ll inv_n = modpow(n, mod - 2);
        for (int & x : a) x = (int)((x * inv_n) % mod);
    }
}

vector<int> conv(const vector<int> &A, const vector<int> &B) {
    if (A.empty() || B.empty()) return {};
    int n1 = (int)A.size(), n2 = (int)B.size();
    int n = 1;
    while (n < n1 + n2 - 1) n <<= 1;

    vector<int> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(n); fb.resize(n);

    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; ++i) fa[i] = (int)((ll)fa[i] * fb[i] % mod);
    ntt(fa, true);

    fa.resize(n1 + n2 - 1);
    return fa;
}
