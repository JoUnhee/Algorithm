#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
bool cmp(pair<int, int> A, pair<int, int> B) {
	return A.second < B.second;
}
int solution(vector<int> food_times, long long k) {
	int sz = food_times.size();
	int answer = -1;
	vector<pair<int, int>> q(sz);

	for (int i = 0; i < sz; i++) {
		q[i] = { food_times[i],i + 1 };
	}

	sort(q.begin(), q.end());

	int idx = 0;
	int before = 0;

	while (idx < sz) {
		int time = q[idx].first;
		int strt = idx;

		while (idx + 1 < sz && q[idx + 1].first == time) idx++;

		int cnt = sz - strt;

		if (k < (long long)(time - before) * (long long)cnt) {
			sort(q.begin() + strt, q.end(), cmp);
			answer = q[strt + (k % cnt)].second;
			break;
		}
		k -= (time - before) * cnt;
		before = time;
		idx++;
	}
	return answer;
}
