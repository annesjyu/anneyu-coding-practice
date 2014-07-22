/*let r, s, and m be distinct nodes in a BST. in this BST, nodes do not have pointers to their parents, and all keys are unique. check if m has both an ancestor and a descendent in the set {r,s}.
 *either r or s is the ancestor of m and either s or r locates in the subtrees of m
 * when the search reaches m, either r or s definitely will be found before. and both r and s are not reached to the end.
 * */
#include <memory>
#include "bst_node_raw.cpp"

using namespace std;

bool binary_search_bst(BSTNode* node, const int v);

bool is_r_s_descendant_ancestor_of_m(const unique_ptr<BSTNode>& r,
                                     const unique_ptr<BSTNode>& s,
                                     const unique_ptr<BSTNode>& m) {
    if ( !r || !s || !m ) {
        return false;
    }

    //check either r or s is the ancestor of m
    //loop finishes:
    //1. m is found
    //2. either r or s reaches the very end, which is the descendent of m
    auto *cur_r = r.get();
    auto *cur_s = s.get();
    const int mv = m.get()->data;
    while ( cur_r && cur_r->data != mv && cur_s && cur_s->data != mv ) {
        cur_r = ( mv < cur_r->data ? cur_r->left : cur_r->right );
        cur_s = ( mv < cur_s->data ? cur_s->left : cur_s->right );
    }
    
    if ( !cur_s ) {
        return binary_search_bst(cur_r, mv) && binary_search_bst(m.get(), s.get()->data);  
    } else if ( !cur_r ) {
        return binary_search_bst(cur_s, mv) && binary_search_bst(m.get(), r.get()->data);
    } else if ( cur_r->data == mv ) {
        return binary_search_bst(m.get(), s.get()->data);
    } else {
        return binary_search_bst(m.get(), r.get()->data);
    }
}

bool binary_search_bst(BSTNode* node, const int v) {
    while ( node ) {
        if ( v < node->data ) {
            node = node->left;
        } else if ( v > node->data ) {
            node = node->right;
        } else {
            return true;
        }
    }
    return false;
}

int main() {
    vector<int> A = {14, 82, 101, 129, 46, 131, 153, 130, 177, 15, 36, 99, 95, 199, 71, 61, 54, 35, 80, 34, 2, 1, 98, 12, 18, 77};
    sort(A.begin(), A.end());
    unique_ptr<BSTNode> root = unique_ptr<BSTNode>(build_bst_from_sorted_array(A));

    cout << "inorder print: " << endl;
    inorder_print(root.get());
    cout << endl;

    cout << "level order print:" << endl;
    level_order_print(root.get());

    unique_ptr<BSTNode> r = unique_ptr<BSTNode>(new BSTNode{18, nullptr, nullptr});
    unique_ptr<BSTNode> m = unique_ptr<BSTNode>(new BSTNode{54, nullptr, nullptr});    
    unique_ptr<BSTNode> s = unique_ptr<BSTNode>(new BSTNode{46, nullptr, nullptr});
    cout << "r = " << r.get()->data << endl;
    cout << "s = " << s.get()->data << endl;
    cout << "m = " << m.get()->data << endl;

    if ( is_r_s_descendant_ancestor_of_m(r, s, m) ) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    return 0;
}
