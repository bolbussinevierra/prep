package java_prep;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.IntStream;

public class Chapter24 {
    public static void main(String[] args){
        // 24.1
        System.out.println("24.1 -> " + GCD(24, 300));

        // 24.2
        System.out.println("24.2 -> " + findFirstMissingPositive(Arrays.asList(3, 4, 0, 2)));
    }

    // 24.1
    public static long GCD(long x, long y) {
       //  System.out.println("x = " + x + " y = " + y);

        // For simplicity, make sure y is always bigger.
        if (x > y) {
            return GCD(y, x);
        } else if (x == 0) {
            return y;
        } else if ((x & 1) == 0 && (y & 1) == 0) {  // x and y are even.
            return GCD(x >>> 1, y >>> 1) << 1;  // GCD(x/2, y/2) * 2;
        } else if ((x & 1) == 0 && (y & 1) != 0) {  // x is even, y is odd.
            return GCD(x >>> 1, y);
        } else if ((x & 1) != 1 && (y & 1) == 0) {  // x is odd, y is even.
            return GCD(x, y >>> 1);
        } else {  // both are odd
            return GCD(x, y - x);
        }
    }

    // 24.2
    public static int findFirstMissingPositive(List<Integer> A) {
        for (int i = 0; i < A.size(); ++i) {
            while (0 < A.get(i) && A.get(i) <= A.size()
                           && !A.get(i).equals(A.get(A.get(i) - 1))) {
                Collections.swap(A, i, A.get(i) - 1);
            }
        }

        return IntStream.range(0, A.size())
                       .filter(i -> A.get(i) != i + 1)
                       .findFirst()
                       .orElse(A.size()) + 1;
    }
}
