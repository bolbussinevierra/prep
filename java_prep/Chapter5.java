package java_prep;

import java.util.*;

public class Chapter5 {
    public static void main(String[] args) {
        // 5.1
        ArrayList<Integer> arr1 = new ArrayList<>(Arrays.asList(3, 4, 1, 0, -1));
        System.out.println("5.1: -> " + dutchFlags(2, arr1));

        // 5.6
        ArrayList<Double> arr2
                = new ArrayList<>(Arrays.asList(310.0, 315.0, 275.0, 295.0, 260.0, 270.0, 290.0, 230.0, 255.0, 250.0));
        System.out.println("5.6: -> " + computeMaxProfit(arr2));

        // 5.12
        ArrayList<Integer> arr3 = new ArrayList<>(Arrays.asList(3, 5, 7, 11));
        randomSampling(3, arr3);
        System.out.println("5.12 -> " + arr3);

        // 5.18
        List<List<Integer>> matrix1 = new ArrayList<>();
        matrix1.add(new ArrayList<>(Arrays.asList(1, 2, 3)));
        matrix1.add(new ArrayList<>(Arrays.asList(4, 5, 6)));
        matrix1.add(new ArrayList<>(Arrays.asList(7, 8, 9)));
        System.out.println("5.18 (a) -> " + spiralOrder(matrix1));

        List<List<Integer>> matrix2 = new ArrayList<>();
        matrix2.add(new ArrayList<>(Arrays.asList(1,  2,   3,  4)));
        matrix2.add(new ArrayList<>(Arrays.asList(5,  6,   7,  8)));
        matrix2.add(new ArrayList<>(Arrays.asList(9,  10,  11, 12)));
        matrix2.add(new ArrayList<>(Arrays.asList(13, 14,  15, 16)));
        System.out.println("5.18 (b) -> " + spiralOrder(matrix2));
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

    // 5.12
    public static void randomSampling(int k, List<Integer> arr) {
        Random random = new Random();
        for (int i = 0; i < k; ++i) {
            Collections.swap(arr, i, i + random.nextInt(arr.size() - i));
        }
    }

    // 5.18 (uses neet code Spiral Matrix II solution)
    public static List<Integer> spiralOrder(List<List<Integer>> matrix) {
        List<Integer> spiralOrder = new ArrayList<>();
        int left = 0, right = matrix.size() - 1;
        int top = 0, bottom = matrix.size() - 1 ;

        while (left <= right) {
            // top row, left to right
            for (int col = left; col <= right; ++col) {
                spiralOrder.add(matrix.get(top).get(col));
            }
            top++;

            // right column, top+1 to bottom
            for (int row = top; row <= bottom; ++row) {
                spiralOrder.add(matrix.get(row).get(right));
            }
            right--;

            // bottom row, right-1 to left
            for (int col = right; col >= left; --col) {
                spiralOrder.add(matrix.get(bottom).get(col));
            }
            bottom--;

            // left column, bottom-1 to top+1 (updated above already
            for (int row = bottom; row >= top; --row) {
                spiralOrder.add(matrix.get(row).get(left));
            }
            left++;
        }
        return spiralOrder;
    }
}
