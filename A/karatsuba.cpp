//karatsuba algorithm with complexity ~o(n^(1.59))
#include<bits/stdc++.h>
#define ll long long
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define sp << " "
using namespace std;
string a, b;

string add(string a, string b){
	while(a.size()<b.size()) a='0'+a;
	while(a.size()>b.size()) b='0'+b;
	ll carry=0, tmp;
	string ans;
	for(ll i = a.size()-1; i >= 0; i--){
		tmp = (a[i]-'0')+(b[i]-'0')+carry;
		carry=tmp/10;
		tmp%=10;
		ans=char(tmp+'0')+ans;
	}
	if(carry) ans=char(carry+'0')+ans;
	return ans;
}
 
string subtract(string a, string b){
	while(a.size()<b.size()) a='0'+a;
	while(a.size()>b.size()) b='0'+b;
	ll carry=0, tmp;
	string ans;
	for(ll i = a.size()-1; i >= 0; i--){
		tmp = a[i]-b[i]-carry;
		if(tmp<0){
			tmp+=10;
			carry=1;
		}
		else carry=0;
		ans+=char(tmp+'0');
	}
	while(ans.back()=='0') ans.pop_back();
	reverse(ans.begin(),ans.end());
	return ans;
}

ll string_to_ll(string s){
	ll ans = 0;
	for(ll i = 0; i < s.size(); i++){
		ans+=(s[i]-'0');
		ans*=10;
	}
	return ans/10;
}

string ll_to_string(ll n){
	string ans = "";
	while(n>0){
		ans=char(n%10+'0')+ans;
		n/=10;
	}
	return ans;
}

string int_multi(string a, string b){
	ll c = string_to_ll(a), d = string_to_ll(b);
	return ll_to_string(c*d);
}

string karatsuba(string a, string b){
	ll half = max(a.size(),b.size())/2;
	string pw;
	string aa, bb, c, d;
	
	if(a=="0"||b=="0") return "0";
	if(a.size()+b.size()<18) return int_multi(a,b);
	for(ll i = 0; i < half; i++) pw+='0';
	
	if(a.size()>=half)bb = a.substr(a.size()-half, half);
	else bb=a;
	if(b.size()>=half)d = b.substr(b.size()-half, half);
	else d=b;
	if(a.size()>=half)aa = a.substr(0, a.size()-half);
	else aa="0";
	if(b.size()>=half)c = b.substr(0, b.size()-half);
	else c="0";
	
	string z0 = karatsuba(aa,c);
	string z1 = karatsuba(add(aa,bb),add(c,d));
	string z2 = karatsuba(bb,d);
	string z3 = z0;
	string z4 = subtract(z1, add(z3, z2));
	
	z4+=pw;
	z0+=pw;
	z0+=pw;
	
	return add(z0, add(z2, z4));
	//return "0";
}

int main(){
	faster;
	cin >> a >> b;
	cout << karatsuba(a, b);
	return 0;
}
