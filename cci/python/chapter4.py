#
# helpers
#
class node(object):
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None 
        self.adjacent = [self.left, self.right]

    def insert(self, data):
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
                
    