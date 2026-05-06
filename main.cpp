//
// Created by khanj on 26. 4. 24..
//
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>
#include <random>
using namespace std;

vector<int> permutations[5] = { {4,10,10,3,9,4,10,10,3,6,3,5,4},{4,9,3,9,6,6,9,4,10,3,10,6,6},{4,4,9,4,4,10,10,6,6,9,4,4},{3,10,3,8,8,4,9,4},{4,4,6,6,4,4} };
vector<int> vc[100][300];
int fitness[100][300];
int u[2][2]; // 0
int d[2][2]; // 1
int l[2][2]; // 2
int r[2][2]; // 3
int f[2][2]; // 4
int b[2][2]; // 5



void left(int t) {

	if (t == -1) {
		int x1 = f[0][0];
		int x2 = f[1][0];
		f[0][0] = d[0][0];
		f[1][0] = d[1][0];
		d[0][0] = b[1][1];
		d[1][0] = b[0][1];
		b[1][1] = u[0][0];
		b[0][1] = u[1][0];
		u[0][0] = x1;
		u[1][0] = x2;

		int temp = l[0][0];
		l[0][0] = l[0][1];
		l[0][1] = l[1][1];
		l[1][1] = l[1][0];
		l[1][0] = temp;
	}
	if (t == 1) {
		int x1 = u[0][0];
		int x2 = u[1][0];
		u[0][0] = b[1][1];
		u[1][0] = b[0][1];
		b[1][1] = d[0][0];
		b[0][1] = d[1][0];
		d[0][0] = f[0][0];
		d[1][0] = f[1][0];
		f[0][0] = x1;
		f[1][0] = x2;
		int temp = l[0][0];
		l[0][0] = l[1][0];
		l[1][0] = l[1][1];
		l[1][1] = l[0][1];
		l[0][1] = temp;
	}
}
void right(int t) {
	if (t == -1) {
		int x1 = f[0][1];
		int x2 = f[1][1];
		f[0][1] = u[0][1];
		f[1][1] = u[1][1];
		u[0][1] = b[1][0];
		u[1][1] = b[0][0];
		b[1][0] = d[0][1];
		b[0][0] = d[1][1];
		d[0][1] = x1;
		d[1][1] = x2;
		int temp = r[0][0];
		r[0][0] = r[0][1];
		r[0][1] = r[1][1];
		r[1][1] = r[1][0];
		r[1][0] = temp;
	}
	if (t == 1) {
		int x1 = d[0][1];
		int x2 = d[1][1];
		d[0][1] = b[1][0];
		d[1][1] = b[0][0];
		b[1][0] = u[0][1];
		b[0][0] = u[1][1];
		u[0][1] = f[0][1];
		u[1][1] = f[1][1];
		f[0][1] = x1;
		f[1][1] = x2;
		int temp = r[0][0];
		r[0][0] = r[1][0];
		r[1][0] = r[1][1];
		r[1][1] = r[0][1];
		r[0][1] = temp;
	}
}
void front(int t) {
	if (t == -1) {
		int x1 = u[1][0];
		int x2 = u[1][1];
		u[1][0] = r[0][0];
		u[1][1] = r[1][0];
		r[0][0] = d[0][1];
		r[1][0] = d[0][0];
		d[0][1] = l[1][1];
		d[0][0] = l[0][1];
		l[1][1] = x1;
		l[0][1] = x2;
		int temp = f[0][0];
		f[0][0] = f[0][1];
		f[0][1] = f[1][1];
		f[1][1] = f[1][0];
		f[1][0] = temp;
	}
	if (t == 1) {
		int x1 = l[1][1];
		int x2 = l[0][1];
		l[1][1] = d[0][1];
		l[0][1] = d[0][0];
		d[0][1] = r[0][0];
		d[0][0] = r[1][0];
		r[0][0] = u[1][0];
		r[1][0] = u[1][1];
		u[1][0] = x1;
		u[1][1] = x2;
		int temp = f[0][0];
		f[0][0] = f[1][0];
		f[1][0] = f[1][1];
		f[1][1] = f[0][1];
		f[0][1] = temp;
	}
}
void back(int t) {
	if (t == -1) {
		int x1 = u[0][0];
		int x2 = u[0][1];
		u[0][0] = l[1][0];
		u[0][1] = l[0][0];
		l[1][0] = d[1][1];
		l[0][0] = d[1][0];
		d[1][1] = r[0][1];
		d[1][0] = r[1][1];
		r[0][1] = x1;
		r[1][1] = x2;
		int temp = b[0][0];
		b[0][0] = b[0][1];
		b[0][1] = b[1][1];
		b[1][1] = b[1][0];
		b[1][0] = temp;
	}
	if (t == 1) {
		int x1 = r[0][1];
		int x2 = r[1][1];
		r[0][1] = d[1][1];
		r[1][1] = d[1][0];
		d[1][1] = l[1][0];
		d[1][0] = l[0][0];
		l[1][0] = u[0][0];
		l[0][0] = u[0][1];
		u[0][0] = x1;
		u[0][1] = x2;
		int temp = b[0][0];
		b[0][0] = b[1][0];
		b[1][0] = b[1][1];
		b[1][1] = b[0][1];
		b[0][1] = temp;
	}
}
void up(int t) {
	if (t == -1) {
		int x1 = f[0][0];
		int x2 = f[0][1];
		f[0][0] = l[0][0];
		f[0][1] = l[0][1];
		l[0][0] = b[0][0];
		l[0][1] = b[0][1];
		b[0][0] = r[0][0];
		b[0][1] = r[0][1];
		r[0][0] = x1;
		r[0][1] = x2;
		int temp = u[0][0];
		u[0][0] = u[0][1];
		u[0][1] = u[1][1];
		u[1][1] = u[1][0];
		u[1][0] = temp;
	}
	if (t == 1) {
		int x1 = r[0][0];
		int x2 = r[0][1];
		r[0][0] = b[0][0];
		r[0][1] = b[0][1];
		b[0][0] = l[0][0];
		b[0][1] = l[0][1];
		l[0][0] = f[0][0];
		l[0][1] = f[0][1];
		f[0][0] = x1;
		f[0][1] = x2;
		int temp = u[0][0];
		u[0][0] = u[1][0];
		u[1][0] = u[1][1];
		u[1][1] = u[0][1];
		u[0][1] = temp;
	}
}
void down(int t) {
	if (t == -1) {
		int x1 = f[1][0];
		int x2 = f[1][1];
		f[1][0] = r[1][0];
		f[1][1] = r[1][1];
		r[1][0] = b[1][0];
		r[1][1] = b[1][1];
		b[1][0] = l[1][0];
		b[1][1] = l[1][1];
		l[1][0] = x1;
		l[1][1] = x2;
		int temp = d[0][0];
		d[0][0] = d[0][1];
		d[0][1] = d[1][1];
		d[1][1] = d[1][0];
		d[1][0] = temp;
	}
	if (t == 1) {
		int x1 = f[1][0];
		int x2 = f[1][1];
		f[1][0] = l[1][0];
		f[1][1] = l[1][1];
		l[1][0] = b[1][0];
		l[1][1] = b[1][1];
		b[1][0] = r[1][0];
		b[1][1] = r[1][1];
		r[1][0] = x1;
		r[1][1] = x2;
		int temp = d[0][0];
		d[0][0] = d[1][0];
		d[1][0] = d[1][1];
		d[1][1] = d[0][1];
		d[0][1] = temp;
	}
}
void xO(int t) {
	if (t == 1) {
		left(-1);
		right(1);
	}
	else {
		left(1);
		right(-1);
	}
}
void yO(int t) {
	if (t == 1) {
		up(1);
		down(-1);

	}
	else {
		up(-1);
		down(1);
	}
}
void zO(int t) {
	if (t == 1) {
		front(1);
		back(-1);
	}
	else {
		front(-1);
		back(1);
	}
}

void int_to_move(int x) {
	if (x == 1) left(-1);
	if (x == 2) left(1);
	if (x == 3) right(-1);
	if (x == 4) right(1);
	if (x == 5) front(-1);
	if (x == 6) front(1);
	if (x == 7) back(-1);
	if (x == 8) back(1);
	if (x == 9) up(-1);
	if (x == 10) up(1);
	if (x == 11) down(-1);
	if (x == 12) down(1);
	if (x == 13) xO(-1);
	if (x == 14) xO(1);
	if (x == 15) yO(-1);
	if (x == 16) yO(1);
	if (x == 17) zO(-1);
	if (x == 18) zO(1);
}
int isSet() {
	int ans = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (u[i][j] != 0) ans++;
			if (d[i][j] != 1) ans++;
			if (f[i][j] != 2) ans++;
			if (b[i][j] != 3) ans++;
			if (l[i][j] != 4) ans++;
			if (r[i][j] != 5) ans++;
		}
	}
	return ans;

}


int fit() {
	int min = 9999;
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	xO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	xO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	xO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	xO(1);
	zO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	zO(1);
	zO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	min = std::min(min, isSet());
	yO(1);
	zO(1);
	return min;

}


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 4);
std::uniform_int_distribution<int> dis1(1, 12);
std::uniform_int_distribution<int> dis2(0, 49);
std::uniform_int_distribution<int> dis3(13, 18);
std::uniform_int_distribution<int> dis4(0, 3);
int randInt(int a, int b) {
	if (b == 3) return dis4(gen);
	if (b == 4) return (dis(gen));
	if (b == 12) return dis1(gen);
	if (b == 49) return dis2(gen);
	if (b == 18) return dis3(gen);
}

vector<int> selectMost(int g) {
	const int N = sizeof(fitness[g]) / sizeof(int);
	vector<pair<int, int>> backup;
	vector<int> ans;
	for (int i = 0; i < 50; i++) {
		int index = distance(fitness[g], min_element(fitness[g], fitness[g] + N));

		ans.push_back(index);
		backup.push_back({ index,*min_element(fitness[g],fitness[g] + N) });
		fitness[g][index] = 900;
	}
	for (int i = 0; i < backup.size(); i++) {
		fitness[g][backup[i].first] = backup[i].second;
	}

	return ans;
}
void initialize() {
	for (int j = 0; j < 2; j++) {
		for (int k = 0; k < 2; k++) {
			u[j][k] = 0;
			d[j][k] = 1;
			l[j][k] = 3;
			r[j][k] = 2;
			f[j][k] = 4;
			b[j][k] = 5;
		}
	}
	int_to_move(6);
	int_to_move(6);
	int_to_move(9);
	int_to_move(4);
	int_to_move(6);
	int_to_move(9);
	int_to_move(5);
	int_to_move(9);
	int_to_move(4);
	int_to_move(10);
	int_to_move(10);

}


int main() {

	try {
		vector<int> ranking;
		for (int i = 0; i < 100; i++) {


			for (int j = 0; j < 300; j++) {
				initialize();

				if (i == 0) {
					int x = randInt(1, 12);
					vc[i][j].push_back(x);
					int_to_move(x);
					x = randInt(1, 12);
					vc[i][j].push_back(x);
					int_to_move(x);
					fitness[i][j] = fit();

					continue;
				}
				if (i == 0) throw string("Underflow!");

				if (j < 50 && i != 0) {
					int rand = randInt(0, 49);
					if (ranking[rand] >= 300) throw string("under");
					vc[i][j].resize(vc[i - 1][ranking[rand]].size());
					std::copy(vc[i - 1][ranking[rand]].begin(), vc[i - 1][ranking[rand]].end(), vc[i][j].begin());

					for (int z = 0; z < vc[i][j].size(); z++) {
						int_to_move(vc[i][j][z]);
					}
					fitness[i][j] = fit();
					continue;
				}

				for (int z = 0; z < vc[i][j].size(); z++) {
					int_to_move(vc[i][j][z]);
				}
				int evolution = randInt(0, 3);
				int rand = randInt(0, 49);

				if (ranking[rand] >= 300) throw string("under");
				vc[i][j].resize(vc[i - 1][ranking[rand]].size());
				std::copy(vc[i - 1][ranking[rand]].begin(), vc[i - 1][ranking[rand]].end(), vc[i][j].begin());
				if (evolution == 0) {
					int index = randInt(0, 4);
					for (int k = 0; k < permutations[index].size(); k++) {
						int_to_move(permutations[index][k]);
						vc[i][j].push_back(permutations[index][k]);
					}

				}
				if (evolution == 1) {
					int index = randInt(0, 4);
					for (int k = 0; k < permutations[index].size(); k++) {
						int_to_move(permutations[index][k]);
						vc[i][j].push_back(permutations[index][k]);
					}
					index = randInt(0, 4);
					for (int k = 0; k < permutations[index].size(); k++) {
						int_to_move(permutations[index][k]);
						vc[i][j].push_back(permutations[index][k]);
					}
				}
				if (evolution == 2) {
					int index2 = randInt(13, 18);
					int_to_move(index2);
					vc[i][j].push_back(index2);
					int index = randInt(0, 4);
					for (int k = 0; k < permutations[index].size(); k++) {
						int_to_move(permutations[index][k]);
						vc[i][j].push_back(permutations[index][k]);
					}
				}
				if (evolution == 3) {
					int index = randInt(13, 18);
					vc[i][j].push_back(index);
					int_to_move(index);
					index = randInt(13, 18);
					vc[i][j].push_back(index);
					int_to_move(randInt(13, 18));
					index = randInt(0, 4);

					for (int k = 0; k < permutations[index].size(); k++) {
						int_to_move(permutations[index][k]);
						vc[i][j].push_back(permutations[index][k]);
					}
				}
				fitness[i][j] = fit();


			}

			vector<int> temp = selectMost(i);
			ranking.clear();
			ranking.resize(temp.size());
			std::copy(temp.begin(), temp.end(), ranking.begin());





			if (ranking.size() == 0) throw string("d");
			if (fitness[i][ranking[0]] == 0) {
				cout << "Solution found" << endl;
				cout << "제" << i << "세대" << ranking[0] << "번째 개체 / 회전수 :" << vc[i][ranking[0]].size() << endl;
				cout << "Solution" << endl;
				for (int j = 0; j < vc[i][ranking[0]].size(); j++) {
					cout << vc[i][ranking[0]][j] << " ";
				}
				cout << endl;
				return 0;
			}
			cout << "제" << i << "세대" << ranking[0] << "번째 개체 / 회전수 :" << vc[i][ranking[0]].size() << endl;
			cout << "Solution" << endl;
			for (int j = 0; j < vc[i][ranking[0]].size(); j++) {
				cout << vc[i][ranking[0]][j] << " ";
			}
			cout << "점수 " << fitness[i][ranking[0]] << endl;
			cout << endl;

		}
	}
	catch (...) {
		cout << "error";
	}



}
