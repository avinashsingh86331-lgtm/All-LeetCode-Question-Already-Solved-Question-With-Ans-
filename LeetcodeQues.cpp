// cd "C:\Users\Avii\OneDrive\Desktop\VS CODE 1\launage\C++"
// git pull origin main --rebase
// git add .
// git commit -m "Day X - Problem Name"
// git push


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Build tree from level-order input with -1 as NULL
Node* buildTree(const vector<int>& values) {
    if (values.empty() || values[0] == -1) return nullptr;

    Node* root = new Node(values[0]);
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < values.size()) {
        Node* current = q.front();
        q.pop();

        // Left child
        if (values[i] != -1) {
            current->left = new Node(values[i]);
            q.push(current->left);
        }
        i++;
        if (i >= values.size()) break;

        // Right child
        if (values[i] != -1) {
            current->right = new Node(values[i]);
            q.push(current->right);
        }
        i++;
    }
    return root;
}

// Search for a key in the tree
bool search(Node* root, int key) {
    if (!root) return false;
    if (root->data == key) return true;
    return search(root->left, key) || search(root->right, key);
}

// Traversals
void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

int main() {
    cout << "Enter tree values (space-separated, -1 for NULL): ";
    vector<int> values;
    int x;
    while (cin >> x) {
        values.push_back(x);
        if (cin.peek() == '\n') break; // stop at newline
    }

    Node* root = buildTree(values);

    cout << "Enter key to search: ";
    int key;
    cin >> key;

    bool found = search(root, key);
    cout << "Key found: " << (found ? "true" : "false") << endl;

    cout << "Preorder Traversal: ";
    preorder(root);
    cout << endl;

    cout << "Inorder Traversal: ";
    inorder(root);
    cout << endl;

    cout << "Postorder Traversal: ";
    postorder(root);
    cout << endl;

    return 0;
}


// Window + Hash Set/Map problem

#include <iostream>
#include <unordered_set>
using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_set<char> st;
    int left = 0, maxLength = 0;

    for (int right = 0; right < s.length(); right++) {
        while (st.find(s[right]) != st.end()) {
            st.erase(s[left]);
            left++;
        }
        st.insert(s[right]);
        maxLength = max(maxLength, right - left + 1);
    }

    return maxLength;
}

int main() {
    string s = "abcabcbb";
    cout << lengthOfLongestSubstring(s);
}


// Insert into a Binary Search Tree
#include <iostream>
using namespace std;

// ✅ Added TreeNode definition
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = right = nullptr;
    }
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }

        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        } else {
            root->right = insertIntoBST(root->right, val);
        }

        return root;
    }
};



// Increasing Order Search Tree
class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* dummy = new TreeNode(-1); // temporary node
        TreeNode* curr = dummy;

        inorder(root, curr);

        return dummy->right; // new root
    }

    void inorder(TreeNode* node, TreeNode*& curr) {
        if (node == NULL) return;

        // Step 1: go left
        inorder(node->left, curr);

        // Step 2: process current node
        node->left = NULL;          // remove left child
        curr->right = node;         // attach node to right
        curr = node;                // move pointer forward

        // Step 3: go right
        inorder(node->right, curr);
    }
};