#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;
int ret;
bool isSame(string obj) {

	char cur = obj[0];
	for (int i = 1; i < 4; i++) {
		if (cur != obj[i]) return false;
		if (cur == '.' || obj[i] == '.') return false;
	}
	return true;
}
void printArr(int m, int n, vector<string> b) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%2c", b[i][j]);
		}
		printf("\n");
	}
}
bool check(int m, int n, vector<string>& b) {
	bool visit[30][30];
	memset(visit, 0, sizeof(visit));

	bool flag = false;
	for (int y = 0; y < m - 1; y++) {
		for (int x = 0; x < n - 1; x++) {
			string obj = "";
			obj += b[y][x] ;
			obj += b[y][x + 1];
			obj += b[y + 1][x];
			obj += b[y + 1][x + 1];
			if (isSame(obj)) {
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 2; j++) {
						visit[y + i][x + j] = true;
					}
				}
			}
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (visit[i][j]) {
				b[i][j] = '.';
				ret++;
				flag = true;
			}
		}
	}
	return flag;
}

void move(int m, int n, vector<string>& b) {
	int idx = -2;
	for (int x = 0; x < n; x++) {
		idx = -2;
		for (int y = m - 1; y >= 0; y--) {
		
			if (b[y][x] == '.') {
				if (idx < 0) idx = y;
			}
			else {
				if (idx >= 0) {
					b[idx][x] = b[y][x];
					b[y][x] = '.';
					idx--;
				}
			}
		}
	}
	printf("\n");
	printArr(m, n, b);
}
int solution(int m, int n, vector<string> board) {
	int answer = 0;
	
	while (check(m,n,board) != 0) {
		move(m, n, board);
	}
	answer = ret;
	
	cout << answer << endl;
	return answer;
}

int main() {

	int m, n;
	m = 4;
	n = 5;
	vector<string> b = { "CCBDE", "AAADE","AAABF", "CCBBF" };
	printArr(m, n, b);
	solution(m, n, b);
}