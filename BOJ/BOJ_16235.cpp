#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct tree {
	int x;
	int y;
	int age;

	tree(int _x, int _y, int _age) : x(_x), y(_y), age(_age) {}
};
typedef struct land {
	vector<int> trees;
	int amnt;
};

int N, M, K;

vector<tree> dead;

land map[10][10];
int A[10][10];

int dx[8] = { -1,0,1,-1,1,-1,0,1 };
int dy[8] = { -1,-1,-1,0,0,1,1,1 };

bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
bool cmp(int a, int b) {
	return a < b;
}
void _input() {
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		int r, c, age;

		cin >> r >> c >> age;

		map[r-1][c-1].trees.push_back(age);
		sort(map[r-1][c-1].trees.begin(), map[r-1][c-1].trees.end(), cmp);
	}

}
void _init() {
	memset(A, 0, sizeof(A));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j].trees.clear();
			map[i][j].amnt = 5;
		}
	}
	dead.clear();
}
void spring() {

	for(int i = 0 ; i < N; i++){
		for (int j = 0; j < N; j++) {
			if (map[i][j].trees.size() == 0) continue;
			
			vector<int>& q = map[i][j].trees;
			int& amnt = map[i][j].amnt;
			vector<int>::iterator it;

			for (it = q.begin(); it != q.end();) {
				int& cur = (*it);

				if (amnt >= cur) {

					amnt -= cur++;
					it++;
				}
				else {
					if(cur / 2 > 0)dead.push_back(tree(j, i, cur/2));
					it = q.erase(it);
				}
			}
			
		}
	}
}
void summer() {
	for (int i = 0; i < dead.size(); i++) {
		int x = dead[i].x;
		int y = dead[i].y;
		int amnt = dead[i].age;

		map[y][x].amnt += amnt;
	}
	dead.clear();
}
void fall() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j].trees.size() == 0) continue;

			vector<int>& q = map[i][j].trees;

			for (int k = 0; k < q.size(); k++) {
				if (q[k] % 5 != 0) continue;

				for (int l = 0; l < 8; l++) {
					int nx = j + dx[l];
					int ny = i + dy[l];

					if (!isInside(nx, ny)) continue;

					map[ny][nx].trees.push_back(1);
					sort(map[ny][nx].trees.begin(), map[ny][nx].trees.end(), cmp);
				}
			}
		}
	}
}
void winter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j].amnt += A[i][j];
		}
	}
}
int cnt() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ret += map[i][j].trees.size();
		}
	}
	return ret;
}
void solve() {

	_init();
	_input();

	int ans = 0;
	for (int k = 0; k < K; k++) {
	
		spring();
		summer();
		fall();
		winter();
	}

	ans = cnt();

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	
	solve();
	//vector<int> a = { 0,0,0,1,2,3,4,0,0,0,0 };

	//vector<int>::iterator it = a.begin();

	//for (; it != a.end(); it++) {
	//	if ((*it) > 0) a.erase(it--);
	//}


	//for (int i = 0; i < a.size(); i++) {
	//	cout << a[i] << " ";
	//}
	//cout << endl;
}