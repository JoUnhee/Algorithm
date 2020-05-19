#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int N, M, x, y, K;

int dice[7];

int dx[5] = { 0, 1,-1,0,0 };
int dy[5] = { 0,0,0,-1,1 };

int map[20][20];
vector<int> order;

void _init() {
	memset(map, 0, sizeof(map));
	memset(dice, 0, sizeof(dice));
	order.clear();

}
void _input() {
	cin >> N >> M >> y >> x >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int k = 0; k < K; k++) {
		int dir;
		cin >> dir;
		order.push_back(dir);
	}
}
void cpyDice(int obj[7]) {
	for (int i = 1; i <= 6; i++) {
		dice[i] = obj[i];
	}
}
void move(int dir) {
	int tmp[7];
	if (dir == 1) {		//µ¿
		tmp[1] = dice[3];
		tmp[2] = dice[2];
		tmp[3] = dice[6];
		tmp[4] = dice[1];
		tmp[5] = dice[5];
		tmp[6] = dice[4];
	}
	else if (dir == 2) {	//¼­
		tmp[1] = dice[4];
		tmp[2] = dice[2];
		tmp[3] = dice[1];
		tmp[4] = dice[6];
		tmp[5] = dice[5];
		tmp[6] = dice[3];
	}
	else if (dir == 3) {	//ºÏ
		tmp[1] = dice[2];
		tmp[2] = dice[6];
		tmp[3] = dice[3];
		tmp[4] = dice[4];
		tmp[5] = dice[1];
		tmp[6] = dice[5];
	}
	else if (dir == 4) {	//³²
		tmp[1] = dice[5];
		tmp[2] = dice[1];
		tmp[3] = dice[3];
		tmp[4] = dice[4];
		tmp[5] = dice[6];
		tmp[6] = dice[2];
	}
	cpyDice(tmp);
}
bool isInside(int nx, int ny) {
	return nx >= 0 && nx < M && ny >= 0 && ny < N;
}
void solve() {
	_init();
	_input();

	for (int i = 0; i < order.size(); i++) {
		int dir = order[i];

		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (!isInside(nx, ny)) continue;

		move(dir);
		if (map[ny][nx] == 0) {
			map[ny][nx] = dice[1];
		}
		else {
			dice[1] = map[ny][nx];
			map[ny][nx] = 0;
		}
		cout << dice[6] << endl;
		x = nx, y = ny;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}