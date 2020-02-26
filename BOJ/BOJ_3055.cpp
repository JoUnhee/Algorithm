#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;


int R, C;
int ret = 987654321;

char MAP[51][51];


int dx[4] = { -1, 0 , 1 , 0 };
int dy[4] = { 0 , 1, 0 , -1 };

queue<pair<int,int>> Wq;
queue<pair<int, int>> Sq;

void input() {
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == '*') {
				Wq.push({ i,j });
			}
			else if (MAP[i][j] == 'S') {
				Sq.push({ i,j });
			}
		}
	}


}
bool isInside(int x, int y) {
	return x >= 0 && x < C && y >= 0 && y < R;
}

void BFS_W() {
	int sz = Wq.size();

	for (int i = 0; i < sz; i++) {
		int x = Wq.front().second;
		int y = Wq.front().first;

		Wq.pop();

		for (int j = 0; j < 4; j++) {
			int nx = x + dx[j];
			int ny = y + dy[j];

			if (isInside(nx, ny) && MAP[ny][nx] == '.') {
				MAP[ny][nx] = '*';
				Wq.push({ ny,nx });
			}
		}
	}
}
bool BFS_S() {
	int sz = Sq.size();

	for (int i = 0; i < sz; i++) {
		int x = Sq.front().second;
		int y = Sq.front().first;

		Sq.pop();

		for (int j = 0; j < 4; j++) {
			int nx = x + dx[j];
			int ny = y + dy[j];

			if (isInside(nx, ny)) {
				if (MAP[ny][nx] == 'D') return true;
				else if (MAP[ny][nx] == '.') {
					MAP[ny][nx] = 'S';
					Sq.push({ ny,nx });
				}
			}
		}
	}

	return false;
}
void solve() {
	int time = 0;
	while (1) {
		time++;

		if (Sq.size() == 0) {
			cout << "KAKTUS"<< endl;
			return;
		}

		BFS_W();
		if (BFS_S()) {
			cout << time << endl;
			return;
		}

	}
	return;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	solve();

}
