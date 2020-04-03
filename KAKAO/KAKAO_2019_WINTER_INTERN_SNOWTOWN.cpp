#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
map<long long, long long> m;

long long search(long long u) {
	if (!m[u]) return u;
	return m[u] = search(m[u]);
}
vector<long long> solution(long long k, vector<long long> room_number) {
	vector<long long> answer;



	for (int i = 0; i < room_number.size(); i++) {
		long long num = room_number[i];

		if (!m[num]) answer.push_back(num), m[num] = search(num + 1);
		else {
			long long tmp = search(num);
			answer.push_back(tmp);
			m[tmp] = search(tmp + 1);
		}
	}
	return answer;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	long long k = 10;
	vector<long long> r = {1, 3, 4, 1, 3, 1};
	
	

	solution(k,r);
}