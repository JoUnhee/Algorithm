#include <string>
#include <vector>
#include<iostream>

using namespace std;


int crain(vector<vector<int>>& board, int idx) {
	int n = board.size();
	int y = 0;
	int ret = 0;
	while (y < n && board[y][idx] == 0) y++;

	if (y >= n) return -1;
	ret = board[y][idx];
	board[y][idx] = 0;
	return ret;
}
int push(vector<int>& stack, int obj) {
	int ret = 0;
	if (stack.empty()) stack.push_back(obj);
	else {
		int top = stack[stack.size() - 1];

		if (top == obj) {
			stack.pop_back();
			ret = 2;
		}
		else stack.push_back(obj);
	}
	return ret;
}
int solution(vector<vector<int>> board, vector<int> moves) {
	int answer = 0;
	vector<int> stack;

	for (int i = 0; i < moves.size(); i++) {
		int obj = crain(board, moves[i] - 1);
		if (obj > 0) {
			answer += push(stack, obj);
		}
	}
	return answer;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	vector<vector<int>> b = { {0, 0, 0, 0, 0}, {0, 0, 1, 0, 3}, {0, 2, 5, 0, 1}, {4, 2, 4, 4, 2}, {3, 5, 1, 3, 1} };
	vector<int> m = { 1, 5, 3, 5, 1, 2, 1, 4 };


	cout << solution(b, m) << endl;
}