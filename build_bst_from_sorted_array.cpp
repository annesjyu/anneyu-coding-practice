/*
 * build bst of minimum possible height from a sorted array A
 */

#include <iostream>
#include <vector>
#include "bst_node.cpp"
#include <list>

using namespace std;

BSTNode* build_bst_from_sorted_array_helper(
                        const vector<int>& A,
                        int l, int h ) {
    if ( l > h ) {
        return nullptr;
    }
    int m = l + (( h - l ) >> 1);
    cout << "l = " << l << ", h = " << h << ", A[" << m << "] = " << A[m] << endl;
    BSTNode* node = new BSTNode(A[m], nullptr, nullptr); 
    node->left = unique_ptr<BSTNode>(build_bst_from_sorted_array_helper(A, l, m - 1));
    node->right = unique_ptr<BSTNode>(build_bst_from_sorted_array_helper(A, m + 1, h));
    return node;
}

BSTNode* build_bst_from_sorted_array(const vector<int>& A) {
    if ( A.empty() ) {
        return nullptr;
    }
    return build_bst_from_sorted_array_helper(A, 0, A.size() - 1);
}

BSTNode* build_bst_from_sorted_dlist_helper(list<int>& A, int l, int h, list<int>::iterator& dlist_mid_it) {
    if ( l > h ) {
        return nullptr;
    }
    int m = l + (( h - l ) >> 1);
    BSTNode* left = build_bst_from_sorted_dlist_helper(A, l, m - 1, dlist_mid_it);
    const int v = *(dlist_mid_it);
    return new BSTNode(v, left, build_bst_from_sorted_dlist_helper(A, m + 1, h, ++dlist_mid_it));
}

BSTNode* build_bst_from_sorted_dlist(list<int>& A) {
    if ( A.empty() ) {
        return nullptr;
    }
    auto it = A.begin();
    return build_bst_from_sorted_dlist_helper(A, 0, A.size() - 1, it);
}

int main() {
    vector<int> A = { 1, 3, 4, 5, 6, 9, 11, 23, 43, 52};
    unique_ptr<BSTNode> root = unique_ptr<BSTNode>(build_bst_from_sorted_array(A));
    //debug
    cout << "A = ";
    for_each(A.begin(), A.end(), [](int i){cout << i << " ";});
    cout << endl << "inorder print" << endl;
    inorder_print(root);
    cout << endl;

    list<int> B;
    for_each(A.begin(), A.end(), [&](int i) {B.emplace_back(i);});
    unique_ptr<BSTNode> droot = unique_ptr<BSTNode>(build_bst_from_sorted_dlist(B));
    cout << "B = ";
    for_each(B.begin(), B.end(), [](int i){cout << i << " ";});
    cout << endl << "level print" << endl;
    level_order_print(droot);
    
    cout << endl;

    return 0;
}
