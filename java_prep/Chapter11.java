package java_prep;

public class Chapter11 {
    public static void main(String[] args) {
        int[] A = new int[]{1, 3, 5, 6, 7, 9};
        System.out.println(bsearch(6, A));
    }

    public static int bsearch(int t, int[] A) {
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
}
