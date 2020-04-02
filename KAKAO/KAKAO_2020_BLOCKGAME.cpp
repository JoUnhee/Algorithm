#include <string>
#include <vector>
#include<iostream>
using namespace std;

bool check(vector<vector<int>> b, vector<pair<int, int>> num) {
	
	int obj = b[num[0].first][num[0].second];

	for (int i = 1; i < num.size(); i++) {
		if (obj != b[num[i].first][num[i].second]) return false;
	}
	return true;
}
bool canDel(vector<vector<int>> b, vector<pair<int, int>> z) {

	for (int i = 0; i < z.size(); i++) {
		int y = z[i].first;
		int x = z[i].second;

		while (y >= 0) {
			if (b[y][x] != 0) return false;
			y--;
		}
	}
	return true;
}
int solution(vector<vector<int>> board) {
	int answer = 0;
	int n = board.size();
	while(1){
		bool flag = false;
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
		
				vector<pair<int,int>> zero;
				vector<pair<int,int>> num;


				if (y + 1 < n && x + 2 < n) {
					for (int curY = 0; curY < 2; curY++) {
						for (int curX = 0; curX < 3; curX++) {
							int nx = x + curX;
							int ny = y + curY;

							if (board[ny][nx] == 0) zero.push_back({ ny,nx });
							else num.push_back({ ny,nx });
						}
					}

					if (zero.size() == 2) {
						if (check(board, num) && canDel(board,zero)) {
							answer++;
							flag = true;
							for (int i = 0; i < num.size(); i++) {
								int ty = num[i].first;
								int tx = num[i].second;

								board[ty][tx] = 0;
							}
						}
					}
				}

				zero.clear();
				num.clear();
				if(y+2 < n && x + 1 < n){
					for (int curY = 0; curY < 3; curY++) {
						for (int curX = 0; curX < 2; curX++) {
							int nx = x + curX;
							int ny = y + curY;

							if (board[ny][nx] == 0) zero.push_back({ ny,nx });
							else num.push_back({ ny,nx });
						}
					}

					if (zero.size() == 2) {
						if (check(board, num) && canDel(board, zero)) {
							answer++;
							flag = true;
							for (int i = 0; i < num.size(); i++) {
								int ty = num[i].first;
								int tx = num[i].second;

								board[ty][tx] = 0;
							}
						}
					}


				}


			}
		}
		if (!flag) break;
	}

	return answer;
}

int main() {

	vector<vector<int>> b =
		{{0, 0, 0, 0, 0, 0, 0, 6, 0, 0}
		, {0, 0, 0, 0, 5, 0, 6, 6, 6, 0}
		, {0, 0, 0, 4, 5, 5, 5, 0, 0, 0}
		, {0, 0, 3, 4, 4, 4, 8, 0, 0, 0}
		, {1, 2, 3, 3, 3, 8, 8, 0, 0, 0}
		, {1, 2, 2, 2, 0, 7, 8, 0, 0, 0}
		, {1, 1, 0, 0, 7, 7, 7, 0, 0, 0}
		, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}} ;
	cout << solution(b) << endl;
}