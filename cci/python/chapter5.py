
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
        
        print "bs = " + binary_string

    return binary_string

# 5.2 extra credit (assume positive)
def print_binary_int(num):
    q = num / 2
    r = num % 2
    binary_string = ""
    while (q > 0):
        binary_string = str(r) + binary_string
        r = q % 2
        q = q / 2

    return '0' + str(r) + binary_string
