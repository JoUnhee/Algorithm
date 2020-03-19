#include <string>
#include <vector>
#include <queue>
#include<iostream>
using namespace std;
typedef struct info {
	int x;
	int y;
	int state;
	info(int _x, int _y, int _state) : x(_x), y(_y), state(_state) {}
};

int N;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int cx[4] = { 1,-1,-1,1 };
int cy[4] = { 1,1,-1,-1 };
int map[100][100];
void cpy(vector<vector<int>> obj) {
	N = obj.size();
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = obj[i][j];
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
int check_state(int sx, int sy, int objx, int objy) {
	if (sx+1 == objx && sy == objy) return 0;
	if (sx == objx && sy + 1 == objy) return 1;
	if (sx - 1 == objx && sy == objy) return 2;
	if(sx == objx && sy-1 == objy) return 3;

	return -1;
}
int check(int sx, int sy, int objx,int objy,int dir) {
	if (dir == 1) {
		int idx = check_state(sx, sy, objx, objy);
		int nx = sx + cx[idx];
		int ny = sy + cy[idx];
		int rx = sx + dx[(idx + 1) % 4];
		int ry = sy + dy[(idx + 1) % 4];

		if (isInside(nx, ny) && isInside(rx, ry) && map[ny][nx] == 0 && map[ry][rx] == 0) return (idx + 1) % 4;
	}
	else if (dir == 0) {
		int idx = check_state(sx, sy, objx, objy);
		int nx = sx + cx[(idx + 3) % 4];
		int ny = sy + cy[(idx + 3) % 4];
		int rx = sx + dx[(idx + 3) % 4];
		int ry = sy + dy[(idx + 3) % 4];
		if (isInside(nx, ny) && isInside(rx, ry) && map[ny][nx] == 0 && map[ry][rx] == 0) return (idx + 3) % 4;
	}
	return -1;
}
int BFS() {

	bool visit[100][100][4];
	memset(visit, 0, sizeof(visit));
	queue<info> q;
	q.push(info(0, 0, 0));
	visit[0][0][0] = true;

	int cnt = 0;

	while (!q.empty()) {
		int sz = q.size();
		
		for (int s = 0; s < sz; s++) {
			int x = q.front().x;
			int y = q.front().y;
			int state = q.front().state;
			int x2 = x + dx[state];
			int y2 = y + dy[state];

			q.pop();

			if (x == N - 1 && y == N - 1) return cnt;
			if (x2 == N - 1 && y2 == N - 1) return cnt;

			for (int i = 0; i < 4; i++) {
				int nx1 = x + dx[i];
				int ny1 = y + dy[i];
				int nx2 = x2 + dx[i];
				int ny2 = y2 + dy[i];
				if (!isInside(nx1, ny1)) continue;
				if (!isInside(nx2, ny2)) continue;
				if (map[ny1][nx1] == 1 || map[ny2][nx2] == 1) continue;
				if (visit[ny1][nx1][state]) continue;

				visit[ny1][nx1][state] = true;
				q.push(info(nx1, ny1,state));
			}
			for (int i = 0; i < 2; i++) {
				int idx = check(x, y, x2, y2,i);
				if (idx == -1) continue;
				int nx2 = x + dx[idx];
				int ny2 = y + dy[idx];
				int nstate = ( i == 1 ? (state +1)%4 : (state +3)%4);
				if (visit[y][x][nstate]) continue;
				visit[y][x][nstate] = true;
				q.push(info(x, y, nstate));
			}
			for (int i = 0; i < 2; i++) {
				int idx = check(x2, y2, x, y, i);
				if (idx == -1) continue;
				int nx1 = x2 + dx[idx];
				int ny1 = y2 + dy[idx];
				int nstate = (i == 1 ? (state + 1) % 4 : (state + 3) % 4);
				if (visit[ny1][nx1][nstate]) continue;
				visit[ny1][nx1][nstate] = true;
				q.push(info(nx1, ny1,nstate));
			}
		}
		
		cnt++;
	}
}
int solution(vector<vector<int>> board) {
	int answer = 0;
	cpy(board);
	answer = BFS();

	return answer;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	vector<vector<int>> bd;

	bd.push_back({ 0, 0, 0, 1, 1 });
	bd.push_back({ 0, 0, 0, 1, 0 });
	bd.push_back({ 0, 1, 0, 1, 1 });
	bd.push_back({ 1, 1, 0, 0, 1 });
	bd.push_back({ 0, 0, 0, 0, 0 });

	int ans = solution(bd);

	cout << ans << endl;
}