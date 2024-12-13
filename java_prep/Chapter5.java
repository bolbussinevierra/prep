package java_prep;

import java.util.*;

public class Chapter5 {
    public static void main(String[] args) {
        // 5.1
        ArrayList<Integer> arr1 = new ArrayList<>(Arrays.asList(3, 4, 1, 0, -1));
        System.out.println("5.1 -> " + dutchFlags(2, arr1));

        // 5.2
        System.out.println("5.2 -> " + plusOne(new ArrayList<>(List.of(9, 9, 9))));

        // 5.6
        ArrayList<Double> arr2
                = new ArrayList<>(Arrays.asList(310.0, 315.0, 275.0, 295.0, 260.0, 270.0, 290.0, 230.0, 255.0, 250.0));
        System.out.println("5.6 -> " + computeMaxProfit(arr2));

        // 5.12
        ArrayList<Integer> arr3 = new ArrayList<>(Arrays.asList(3, 5, 7, 11));
        randomSampling(3, arr3);
        System.out.println("5.12 -> " + arr3);

        // 5.17
        ArrayList<List<Integer>> sudoku = new ArrayList<>() {
            {
                add(List.of(5, 3, 4, 6, 7, 8, 9, 1, 2));
                add(List.of(6, 7, 2, 1, 9, 5, 3, 4, 8));
                add(List.of(1, 9, 8, 3, 4, 2, 5, 6, 7));

                add(List.of(8, 5, 9, 7, 6, 1, 4, 2, 3));
                add(List.of(4, 2, 6, 8, 5, 3, 7, 9, 1));
                add(List.of(7, 1, 3, 9, 2, 4, 8, 5, 6));

                add(List.of(9, 6, 1, 5, 3, 7, 2, 8, 4));
                add(List.of(2, 8, 7, 4, 1, 9, 6, 3, 5));
                add(List.of(3, 4, 5, 2, 8, 6, 1, 7, 9));

            }
        };
        System.out.println("5.17 -> " + isValidSudoku(sudoku));

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

    // 5.2
    public static List<Integer> plusOne(List<Integer> A) {
        // Add 1 to the last position, making it 10 if we need to carry;
        int curPos = A.size() - 1;
        A.set(curPos, A.get(curPos) + 1);

        // Process the carry if needed
        for (int i = curPos; i > 0 && A.get(i) == 10; --i) {
            // Set i to 0, and +1 the one before
            A.set(i, 0);
            A.set(i - 1, A.get(i - 1) + 1);
        }
        // if the carry traveled all the way to 0, make it 1 and add a 0 at the end
        if (A.getFirst() == 10) {
            A.set(0, 1);
            A.add(0);
        }
        return A;
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

    // 5.17
    public static boolean isValidSudoku(List<List<Integer>> partialAssignment) {
        // Check row constraints.
        for (int i = 0; i < partialAssignment.size(); ++i) {
            if (hasDuplicate(partialAssignment, i, i + 1,
                    0, partialAssignment.size())) {
                return false;
            }
        }
        // Check column constraints.
        for (int j = 0; j < partialAssignment.size(); ++j) {
            if (hasDuplicate(partialAssignment, 0,
                    partialAssignment.size(), j, j + 1)) {
                return false;
            }
        }
        // Check region constraints.
        int regionSize = (int)Math.sqrt(partialAssignment.size());
        for (int I = 0; I < regionSize; ++I) {
            for (int J = 0; J < regionSize; ++J) {
                if (hasDuplicate(partialAssignment, regionSize * I, regionSize * (I + 1),
                        regionSize * J, regionSize * (J + 1))) {
                    return false;
                }
            }
        }
        return true;
    }

    private static boolean hasDuplicate(List<List<Integer>> partialAssignment,
                                        int startRow, int endRow, int startCol, int endCol) {
        // [1, 9], +1 due to 0 indexed.
        boolean [] isPresent = new boolean[partialAssignment.size() + 1];
        for (int i = startRow; i < endRow; ++i) {
            for (int j = startCol; j < endCol; ++j) {
                if (partialAssignment.get(i).get(j) != 0 &&
                        isPresent[partialAssignment.get(i).get(j)]) {
                    return true;
                }
                isPresent[partialAssignment.get(i).get(j)] = true;
            }
        }
        return false;
    }
}
