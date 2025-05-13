//cre: thenymphsofdelphi
struct CHT{
    int n, idx;
    vector <ll> a, b;
 
    CHT(): n(0), idx(0){
 
    }
 
    bool redundant(int i, int j, int k){
        if (a[j] == a[k]){
            return b[j] < b[k];
        }
        ld xj = (ld)(b[j] - b[i]) / (a[i] - a[j]);
        ld xk = (ld)(b[k] - b[i]) / (a[i] - a[k]);
        return xj > xk;
    }
 
    void add(ll ta, ll tb){
        n++;
        a.push_back(ta);
        b.push_back(tb);
        while (n >= 2 && a[n - 2] == a[n - 1] && b[n - 2] <= b[n - 1]){
            a.erase(a.begin() + n - 2);
            b.erase(b.begin() + n - 2);
            n--;
        }
        while (n >= 3 && redundant(n - 3, n - 2, n - 1)){
            a.erase(a.begin() + n - 2);
            b.erase(b.begin() + n - 2);
            n--;
        }
    }
 
    ll query(ll x){
        idx = min(idx, n - 1);
        while (idx + 1 < n && a[idx] * x + b[idx] < a[idx + 1] * x + b[idx + 1]){
            idx++;
        }
        return a[idx] * x + b[idx];
    }
};
