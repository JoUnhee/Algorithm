#include <string>
#include <vector>
#include<iostream>
using namespace std;
int N, M;


void rotate(vector<vector<int>>& key) {
	vector<vector<int>> temp = key;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			key[i][j] = temp[j][M - 1 - i];
		}
	}
}
bool match(int kx, int ky,vector<vector<int>> key, vector<vector<int>> lock) {
	int back[60][60];
	memset(back, 0, sizeof(back));

	for (int y = 0; y < M; y++) {
		for (int x = 0; x < M; x++) {
			back[ky + y][kx + x] = key[y][x];
		}
	}
	int offset = M - 1;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			back[y + offset][x + offset] += lock[y][x];
			if (back[y + offset][x + offset] != 1) return false;
		}
	}
	return true;

}
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = false;
	N = lock.size();
	M = key.size();
	int cursor = N + M - 1;
	for (int i = 0; i < 4; i++) {
		for (int ky = 0; ky <= cursor; ky++) {
			for (int kx = 0; kx <= cursor; kx++) {
				answer = match(kx, ky,key, lock);
				if (answer) return true;
			}
		}
		rotate(key);
	}
	return false;
}
int main() {
	vector<vector<int>> l;
	vector<vector<int>> k;

	l.push_back({ 1, 1, 1 });
	l.push_back({ 1, 1, 0 });
	l.push_back({ 1, 0, 1 });
	k.push_back({ 0, 0, 0 });
	k.push_back({ 1, 0, 0 });
	k.push_back({ 0, 1, 1 });
	cout << solution(k, l) << endl;
}