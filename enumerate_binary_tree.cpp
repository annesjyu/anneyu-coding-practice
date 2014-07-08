/*
 * take an integer n and return all distinct binary search tree with n nodes.
 *
 * */

#include <iostream>
#include <./Binary_tree_prototype_template.h>

vector<unique_ptr<BinaryTree<int> >> build_binary_tree_n_helper(const  int l, const int h) {
    vector<unique_ptr<BinaryTree<int> >> res;
    if ( l > h ) {
        res.emplace_back(nullptr);
        return res;
    }
    for ( int i = l; i <= h; i ++ ) {
        auto left_subtrees = build_binary_tree_n_helper(l, i - 1);
        for ( auto &left : left_subtrees ) {
            //i+1 is the center
            auto right_subtree = build_binary_tree_n_helper(i + 1, h);
            for ( auto &right : right_subtree ) {
                res.emplace_back(new BinaryTree<int>{i+1, move(left), move(right)});
            }
        }
    }
    return res;
}

vector<unique_ptr<BinaryTree<int> >> build_binary_tree_book_helper(const int start, const int end) {
    vector<unique_ptr<BinaryTree<int> >> res;
    if ( start > end ) {
        res.emplace_back(nullptr);
        return res;
    }
    for ( int i = start; i <= end; i ++) {
        auto left_res = build_binary_tree_book_helper(start, i - 1);
        auto right_res = build_binary_tree_book_helper(i + 1, end);
        for ( auto &left : left_res ) {
            for ( auto &right : right_res ) {
                res.emplace_back(new BinaryTree<int>{i, move(left), move(right)});
            }
        }
    }
    return res;
}

vector<unique_ptr<BinaryTree<int> >> build_binary_tree_n(const int n) {
    if ( n <= 0 ) {
        throw invalid_argument("n should be larger than 1");
    }
    //vector<unique_ptr<BinaryTree<int> >> trees = build_binary_tree_helper(n);
    vector<unique_ptr<BinaryTree<int> >> trees = build_binary_tree_book_helper(1, n);
}


int main() {
    vector<unique_ptr<BinaryTree<int> >> trees = build_binary_tree_n(10); 
}
