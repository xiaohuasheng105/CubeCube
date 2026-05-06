#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;


const int GENERATIONS = 100;
const int POP_SIZE = 300;
const int ELITE_SIZE = 50;
const int RESTARTS = 20;


// 1 L'  2 L   3 R'  4 R   5 F'  6 F
// 7 B'  8 B   9 U' 10 U  11 D' 12 D
// 13 x' 14 x  15 y' 16 y 17 z' 18 z

vector<int> formulas[5] = {
    {4,10,10,3,9,4,10,10,3,6,3,5,4},
    {4,9,3,9,6,6,9,4,10,3,10,6,6},
    {4,4,9,4,4,10,10,6,6,9,4,4},
    {3,10,3,8,8,4,9,4},
    {4,4,6,6,4,4}
};

vector<int> vc[GENERATIONS][POP_SIZE];
int fitness[GENERATIONS][POP_SIZE];

int u[2][2]; // 0
int d[2][2]; // 1
int f[2][2]; // 2
int b[2][2]; // 3
int l[2][2]; // 4
int r[2][2]; // 5

random_device rd;
mt19937 gen(rd());

int randInt(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}

string moveName(int x) {
    switch (x) {
        case 1: return "L'"; case 2: return "L";
        case 3: return "R'"; case 4: return "R";
        case 5: return "F'"; case 6: return "F";
        case 7: return "B'"; case 8: return "B";
        case 9: return "U'"; case 10: return "U";
        case 11: return "D'"; case 12: return "D";
        case 13: return "x'"; case 14: return "x";
        case 15: return "y'"; case 16: return "y";
        case 17: return "z'"; case 18: return "z";
        default: return "?";
    }
}

void printMoves(const vector<int>& moves) {
    for (int x : moves) cout << moveName(x) << ' ';
    cout << '\n';
}

void left(int t) {
    if (t == -1) {
        int x1 = f[0][0], x2 = f[1][0];
        f[0][0] = d[0][0]; f[1][0] = d[1][0];
        d[0][0] = b[1][1]; d[1][0] = b[0][1];
        b[1][1] = u[0][0]; b[0][1] = u[1][0];
        u[0][0] = x1;       u[1][0] = x2;

        int temp = l[0][0];
        l[0][0] = l[0][1]; l[0][1] = l[1][1];
        l[1][1] = l[1][0]; l[1][0] = temp;
    }
    if (t == 1) {
        int x1 = u[0][0], x2 = u[1][0];
        u[0][0] = b[1][1]; u[1][0] = b[0][1];
        b[1][1] = d[0][0]; b[0][1] = d[1][0];
        d[0][0] = f[0][0]; d[1][0] = f[1][0];
        f[0][0] = x1;      f[1][0] = x2;

        int temp = l[0][0];
        l[0][0] = l[1][0]; l[1][0] = l[1][1];
        l[1][1] = l[0][1]; l[0][1] = temp;
    }
}

void right(int t) {
    if (t == -1) {
        int x1 = f[0][1], x2 = f[1][1];
        f[0][1] = u[0][1]; f[1][1] = u[1][1];
        u[0][1] = b[1][0]; u[1][1] = b[0][0];
        b[1][0] = d[0][1]; b[0][0] = d[1][1];
        d[0][1] = x1;      d[1][1] = x2;

        int temp = r[0][0];
        r[0][0] = r[0][1]; r[0][1] = r[1][1];
        r[1][1] = r[1][0]; r[1][0] = temp;
    }
    if (t == 1) {
        int x1 = d[0][1], x2 = d[1][1];
        d[0][1] = b[1][0]; d[1][1] = b[0][0];
        b[1][0] = u[0][1]; b[0][0] = u[1][1];
        u[0][1] = f[0][1]; u[1][1] = f[1][1];
        f[0][1] = x1;      f[1][1] = x2;

        int temp = r[0][0];
        r[0][0] = r[1][0]; r[1][0] = r[1][1];
        r[1][1] = r[0][1]; r[0][1] = temp;
    }
}

void front(int t) {
    if (t == -1) {
        int x1 = u[1][0], x2 = u[1][1];
        u[1][0] = r[0][0]; u[1][1] = r[1][0];
        r[0][0] = d[0][1]; r[1][0] = d[0][0];
        d[0][1] = l[1][1]; d[0][0] = l[0][1];
        l[1][1] = x1;      l[0][1] = x2;

        int temp = f[0][0];
        f[0][0] = f[0][1]; f[0][1] = f[1][1];
        f[1][1] = f[1][0]; f[1][0] = temp;
    }
    if (t == 1) {
        int x1 = l[1][1], x2 = l[0][1];
        l[1][1] = d[0][1]; l[0][1] = d[0][0];
        d[0][1] = r[0][0]; d[0][0] = r[1][0];
        r[0][0] = u[1][0]; r[1][0] = u[1][1];
        u[1][0] = x1;      u[1][1] = x2;

        int temp = f[0][0];
        f[0][0] = f[1][0]; f[1][0] = f[1][1];
        f[1][1] = f[0][1]; f[0][1] = temp;
    }
}

void back(int t) {
    if (t == -1) {
        int x1 = u[0][0], x2 = u[0][1];
        u[0][0] = l[1][0]; u[0][1] = l[0][0];
        l[1][0] = d[1][1]; l[0][0] = d[1][0];
        d[1][1] = r[0][1]; d[1][0] = r[1][1];
        r[0][1] = x1;      r[1][1] = x2;

        int temp = b[0][0];
        b[0][0] = b[0][1]; b[0][1] = b[1][1];
        b[1][1] = b[1][0]; b[1][0] = temp;
    }
    if (t == 1) {
        int x1 = r[0][1], x2 = r[1][1];
        r[0][1] = d[1][1]; r[1][1] = d[1][0];
        d[1][1] = l[1][0]; d[1][0] = l[0][0];
        l[1][0] = u[0][0]; l[0][0] = u[0][1];
        u[0][0] = x1;      u[0][1] = x2;

        int temp = b[0][0];
        b[0][0] = b[1][0]; b[1][0] = b[1][1];
        b[1][1] = b[0][1]; b[0][1] = temp;
    }
}

void up(int t) {
    if (t == -1) {
        int x1 = f[0][0], x2 = f[0][1];
        f[0][0] = l[0][0]; f[0][1] = l[0][1];
        l[0][0] = b[0][0]; l[0][1] = b[0][1];
        b[0][0] = r[0][0]; b[0][1] = r[0][1];
        r[0][0] = x1;      r[0][1] = x2;

        int temp = u[0][0];
        u[0][0] = u[0][1]; u[0][1] = u[1][1];
        u[1][1] = u[1][0]; u[1][0] = temp;
    }
    if (t == 1) {
        int x1 = r[0][0], x2 = r[0][1];
        r[0][0] = b[0][0]; r[0][1] = b[0][1];
        b[0][0] = l[0][0]; b[0][1] = l[0][1];
        l[0][0] = f[0][0]; l[0][1] = f[0][1];
        f[0][0] = x1;      f[0][1] = x2;

        int temp = u[0][0];
        u[0][0] = u[1][0]; u[1][0] = u[1][1];
        u[1][1] = u[0][1]; u[0][1] = temp;
    }
}

void down(int t) {
    if (t == -1) {
        int x1 = f[1][0], x2 = f[1][1];
        f[1][0] = r[1][0]; f[1][1] = r[1][1];
        r[1][0] = b[1][0]; r[1][1] = b[1][1];
        b[1][0] = l[1][0]; b[1][1] = l[1][1];
        l[1][0] = x1;      l[1][1] = x2;

        int temp = d[0][0];
        d[0][0] = d[0][1]; d[0][1] = d[1][1];
        d[1][1] = d[1][0]; d[1][0] = temp;
    }
    if (t == 1) {
        int x1 = f[1][0], x2 = f[1][1];
        f[1][0] = l[1][0]; f[1][1] = l[1][1];
        l[1][0] = b[1][0]; l[1][1] = b[1][1];
        b[1][0] = r[1][0]; b[1][1] = r[1][1];
        r[1][0] = x1;      r[1][1] = x2;

        int temp = d[0][0];
        d[0][0] = d[1][0]; d[1][0] = d[1][1];
        d[1][1] = d[0][1]; d[0][1] = temp;
    }
}

void xO(int t) {
    if (t == 1) { left(-1); right(1); }
    else        { left(1);  right(-1); }
}

void yO(int t) {
    if (t == 1) { up(1);   down(-1); }
    else        { up(-1);  down(1); }
}

void zO(int t) {
    if (t == 1) { front(1);  back(-1); }
    else        { front(-1); back(1); }
}

void int_to_move(int x) {
    if (x == 1) left(-1);
    else if (x == 2) left(1);
    else if (x == 3) right(-1);
    else if (x == 4) right(1);
    else if (x == 5) front(-1);
    else if (x == 6) front(1);
    else if (x == 7) back(-1);
    else if (x == 8) back(1);
    else if (x == 9) up(-1);
    else if (x == 10) up(1);
    else if (x == 11) down(-1);
    else if (x == 12) down(1);
    else if (x == 13) xO(-1);
    else if (x == 14) xO(1);
    else if (x == 15) yO(-1);
    else if (x == 16) yO(1);
    else if (x == 17) zO(-1);
    else if (x == 18) zO(1);
}

void applyMoves(const vector<int>& moves) {
    for (int mv : moves) int_to_move(mv);
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
    int best = 9999;

    best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1);

    xO(1);
    best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1);

    xO(1);
    best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1);

    xO(1);
    best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1);

    xO(1);
    zO(1);
    best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1);

    zO(1); zO(1);
    best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1); best = min(best, isSet());
    yO(1);

    zO(1);
    return best;
}

void initialize() {
	
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            u[j][k] = 0;
            d[j][k] = 1;
            f[j][k] = 2;
            b[j][k] = 3;
            l[j][k] = 4;
            r[j][k] = 5;
        }
    }


    int scramble[] = {6, 6, 9, 4, 6, 9, 5, 9, 4, 10, 10};
    for (int mv : scramble) int_to_move(mv);
}

vector<int> selectMost(int g) {
    vector<pair<int,int>> order;
    for (int i = 0; i < POP_SIZE; i++) {
        order.push_back({fitness[g][i], i});
    }
    sort(order.begin(), order.end());

    vector<int> ans;
    for (int i = 0; i < ELITE_SIZE; i++) {
        ans.push_back(order[i].second);
    }
    return ans;
}

void appendMove(vector<int>& chromosome, int mv) {
    chromosome.push_back(mv);
    int_to_move(mv);
}

void appendFormula(vector<int>& chromosome) {
    int index = randInt(0, 4);
    for (int mv : formulas[index]) {
        appendMove(chromosome, mv);
    }
}

// Simplifies consecutive same-face moves
vector<int> simplifyMoves(const vector<int>& moves) {
    vector<int> result;

    auto face = [](int mv) {
        if (mv <= 12) return (mv - 1) / 2;       
        return 100 + (mv - 13) / 2;            
    };
    auto turnValue = [](int mv) {
        return (mv % 2 == 1) ? -1 : 1;         
    };
    auto moveFrom = [](int fc, int val) {
        if (fc < 100) {
            int base = fc * 2 + 1;
            if (val == -1) return base;
            if (val == 1) return base + 1;
            if (val == 2) return base + 1;
        }
        else {
            int base = 13 + (fc - 100) * 2;
            if (val == -1) return base;
            if (val == 1) return base + 1;
            if (val == 2) return base + 1;
        }
        return 0;
    };

    for (int mv : moves) {
        if (result.empty() || face(result.back()) != face(mv)) {
            result.push_back(mv);
            continue;
        }

        int fc = face(mv);
        int sum = turnValue(result.back()) + turnValue(mv);
        result.pop_back();
        sum %= 4;
        if (sum < 0) sum += 4;

        if (sum == 0) {
            // canceled out
        }
        else if (sum == 1) {
            result.push_back(moveFrom(fc, 1));
        }
        else if (sum == 2) {
            int m = moveFrom(fc, 1);
            result.push_back(m);
            result.push_back(m);
        }
        else if (sum == 3) {
            result.push_back(moveFrom(fc, -1));
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int restart = 0; restart < RESTARTS; restart++) {
        for (int i = 0; i < GENERATIONS; i++) {
            for (int j = 0; j < POP_SIZE; j++) {
                vc[i][j].clear();
            }
        }

        vector<int> ranking;

        for (int g = 0; g < GENERATIONS; g++) {
            for (int j = 0; j < POP_SIZE; j++) {
                initialize();

                if (g == 0) {
                    appendMove(vc[g][j], randInt(1, 12));
                    appendMove(vc[g][j], randInt(1, 12));
                    fitness[g][j] = fit();
                    continue;
                }

                if (j < ELITE_SIZE) {
                    int parent = ranking[j];
                    vc[g][j] = vc[g - 1][parent];
                    applyMoves(vc[g][j]);
                    fitness[g][j] = fit();
                    continue;
                }

                int parent = ranking[randInt(0, ELITE_SIZE - 1)];
                vc[g][j] = vc[g - 1][parent];

                applyMoves(vc[g][j]);

                int evolution = randInt(0, 3);

                if (evolution == 0) {
                    appendFormula(vc[g][j]);
                }
                else if (evolution == 1) {
                    appendFormula(vc[g][j]);
                    appendFormula(vc[g][j]);
                }
                else if (evolution == 2) {
                    appendMove(vc[g][j], randInt(13, 18));
                    appendFormula(vc[g][j]);
                }
                else {
                    appendMove(vc[g][j], randInt(13, 18));
                    appendMove(vc[g][j], randInt(13, 18));
                    appendFormula(vc[g][j]);
                }

                fitness[g][j] = fit();
            }

            ranking = selectMost(g);
            int bestIndex = ranking[0];
            int bestFitness = fitness[g][bestIndex];

            cout << "[restart " << restart << "] Generation " << g << " / individual "
                 << bestIndex << " / move count: " << vc[g][bestIndex].size()
                 << " / fitness: " << bestFitness << '\n';

            if (bestFitness == 0) {
                cout << "\nSolution found!\n";
                cout << "Generation: " << g << ", individual: " << bestIndex << '\n';
                cout << "Original move count: " << vc[g][bestIndex].size() << '\n';
                printMoves(vc[g][bestIndex]);

                vector<int> simplified = simplifyMoves(vc[g][bestIndex]);
                cout << "\nSimplified move count: " << simplified.size() << '\n';
                printMoves(simplified);

                initialize();
                applyMoves(vc[g][bestIndex]);
                cout << "\nVerification score: " << fit() << " (0 means solved)\n";
                return 0;
            }
        }
    }

    cout << "\nNo solution found. Try increasing GENERATIONS, POP_SIZE, or RESTARTS.\n";
    return 0;
}
