#pragma once
// based on:
// http://en.wikipedia.org/wiki/Splay_tree#Implementation

template <typename T>
class splay_tree {
private:
    splay_tree(splay_tree const&);
    splay_tree& operator=(splay_tree const&);

    size_t m_size;

    struct node {
        node *left, *right, *parent;
        T key;
        explicit node (const T& init = T()) 
            : left(nullptr), right(nullptr), parent(nullptr), key(init) {}
    } *m_root; // declaration and definition together;

    node* _get_grand_parent(node* n){
        if (n->parent) return n->parent->parent;
        else return nullptr;
    }

    void _release(node* root){
        if (!root) return;
        _release(root->right);
        _release(root->left);
        delete root;
        root = nullptr;
    }


   /* via_parent is the OUTGOING parent to be rotated through. The rotatee is the right
      child of via_parent */
   void _left_rotate_thru(node* via_parent) {
       node *rotatee = via_parent->right;
       via_parent->right = rotatee->left;
       
       // set the parent pointers properly
       if (rotatee->left) 
           rotatee->left->parent = via_parent;
       
       node* grand_parent = via_parent->parent;
       if (!grand_parent) {
           m_root = rotatee;
           rotatee->parent = nullptr;
       }
       // if old parent was on the left side of ITS parent (Grandparent of rotatee),
       // then the new grandchild of GP, is rotatee (ditto for right )
       else { 
            if (via_parent == grand_parent->left ) 
                grand_parent->left = rotatee;
            else 
                grand_parent->right = rotatee;
            rotatee->parent = grand_parent;
       }

       // complete left and right assignments
       rotatee->left = via_parent;
       via_parent->parent = rotatee;
   }
   /*  via_parent is the OUTGOING parent being rotated through, the rotatee is the left
       child of via_parent */
   void _right_rotate_thru(node* via_parent) {
       node *rotatee = via_parent->left;
       via_parent->left = rotatee->right;

       // set the parent pointers appropriately
       if (rotatee->right) 
           rotatee->right->parent = via_parent;

       node* grand_parent = via_parent->parent;
       if (!grand_parent) {
           m_root = rotatee;
           rotatee->parent = nullptr;
       }

       // else if the old parent (via_parent) is on the left side of GP, then
       // left of GrandParent is now rotee
       else {
            if (via_parent == grand_parent->left) 
                grand_parent->left = rotatee;
            else 
                grand_parent->right = rotatee;
           
            rotatee->parent = grand_parent;
       }

       rotatee->right = via_parent;
       via_parent->parent = rotatee;
   }

   /* "_splay" the splayee up to the root". If splayer is a left child of a left child
       or a right child of a right child, we need to rotate the parent through gparent
       first before we tackle the splayee */
   void _splay (node* splayee) {
       while (splayee->parent) { // while the splayee is not root
           // if splayee is a child of root, we need to do a right_rotate if its a left
           // child and vice versa
           if (!_get_grand_parent(splayee)) {
               if (splayee->parent->left == splayee) 
                   _right_rotate_thru(splayee->parent);
               else 
                   _left_rotate_thru(splayee->parent);
           }
           // splayee is leftof(parent) who is leftof(grandparent), we need to do
           // two right rotations starting with a rotation through the grand parent
           // followed by a rotation through the parent
           else if (splayee == splayee->parent->left && 
                   splayee->parent == _get_grand_parent(splayee)->left){
               _right_rotate_thru(_get_grand_parent(splayee));
               _right_rotate_thru(splayee->parent);
           }
           // splayess is rightof(parent) who is rightof(grandparent), we need to do two
           // left rotations starting with a rotation through the grand parent followed by
           // a rotation through the parent
           else if (splayee == splayee->parent->right && 
                    splayee->parent == _get_grand_parent(splayee)->right) {
               _left_rotate_thru(_get_grand_parent(splayee));
               _left_rotate_thru(splayee->parent);
           }
           // splayee is leftof(parent) who is rightof(grandparent), we need to do a 
           // right rotation THROUGH *PARENT* followed by a left rotation through *PARENT*
           // again and vice versa
           else if (splayee == splayee->parent->left && 
                   splayee->parent == _get_grand_parent(splayee)->right) {
               _right_rotate_thru(splayee->parent);
               _left_rotate_thru(splayee->parent);
           }
           else {
               _left_rotate_thru(splayee->parent);
               _right_rotate_thru(splayee->parent);
           }
       }
       m_root = splayee;
   }
   
   node * _get_maximum_node(node * root) {
       while (root->right) root = root->right;
       return root;
   }

   void _print(node *root, int indent=0) {
       if (!root) return;

       _print(root->right, indent+1);
       if (indent > 0) {
           for (int i = 1; i <= indent; ++i)
               cout << "    ";
       }
       printf("%d[p:%d]\n", root->key, (root->parent ? root->parent->key : -1));
       _print(root->left, indent+1);
   }


public:
    splay_tree():m_root(nullptr), m_size(0) {}
    ~splay_tree() { _release(m_root); m_root = nullptr; }

    node* find(int target) {
       if (!m_root) return nullptr;
       // locate the node, then _splay it up if we find it. If we dont find it, _splay up
       // the last node we saw when looking
       node *current = m_root;
       while (true) {
           if (current->key == target) 
               break;
           else if (current->key > target) {
               if (!current->left) break;
               else current = current->left;
           }
           else {
               if (!current->right) break;
               else current = current->right;
           }
       }
       // when we exit the loop, we have either found the key or have stopped at the last
       // valid node on the path to finding it. _splay that value up to the root. However
       // we want to make sure that we only return a !nullptr value if we actually found
       // the value we were looking for
       assert(current);
       if (m_root != current)
            _splay(current);
       assert(m_root == current);

       return (m_root->key == target ? m_root : nullptr); 
  
    }

    void print() { 
        if (!m_root) {
            cout << "Tree is Empty!\n" << endl;
            return;
        }
        _print(m_root); 
        cout << "------------------------\n";
    }

    // add the node as you would in a bst but then _splay it up after
    void insert(int data) {
        if (!m_root) {
            m_root = new node(data);
            m_size = 1;
            return;
        }   
       
        node* current = m_root;
        while (true) {
            if (current->key >= data) {
                if (current->left) 
                    current = current->left;
                else {
                    current->left = new node(data);
                    current->left->parent = current;
                    current = current->left; // important so as to splay correct node
                    break;
                }
           
            } 
            else { 
                if (current->right) 
                    current = current->right;
                else {
                    current->right = new node(data);
                    current->right->parent = current;
                    current = current->right; // important so as to splay correct node
                    break;
                }
            }
        }
        m_size++;
        // splay the inserted value up to the root
        _splay(current);
        assert(m_root == current);
        return;
    }  
   
    // erase a node from a bst
    void erase(T const& key) {
        if (!m_root || m_size==0) {
            assert(!m_root && m_size == 0);
            return;
        }
        // first find the node. This will _splay the node up to the root
        node* found = find(key);
        if (!found) return;
        assert(m_root->key == key); // make sure splaying occurred.

        // now remove the root and free it
        node *left_subtree = found->left;
        node *right_subtree = found->right;
        delete found;
        m_size--;

        if (!left_subtree && !right_subtree) {
            assert(m_size == 0);
            m_root = nullptr;
            return;
        }

        // if left subtree is valid, need to get the maximum element in the left subtree
        // and make that the new root (which will be the root of the new melded tree we
        // are making (_correctly set by _splay)
        if (left_subtree && right_subtree) {
            _splay(_get_maximum_node(left_subtree));
            // make the right subtree the right child of the left
            m_root->right = right_subtree;
        }
        else {
            m_root = left_subtree ? left_subtree : right_subtree;
        }
        m_root->parent = nullptr; // make sure new root's parent is cleared.
    }
};

