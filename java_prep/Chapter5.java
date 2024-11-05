package java_prep;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Chapter5 {
    public static void main(String[] args) {
        // 5.1
        ArrayList<Integer> A = new ArrayList<>(Arrays.asList(3, 4, 1, 0, -1));
        System.out.println("5.1: -> " + dutchFlags(2, A));

        ArrayList<Double> B
                = new ArrayList<>(Arrays.asList(310.0, 315.0, 275.0, 295.0, 260.0, 270.0, 290.0, 230.0, 255.0, 250.0));
        System.out.println("5.6: -> " + computeMaxProfit(B));

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

    public static Double computeMaxProfit(List<Double> prices) {
        double minPrice = Double.MAX_VALUE, maxProfit = 0.0;
        for (Double p : prices) {
            maxProfit = Math.max(maxProfit, p - minPrice);
            minPrice = Math.min(minPrice, p);
        }
        return maxProfit;
    }
}
