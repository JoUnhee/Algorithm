#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;
#define MAX 110

int T, H, W;
int ans;
char map[MAX][MAX];
bool visit[MAX][MAX];
bool key[26];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };


/*
	얍문님의 알고리즘을 참고하여 풀었습니다.
	출처 : http://yabmoons.tistory.com/97
*/
void _input() {

	cin >> H >> W;

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cin >> map[i][j];
		}
	}
	string keys;
	cin >> keys;
	if (keys == "0") return;
	for (int i = 0; i < keys.size(); i++) {
		key[keys[i] - 'a'] = true;
	}
}
void _init() {
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
	memset(key, 0, sizeof(key));
	ans = 0;
}
bool isInside(int x, int y) {
	return x >= 0 && x <= W + 1 && y >= 0 && y <= H + 1;
}
void BFS() {
	queue<pair<int, int>> Door[26];
	queue<pair<int, int>> q;
	visit[0][0] = true;
	q.push({ 0,0 });

	while (!q.empty()) {
		int x = q.front().second;
		int y = q.front().first;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!isInside(nx, ny)) continue;
			if (visit[ny][nx]) continue;
			if (map[ny][nx] == '*') continue;


			visit[ny][nx] = true;
			char obj = map[ny][nx];
			if (obj >= 'A' && obj <= 'Z') {
			
				if (key[obj - 'A']) {
					q.push({ ny,nx });
				}
				else {
					Door[obj - 'A'].push({ ny,nx });
				}
			}
			else if (obj >= 'a' && obj <= 'z') {
				q.push({ ny,nx });

				if (key[obj - 'a'] == false) {
					key[obj - 'a'] = true;

					while (!Door[obj - 'a'].empty()) {
						q.push(Door[obj - 'a'].front());
						Door[obj - 'a'].pop();
					}
				}
				
			}
			else {
				q.push({ ny,nx });
				if (obj == '$') ans++;
			}

		}
	}
}
void _solve() {
	cin >> T;

	for (int t = 1; t <= T; t++) {
	
		_init();
		_input();
		BFS();

		cout << ans << endl;
	}

}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_solve();

}