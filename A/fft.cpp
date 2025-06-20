using cd = complex<long double>;
const long double PI = acos(-1);

void fft(vector<cd> &a, bool invert) {
    long long n = a.size(), L = __builtin_ctz(n);
    vector<long long> rev(n);
    for (long long i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (long long len = 2; len <= n; len <<= 1) {
        cd wlen = polar(1.0L, acos(-1.0L) / len * (invert ? -2 : 2));
        for (long long i = 0; i < n; i += len) {
            cd w = 1;
            for (long long j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (auto &x : a) x /= n;
    }
}

vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    long long n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (long long i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (long long i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
