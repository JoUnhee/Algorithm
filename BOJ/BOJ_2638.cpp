#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, M;
int map[100][100];
int visit[100][100];

vector<pair<int, int>> chz;
vector<pair<int, int>> check;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

void _input() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] == 1) chz.push_back({ i,j });
		}
	}
}
void _init() {
	memset(map, 0, sizeof(map));
	chz.clear();
	check.clear();
}
void clearV() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[i][j] = -1;
		}
	}
	check.clear();
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
void Check(int x, int y) {
	visit[y][x] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (!isInside(nx, ny)) continue;
		if (map[ny][nx] == 1) continue;
		if (visit[ny][nx] != -1) continue;

		Check(nx, ny);
	}
}
void printVisit() {
	printf("-------------------------\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%3d", visit[i][j]);

		}
		printf("\n");
	}
}
void printmap() {
	printf("----------map------------\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%3d", map[i][j]);

		}
		printf("\n");
	}
}
void solve() {

	_init();
	_input();

	int ans = 0;

	while (!chz.empty()) {

		clearV();
		Check(0, 0);
		printVisit();

		vector<pair<int,int>> ::iterator cur;

		for (cur = chz.begin(); cur != chz.end();) {
			int x = (*cur).second;
			int y = (*cur).first;
			int cnt = 0;
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!isInside(nx, ny)) continue;
				if (map[ny][nx] == 1) continue;
				if (visit[ny][nx] == -1) continue;
				cnt++;
			}

			if (cnt >= 2) {
				check.push_back({ y,x });
				cur = chz.erase(cur);
			}
			else cur++;
		}

		for (int i = 0; i < check.size(); i++) {
			int y = check[i].first;
			int x = check[i].second;

			map[y][x] = 0;
		}
		ans++;
		printmap();
	
	}
	cout << ans << endl;
}
int main() {
	
	solve();

}