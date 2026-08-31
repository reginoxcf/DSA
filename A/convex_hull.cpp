//cses convex hull
#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef long double ld;
 
#define all(v) begin((v)), end((v))
#define Unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end());
#define lb(v, x) lower_bound((v).begin(), (v).end(), x) - (v).begin()
#define bit(x, y) (((x)>>(y))&1)
#define Timer 1.0 * clock() / CLOCKS_PER_SEC
ll rd(ll l, ll r){return uniform_int_distribution<ll>(l, r)(rng);}
int n;
struct point{
  int x, y;
  bool operator< (const point &o){
    return make_pair(x, y) < make_pair(o.x, o.y);
  }
};
 
ll cross(const point &a, const point &b, const point &c){
  return 1ll * (b.x - a.x) * (c.y - b.y) - 1ll * (b.y - a.y) * (c.x - b.x);
}
 
vector<point> convex_hull(vector<point> &p){
  sort(all(p)); int n = p.size();
  vector<point> hull;
  hull.push_back(p[0]);
 
  for(int i = 1; i < n; i++){
    while(hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), p[i]) > 0) hull.pop_back();
    hull.push_back(p[i]);
  }
  
  for(int i = n-2; i >= 0; i--){
    while(hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), p[i]) > 0) hull.pop_back();
    hull.push_back(p[i]);
  }
 
  if(n > 1) hull.pop_back();
  return hull;
}
 
int main(){
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  vector<point> p(n);
  for(auto &x:p) cin >> x.x >> x.y;
 
  p = convex_hull(p);
  cout << p.size() << "\n";
  for(auto x:p) cout << x.x << " " << x.y << "\n";
  return 0;
}
