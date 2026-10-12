#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
private:
    unordered_map<int, pair<int, int>> nodeInfo; // val -> {depth, parent_val}
    
    // Build tree from preorder traversal and record node information
    void buildAndRecord(const vector<int>& preorder, int& index, int depth, int parent_val) {
        if (index >= (int)preorder.size()) return;
        
        int val = preorder[index];
        index++;
        
        if (val == -1) {
            // Null node, don't record anything
            return;
        }
        
        // Record this node's information
        nodeInfo[val] = {depth, parent_val};
        
        // Recursively build left and right subtrees
        buildAndRecord(preorder, index, depth + 1, val);
        buildAndRecord(preorder, index, depth + 1, val);
    }
    
public:
    Solution(const vector<int>& preorder) {
        int index = 0;
        buildAndRecord(preorder, index, 0, -1);
    }
    
    bool areCousins(int x, int y) {
        // If nodes are the same, they can't be cousins
        if (x == y) return false;
        
        // Check if both nodes exist
        if (nodeInfo.find(x) == nodeInfo.end() || nodeInfo.find(y) == nodeInfo.end()) {
            return false;
        }
        
        auto infoX = nodeInfo[x];
        auto infoY = nodeInfo[y];
        
        // Same depth but different parents
        return infoX.first == infoY.first && infoX.second != infoY.second;
    }
};

vector<int> parseLine(const string& line) {
    vector<int> result;
    stringstream ss(line);
    int num;
    while (ss >> num) {
        result.push_back(num);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    
    // Read number of queries
    if (!getline(cin, line)) return 0;
    int q = stoi(line);
    
    // Read queries
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        if (!getline(cin, line)) break;
        vector<int> nums = parseLine(line);
        if (nums.size() >= 2) {
            queries.push_back({nums[0], nums[1]});
        }
    }
    
    // Read tree preorder traversal
    if (!getline(cin, line)) return 0;
    vector<int> preorder = parseLine(line);
    
    // Create solution and process queries
    Solution sol(preorder);
    
    for (const auto& query : queries) {
        cout << (sol.areCousins(query.first, query.second) ? 1 : 0) << "\n";
    }
    
    return 0;
}