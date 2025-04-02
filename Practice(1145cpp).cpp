#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
vector<string> maze;
vector<vector<int>> dist;
const int dx[] = { 1, -1, 0, 0 };
const int dy[] = { 0, 0, 1, -1 };

bool in_bounds(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

pair<int, pair<int, int>> bfs(int sx, int sy) {
    dist.assign(m, vector<int>(n, -1));
    queue<pair<int, int>> q;
    q.push({ sx, sy });
    dist[sx][sy] = 0;

    pair<int, pair<int, int>> res = { 0, {sx, sy} };

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (in_bounds(nx, ny) && maze[nx][ny] == '.' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({ nx, ny });
                if (dist[nx][ny] > res.first) {
                    res = { dist[nx][ny], {nx, ny} };
                }
            }
        }
    }
    return res;
}

int main() {
    cin >> n >> m;
    maze.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> maze[i];
    }

    int sx = -1, sy = -1;
    for (int i = 0; i < m && sx == -1; ++i) {
        for (int j = 0; j < n && sy == -1; ++j) {
            if (maze[i][j] == '.') {
                sx = i;
                sy = j;
            }
        }
    }

    auto first = bfs(sx, sy);
    auto result = bfs(first.second.first, first.second.second);

    cout << result.first << endl;
    return 0;
}
