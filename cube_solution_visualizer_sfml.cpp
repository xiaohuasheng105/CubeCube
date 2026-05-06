

#include <SFML/Graphics.hpp>
#include <array>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

int u[2][2]; // Up
int d[2][2]; // Down
int l[2][2]; // Left
int r[2][2]; // Right
int f[2][2]; // Front
int b[2][2]; // Back

// -------------------- Cube movement logic --------------------

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
    } else {
        left(1);
        right(-1);
    }
}

void yO(int t) {
    if (t == 1) {
        up(1);
        down(-1);
    } else {
        up(-1);
        down(1);
    }
}

void zO(int t) {
    if (t == 1) {
        front(1);
        back(-1);
    } else {
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

string moveName(int x) {
    switch (x) {
        case 1: return "L'";
        case 2: return "L";
        case 3: return "R'";
        case 4: return "R";
        case 5: return "F'";
        case 6: return "F";
        case 7: return "B'";
        case 8: return "B";
        case 9: return "U'";
        case 10: return "U";
        case 11: return "D'";
        case 12: return "D";
        case 13: return "x'";
        case 14: return "x";
        case 15: return "y'";
        case 16: return "y";
        case 17: return "z'";
        case 18: return "z";
        default: return "?";
    }
}

int wrongStickerCountFixedOrientation() {
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

void resetSolvedCube() {
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
}

void applyScramble() {
    // Same scramble used in your original project:
    // F2 U' R F U' F' U' R U2
    vector<int> scramble = {6, 6, 9, 4, 6, 9, 5, 9, 4, 10, 10};

    for (int mv : scramble) {
        int_to_move(mv);
    }
}

void initializeScrambledCube() {
    resetSolvedCube();
    applyScramble();
}

// -------------------- SFML drawing logic --------------------

sf::Color stickerColor(int colorId) {
    // 0=U, 1=D, 2=F, 3=B, 4=L, 5=R
    // You may change these colors if you want.
    switch (colorId) {
        case 0: return sf::Color(245, 245, 245); // white
        case 1: return sf::Color(245, 220, 40);  // yellow
        case 2: return sf::Color(220, 40, 40);   // red
        case 3: return sf::Color(245, 140, 35);  // orange
        case 4: return sf::Color(50, 90, 220);   // blue
        case 5: return sf::Color(40, 170, 70);   // green
        default: return sf::Color(80, 80, 80);
    }
}

void drawText(sf::RenderWindow& window, const sf::Font& font, const string& text,
              float x, float y, unsigned int size = 24) {
    sf::Text t;
    t.setFont(font);
    t.setString(text);
    t.setCharacterSize(size);
    t.setFillColor(sf::Color(230, 230, 230));
    t.setPosition(x, y);
    window.draw(t);
}

void drawFace(sf::RenderWindow& window, int face[2][2], float x, float y,
              float cell, const sf::Font& font, const string& label) {
    drawText(window, font, label, x + cell * 0.68f, y - 30.0f, 22);

    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 2; col++) {
            sf::RectangleShape rect(sf::Vector2f(cell - 4, cell - 4));
            rect.setPosition(x + col * cell, y + row * cell);
            rect.setFillColor(stickerColor(face[row][col]));
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color(25, 25, 25));
            window.draw(rect);
        }
    }
}

void drawCubeNet(sf::RenderWindow& window, const sf::Font& font,
                 int step, int totalSteps, int currentMove) {
    window.clear(sf::Color(30, 30, 34));

    const float cell = 68.0f;
    const float gap = 14.0f;

    // Net layout:
    //
    //         U
    //   L     F     R     B
    //         D
    //
    const float startX = 115.0f;
    const float startY = 170.0f;
    const float faceW = cell * 2.0f;

    float ux = startX + faceW + gap;
    float uy = startY - faceW - gap;

    float lx = startX;
    float ly = startY;

    float fx = startX + faceW + gap;
    float fy = startY;

    float rx = startX + (faceW + gap) * 2.0f;
    float ry = startY;

    float bx = startX + (faceW + gap) * 3.0f;
    float by = startY;

    float dx = startX + faceW + gap;
    float dy = startY + faceW + gap;

    drawText(window, font, "2x2x2 Cube Solution Visualizer", 55, 30, 30);

    string moveInfo = "Step " + to_string(step) + " / " + to_string(totalSteps);
    if (step == 0) {
        moveInfo += "   Current: scrambled state";
    } else {
        moveInfo += "   Move: " + moveName(currentMove);
    }
    drawText(window, font, moveInfo, 55, 75, 22);

    drawText(window, font,
             "Wrong stickers in fixed orientation: " + to_string(wrongStickerCountFixedOrientation()),
             55, 110, 20);

    drawFace(window, u, ux, uy, cell, font, "U");
    drawFace(window, l, lx, ly, cell, font, "L");
    drawFace(window, f, fx, fy, cell, font, "F");
    drawFace(window, r, rx, ry, cell, font, "R");
    drawFace(window, b, bx, by, cell, font, "B");
    drawFace(window, d, dx, dy, cell, font, "D");

    drawText(window, font, "Close the window to stop.", 55, 535, 18);
    window.display();
}

vector<int> parseMovesFromLine(const string& line) {
    vector<int> result;
    stringstream ss(line);
    int x;

    while (ss >> x) {
        if (x >= 1 && x <= 18) {
            result.push_back(x);
        }
    }

    return result;
}

int main() {
    // Put the solution printed by your GA code here.
    // Example:
    // vector<int> solution = {2, 9, 14, 3, 10, 3};
    //
    // You can also leave this empty and paste numbers into the console when the program starts.
    vector<int> solution = {
        // Paste your solution numbers here.
    };

    if (solution.empty()) {
        cout << "Paste solution move numbers, then press Enter." << endl;
        cout << "Example: 2 9 14 3 10 3 7" << endl;
        cout << "> ";

        string line;
        getline(cin, line);
        solution = parseMovesFromLine(line);
    }

    if (solution.empty()) {
        cout << "No solution moves were provided." << endl;
        return 0;
    }

    sf::RenderWindow window(sf::VideoMode(820, 590), "2x2x2 Cube Solution Visualizer");
    window.setFramerateLimit(60);

    sf::Font font;

    // Windows users:
    // If this font does not load, copy a .ttf font file into the same folder and change the path.
    bool fontLoaded =
        font.loadFromFile("C:/Windows/Fonts/arial.ttf") ||
        font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf") ||
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    if (!fontLoaded) {
        cout << "Font load failed. Put a .ttf font in this folder and change the font path in the code." << endl;
        return 1;
    }

    initializeScrambledCube();

    int step = 0;
    int currentMove = 0;
    drawCubeNet(window, font, step, static_cast<int>(solution.size()), currentMove);

    sf::Clock clock;
    const float delaySeconds = 0.45f;

    bool finished = false;

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Press Space to skip one step manually.
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (step < static_cast<int>(solution.size())) {
                    currentMove = solution[step];
                    int_to_move(currentMove);
                    step++;
                    drawCubeNet(window, font, step, static_cast<int>(solution.size()), currentMove);
                    clock.restart();
                }
            }

            // Press R to restart the animation.
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                initializeScrambledCube();
                step = 0;
                currentMove = 0;
                finished = false;
                drawCubeNet(window, font, step, static_cast<int>(solution.size()), currentMove);
                clock.restart();
            }
        }

        if (!finished && clock.getElapsedTime().asSeconds() >= delaySeconds) {
            if (step < static_cast<int>(solution.size())) {
                currentMove = solution[step];
                int_to_move(currentMove);
                step++;
                drawCubeNet(window, font, step, static_cast<int>(solution.size()), currentMove);
                clock.restart();
            } else {
                finished = true;
                drawText(window, font, "Finished. Press R to replay.", 55, 500, 22);
                window.display();
            }
        }

        this_thread::sleep_for(chrono::milliseconds(10));
    }

    return 0;
}
