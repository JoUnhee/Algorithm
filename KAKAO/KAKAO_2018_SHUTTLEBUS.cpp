#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
typedef struct bus {
	int time;
	vector<int> passenger;

	bus(int _time, vector<int> _passenger) : time(_time), passenger(_passenger) {}
};
string convert(int time) {
	string hour = to_string(time / 60);
	string min = to_string(time % 60);

	if (hour.size() == 1) hour = "0" + hour;
	if (min.size() == 1) min = "0" + min;

	return hour + ":" + min;
}
string solution(int n, int t, int m, vector<string> timetable) {
	string answer = "";
	
	vector<bus> buses;
	int curtime = 540;
	for (int i = 0; i < n; i++) {
		int time = curtime;
		vector<int> p;
		buses.push_back(bus(time, p));
		curtime += t;
	}

	int idx = 0;
	vector<int> p;
	for (int i = 0; i < timetable.size(); i++) {
		int time = stoi(timetable[i].substr(0, 2)) * 60 + stoi(timetable[i].substr(3, 2));
		p.push_back(time);
	}

	sort(p.begin(), p.end());

	for (int i = 0; i < p.size() && idx < buses.size(); i++) {
		int time = p[i];
		if (buses[idx].time >= time) {
			buses[idx].passenger.push_back(time);

			if (buses[idx].passenger.size() == m) idx++;
		}
		else idx++,i--;
	}
	idx = buses.size() - 1;


	int ret = 0;
	if (buses[idx].passenger.size() == m) {
		ret = buses[idx].passenger[m - 1] - 1;
	}
	else if (buses[idx].passenger.size() < m) ret = buses[idx].time;

	answer = convert(ret);
	return answer;
}
int main() {
	
	int n = 10;
	int t = 60;
	int m = 45;
	vector<string> timet= {"23:59","23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59"};

	cout << solution(n, t, m, timet) << endl;
}