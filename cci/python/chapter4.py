#
# helpers
#
class node(object):
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None 
        self.parent = None
        self.adjacent = [self.left, self.right]

    def __str__(self, depth=0):
        ret = ""

        # Print right branch
        if self.right != None:
            ret += self.right.__str__(depth + 1)

        # Print own value
        ret += "\n" + ("     "*depth) + str(self.data)

        # Print left branch
        if self.left != None:
            ret += self.left.__str__(depth + 1)

        return ret

    def insert(self, data): # OPTIMAL FOR BST FROM SORTED ARRAY
        if data < self.data:
            if self.left is None:
                self.left = node(data)
                self.adjacent[0] = self.left
            else:
                self.left.insert(data)
        else:
            if self.right is None:
                self.right = node(data)
                self.adjacent[1] = self.right
            else:
                self.right.insert(data)
 
def reset_visit(root):
    if not root: return
    root.visited = False
    for n in root.adjacent:
        if (n): 
            reset_visit(n)

def _dfs_find(root, value):
    if not root: return None
    if root.data == value: return root
    else:
       for n in root.adjacent:
            if n and not n.visited: 
                n.visited = True
                found = dfs_find(n, value)
                if (found): 
                    return found
       return None
       
def dfs_find(root, value):
    reset_visit(root)
    return _dfs_find(root, value)
    
def make_tree(values):
    if values:
        root = node(values.pop(0))
        for n in values:
            root.insert(n)
        return root

def dfs_tree(root):
    if root:
        print root.data
        dfs_tree(root.left)
        dfs_tree(root.right)

def bfs_tree(root):
    if not root: return    
    bfs_list = []
    bfs_list.append(root)

    while (bfs_list):
        n = bfs_list.pop(0)
        print n.data
        if n.left:
            bfs_list.append(n.left)
        if n.right:
            bfs_list.append(n.right)

def in_order(root):
    if not root:
        return

    in_order(root.left)
    print root.data
    in_order(root.right)

#
# 4.1 - O(N^2)
# 
def measure_height(root):
    if not root:
        return 0
    else:
        return max(measure_height(root.left), measure_height(root.right)) + 1

def is_balanced(root):
    if not root: return True
    return abs(measure_height(root.left) - measure_height(root.right)) <= 1


#
# 4.1 - O(N)   
#
def measure_height_2(root):
    if not root:
        return 0;
    
    left_height = measure_height_2(root.left)
    if left_height == -1: return -1

    right_height = measure_height_2(root.right)
    if right_height == -1: return -1

    if abs(left_height - right_height) <= 1:
        return max(left_height, right_height) + 1
    else:
        return -1

def is_balanced_2(root):
    return not (measure_height_2(root) == -1)

def _path_exists_dfs(a,b):
    if not a or not b: return False
    if a == b: return True
    for n in a.adjacent:
        if n and not n.visited:
            n.visited = True
            found = path_exists_dfs(n, b)
            if (found): return True
    return False

#
# 4.2 -
#
def path_exists_bfs(a,b):
    if not a or not b: return False
    
    reset_visit(a)

    bfs_list = []
    bfs_list.append(a)

    while (bfs_list):
        check = bfs_list.pop(0)
        check.visited = True
        if check == b:
            return True
        else:
            for n in check.adjacent:
                if (n and not n.visited): bfs_list.append(n)

    return False

    
def path_exists_dfs(a,b):
    reset_visit(a)
    return _path_exists_dfs(a,b)
                

#
# 4.3 - actual answer!!!~
#
def _optimal_mst(array, start, end):
    if end < start:
        return None

    mid = (start + end)/2
    n = node(array[mid])
    n.left = _optimal_mst(array, start, mid-1)
    n.right = _optimal_mst(array, mid+1, end)
    
    # UNNNECCESARY - needed for 4.6 below
    n.adjacent[0] = n.left
    n.adjacent[1] = n.right
    if n.left: n.left.parent = n         
    if n.right: n.right.parent = n
    
    return n

def optimal_mst(values):
    return _optimal_mst(values, 0, len(values)-1)


#
# 4.6
#    
def leftmost(node):
    if not node:
        return None

    while (node.left):
        node = node.left

    return node

def in_order_succ(node):
    if not node:
        return None

    if node.right:
        return leftmost(node.right)
    
    else:
        child = node
        parent = child.parent;
        # keep going until child is not right side of parent.
        # if we were already on far right, we will return null
        while (parent and child == parent.right):
            child = parent
            parent = child.parent
        return parent

    