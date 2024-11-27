package java_prep;

public class Chapter11 {
    public static void main(String[] args) {
        int[] A = new int[]{1, 3, 5, 6, 7, 9};
        System.out.println(bSearch(6, A));

        // 11.1
        int[] B = new int[]{1, 3, 3, 3, 5, 6, 7, 9};
        System.out.println("11.1 -> " + bSearchFirst(3, B));

        // 11.4
        System.out.println("11.4 -> " + integerSquareRoot(300));
    }

    public static int bSearch(int t, int[] A) {
        int l = 0, u = A.length - 1;
        while (l <= u) {
            int m = (l + u) / 2;
            if (A[m] < t) {
                l = m + 1;
            } else if (A[m] == t) {
                return m;
            } else {
                u = m - 1;
            }
        }
        return -1;
    }

    // 11.1
    public static int bSearchFirst(int t, int[] A) {
        int l = 0, r = A.length - 1, result = -1;

        while (l <= r) {
            int m = l + ((r - l) / 2);
            if (A[m] < t) {
                l = m + 1;
            } else if (A[m] == t) {
                result = m;
                r = m - 1;
            } else {
                r = m - 1;
            }
        }
        return result;
    }

    // 11.4
    public static int integerSquareRoot(int n) {
        long left = 0, right = n;

        while (left <= right) {
            long mid = (left + right) / 2;
            long midSquared = mid * mid;
            if (midSquared <= n) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return (int) left - 1;
    }
}
