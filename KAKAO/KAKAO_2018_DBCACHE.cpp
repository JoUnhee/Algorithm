#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int offset = 32;
string MakeLower(string obj) {
	string ret = "";

	for (int i = 0; i < obj.size(); i++) {
		char cur = obj[i];

		if (cur >= 'A' && cur <= 'Z') {
			cur = cur + offset;
		}

		ret += cur;
	}

	return ret;
}
bool cmp(pair<string, int> A , pair<string, int> B) {
	return A.second < B.second;
}
int Find(vector<pair<string, int>>& cache, string city,int t,int mxCsz) {


	int sz = cache.size();
	int ret = 0;
	for (int i = 0; i < sz; i++) {
		string& name = cache[i].first;
		int& time = cache[i].second;
		// hit
		if (name == city) {
			time = t;
			sort(cache.begin(), cache.end(),cmp);
			return 1;
		}
	}
	//miss
	if (sz == mxCsz) {
		cache[0].first = city;
		cache[0].second = t;
		sort(cache.begin(), cache.end(), cmp);
	}
	else {
		cache.push_back({ city,t });
	}
	return 5;
}
int solution(int cacheSize, vector<string> cities) {
	int answer = 0;
	vector<pair<string, int>> cache;

	int sz = cities.size();
	
	if (cacheSize > 0) {
		for (int i = 0; i < sz; i++) {
			string name = MakeLower(cities[i]);

			answer += Find(cache, name, i, cacheSize);
		}
	}
	else answer = sz * 5;

	return answer;
}

int main() {

	int sz = 3;

	vector<string> cities = { "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul" };

	solution(sz, cities);
}