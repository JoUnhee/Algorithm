#include<algorithm>
#include<cstring>
#include<iostream>
#include<memory.h>
#include<queue>
using namespace std;

typedef struct POS {
	int x;
	int y;
	int z;

	POS(int tx, int ty, int tz) : x(tx), y(ty), z(tz) {}
};

int ret = 987654321;

int dx[6] = { -1,1,0,0,0,0 };
int dy[6] = { 0,0,-1,1,0,0 };
int dz[6] = { 0, 0, 0, 0, -1, 1 };

int input[5][5][5] = { 0, };
int map[5][5][5] = { 0, };
bool check(int obj) {
	return obj >= 0 && obj < 5;
}
bool isInside(int x, int y, int z) {
	return check(x) && check(y) && check(z);
}
void BFS() {

	queue<POS> q;
	int dist[5][5][5] = { -1, };

	memset(dist, -1, sizeof(dist));
	dist[0][0][0] = 0;
	q.push(POS(0, 0, 0));

	while (!q.empty()) {

		int x = q.front().x;
		int y = q.front().y;
		int z = q.front().z;

		q.pop();

		if (x == 4 && y == 4 && z == 4) {
			if (ret > dist[z][y][x]) ret = dist[z][y][x];
			return;
		}

		for (int i = 0; i < 6; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			int nz = z + dz[i];

			if (!isInside(nx, ny, nz)) continue;

			if (map[nz][ny][nx] == 1 && dist[nz][ny][nx] == -1) {
				q.push(POS(nx, ny, nz));
				dist[nz][ny][nx] = dist[z][y][x] + 1;
			}
		}

	}
}
void rotate(int layer) {

	int Temp[5][5] = { 0, };


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			Temp[j][4 - i] = map[layer][i][j];
		}
	}
	memcpy(map[layer], Temp, sizeof(map[layer]));

	return;
}
void DFS(int layer) {
	if (layer == 5) {
		/* ±æÃ£±â~*/
		if (map[0][0][0] == 1 && map[4][4][4] == 1)
			BFS();
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			rotate(layer);
			DFS(layer + 1);
		}
	}
}

void solve() {

	int order[5] = { 0, 1, 2, 3 ,4 };


	do {

		for (int i = 0; i < 5; i++) {
			memcpy(map[i], input[order[i]], sizeof(int) * 5 * 5);
		}

		DFS(0);

	} while (next_permutation(order, order + 5));

	if (ret == 987654321) ret = -1;
	cout << ret << endl;
}
void _input() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				cin >> input[i][j][k];
			}
		}
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
	solve();

}