#include <string>
#include <vector>
#include<algorithm>

using namespace std;

bool cmp(int a, int b) { return a > b; }

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	sort(dist.begin(), dist.end(), cmp);
	int F = dist.size();
	bool finish = false;
	for (int i = 0; i < F && !finish ; i++) {
		
		vector<int> select;
		vector<int> W = weak;
		int Wsz = weak.size();

		for (int k = 0; k <= i; k++) {
			select.push_back(dist[k]);
		}

		int sz = select.size();

		for (int j = 0; j < Wsz; j++) {
			
			do {

				int si = 0;
				int wi = 0;

				int strt = W[wi];
				int end = W[wi] + select[si];

				while (1) {
				
					if (W[wi] >= strt && W[wi] <= end) {
						wi++;
						if (wi == Wsz) {
							finish = true;
							break;
						}
					}
					else {
						si++;
						if (si == sz) {
							finish = false;
							break;
						}
						strt = W[wi];
						end = strt + select[si];

					}
				
				}
				if (finish) break;
			} while (next_permutation(select.begin(), select.end()));

			if (!finish) {
				W[0] += n;
				sort(W.begin(), W.end());
			}
			else break;
		}

		if (finish) answer = sz;
	}


	if (!finish) answer = -1;
	
	return answer;
}