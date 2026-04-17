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

// Add Two Numbers and return the sum as linked list
#include <iostream>
using namespace std;

// Definition of ListNode
struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) {
        val = x;
        next = NULL;
    }
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        int carry = 0;

        while (l1 != NULL || l2 != NULL || carry != 0) {
            int sum = carry;

            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;

            current->next = new ListNode(sum % 10);
            current = current->next;
        }

        return dummy->next;
    }
};


// Roman to Integer
#include <iostream>
#include <unordered_map>
using namespace std;

int romanToInt(string s) {
    unordered_map<char, int> value = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100},
        {'D', 500}, {'M', 1000}
    };

    int total = 0;

    for (int i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && value[s[i]] < value[s[i + 1]]) {
            total -= value[s[i]];
        } else {
            total += value[s[i]];
        }
    }

    return total;
}

int main() {
    string s;
    cout << "Enter Roman Number: ";
    cin >> s;

    int result = romanToInt(s);

    cout << "Integer value = " << result << endl;

    return 0;
}


// Longest Common Prefix
#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.empty()) return "";

        // Start with the first string as the potential prefix
        std::string prefix = strs[0];

        for (int i = 1; i < strs.size(); i++) {
            // While the current string strs[i] does not start with the prefix
            // .find() returns 0 if the prefix is at the very beginning
            while (strs[i].find(prefix) != 0) {
                // Shorten the prefix by one character from the end
                prefix = prefix.substr(0, prefix.length() - 1);

                // If at any point the prefix becomes empty, there is no match
                if (prefix.empty()) return "";
            }
        }

        return prefix;
    }
};


//Valid Parentheses

#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char ch : s) {
            // If opening bracket → push
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            }
            // If closing bracket
            else {
                if (st.empty()) return false;

                char top = st.top();

                // Check matching
                if ((ch == ')' && top == '(') ||
                    (ch == '}' && top == '{') ||
                    (ch == ']' && top == '[')) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }

        // If stack is empty → valid
        return st.empty();
    }
};

// Merge Two Sorted Lists
#include <stdio.h>
#include <stdlib.h>

// Definition of ListNode
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to merge two sorted lists
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    dummy.next = NULL;

    struct ListNode* tail = &dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    // Attach remaining nodes
    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next;
}

// Function to create a new node
struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Function to print list
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    // Creating first list: 1 -> 2 -> 4
    struct ListNode* list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(4);

    // Creating second list: 1 -> 3 -> 4
    struct ListNode* list2 = createNode(1);
    list2->next = createNode(3);
    list2->next->next = createNode(4);

    printf("List 1: ");
    printList(list1);

    printf("List 2: ");
    printList(list2);

    // Merge lists
    struct ListNode* merged = mergeTwoLists(list1, list2);

    printf("Merged List: ");
    printList(merged);

    return 0;
}

//Minimum Distance to the Target Element
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

// Function to find minimum distance
int getMinDistance(vector<int>& nums, int target, int start) {
    int minDist = INT_MAX;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == target) {
            int dist = abs(i - start);
            minDist = min(minDist, dist);
        }
    }

    return minDist;
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int target, start;
    cout << "Enter target: ";
    cin >> target;

    cout << "Enter start index: ";
    cin >> start;

    int result = getMinDistance(nums, target, start);

    cout << "Minimum Distance: " << result << endl;

    return 0;
}

//  Divide Two Integers
#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

int divide(int dividend, int divisor) {
    // Handle overflow case
    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    // Determine sign
    bool negative = (dividend < 0) ^ (divisor < 0);

    // Convert to long long to avoid overflow
    long long dvd = llabs((long long)dividend);
    long long dvs = llabs((long long)divisor);

    int result = 0;

    // Main logic using bit shifting
    while (dvd >= dvs) {
        long long temp = dvs;
        int multiple = 1;

        while (dvd >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }

        dvd -= temp;
        result += multiple;
    }

    return negative ? -result : result;
}

int main() {
    int dividend, divisor;

    cout << "Enter dividend: ";
    cin >> dividend;

    cout << "Enter divisor: ";
    cin >> divisor;

    int result = divide(dividend, divisor);

    cout << "Result: " << result << endl;

    return 0;
}

// Search Insert Position 
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } 
            else if (nums[mid] < target) {
                left = mid + 1;
            } 
            else {
                right = mid - 1;
            }
        }

        return left; // insertion position
    }
};

int main() {
    Solution obj;

    vector<int> nums = {1, 3, 5, 6};
    int target;

    cout << "Enter target: ";
    cin >> target;

    int result = obj.searchInsert(nums, target);

    cout << "Position: " << result << endl;

    return 0;
}

//  Binary Tree Inorder Traversal
#include <iostream>
#include <vector>
using namespace std;

// Define TreeNode
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

// Solution class
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& result) {
        if (root == NULL) return;

        inorder(root->left, result);   // Left
        result.push_back(root->val);   // Root
        inorder(root->right, result);  // Right
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
};

// Main function
int main() {
    /*
        Example Tree:
              1
               \
                2
               /
              3
    */

    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    Solution obj;
    vector<int> result = obj.inorderTraversal(root);

    // Print result
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}