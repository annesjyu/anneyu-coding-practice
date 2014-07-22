/*
 * no pointer
 * */
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct BSTNode {
    int data;
    BSTNode* left, *right;
};

void inorder_print(BSTNode* node) {
    if ( !node ) {
        return;
    }
    inorder_print(node->left);
    cout << node->data << ", ";
    inorder_print(node->right);
}

void level_order_print(BSTNode* node) {
    queue<BSTNode*> q;
    q.push(node);
    int num_nodes_per_level = 1;
    int num_nodes_next_level = 0;
    while ( !q.empty() ) {
        BSTNode* new_node = q.front();
        q.pop();
        cout << new_node->data << " ";
        if ( new_node->left ) {
            q.push(new_node->left);
            num_nodes_next_level ++;
        }
        if ( new_node->right ) {
            q.push(new_node->right);
            num_nodes_next_level ++;
        }
        if ( --num_nodes_per_level == 0 ) {
            cout << endl;
            num_nodes_per_level = num_nodes_next_level;
            num_nodes_next_level = 0;
        }
    }
}

class BinaryTree {
    BSTNode* root = nullptr;

    public:
        bool empty() {
            return ( root == nullptr );
        }

        bool insert(const int v) {
            BSTNode* cur = root, *prev = nullptr;
            while ( cur != nullptr ) {
                prev = cur;
                if ( v < cur->data ) {
                   cur = cur->left;
                } else if ( v > cur->data ) {
                   cur = cur->right;
                } else {
                   return false;
                }
            }
            BSTNode *new_node = new BSTNode{v, nullptr, nullptr};
            if ( prev == nullptr ) {
                root = new_node;
            } else {
                if ( v < prev->data ) {
                    prev->left = new_node;
                } else {
                    prev->right = new_node;
                }
            }
            return true;
        }

        ~BinaryTree() {
            clear(root);
        }
        
        BSTNode* get_root() {
            return root;
        }

    private:
        void clear(BSTNode* node) {
            if ( node == nullptr ) {
                return;
            }
            BSTNode* left = node->left;
            BSTNode* right = node->right;
            delete node;
            clear(left);
            clear(right);
        }
};

BSTNode* build_bst_tree(vector<int>& A) {
    BinaryTree bt;
    for_each(A.begin(), A.end(), [&](int i) {bt.insert(i);});
    return bt.get_root();
}

BSTNode* build_bst_from_sorted_array_helper(vector<int>& A, int l, int h) {
    if ( l <= h ) {
        int m = l + (( h - l ) >> 1);
        BSTNode* node = new BSTNode{A[m],
                    build_bst_from_sorted_array_helper(A, l, m - 1),
                    build_bst_from_sorted_array_helper(A, m + 1, h)};
        return node;
    }
    return nullptr;
}

BSTNode* build_bst_from_sorted_array(vector<int>& A) {
    if ( A.empty() ) {
        return nullptr;
    }
    return build_bst_from_sorted_array_helper(A, 0, A.size() - 1);
}
