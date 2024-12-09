package java_prep;

import java.util.HashSet;
import java.util.List;

public class Chapter17 {
    public static void main(String[] args) {
        System.out.println("TwoSum -> " + hasTwoSum(List.of(1,5,7,9), 14));

        // 17.4
        System.out.println("17.4 -> " + hasThreeSum(List.of(1, 5, 7, 9), 15));
    }

    private static boolean hasTwoSum(List<Integer> a, int s) {
        HashSet<Integer> prev = new HashSet<>();
        for (int i : a) {
            int diff = s - i;
            if (prev.contains(diff)) {
                return true;
            }
            prev.add(i);
        }
        return false;
    }

    private static boolean hasThreeSum(List<Integer> a, int s) {
        return a.stream().anyMatch(i -> hasTwoSum(a, s - i));
    }
}
