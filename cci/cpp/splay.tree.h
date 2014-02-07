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
        explicit node (const T& init = T()) 
            : left(nullptr), right(nullptr), parent(nullptr), key (init) {}
    } *m_root; // declaration and definition together;

    node* _get_grand_parent(node* n){
        if (node->parent) return node->parent->parent;
        else return nullptr;
    }


   /* via_parent is the OUTGOING parent to be rotated through. The rotatee is the right
      child of via_parent */
   void _left_rotate_thru(node* via_parent) {
       node * rotatee = via_parent->right;
       via_parent->right = rotatee->left;
       
       // set the parent pointers properly
       if (rotatee->left) 
           rotatee->left->parent = via_parent;
       
       node *grand_parent = via_parent->parent;
       if (!grand_parent) 
           root = rotatee;
       // if old parent was on the left side of ITS parent (Grandparent of rotatee),
       // then the new grandchild of GP, is rotatee (ditto for right )
       else if (via_parent == grand_parent->left ) 
           grand_parent->left = rotatee;
       else 
           grand_parent->right = rotatee;

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
       if (!rotatee->right) 
           rotatee->right->parent = via_parent;

       node* grandparent = via_parent->parent;
       if (!grand_parent)
           root = rotatee;

       // else if the old parent (via_parent) is on the left side of GP, then
       // left of GrandParent is now rotee
       else if (via_parent == grand_parent->left)
           grand_parent->left = rotatee;
       else 
           grand_parent->right = rotatee;

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
public:
    splay_tree():m_root(nullptr), m_size(0) {}
    node* find(int target) {
       if (!root) return nullptr;
       // locate the node, then _splay it up if we find it. If we dont find it, _splay up
       // the last node we saw when looking
       node * current = root;
       while (true) {
           if (current->key == target) 
               break;
           else if (current->key > key) {
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
       _splay(current);
       assert(m_root == current);

       return (m_root->key == target ? m_root : nullptr); 
  
    }

    // add the node as you would in a bst but then _splay it up after
    void insert(int data) {
        if (!root) {
            root = new node(data);
            m_size = 1;
            return;
        }   
       
        node* current = root;
        while (true) {
            if (current->key >= data) {
                if (current->left) 
                    current = current->left;
                else {
                    current->left = new node(data);
                    current->left->parent = current;
                    current = current->left;
                    break;
                }
           
            } 
            else { 
                if (current->right) 
                    current = current->right;
                else {
                    current->right = new node(data);
                    current->right->parent = current;
                    current = current->right;
                    break;
                }
            }
        }
        m_size++;
        // splay the inserted value up to the root
        _splay(current);
        assert(m_root == current);
    }  
   
   
};

