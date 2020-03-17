#include <string>
#include <vector>
#include<algorithm>
#include<cstring>
#include<iostream>

using namespace std;
int N;
bool map[101][101][2];

bool isInside(int x, int y) {
	return x >= 0 && x <= N && y >= 0 && y <= N;
}
bool able(int x, int y, int type) {

	if (type == 0) {
		if (y == 0) return true;
		if (isInside(x - 1, y) && map[y][x - 1][1]) return true;
		if (isInside(x, y) && map[y][x][1]) return true;
		if (isInside(x, y - 1) && map[y - 1][x][0]) return true;
	}
	else if (type == 1) {
		if (isInside(x - 1, y) && isInside(x + 1, y) && map[y][x - 1][1] && map[y][x + 1][1]) return true;
		if (isInside(x, y - 1) && map[y - 1][x][0]) return true;
		if (isInside(x + 1, y - 1) && map[y - 1][x + 1][0]) return true;
	}
	return false;
}

bool check( int x, int y, int type, int action) {

	if (action == 1) {
		if (!able(x, y, type)) return false;
	}
	else if (action == 0) {
		map[y][x][type] = false;
		if (type == 0) {
			if (isInside(x - 1, y + 1) && map[y + 1][x - 1][1] && !able(x - 1, y + 1, 1)) { map[y][x][type] = true;  return false; }
			if (isInside(x, y + 1) && map[y + 1][x][1] && !able(x, y + 1, 1)) { map[y][x][type] = true;  return false; }
			if (isInside(x, y + 1) && map[y + 1][x][0] && !able(x, y + 1, 0)) { map[y][x][type] = true;  return false; }
		}
		else if (type == 1) {
			if (isInside(x, y) && map[y][x][0] && !able(x, y, 0)) { map[y][x][type] = true;  return false; }
			if (isInside(x + 1, y) && map[y][x + 1][1] && !able(x + 1, y, 1)) { map[y][x][type] = true;  return false; }
			if (isInside(x - 1, y) && map[y][x - 1][1] && !able(x - 1, y, 1)) { map[y][x][type] = true;  return false; }
			if (isInside(x + 1, y) && map[y][x + 1][0] && !able(x + 1, y, 0)) { map[y][x][type] = true;  return false; }
		}
		map[y][x][type] = true;
	}
	return true;
}
bool cmp(vector<int>& A, vector<int>& B) {
	if (A[0] == B[0]) {
		if (A[1] == B[1]) {
			return A[2] < B[2];
		}
		else return A[1] < B[1];
	}
	return A[0] < B[0];
}
vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;

	memset(map, 0, sizeof(map));
	N = n;;
	for (int i = 0; i < build_frame.size(); i++) {
		int x = build_frame[i][0];
		int y = build_frame[i][1];
		int type = build_frame[i][2];
		int action = build_frame[i][3];

		if (check(x, y, type, action)) {
			if (action == 1) map[y][x][type] = true;
			else map[y][x][type] = false;

		}


	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k < 2; k++) {
				if (map[i][j][k]) answer.push_back({ j,i,k });
			}
		}
	}
	sort(answer.begin(), answer.end(), cmp);
	return answer;
}
int main() {

	vector<vector<int>> ret;
	vector<vector<int>> build;

	build.push_back({ 0, 0, 0, 1 });
	build.push_back({ 2, 0, 0, 1 });
	build.push_back({ 4, 0, 0, 1 });
	build.push_back({ 0, 1, 1, 1 });
	build.push_back({ 1, 1, 1, 1 });
	build.push_back({ 2, 1, 1, 1 });
	build.push_back({ 3, 1, 1, 1 });
	build.push_back({ 2, 0, 0, 0 });
	build.push_back({ 1, 1, 1, 0 });
	build.push_back({ 2, 2, 0, 1 });
	
	ret = solution(5, build);
	cout << ret.size() << endl;
}