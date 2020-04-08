
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;

int cache[19683];
int biject(const vector<string>& b) {
	int ret = 0;

	for(int y = 0 ; y < 3; y++){
		for (int x = 0; x < 3; x++) {
			ret = ret * 3;
			if (b[y][x] == 'o') ret++;
			else if (b[y][x] == 'x') ret += 2;
		}
	}
	return ret;
}
bool isFinished(const vector<string>& b, char turn) {
	//가로

	for (int y = 0; y < 3; y++) {

		for (int x = 0; x < 3; x++) {
			if (b[y][x] != turn) break;
			if (x == 2) return true;

		}
	}
	// 세로

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (b[y][x] != turn) break;
			if (y == 2) return true;
		}
	}
	
	//대각선
	for (int i = 0; i < 3; i++) {
		if (b[i][i] != turn) break;
		if (i == 2) return true;
	}

	for (int i = 0; i < 3; i++) {
		if (b[i][2 - i] != turn) break;
		if (i == 2) return true;
	}
	return false;
}
int canWin(vector<string>& b, char turn) {
	
	if (isFinished(b, 'x'+'o' - turn)) return -1;

	int& ret = cache[biject(b)];

	if (ret != -2) return ret;

	int minV = 2;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (b[y][x] == '.') {
				b[y][x] = turn;
				minV = canWin(b, 'o' + 'x' - turn);
				b[y][x] = '.';
			}
		}
	}
	
	if (minV == 2 || minV == 0) return ret = 0;
	
	
	return ret = - minV;
}
int main() {

	vector<string> b = { "...","...","..." };
	for (int i = 0; i < 19683; i++) cache[i] = -2;
	cout << canWin(b,'o') << endl;

}