#include <iostream>
#include <queue>
#include <cstring>

/* Solution using bidirectional search. */

using namespace std;

struct State {
    int x, y, vx, vy;
    State () { };
    State(int x, int y, int vx, int vy) : x(x), y(y), vx(vx), vy(vy) { }
};

// 1 indicated the presence of an obstacle.
int obstacle[60][60];

// The depth arrays for the two BFSs. Entry -1 indicates an unvisited vertex.
int d1[60][60][7][7];
int d2[60][60][7][7];

// Returns the depth of the state; even indicates which BFS is considered
// (true -> BFS from start; false -> BFS from end).
inline int depth(State s, bool even) {
    if (even) {
        return d1[s.x][s.y][s.vx+3][s.vy+3];
    } else {
        return d2[s.x][s.y][s.vx+3][s.vy+3];
    }
}

// Bidirectional BFS.
void solve(int X, int Y, int sx, int sy, int tx, int ty) {
    queue< State > q1, q2;
    bool even = true;

    // Push starting states on both queues.
    q1.push(State(sx, sy, 0, 0));
    d1[sx][sy][3][3] = 0;
    for (int vx = -3; vx <= 3; vx++) {
        for (int vy = -3; vy <= 3; vy++) {
            d2[tx][ty][vx+3][vy+3] = 0;
            q2.push(State(tx, ty, vx, vy));
        }
    }
    // It is necessary to check if (tx,ty) is covered by an obstacle.
    if (obstacle[tx][ty]) {
        cout << "No solution." << endl;
        return;
    }

    while (!q1.empty() && !q2.empty()) {
        // q is the current BFS queue.
        queue<State > *q;
        if (even) {
            q = &q1;
        } else {
            q = &q2;
        }
        State s = q->front();
        int curdepth = depth(s, even);
        while (!q->empty() && depth(q->front(), even) == curdepth) {
            State s = q->front();
            q->pop();
            if (depth(s, !even) != -1) {
                int answer = curdepth + depth(s, !even);
                cout << "Optimal solution takes " << answer << " hops." << endl;
                return;
            }
            for (int vx = max(s.vx-1, -3); vx <= min(s.vx+1, 3); vx++) {
                for (int vy = max(s.vy-1, -3); vy <= min(s.vy+1, 3); vy++) {
                    State t;
                    if (even) {
                        t = State(s.x+vx, s.y+vy, vx, vy);
                    } else {
                        t = State(s.x-s.vx, s.y-s.vy, vx, vy);
                    }
                    if (0 <= t.x && t.x < X
                        && 0 <= t.y && t.y < Y
                        && depth(t, even) == -1
                        && obstacle[t.x][t.y] == 0) {
                        q->push(t);
                        if (even) {
                            d1[t.x][t.y][t.vx+3][t.vy+3] = curdepth+1;
                        } else {
                            d2[t.x][t.y][t.vx+3][t.vy+3] = curdepth+1;
                        }
                    }
                }
            }
        }
        even = !even;
    }
    cout << "No solution." << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int X, Y, sx, sy, tx, ty, p;
        cin >> X >> Y;
        cin >> sx >> sy >> tx >> ty;
        cin >> p;

        // Populate obstacle & depth arrays.
        fill (&obstacle[0][0], &obstacle[0][0] + 60*60, 0);
        fill (&d1[0][0][0][0], &d1[0][0][0][0] + 60*60*7*7, -1);
        fill (&d2[0][0][0][0], &d2[0][0][0][0] + 60*60*7*7, -1);
        for (int i = 0; i < p; i++) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            for (int x = x1; x <= x2; x++) {
                for (int y = y1; y <= y2; y++) {
                    obstacle[x][y] = 1;
                }
            }
        }
        solve(X, Y, sx, sy, tx, ty);
    }
    return 0;
}
