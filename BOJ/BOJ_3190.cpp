#include <cstring>
#include <cstdio>
#include <deque>
#include <iostream>

using namespace std;

typedef struct Po {
	int x;
	int y;

	Po(int _x,int _y) : x(_x),y(_y){}
};
typedef struct info {
	int t;
	char d;

	info(int _t, char _d) : t(_t), d(_d) {}
};


int N, K;
int l;
deque<Po> snake;
deque<info> dirInfo;

bool map[100][100];
int dx[4] = { 0, 1, 0 , -1 };
int dy[4] = { -1,0,1,0 };

void _input() {

	cin >> N >> K;

	for (int k = 0; k < K; k++) {
		int r, c;
		cin >> r >> c;

		map[r - 1][c - 1] = true;
	}

	cin >> l;
	for (int i = 0; i < l; i++) {
		int t; char d;
		cin >> t >> d;
		dirInfo.push_back(info(t, d));
	}

}
void _init() {
	snake.clear();
	dirInfo.clear();
	memset(map, 0, sizeof(map));
}
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
bool check(int nx, int ny) {

	for (int i = 1; i < snake.size(); i++) {
		int x = snake[i].x;
		int y = snake[i].y;

		if (nx == x && y == ny) return true;
	}
	return false;
}
void solve() {

	_init();
	_input();

	int time = 0;
	int dir = 1;
	bool flag = true;
	snake.push_back(Po(0,0));

	while (flag) {

		if (dirInfo.size() > 0 && dirInfo.front().t == time) {
			char which = dirInfo.front().d;
			dirInfo.pop_front();

			dir = which == 'L' ? (dir +3) % 4 : (dir+1) %4;
		}

		int nx = snake[0].x + dx[dir];
		int ny = snake[0].y + dy[dir];

		snake.push_front(Po(nx, ny));

		if (!isInside(nx, ny) || check(nx, ny)) flag = false;
		else if (map[ny][nx]) {
			map[ny][nx] = false;
		}
		else {
			snake.pop_back();
		}
		time++;
		
	}

	cout << time << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
