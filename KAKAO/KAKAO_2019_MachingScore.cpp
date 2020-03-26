#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;

typedef struct info {
	string url;
	double matching;
	int basic;
	int externel;
	double link;
	vector<string> ref;
};


string meta = "<meta";
string https = "\"https://";
string aref = "<a href=\"";
string END = "\"";

bool cmp(pair<double,int> A, pair<double,int> B) {

	if (A.first == B.first) return A.second < B.second;
	return A.first > B.first;
}

vector<string> extractRef(string obj) {
	vector<string> ret;
	int find = 0;
	while (true) {
	
		find = obj.find(aref, find);
		if (find == string::npos) break;

		string temp = obj.substr(find + aref.length());
		temp = temp.substr(0, temp.find("\">"));

		find += aref.length();

		ret.push_back(temp);
	}

	return ret;
}
string extractURL(string obj) {
	string ans = "";
	
	int find = 0;
	while (true) {
		find = obj.find(meta, find);

		if (find == string::npos) break;

		string temp = obj.substr(find + meta.length());

		temp = temp.substr(0, temp.find(">"));

		find += meta.length();

		if (temp.find(https) != string::npos) {
			size_t found = temp.find(END, temp.find(https) + https.length());
			temp = temp.substr(temp.find(https) + 1, found - 1 - temp.find(https));

			ans = temp;
			return ans;
		}
	}

	return ans;
}
string makelower(string obj) {
	string ret = "";
	for (int i = 0; i < obj.size(); i++) {
		if (obj[i] >= 'A' && obj[i] <= 'Z') {
			ret += (obj[i] + 32);
		}
		else ret += obj[i];
	}
	return ret;
}
int basicScore(string word, string page) {

	int ret = 0;
	string key = makelower(word);
	string obj = makelower(page);

	int find = obj.find(key,0);
	while (find != string::npos) {
		ret++;

		if((find != -1 && obj[find-1] >= 'a' && obj[find-1] <= 'z') ||(find + key.length() < obj.size() -1 && obj[find + key.length()] >= 'a' && obj[find + key.length()] <= 'z')) ret --;

		find = obj.find(key, find + key.length());
	}
	return ret;
}
int solution(string word, vector<string> pages) {
	int answer = 0;
	vector<info> URL;
	for (int i = 0; i < pages.size(); i++) {

		string url = extractURL(pages[i]);
		vector<string> ref = extractRef(pages[i]);
		int basic = basicScore(word,pages[i]);

		info temp;

		temp.basic = basic;
		temp.externel = ref.size();
		temp.link = 0.0;
		temp.matching = 0.0;
		temp.ref = ref;
		temp.url = url;

		URL.push_back(temp);
	}

	for (int i = 0; i < URL.size(); i++) {
		info& cur = URL[i];

		if (cur.basic == 0) continue;
		if (cur.externel == 0) continue;

		for (int j = 0; j < cur.externel; j++) {
			
			for (int k = 0; k < URL.size(); k++) {
				if (i == k) continue;

				info& obj = URL[k];

				if (obj.url == cur.ref[j]) {
					obj.link += (double)cur.basic / cur.externel;
				}
			}

		}
		
	}

	vector<pair<double, int>> q;
	for (int i = 0; i < URL.size(); i++) {
		info& cur = URL[i];

		cur.matching = cur.basic + cur.link;
		q.push_back({ cur.matching,i });
	}
	
	sort(q.begin(), q.end(), cmp);
	
	answer = q[0].second;

	return answer;
}



int main(int argc, char** argv) {
	string word = "Muzi";
	vector<string> q;
	q.push_back("<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>");
	q.push_back("<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>");

	solution(word, q);
}
