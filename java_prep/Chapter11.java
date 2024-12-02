package java_prep;

import java.util.*;

public class Chapter11 {
    public static void main(String[] args) {
        int[] A = new int[]{1, 3, 5, 6, 7, 9};
        System.out.println(bSearch(6, A));

        // 11.1
        int[] B = new int[]{1, 3, 3, 3, 5, 6, 7, 9};
        System.out.println("11.1 -> " + bSearchFirst(3, B));

        // 11.4
        System.out.println("11.4 -> " + integerSquareRoot(300));

        // 11.8: TODO: does not work as expected for all values. Revisit
        ArrayList<Integer> C = new ArrayList<>(Arrays.asList(3, 2, 1, 5, 4));
        for (int i = 1; i <=5; ++i) {
            System.out.println("11.8 -> " + findKthLargest(i, C));
        }
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

    // 11.8
    private static int findKthLargest(int k, List<Integer> A) {
       int left = 0, right = A.size() - 1;
        Random r = new Random(0);
        while (left <= right) {
            int pivotIdx = r.nextInt(right - left + 1) + left;
            int newPivotIdx = partitionAroundPivot(left, right, pivotIdx, A);
            int kIndex = A.size() - k; // kth largest in sorted order.
            if (newPivotIdx == kIndex) {
                return A.get(newPivotIdx);
            } else if (newPivotIdx < kIndex ) {
                left = newPivotIdx + 1;
            } else {  // newPivotIndex > kIndex
                right = newPivotIdx - 1;
            }
        }
        // Should never get here.
        throw new RuntimeException();
    }

    private static int partitionAroundPivot(int left, int right, int pivotIdx,
                                            List<Integer> A) {
        int newPivotIndex = left;
        int pivotValue = A.get(pivotIdx);
        for (int i = left; i < right; ++i) {
            // means greater than here due to cmp definition passed in
            if (A.get(i) <= pivotValue) {
                Collections.swap(A, i, newPivotIndex++);
            }
        }
        Collections.swap(A, right, newPivotIndex);
        return newPivotIndex;
    }
}
