package java_prep;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Chapter5 {
    public static void main(String[] args) {
        // 5.1
        ArrayList<Integer> A = new ArrayList<>(Arrays.asList(3, 4, 1, 0, -1));
        System.out.println(dutchFlags(2, A));
    }

    public static List<Integer> dutchFlags(int pivotIndex, List<Integer> A) {
        int pivot = A.get(pivotIndex);
        int smaller = 0, equal = 0, larger = A.size();
        while (equal < larger) {
            if (A.get(equal) < pivot) {
                Collections.swap(A, equal++, smaller++);
            } else if (A.get(equal) == pivot) {
                equal++;
            } else {
                Collections.swap(A, equal, --larger);
            }
        }
        return A;
    }
}
