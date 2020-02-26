#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

typedef struct Cell {
	int type;
	vector<int> q;
};

typedef struct Mal {
	int x;
	int y;
	int dir;
};

Cell MAP[13][13];
vector<Mal> q;

int N, K;
int ret;

int dx[5] = { 0,1,-1,0,0 };
int dy[5] = { 0,0,0,-1,1 };

bool isInside(int x, int y) {
	return x >= 1 && x <= N && y >= 1 && y <= N;
}
int FindIdx(int x, int y, int obj) {

	for (int i = 0; i < MAP[y][x].q.size(); i++) {
		if (MAP[y][x].q[i] == obj) return i;
	}
	return 0;
}
int changeDir(int dir) {

	if (dir == 1) return 2;
	else if (dir == 2) return 1;
	else if (dir == 3) return 4;
	else if (dir == 4) return 3;
}
void DoneByType(int nx, int ny, vector<int>& tq) {

	if (MAP[ny][nx].type == 0) {

		for (int i = 0; i < tq.size(); i++) {
			MAP[ny][nx].q.push_back(tq[i]);
			q[tq[i]].x = nx;
			q[tq[i]].y = ny;
		}
	}
	else if (MAP[ny][nx].type == 1) {

		for (int i = tq.size() - 1; i >= 0; i--) {
			MAP[ny][nx].q.push_back(tq[i]);
			q[tq[i]].x = nx;
			q[tq[i]].y = ny;
		}
	}
	tq.clear();
	return;
}
int main() {

	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int type;
			cin >> type;
			MAP[i][j].type = type;
		}
	}
	for (int i = 0; i < K; i++) {
		int x, y, dir;
		cin >> y >> x >> dir;
		q.push_back({ x,y,dir });
		MAP[y][x].q.push_back(i);
	}

	int turn = 1;
	bool flag = false;
	while (turn <= 1000 && !flag) {
		for (int i = 0; i < K; i++) {
			vector<int> tq;
			int x = q[i].x;
			int y = q[i].y;
			int& dir = q[i].dir;

			if (MAP[y][x].q.size() > 1) {
				int strt = FindIdx(x, y, i);
				int size = MAP[y][x].q.size();
				for (int j = 0; j < size - strt; j++) {
					tq.push_back(MAP[y][x].q[strt]);
					MAP[y][x].q.erase(MAP[y][x].q.begin() + strt);
				}
			}
			else {
				tq.push_back(i);
				MAP[y][x].q.pop_back();
			}


			int nx = x + dx[dir];
			int ny = y + dy[dir];

			if (isInside(nx, ny) && MAP[ny][nx].type != 2)	DoneByType(nx, ny, tq);
			else if (!isInside(nx, ny) || (isInside(nx, ny) && MAP[ny][nx].type == 2)) {

				dir = changeDir(dir);

				nx = x + dx[dir];
				ny = y + dy[dir];

				if (isInside(nx, ny) && MAP[ny][nx].type != 2) DoneByType(nx, ny, tq);
				else if (!isInside(nx, ny) || (isInside(nx, ny) && MAP[ny][nx].type == 2)) {

					for (int i = 0; i < tq.size(); i++) MAP[y][x].q.push_back(tq[i]);
					tq.clear();
					nx = x;
					ny = y;
				}

			}
			if (MAP[ny][nx].q.size() >= 4) {
				flag = true;
				break;
			}
		}

		if (!flag)	turn++;

	}

	if (turn > 1000) ret = -1;
	else ret = turn;

	printf("%d\n", ret);
	return 0;
}