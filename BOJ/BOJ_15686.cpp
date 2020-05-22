#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef struct po {
	int x;
	int y;

	po(int _x, int _y) :x(_x), y(_y) {}
};

int N, M;
int map[50][50];

vector<po> Chickens;
vector<po> houses;

int ans;

void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			if (map[i][j] == 1) houses.push_back(po(j, i));
			else if (map[i][j] == 2) Chickens.push_back(po(j, i));
		}
	}
}
void _init() {
	Chickens.clear();
	houses.clear();
	memset(map, 0, sizeof(map));
	ans = 987654321;
}
void calc(vector<po> chicken) {

	int sum = 0;
	for (int i = 0; i < houses.size(); i++) {
		int hx = houses[i].x;
		int hy = houses[i].y;
		int tmp = 987654321;

		for (int j = 0; j < chicken.size(); j++) {
			int cx = chicken[j].x;
			int cy = chicken[j].y;

			tmp = min(tmp, abs(hx - cx) + abs(hy - cy));
		}

		sum += tmp;
	}

	ans = min(ans, sum);
}
void DFS(int idx,vector<po> chck,int m) {

	if (chck.size() == m) {
		calc(chck);
		return;
	}

	for (int i = idx+1; i < Chickens.size(); i++) {
		
		chck.push_back(Chickens[i]);
		DFS(i, chck, m);
		chck.pop_back();
	}
}
void solve() {
	
	_init();
	_input();

	for (int m = 1; m <= M; m++) {
		vector<po> ch;
		DFS(-1, ch, m);
	}

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
