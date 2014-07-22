/*
 * takes a binary search tree with integer labeled nodes and determine if it is an almost BST.It it is an almost BST, reconstruct the original BST.
 * */
#include <iostream>
#include "bst_node_raw.cpp"

bool find_two_inverted_nodes(BSTNode* node, BSTNode*& inv1, BSTNode*& inv2, BSTNode*& prev) {
    if ( !node ) {
        return true;
    }

    cout << "[Debug] call: prev = " << prev->data << " cur = " << node->data << endl;
    
    if ( !find_two_inverted_nodes(node->left, inv1, inv2, prev) ) {
        return false;
    }

    if ( node->data < prev->data ) {
        if ( inv1 == nullptr ) {
            inv1 = prev;
            cout << "[Debug] found inv1 = " << inv1->data << " ";
            cout << "prev = " << prev->data << " cur = " << node->data << endl;  
        } else if ( inv2 == nullptr ) {
            inv2 = node;
            cout << "[Debug] found inv2 = " << inv2->data << " prev = " << prev->data << " cur = " << node->data << endl;
        } else {
            cout << "[Debug] cant assign inverted node anymore. more than 2 were found" << endl;
            return false;
        }
    }
    
    prev = node;
    
    return find_two_inverted_nodes(node->right, inv1, inv2, prev);
}

bool reconstruct_almost_bst(BSTNode* root) {
    BSTNode *inv1 = nullptr;
    BSTNode *inv2 = nullptr;
    BSTNode *prev = new BSTNode{numeric_limits<int>::min(), nullptr, nullptr};
    if ( !find_two_inverted_nodes(root, inv1, inv2, prev) ) {
        cout << "Found more than two inverted nodes." << endl;
        return false;
    }
    if ( !inv1 || !inv2 ) {
        cout << "Found less than two inverted BSTNodes." << endl;
        return false;
    }
    swap(inv1->data, inv2->data);
    return true;
}

int main() {
    //vector<int> A = {3,17,16,14,20};
    vector<int> A = {61, 18, 41, 51, 12, 100};
    unique_ptr<BSTNode> root = unique_ptr<BSTNode>(build_bst_from_sorted_array(A));
    cout << "inorder print: " << endl;
    inorder_print(root.get());
    cout << endl;

    cout << "level order print:" << endl;
    level_order_print(root.get());

    if ( reconstruct_almost_bst(root.get()) ) {
        cout << "successfully reconstructed the tree, inorder print: " << endl;
        inorder_print(root.get());
        cout << endl;
    } else {
        cout << "not an almost bst" << endl;
    }
    return 0;
}
