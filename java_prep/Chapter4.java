package java_prep;

public class Chapter4 {
    public static void main(String[] args) {
        // 4.8
        System.out.println("4.8 -> " + reverse(-4326));
    }

    // 4.8
    public static long reverse(long n) {
        long res = 0;
        while (n != 0) {
            res = res * 10 + (n % 10);
            n /= 10;
        }
        return res;
    }
}
