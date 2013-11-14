
# 
# 5.1
#
def insert_bits(n, m, i, j):
    # first we need to clear all bits in n between j and i 
    # for this we need a mask of the form 1111 ..00000... 1111 where both [j..i]
    # are 0. we make this mask in two parts, the right and left parts
    all_ones = ~0
    right_mask = all_ones << (j + 1) # + 1 to move the trailing 1 past j
    left_mask = (1 << i) - 1 #-1 to make i 0 and turn all all prior bits
    mask = right_mask | left_mask
    new_n = n & mask

    # shift m into place
    new_m = m << i

    # insert new_m into new_n by OR
    return new_n | new_m

#
# 5.2
#
def print_binary(num):
    if (num < 0) or (num > 1):
        return "error"
    
    binary_string = "."
    while (num > 0):
        if len(binary_string) > 32:
            return "error"

        num *= 2
        if num >= 1:
            binary_string += '1'
            num -= 1
        else:
            binary_string += '0'

    return binary_string

# 5.2 extra credit (assume positive)
# ** UPDATE ** do this using left shift!!! see count_ones_better
def print_binary_int(num):
    q = num / 2
    r = num % 2
    binary_string = ""
    while (q > 0):
        binary_string = str(r) + binary_string
        r = q % 2
        q = q / 2

    return '0' + str(r) + binary_string

#
# 5.3
# a) super simple approach
# *UPDATE*: can do this with just left shift see below!
def count_ones(num):
    q = num / 2
    r = num % 2
    number_ones = 0
    while (q > 0):
        if r == 1: number_ones +=1
        r = q % 2
        q = q /2

    if r == 1: number_ones += 1
    return number_ones

def count_ones_better(num):
    count = 0
    while (num > 0):
        if (num & 1) == 1: count +=1 
        num >>= 1
    return count
        

def next_larger(num):
    if num <= 0: return None
    
    number_ones = count_ones_better(num)

    num +=1
    while (number_ones != count_ones_better(num)):
        num += 1

    return num
    
def next_smaller(num):
    if num <= 0: return None

    number_ones = count_ones_better(num)
    num -=1
    while (number_ones != count_ones_better(num)) and num:
        num -= 1

    return num if num > 0 else None

#
# 5.3
# b) bit fiddling approach
def getnext(num):
    if num <= 0: return None #error check. 0 cant have a greater value with same 1s

    # get the position of the rightmost non-zero bit. This will be the bit after
    # all the trailing zeros and the ones that follow those trailing zeros
    temp = num
    rm0 = 0 
    rm1 = 0 
    while (temp & 1) == 0 and temp > 0:
        rm0 += 1 
        temp >>= 1

    # temp has a rightmost bit of 1 or 0 at this point. count the 
    while (temp & 1) == 1:
        rm1 += 1 
        temp >>= 1 

    turnon_bit_at_index = rm1 + rm0 # bits are 0 indexed so just adding the counts gets as at the index beyond the 1s and 0s we want to skip 
    if turnon_bit_at_index == 31:
        return None

    # flip the bit that needs to turn to 1
    num |= (1 << turnon_bit_at_index)
    
    #clear out the last p - 1  bits
    num &= ~0 << turnon_bit_at_index

    #insert rm1 - 1 bits 
    num |= (1 << rm1-1) - 1

    return num

def getprev(num):
    if num <= 0: return None

    temp = num
    rm0 = 0 
    rm1 = 0

    # get to the rightmost 1 that is not trailing
    while (temp & 1) == 1:
        rm1 += 1 
        temp >>= 1

    # now skip the block of zeros that follow
    while (temp & 1) == 0 and temp > 0:
        rm0 += 1
        temp >>=1

    # turn off the bit at p
    turnoff_bit_at_index = rm0 + rm1
    num &= ~(1 << turnoff_bit_at_index) 

    # clear all bits to right of parts
    num &= (~0) << turnoff_bit_at_index

    # add rm+1 1s to the immediate right of p
    # sequence of 1s
    ones = (1 << (rm1 + 1)) - 1
    ones_moved_right = ones << (rm0 - 1) 
    num |= ones_moved_right

    return num

    
        



    
