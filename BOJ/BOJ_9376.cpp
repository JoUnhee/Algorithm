#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>

#define MAX 102
#define INF 1e9;

using namespace std;

int T;
int h, w;
int H, W;
int visit[MAX][MAX][3];
char map[MAX][MAX];

pair<int, int> p[3];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return x >= 0 && x < W && y >= 0 && y <H;
}
void BFS(int type) {

	deque<pair<int, int>> q;
	q.push_back(p[type]);

	visit[p[type].first][p[type].second][type] = 0;

	while (!q.empty()) {
	
		int x = q.front().second;
		int y = q.front().first;
		int& cur = visit[y][x][type];
		q.pop_front();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!isInside(nx, ny)) continue;
			if (map[ny][nx] == '*') continue;
			if (visit[ny][nx][type] >= 0 ) continue;
			int& next = visit[ny][nx][type];

			if (map[ny][nx] == '.') next = cur, q.push_front({ ny,nx });
			else if(map[ny][nx] == '#')	next = cur + 1,q.push_back({ ny,nx });
		
		}
	}
	
	
}
void _init() {
	memset(map, 0, sizeof(map));
	memset(visit, -1, sizeof(visit));
}
void _input() {
	cin >> h >> w;
	int cnt = 0;
	H = h + 2;
	W = w + 2;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			
			if (i == 0 || j == 0 || i == h+1 || j == w+1) {
				map[i][j] = '.';
				continue;
			}
			cin >> map[i][j];

			if (map[i][j] == '$') {
				p[cnt].first = i;
				p[cnt].second = j;
				cnt++;

				map[i][j] = '.';
			}
		}
	}
	p[2].first = p[2].second = 0;
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);
	cin >> T;

	for (int t = 1; t <= T; t++) {
		_init();
		_input();

		for (int i = 0; i < 3; i++) {
			BFS(i);
		}
		int ans = INF;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (map[i][j] == '*') continue;
				int dist = 0;
				for (int type = 0; type < 3; type++) dist += visit[i][j][type];
				if (map[i][j] == '#') dist -= 2;
				ans = min(ans, dist);
			}
		}
		cout << ans << endl;
	}
}
int main() {

	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
