//AC code for https://www.spoj.com/problems/DQUERY/en/ using MO's algorithm
#include<bits/stdc++.h>
#define task "test"
using namespace std;
struct query{
	int l, r, id, val;
};
const int N = 2e5+3, block_size = 450, maxv = 1e6+3;
int n, t, a[N], cnt[maxv];
int res;
query q[N];
void solve(int pl, int pr, int l, int r, int id){
	int ml = min(pl, l);
	int mr = max(pr, r);
	for(int i = pl-1; i >= ml; i--){
		cnt[a[i]]++;
		if(cnt[a[i]]==1) res++;
	}
	for(int i = pr+1; i <= mr; i++){
		cnt[a[i]]++;
		if(cnt[a[i]]==1) res++;
	}
	for(int i = ml; i <= l-1; i++){
		if(cnt[a[i]]==1) res--;
		cnt[a[i]]--;
	}
	for(int i = mr; i >= r+1; i--){
		if(cnt[a[i]]==1) res--;
		cnt[a[i]]--;
	}
	q[id].val = res;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	if(fopen(task".inp","r")){
		freopen(task".inp","r",stdin);
		freopen(task".out","w",stdout);	
	}
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> q[i].l >> q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+t+1,[&](query a, query b){
		if(a.l/block_size!=b.l/block_size) return a.l/block_size<b.l/block_size;
		return a.r<b.r;
	});
	for(int i = q[1].l; i <= q[1].r; i++){
		cnt[a[i]]++;
		if(cnt[a[i]]==1) res++;
	}
	q[1].val = res;
	for(int i = 2; i <= t; i++){
		solve(q[i-1].l, q[i-1].r, q[i].l, q[i].r, i);
	}
	sort(q+1,q+t+1,[&](query a, query b){
		return a.id<b.id;
	});
	for(int i = 1; i <= t; i++) cout << q[i].val << "\n";
	return 0;
}