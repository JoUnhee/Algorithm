#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
typedef struct info {
	int st;
	int end;

	info(int _st, int _end) : st(_st), end(_end) {}
};
vector<string> split(string input, char cur) {
	vector<string> ret;
	stringstream ss(input);

	string tmp;

	while (getline(ss, tmp, cur)) {
		ret.push_back(tmp);
	}
	return ret;
}

int solution(vector<string> lines) {
	int answer = 0;

	vector<info> log;
	int sz = lines.size();
	for (int i = 0; i < sz; i++) {
		int st = 0;
		int end = 0;
		vector<string> tmp = split(lines[i], ' ');
		int pt = stof(tmp[2]) * 1000 - 1;

		vector<string> time = split(tmp[1], ':');

		end = stoi(time[0]) * 3600000 + stoi(time[1]) * 60000 + stof(time[2]) * 1000;

		log.push_back(info(end - pt, end));
	}

	for (int i = 0; i < sz; i++) {
		int cur = log[i].st - 999;
		int cnt = 0;
		for (int j = 0; j < sz; j++) {

			if (cur <= log[j].st && log[j].st <= log[i].st) cnt++;
			else if (cur >= log[j].st && cur <= log[j].end) cnt++;
		}
		answer = max(answer, cnt);
	}


	return answer;
}