#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

typedef struct Thing {
	string name;
	int w;
	int need;

	Thing(string _name, int _w, int _need) : name(_name), w(_w), need(_need) {}
};

int C, N, W;
vector<Thing> q;

int cache[1001][100];

int DFS(int item, int cap) {
	
	if (item == N) return 0;
	int& ret = cache[cap][item];

	if (ret != -1) return ret;
	
	ret = DFS(item +1, cap);

	if (cap >= q[item].w) {
		ret = max(ret, DFS(item + 1, cap - q[item].w) + q[item].need);
	}

	return ret;
}

void recon(int cap, int item, vector<string>& picked) {
	if (item == N) return;
	if (DFS(item, cap) == DFS(item+1, cap)) recon(cap, item + 1, picked);
	else {
		picked.push_back(q[item].name);
		recon(cap - q[item].w, item + 1, picked);
	}
}
void _init() {
	q.clear();
	memset(cache, -1, sizeof(cache));
}
void _input(){
	cin >> N >> W;
	
	for (int i = 0; i < N; i++) {
		string name;
		int w, need;

		cin >> name >> w >> need;

		q.push_back(Thing(name, w, need));
	}
}
void print(int ans, int cnt, vector<string>& picked) {
	printf("%d %d\n", ans, cnt);
	for (int i = 0; i < cnt; i++) {
		cout << picked[i] << endl;
	}
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;

	for (int c = 1; c <= C; c++) {
		_init();
		_input();

		vector<string> picked;
		int ans, cnt;

		ans = DFS(0, W);
		recon(W, 0, picked);
		cnt = picked.size();

		print(ans, cnt, picked);
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	
	solve();
	
}
