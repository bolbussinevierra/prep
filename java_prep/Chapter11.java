package java_prep;

import java.util.*;

public class Chapter11 {
    public static void main(String[] args) {
        int[] A = new int[]{1, 3, 5, 6, 7, 9};
        System.out.println(bSearch(6, A));

        // 11.1
        int[] B = new int[]{1, 3, 3, 3, 5, 6, 7, 9};
        System.out.println("11.1 -> " + bSearchFirst(3, B));

        // 11.3
        int[] D = new int[]{378, 478, 550, 631, 103, 203, 220, 234, 279, 368};
        System.out.println("11.3 -> " + findSmallest(D));


        // 11.4
        System.out.println("11.4 -> " + integerSquareRoot(300));

        // 11.5
        System.out.println("11.5 -> " + squareRoot(4.4));

        // 11.8: Uses neetcode version of the solution not the one in the book
        // TODO: can you make work with random()
        ArrayList<Integer> C = new ArrayList<>(Arrays.asList(3, 2, 1, 5, 4));
        for (int i = 1; i <= 5; ++i) {
            System.out.println("11.8 -> " + findKthLargest(i, C));
        }

        // 11.19
        System.out.println("11.19 ->" + findMissingIP(List.of(0,1,2,3)));
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

    // 11.3
    public static int findSmallest(int[] a) {
        int left = 0, right = a.length - 1;
        while (left < right) {
            int mid = left + ((right - left)/2);
            if (a[mid] > a[right] ) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        // Loop ends when left == right
        return left;
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

    // 11.5
    private static double squareRoot(double x) {
        double left, right;

        if (x < 1.0) {
            left = x;
            right = 1;
        } else {
            left = 1;
            right = x;
        }

        while (compare(left, right) != CompareResult.EQUAL) {
            double mid = left + 0.5 * (right - left);
            double midSquared = mid * mid;
            if (compare(midSquared, x) == CompareResult.LARGER) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return left;
    }

    // 11.8
    private static int findKthLargest(int k, List<Integer> A) {
        int left = 0, right = A.size() - 1;
        k = A.size() - k; // kth largest in sorted order.
        while (left <= right) {
            int pivotIdx = partitionAroundPivot(left, right, A);
            if (pivotIdx == k) {
                return A.get(pivotIdx);
            } else if (pivotIdx < k) {
                left = pivotIdx + 1;
            } else {  // newPivotIndex > kIndex
                right = pivotIdx - 1;
            }
        }
        // Should never get here.
        throw new RuntimeException();
    }

    // 11.9
    public static int findMissingIP(Iterable<Integer> stream) {
        final int NUM_BUCKET = 1 << 16; // 65536;
        int [] counter = new int[NUM_BUCKET];

        // Isolate 16 higher bits and count how many IPs exist
        // with those bits set
        for (Integer i : stream) {
            int idx = i >>> 16;  // triple shift to fill left side with 0s
            ++counter[idx];
        }

        // Look for a bucket that contains less than 1 << 16 elements
        final int BUCKET_CAPACITY = 1 << 16;
        int candidateBucket = 0;
        for (int i = 0; i < NUM_BUCKET; ++i) {
            if (counter[i] < BUCKET_CAPACITY) {
                candidateBucket = i;
                break;
            }
        }

        // Find all IP address in the stream whose first 16 bits are equal to
        // candidate bucket
        BitSet candidates = new BitSet(BUCKET_CAPACITY);
        for (Integer i : stream) {
            int upperPart = i >>> 16;
            if (candidateBucket == upperPart) {
                // Records the presence of the 16 LSB of x.
                // First part is a bit mask to clear top 16 bits.
                int lowerPart = ((1 << 16) - 1) & i;
                candidates.set(lowerPart);
            }
        }

        // Now identity an integer that is absent for this bucket
        for (int i = 0; i < BUCKET_CAPACITY; ++i) {
            if (!candidates.get(i)) {
                return (candidateBucket << 16) | i;
            }
        }
        // Should not be reachable unless there is a bug
        return -1;
    }

    private static int partitionAroundPivot(int left, int right,
                                            List<Integer> A) {
        int newPivotIndex = left;
        Random r = new Random(0);
        // int pivotValue = A.get(right);
        //int p = r.nextInt(left, right + 1);
        int pivotValue = A.get(right);

        for (int i = left; i < right; ++i) {
            // means greater than here due to cmp definition passed in
            if (A.get(i) <= pivotValue) {
                Collections.swap(A, i, newPivotIndex++);
            }
        }
        Collections.swap(A, right, newPivotIndex);
        return newPivotIndex;
    }

    private enum CompareResult { SMALLER, EQUAL, LARGER }
    private static CompareResult compare(double a, double b) {
        final double EPSILON = 0.000001;
        // Uses normalization for precision problem. Otherwise for very large
        // and small numbers gets weird e.g a = 0.000000000101 and b = 0.0000000001
        double diff = (a - b) / Math.max(Math.abs(a), Math.abs(b));
        return diff < -EPSILON
                ? CompareResult.SMALLER
                : (diff > EPSILON ? CompareResult.LARGER : CompareResult.EQUAL);
    }
}
