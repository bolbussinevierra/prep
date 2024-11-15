package java_prep;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Chapter13 {
    public static void main(String[] args) {
        List<Integer> A = new ArrayList<>(Arrays.asList(1, 2, 3, 5, 7));
        List<Integer> B = new ArrayList<>(Arrays.asList(2, 5, 9));
        System.out.print("13.1 -> " + intersect(A, B));
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
}
