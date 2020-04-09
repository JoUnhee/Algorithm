#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int C;
char cache[1<< 25];
vector<int> canPut;

int idx(int x, int y) { return 1 << (y * 5 + x); }
void makecanPut() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			vector<int> v;
			for (int dy = 0; dy < 2; dy++)
				for (int dx = 0; dx < 2; dx++)
					v.push_back(idx(y + dy, x + dx));

			int s = v[0] + v[1] + v[2] + v[3];
			for (int i = 0; i < 4; i++) {
				canPut.push_back(s - v[i]);
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			canPut.push_back(idx(i, j) + idx(i, j + 1));
			canPut.push_back(idx(j, i) + idx(j + 1, i));
		}
	}
}

int _input() {
	int ret = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			char tmp;
			cin >> tmp;

			if (tmp == '#') ret += idx(j, i);
		}
	}
	return ret;
}
void _init() {
	memset(cache, -1, sizeof(cache));
}
int solve(int board) {
	
	char& ret = cache[board];

	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < canPut.size(); i++) {
		if ((canPut[i] & board )== 0) {
			if (!solve(board | canPut[i])) {
				ret = 1;
				break;
			}
		}
	}
	return ret;
}
void solution() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;
	makecanPut();
	for (int t = 1; t <= C; t++) {
		_init();
		int board = _input();
		char ans = 0;
		

		if (solve(board)) cout << "WINNING" << endl;
		else cout << "LOSING" << endl;
	}
}
int main() {
	
	solution();
}