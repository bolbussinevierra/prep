package java_prep;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Chapter13 {
    public static void main(String[] args) {
        List<Integer> A = new ArrayList<>(Arrays.asList(1, 2, 3, 5, 7));
        List<Integer> B = new ArrayList<>(Arrays.asList(2, 5, 9));
        System.out.println("13.1 -> " + intersect(A, B));

        List<Integer> C = new ArrayList<>(7);
        // trailing zeros are placeholders; accounted for by size passed in.
        C.addAll(List.of(3,13,17, 0, 0, 0, 0));
        List<Integer> D = new ArrayList<>(Arrays.asList(3, 7, 11, 19));
        mergeTwoSortedArrays(C, 3,  D, 4);
        System.out.println("13.2 -> " + C);
    }

    public static List<Integer> intersect(List<Integer> A, List<Integer> B) {
        List<Integer> intersectionAB = new ArrayList<>();
        int i = 0, j = 0;
        while (i < A.size() && j < B.size()) {
            if (A.get(i).equals(B.get(j)) &&
                    (i == 0 || !A.get(i).equals(A.get(i - 1)))) {
                intersectionAB.add(A.get(i));
                ++i;
                ++j;
            } else if (A.get(i) < B.get(j)) {
                ++i;
            } else {
                ++j;
            }
        }
        return intersectionAB;
    }

    public static void mergeTwoSortedArrays(List<Integer> A, int aCount, List<Integer> B, int bCount) {
        int a = aCount - 1, b = bCount - 1, writeIdx = aCount + bCount - 1;
        while (a >= 0 && b >= 0) {
            A.set(writeIdx--, A.get(a) > B.get(b) ? A.get(a--) : B.get(b--));
        }

        while (b >= 0) {
            A.set(writeIdx--, B.get(b--));
        }
    }
}
