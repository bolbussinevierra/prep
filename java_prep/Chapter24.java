package java_prep;

public class Chapter24 {
    public static void main(String[] args){
        // 24.1
        System.out.println("24.1 -> " + GCD(24, 300));
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
}
