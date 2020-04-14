#include <string>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef struct info {
	int rx;
	int ry;
	int bx;
	int by;

	info(int _rx, int _ry, int _bx, int _by) :rx(_rx), ry(_ry), bx(_bx), by(_by) {}
};
int N, M;

char map[10][10];
bool visit[10][10][10][10];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

int ex, ey;
int rc, rr;
int bc, br;

bool ret;
void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] == 'R')	rc = j, rr = i, map[i][j] = '.';
			else if (map[i][j] == 'B') bc = j, br = i, map[i][j] = '.';
			else if (map[i][j] == 'O') ex = j, ey = i;

		}
	}
}

void solve() {
	
	_input();

	queue<info> q;
	q.push(info(rc, rr, bc, br));
	visit[rr][rc][br][bc] = true;

	int cnt = 0;
	ret = false;
	while (cnt < 10 && !q.empty()) {
		
		int sz = q.size();
		for(int i = 0 ; i < sz; i++){
			int rx = q.front().rx;
			int ry = q.front().ry;
			int bx = q.front().bx;
			int by = q.front().by;

			q.pop();

			for (int i = 0; i < 4; i++) {
				
				int first = 0;
				int nx[2] = { rx,bx };
				int ny[2] = { ry,by };
				bool game[2] = { false,false };
				if ((i == 0 && rx < bx) || (i == 1 && ry < by) || (i == 2 && rx > bx) || (i == 3 && ry > by)) first = 0;
				else first = 1;

				for (int n = 0; n < 2; n++) {
					
					int& curx = nx[first];
					int& cury = ny[first];
					while (1) {
						
						if (map[cury][curx] != '.') break;

						curx += dx[i];
						cury += dy[i];
					}

					if (map[cury][curx] == 'O') { 
						
						game[first] = true; 
					
					}
					else {
						curx -= dx[i];
						cury -= dy[i];

						map[cury][curx] = (first == 0 ? 'R' : 'B');
					}


					first = 1 - first;
				}


				if (game[0] && !game[1]) {
					ret = true;
					return;
				}
				
				for (int n = 0; n < 2; n++) {
					if (!game[n]) {
						map[ny[n]][nx[n]] = '.';
					}
				}

				if (!game[1]) {
					if (visit[ny[0]][nx[0]][ny[1]][nx[1]]) continue;
					visit[ny[0]][nx[0]][ny[1]][nx[1]] = true;

					q.push(info(nx[0], ny[0], nx[1],ny[1]));
					
				}


			}
		
		}
		cnt++;
	}

	return;

}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

	cout << ret << endl;
}