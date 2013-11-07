tower_start = []
tower_mid = []
tower_end = []

table_names = { id(tower_start):"start", id(tower_mid):"mid", id(tower_end):"end" }

def is_ordered(tower):
    
    if not tower:
        return True                                                                

    index = len(tower) - 1
    item = tower[index];
    index -= 1

    while (index >= 0):
        if item > tower[index]:
            return False
        item = tower[index]
        index -= 1
    return True 

def check_invariant():
    return is_ordered(tower_start) and is_ordered(tower_mid) and is_ordered(tower_end)        

def print_towers():
    print "-----------------"
    print "sta:" + str(tower_start)
    print "mid:" + str(tower_mid)
    print "end:" + str(tower_end)
    print "------------------"

def do_move(item, stack):
    stack.append(item)
    print "{0}: Moved item={1} to stack={2}".format(
           "Good Move!" if check_invariant() else "Bad Move!", 
            item, 
            table_names[id(stack)])
    print_towers()

    
        
def verify_complete(start, mid, end):
    if (len(start) == 0) and (len(mid) == 0) and is_ordered(end):
        print "SUCCESS"
    else:
        print "FAILED"

#
# 3.4
# 
def _solve_hanoi(n, start, mid, end):
    if n == 0:
        return
    elif n == 1:
        do_move(start.pop(), end)
        return
    else:
        _solve_hanoi(n - 1, start, end, mid)
        do_move(start.pop(), end)
        _solve_hanoi(n - 1, mid, start, end)
        return 

def solve_hanoi(n):
    # clear globals - need [:] to make sure not just shadowing  global names
    tower_start[:] = []
    tower_mid[:] = []
    tower_end[:] = []
    
    item = n - 1

    # set up the start tower
    for i in range(0, n):
        tower_start.append(item)
        item -= 1
    
    print_towers()
    
    _solve_hanoi(n, tower_start, tower_mid, tower_end)
    verify_complete(tower_start, tower_mid, tower_end)

    return



            