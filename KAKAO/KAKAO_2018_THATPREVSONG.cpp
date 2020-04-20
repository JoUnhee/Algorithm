#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<string> split(string music, char dia) {
	vector<string> ret;

	int idx = music.find(dia, 0);
	int st = 0;
	while (idx != string::npos) {
		string tmp = music.substr(st, (idx - st));
		ret.push_back(tmp);
		st = idx + 1;
		idx = music.find(dia, idx + 1);
	}
	ret.push_back(music.substr(st, idx - st));
	return ret;
}
vector<string> splitMusic(string obj) {
	vector<string> ret;

	string tmp = "";
	int sz = obj.size();
	for (int i = 0; i < sz ; i++) {

		if (i + 1 < sz && ((obj[i + 1] >= 'A' && obj[i + 1] <= 'G'))) {
			ret.push_back(tmp + obj[i]);
			tmp.clear();

		}
		else if (i == sz - 1) {
			ret.push_back(tmp + obj[i]);
			tmp.clear();
		}
		else tmp += obj[i];
	}


	return ret;
}
bool check(vector<string> neo, vector<string> obj) {

	if (neo.size() > obj.size()) return false;

	

	for (int i = 0; i < obj.size(); i++) {
		if (neo[0] != obj[i]) continue;

		bool flag = true;
		int cursor = i;

		for (int j = 0; j < neo.size(); j++,cursor ++) {
			
			if (cursor == obj.size() || neo[j] != obj[cursor]) {
				flag = false;
				continue;
			}

		}
		if (flag) return true;
	}
	return false;
}
string solution(string m, vector<string> musicinfos) {
	string answer = "";

	int prevL = -1;
	int prevT = 987654321;

	vector<string> neo = splitMusic(m);
	for (int i = 0; i < musicinfos.size(); i++) {

		vector<string> info = split(musicinfos[i], ',');

		int length = (stoi(info[1].substr(0, 2)) * 60 + stoi(info[1].substr(3, 2))) - (stoi(info[0].substr(0, 2)) * 60 + stoi(info[0].substr(3, 2)));
		int stime = stoi(info[0].substr(0, 2)) * 60 + stoi(info[0].substr(3, 2));
		
		vector<string> note = splitMusic(info[3]);
		vector<string> Rnote;


		if (note.size() < length) {
			int idx = 0;
			for (int t = 0; t < length; t++, idx++) {
				if (idx == note.size()) idx = 0;
				Rnote.push_back(note[idx]);
			}
		}
		else {
			for (int t = 0; t < length; t++) {
				Rnote.push_back(note[t]);
			}
		}
		

		if (check(neo, Rnote)) {
			if (prevL < length) {
				answer = info[2];
				prevL = length;
			}
		}

	}
	if (answer == "") return "(None)";
	return answer;
}
int main() {
	
	string m = "CC";
	vector<string> music =	{"04:00,04:02,ZERO,B#CC", "15:00,15:02,FIRST,B#CC", "04:04,04:06,SECOND,B#CC", "04:08,04:10,THIRD,B#CC"};
	cout << solution(m, music) << endl;

}