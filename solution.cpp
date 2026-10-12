#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* root;
    unordered_map<int, pair<int, int>> nodeInfo; // val -> {depth, parent_val}
    
    // Build tree from preorder traversal
    TreeNode* buildTree(const vector<int>& preorder, int& index) {
        if (index >= (int)preorder.size() || preorder[index] == -1) {
            index++;
            return nullptr;
        }
        
        TreeNode* node = new TreeNode(preorder[index]);
        index++;
        node->left = buildTree(preorder, index);
        node->right = buildTree(preorder, index);
        return node;
    }
    
    // DFS to record depth and parent information
    void recordNodeInfo(TreeNode* node, int depth, int parent_val) {
        if (!node) return;
        
        nodeInfo[node->val] = {depth, parent_val};
        recordNodeInfo(node->left, depth + 1, node->val);
        recordNodeInfo(node->right, depth + 1, node->val);
    }
    
public:
    Solution(const vector<int>& preorder) {
        int index = 0;
        root = buildTree(preorder, index);
        if (root) {
            recordNodeInfo(root, 0, -1); // root has parent -1
        }
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