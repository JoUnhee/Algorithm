
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
int canGo(int left, int right, int m, vector<int>& stones) {

	if (left == right) return (stones[left] - m) < 0;

	int mid = (left + right) / 2;

	int ret = max(canGo(left, mid, m, stones), canGo(mid + 1, right, m, stones));

	int lo = mid;
	int hi = mid + 1;
	int cnt = 0;
	while (hi <= right && (stones[hi] - m) < 0) hi++, cnt++;
	while (lo >= left && (stones[lo] - m) < 0) lo--, cnt++;
	ret = max(ret, cnt);
	return ret;
}
int solution(vector<int> stones, int k) {
	int answer = 0;
	int sz = stones.size();
	int left = 0, right = 2e8;

	while (left <= right) {
		int m = (left + right) / 2;

		int obj = canGo(0, sz - 1, m, stones);

		if (obj < k) {
			answer = m;
			left = m + 1;
		}
		else right = m - 1;
	}


	return answer;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	
	srand((unsigned int)time(NULL));
	int k = (rand() % 200000) + 1;
	int howmany = (rand() % 200000);
	vector<int> tr ;
	for (int i = 0; i < howmany; i++) {
		tr.push_back((rand() % 7) + 1);
	}

	solution(tr,k);


}