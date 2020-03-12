#include<cstring>
#include<vector>
#include<map>
#include<string>

using namespace std;

bool check(string word, string query) {
	if (word.size() != query.size()) return false;
	int w, q;
	w = q = 0;

	while (q < word.size() && w < word.size()) {
		if (query[q] != word[w]) {
			if (query[q] != '?') return false;
		}
		q++;
		w++;
	}
	return true;
}
vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer;
	map<string, int> visit;

	for (int q = 0; q < queries.size(); q++) {
		string query = queries[q];

		if (visit[query] != 0) {
			answer.push_back(visit[query]);
			continue;
		}
		for (int w = 0; w < words.size(); w++) {
			if (check(words[w], queries[q])) visit[query]++;
		}

		answer.push_back(visit[queries[q]]);
	}

	return answer;
}

int main() {
	vector<string> words;
	vector<string> queries;
	words.push_back("frodo");
	words.push_back("front");
	words.push_back("frost"); 
	words.push_back("frozen"); 
	words.push_back("frame");
	words.push_back("kakao");

	queries.push_back("fro??");
	queries.push_back("????o");
	queries.push_back("fr???"); 
	queries.push_back("fro???");
	queries.push_back("pro?");

	vector<int> ans = solution(words, queries);

	for (int i = 0; i < ans.size(); i++) {
		printf("%2d", ans[i]);
	}
	printf("\n");

	return 0;
}