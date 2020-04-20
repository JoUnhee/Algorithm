#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define VMAX 10010
#define MAC 0
#define STB 1
#define MACP 10001
#define STBP 10002
#define INF 999999999

using namespace std;

int V, E, u, v, w, M, S,X,Y;
vector<pair<int, int>> ADJ[VMAX];
bool Check[VMAX];
int Dist[VMAX][2];


void _input() {
	cin >> V >> E;

	for (int i = 1; i <= V; i++) Dist[i][MAC] = INF, Dist[i][STB] = INF;

	for (int i = 0; i < E; i++) {
		cin >> u >> v >> w;
		ADJ[u].push_back({ v,w });
		ADJ[v].push_back({ u,w });
	}

	cin >> M >> X;

	for (int i = 0; i < M; i++) {
		int num;
		cin >> num;
		ADJ[MACP].push_back({ num,0 });
		Check[num] = true;
	}

	cin >> S >> Y;

	for (int i = 0; i < S; i++) {
		int num;
		cin >> num;
		ADJ[STBP].push_back({ num,0 });
		Check[num] = true;
	}
}
void BFS(int strt, int type) {

	queue<pair<int, int>> q;
	q.push({ strt, 0 });
	Dist[strt][type] = 0;

	while (!q.empty()) {
		int Cur = q.front().first;
		int Dis = q.front().second;

		q.pop();

		for (int i = 0; i < ADJ[Cur].size(); i++) {
			int Next = ADJ[Cur][i].first;
			int NDis = ADJ[Cur][i].second;

			if (Dis + NDis < Dist[Next][type]) {
				Dist[Next][type] = Dis + NDis;
				q.push({ Next,NDis + Dis });
			}

		}
	
	}
}
void solve() {
	
	_input();

	BFS(MACP, MAC);
	BFS(STBP, STB);

	int ans = INF;

	for (int i = 1; i <= V; i++) {
		if (Check[i]) continue;
		if (Dist[i][MAC] > X || Dist[i][STB] > Y) continue;

		ans = min(ans, Dist[i][MAC] + Dist[i][STB]);
	}

	if (ans == INF) cout << -1 << endl;
	else cout << ans << endl;

	return;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}