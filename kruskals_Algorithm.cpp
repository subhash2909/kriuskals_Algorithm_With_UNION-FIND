#include<bits/stdc++.h>
using namespace std;
#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define mod 1000000007
#define  pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef  long double ld;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi >vvi;
typedef vector<ll> vll;
typedef vector<vll >vvll;


struct edge_ {
	ll v1, v2, wt;
};

ll max_vertices = 25, max_weights = 10;
ll n, m, u, v, w, cost;
ll _rank[1001], par[1001];
vector<edge_>edges, result;


void create_random_graph() {

	n = 50 + rand() % max_vertices;
	ll max_edges = n * (n - 1) / 2;
	m = 1 + rand() % max_edges;


	ll edge_count = m;
	set<pair<ll, ll> >s;

	while (edge_count) {
		ll v1 = 1 + rand() % n, v2 = 1 + rand() % n;
		if (v1 == v2)continue;
		if (s.find({v1, v2}) != s.end() || s.find({v2, v1}) != s.end())continue;
		ll wt = 1 + rand() % max_weights;
		edges.pb({v1, v2, wt});
		s.insert({v1, v2});
		edge_count--;
	}

}


bool comp(const edge_ &e1, const edge_ &e2) {
	return (e1.wt < e2.wt);
}

ll find(ll v1) {

	if (par[v1] == -1)return v1;

	return par[v1] = find(par[v1]);
}

void combine(ll v1, ll v2) {

	ll a = find(v1), b = find(v2);

	if (_rank[a] == _rank[b])_rank[b]++, par[a] = b;
	if (_rank[a] < _rank[b])par[a] = b;
	else par[b] = a;
}


int main() {
	IOS;
	srand(time(0));

	create_random_graph();

	cout << "n  ---> " << n << "\n";
	cout << "m  ---> " << m << "\n";
	cout << "\ninput graph-->\n";
	for (auto ele : edges)cout << ele.v1 << " " << ele.v2 << " " << ele.wt << "\n";


	for (ll i = 0; i <= n; i++)par[i] = -1;

	sort(edges.begin(), edges.end(), comp);


	for (ll i = 0; i < m; i++) {
		ll v1 = edges[i].v1, v2 = edges[i].v2;
		ll a = find(v1), b = find(v2);
		if (a != b) {
			combine(a, b);
			result.pb({v1, v2, edges[i].wt});
			cost += edges[i].wt;
		}
	}

	cout << "\ncost --> " << cost << "\n";
	cout << "\nminimum spanning forest --->\n";

	for (auto ele : result)cout << ele.v1 << " " << ele.v2 << " " << ele.wt << "\n";

}
