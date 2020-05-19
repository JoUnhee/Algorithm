#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
int map[8][8];
int Tmap[8][8];
int ans;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

vector<pair<int, int>> zeros;
vector<pair<int, int>> viruses;

void _init() {
	memset(map, 0, sizeof(map));
	memset(map, 0, sizeof(Tmap));
	zeros.clear();
	viruses.clear();
	ans = 0;
}
void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] == 0) {
				zeros.push_back({ i,j });
			}
			else if (map[i][j] == 2) {
				viruses.push_back({ i,j });
			}
		}
	}
}
void cpyArr() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Tmap[i][j] = map[i][j];
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
int spread() {
	queue<pair<int, int>> q;
	bool visit[8][8];
	memset(visit, 0, sizeof(visit));
	int ret = 0;
	for (int i = 0; i < viruses.size(); i++) q.push(viruses[i]),visit[viruses[i].first][viruses[i].second] = true;

	while (!q.empty()) {
	
		int x = q.front().second;
		int y = q.front().first;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!isInside(nx, ny)) continue;
			if (visit[ny][nx]) continue;
			if (Tmap[ny][nx] != 0) continue;

			visit[ny][nx] = true;
			Tmap[ny][nx] = 2;
			q.push({ ny,nx });
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) { 
			if (Tmap[i][j] == 0) ret++; 
		}
	}
	return ret;
}
void putWall(int i, int j, int k) {
	Tmap[zeros[i].first][zeros[i].second] = 1;
	Tmap[zeros[j].first][zeros[j].second] = 1;
	Tmap[zeros[k].first][zeros[k].second] = 1;
}
void solve() {
	
	_init();
	_input();

	int sz = zeros.size();

	for (int i = 0; i < sz; i++) {
		for (int j = i + 1; j < sz; j++) {
			for (int k = j + 1; k < sz; k++) {
				cpyArr();
				putWall(i, j, k);

				ans = max(ans, spread());
			}
		}
	}
	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}