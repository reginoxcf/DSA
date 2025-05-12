//AC solution to https://www.spoj.com/problems/ADAINDEX/ using trie
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6+3;
struct Trie{
	struct node{
		int child[26], cnt, exist;
	} tree[N];
	int cur;
	Trie() : cur(0){
		memset(tree[0].child, -1, sizeof(tree[0].child));
		tree[0].cnt = tree[0].exist = 0;
	};

	int new_node(){
		cur++;
		memset(tree[cur].child, -1, sizeof(tree[cur].child));
		tree[cur].cnt = tree[cur].exist = 0;
		return cur;
	}

	void add_string(string s){
		int pos = 0;
		for(auto x:s){
			int c = x-'a';
			if(tree[pos].child[c] == -1) tree[pos].child[c] = new_node();
			pos = tree[pos].child[c];
			tree[pos].cnt++;
		}
		tree[pos].exist++;
	}

	bool deleteUtil(int i, string& s, int pos){
		if(i != (int)s.size()){
			int c = s[i] - 'a';
			if(deleteUtil(i+1, s, tree[pos].child[c])) tree[pos].child[c] = -1;
		}
		else tree[pos].exist--;
		if(pos != 0){
			tree[pos].cnt--;
			if(tree[pos].cnt==0) return true;
		}
		return false;
	}

	void del(string s){
		if(find(s) == false) return ;
		deleteUtil(0, s, 0);
	}

	bool find(string s){
		int pos = 0;
		for(auto x:s){
			int c = x-'a';
			if(tree[pos].child[c] == -1) return false;
			pos = tree[pos].child[c];
		}
		return (tree[pos].exist != 0);
	}
} trie;
ll n, q;
string s;

ll query(string s){
	int pos = 0;
	for(auto x:s){
		int c = x-'a';
		if(trie.tree[pos].child[c]==-1) return 0;
		pos = trie.tree[pos].child[c];
	}
	return trie.tree[pos].cnt;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for(ll i = 1; i <= n; i++){
		cin >> s;
		trie.add_string(s);
	}
	while(q--){
		cin >> s;
		cout << query(s) << "\n";
	}
	return 0;
}