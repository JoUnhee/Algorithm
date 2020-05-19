#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

int N, M;
int B[500][500];
int ans;
vector<vector<pair<int, int>>> shape = {
	{{0,0},{1,0},{2,0},{3,0}},
	{{0,0},{0,1},{0,2},{0,3}},

	{{0,0},{0,1},{1,0},{1,1}},

	{{0,0},{1,0},{2,0},{2,-1}},
	{{0,0},{1,0},{2,0},{2,1}},
	{{0,0},{0,1},{0,2},{-1,2}},
	{{0,0},{0,1},{0,2},{1,2}},
	{{0,0},{-1,0},{-2,0},{-2,1}},
	{{0,0},{-1,0},{-2,0},{-2,-1}},
	{{0,0},{0,-1},{0,-2},{-1,-2}},
	{{0,0},{0,-1},{0,-2},{1,-2}},

	{{0,0},{1,0},{2,0},{1,-1}},
	{{0,0},{1,0},{2,0},{1,1}},
	{{0,0},{0,1},{0,2},{1,1}},
	{{0,0},{0,1},{0,2},{-1,1}},
	{{0,0},{-1,0},{-2,0},{-1,-1}},
	{{0,0},{-1,0},{-2,0},{-1,1}},
	{{0,0},{0,-1},{0,-2},{1,-1}},
	{{0,0},{0,-1},{0,-2},{-1,-1}},

	{{0,0},{1,0},{1,1},{2,1}},
	{{0,0},{1,0},{1,-1},{2,-1}},
	{{0,0},{0,1},{1,1},{1,2}},
	{{0,0},{0,1},{-1,1},{-1,2}},
	{{0,0},{-1,0},{-1,1},{-2,1}},
	{{0,0},{-1,0},{-1,-1},{-2,-1}},
	{{0,0},{0,-1},{-1,-1},{-1,-2}},
	{{0,0},{0,-1},{1,-1},{1,-2}},

};
void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> B[i][j];
		}
	}
}
void _init() {
	memset(B, 0, sizeof(B));
	ans = 0;
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
void solve() {

	_init();
	_input();

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			for (int k = 0; k < shape.size(); k++) {
				int sum = 0;
				for (int i = 0; i < shape[k].size(); i++) {
					int nx = x + shape[k][i].first;
					int ny = y + shape[k][i].second;

					if (!isInside(nx, ny)) { 
						sum = -1;
						break; 
					}
					sum += B[ny][nx];
				}
				if(sum != -1) ans = max(ans, sum);
			}
		}
	}

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}