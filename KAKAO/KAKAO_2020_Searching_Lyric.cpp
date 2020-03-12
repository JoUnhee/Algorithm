#include<cstring>
#include<vector>
#include<map>
#include<string>
using namespace std;
struct Trie {
	bool terminal;
	Trie* next[26];
	int cnt;
	Trie() : terminal(false), cnt(1) {
		memset(next, 0, sizeof(next));
	}
	~Trie() {
		for (int i = 0; i < 26; i++) if (next[i]) delete next[i];
	}

	void insert(const char* key) {
		if (*key == '\0') terminal = true;
		else {
			int cur = *key - 'a';

			if (next[cur] == NULL) next[cur] = new Trie();
			else next[cur]->cnt++;

			next[cur]->insert(key + 1);
		}
	}
	int find(const char* key) {
		int cur = *key - 'a';
		if (*key == '?') {
			int tmp = 0;
			for (int k = 0; k < 26; k++) {
				if (next[k] != NULL) tmp += next[k]->cnt;
			}
			return tmp;
		}
		if (next[cur] == NULL) return 0;
		if (*(key + 1) == '?') return next[cur]->cnt;
		return next[cur]->find(key + 1);

	}

};
Trie* root[10001];
Trie* reroot[10001];

vector<int> solution(vector<string> words, vector<string> queries) {

	int wSize = words.size();
	int qSize = queries.size();

	vector<int> answer(qSize, 0);

	for (auto& w : words) {
		int sz = w.size();

		const char* c = w.c_str();

		if (root[sz] == NULL) root[sz] = new Trie();
		root[sz]->insert(c);

		string reversed = w;
		reverse(reversed.begin(), reversed.end());

		const char* k = reversed.c_str();
		if (reroot[sz] == NULL) reroot[sz] = new Trie();
		reroot[sz]->insert(k);

	}

	int idx = 0;

	for (auto& q : queries) {
		int sz = q.size();

		if (q[sz - 1] == '?') {
			const char* c = q.c_str();

			if (root[sz] == NULL) { idx++; continue; }
			else answer[idx] = root[sz]->find(c);
		}
		else {
			string re = q;
			reverse(re.begin(), re.end());

			const char* k = re.c_str();

			if (reroot[sz] == NULL) { idx++; continue; }
			else answer[idx] = reroot[sz]->find(k);
		}
		idx++;
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