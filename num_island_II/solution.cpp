#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

class Solution {
public:
    /**
     * @param grid: the 2D grid
     * @return: the number of distinct islands
     */
    vector<pair<int, int>> normalize(const vector<pair<int, int>> &points) {
        int min_x = 1e9;
        int min_y = 1e9;
        for (const auto &point : points) {
            min_x = min(min_x, point.first);
            min_y = min(min_y, point.second);
        }
        vector<pair<int, int>> normalized;
        for (const auto &point : points) {
            normalized.push_back(make_pair(point.first - min_x, point.second - min_y));
        }
        sort(normalized.begin(), normalized.end());
        return normalized;
    }
    void dfs(int row, int col, const vector<vector<int>> &grid, vector<vector<bool>> &vis, vector<pair<int, int>> &comp) {
        vis[row][col] = true;
        comp.push_back(make_pair(row, col));
        const int dir_row[4] = {-1, 0, 1, 0};
        const int dir_col[4] = {0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int next_row = row + dir_row[i];
            int next_col = col + dir_col[i];
            if (next_row < 0 || next_row >= grid.size() || next_col < 0 || next_col >= grid[0].size()) {
                continue;
            }
            if (grid[next_row][next_col] == 0 || vis[next_row][next_col]) {
                continue;
            }
            dfs(next_row, next_col, grid, vis, comp);
        }
    }
    vector<pair<int, int>> rotate(const vector<pair<int, int>> &points, const vector<int> &rotate_matrix) {
        vector<pair<int, int>> res;
        for (const auto &point : points) {
            int x = rotate_matrix[0] * point.first + rotate_matrix[1] * point.second;
            int y = rotate_matrix[2] * point.first + rotate_matrix[3] * point.second;
            res.push_back(make_pair(x, y));
        }
        return normalize(res);
    }
    vector<pair<int, int>> reflect(const vector<pair<int, int>> &points, const string &type) {
        vector<pair<int, int>> res;
        if (type == "up_down") {
            for (const auto &point : points) {
                int x = point.first;
                int y = -point.second;
                res.push_back(make_pair(x, y));
            }
        } else {
            for (const auto &point : points) {
                int x = -point.first;
                int y = point.second;
                res.push_back(make_pair(x, y));
            }
        }
        return normalize(res);
    }
    bool is_same(const vector<pair<int, int>> &a, const vector<pair<int, int>> &b) {
        for (int i = 0; i < (int)a.size(); i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }
    bool is_same_under_transform(const vector<pair<int, int>> &a, const vector<pair<int, int>> &b) {
        if (a.size() != b.size()) {
            return false;
        }
        for (const auto &point : b) {
            vector<pair<int, int>> new_b(b);
            int delta_x = a[0].first - point.first;
            int delta_y = a[0].second - point.second;
            for (int i = 0; i < (int)new_b.size(); i++) {
                new_b[i].first += delta_x;
                new_b[i].second += delta_y;
            }
            if (is_same(a, new_b)) {
                return true;
            }
            const vector<int> rotate_matrics[3] = {{0, -1, 1, 0}, {0, 1, -1, 0}, {-1, 0, 0, -1}};
            for (int i = 0; i < 3; i++) {
                auto rotate_b = rotate(new_b, rotate_matrics[i]);
                if (is_same(a, rotate_b)) {
                    return true;
                }
            }
            auto up_down_b = reflect(new_b, "up_down");
            if (is_same(a, up_down_b)) {
                return true;
            }
            auto left_right_b = reflect(new_b, "left_right");
            if (is_same(a, left_right_b)) {
                return true;
            }
        }
        return false;
    }
    int numDistinctIslands2(vector<vector<int>> &grid) {
        // write your code here
        vector<vector<pair<int, int>>> comps;
        vector<vector<bool>> vis(grid.size());
        for (int i = 0; i < grid.size(); i++) {
            vis[i] = vector<bool>(grid[0].size());
            fill(vis[i].begin(), vis[i].end(), false);
        }
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1 && vis[i][j] == false) {
                    vector<pair<int, int>> comp;
                    dfs(i, j, grid, vis, comp);
                    comps.push_back(comp);
                }
            }
        }
        for (int i = 0; i < (int)comps.size(); i++) {
            comps[i] = normalize(comps[i]);
        }
        int ans = 0;
        for (int i = 0; i < (int)comps.size(); i++) {
            bool unique = true;
            for (int j = i + 1; j < (int)comps.size(); j++) {
                if (is_same_under_transform(comps[i], comps[j])) {
                    unique = false;
                    break;
                }
            }
            ans += unique;
        }
        return ans;
    }
};

int main() {
    Solution solution = Solution();
    vector<vector<int>> grid = {{1,0,1,0,0,1,0,0,1,1,0,0,0,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,0,0,1,0,1,0,0,1,1,0,1,0,0},{1,1,0,1,0,0,1,0,1,1,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,0,0,1,1,1,1,1,0,0,1,0,0,0,1,0,1,1,1,1,1,0,0,1},{1,1,0,0,1,0,0,1,0,1,0,1,1,0,0,1,0,0,1,1,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,1,0,0,0,1,1,1,0,0,1,1,0},{1,1,1,0,0,0,0,1,0,1,0,1,1,0,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,0,0,1,0,1},{0,0,1,0,1,0,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,0,1,1,1,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,1,0},{0,0,1,1,1,0,0,1,0,1,1,0,0,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,1,0,1,1,0,1,1},{0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,1,1,1,1},{1,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,1,0,0,1,0,1,0},{0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1},{1,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,0,0,1,0,1,0,1,1,1,1,0,0,0,0,1},{0,1,0,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0},{0,0,1,0,0,0,0,0,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,1},{1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,1,0,1,0,0,0,1,1,1,0,0,0,1,0,1,1,1,1,0,0,0,1,0,0,0},{0,1,1,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,0,0,1,0,1,0,1,1,1,1,0,1,1,1},{1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,0,1,0,0},{1,1,1,0,0,0,1,1,1,0,0,1,0,1,1,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1},{0,0,1,1,1,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,0,0,0,0,1,1,0,0},{1,1,1,0,0,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,0,1},{0,0,1,0,1,1,1,1,0,0,0,1,0,1,1,0,0,1,0,0,1,1,1,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,1,1,0,1,0,1,1,1,0,0,0},{0,1,0,0,1,0,0,1,0,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,0,0,0,0},{1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,1,0,1,0,1,0,0,1,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0},{1,0,1,0,0,1,1,0,1,1,0,0,1,0,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,0,0,1,0,0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,1}};
    // vector<vector<int>> grid = {{1, 1, 0, 0, 0}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1}, {0, 0, 0, 1, 1}};
    int ans = solution.numDistinctIslands2(grid);
    printf("%d\n", ans);
    return 0;
}