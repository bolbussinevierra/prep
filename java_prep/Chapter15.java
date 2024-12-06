package java_prep;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;

public class Chapter15 {
    public static void main(String[] args) {
        System.out.println("15.1 -> " + computeHanoi(3, 3));
        System.out.println("15.3 -> " + nQueens(4));
    }

    public static List<List<Integer>> computeHanoi(int numRings, int numPegs) {
        ArrayList<ArrayDeque<Integer>> pegs = new ArrayList<>();
        // Initialize pegs.
        for (int i = 0; i < numPegs; ++i) {
            pegs.add(new ArrayDeque<>());
        }
        // Initialize rings, biggest ring lowest;
        for (int i = numRings; i >= 1; --i) {
            pegs.getFirst().addFirst(i);
        }
        // Initialize result array;
        List<List<Integer>> result = new ArrayList<>();
        computeHanoiSteps(numRings, pegs, 0, 1, 2, result);
        return result;
    }

    private static void computeHanoiSteps(int numRingsToMove, ArrayList<ArrayDeque<Integer>> pegs,
                                          int fromPeg, int toPeg, int usePeg,
                                          List<List<Integer>> result) {
        if (numRingsToMove == 0) return;

        // Move n - 1 rings from "fromPeg" to "usePeg" (using toPeg as intermediary), leaving only 1 peg on fromPeg
        computeHanoiSteps(numRingsToMove - 1, pegs, fromPeg, usePeg, toPeg, result);
        // n - 1 pegs are now in usePeg, and toPeg is empty now. Move the remaining peg to toPeg, leaving fromPeg empty.
        result.add(List.of(fromPeg, toPeg));
        // Move the n - 1 rings from "usePeg" to "toPeg", using "fromPeg" (now empty) as intermediary.
        computeHanoiSteps(numRingsToMove - 1, pegs, usePeg, toPeg, fromPeg, result);
    }

    // 15.3
    public static List<List<Integer>> nQueens(int n) {
        List<List<Integer>> result = new ArrayList<>();
        solveNQueens(n, 0, new ArrayList<>(), result);
        return result;
    }

    private static void solveNQueens(int n, int row,
                                     List<Integer> colPlacementForRow,
                                     List<List<Integer>> result) {
        if (row == n) {
            // All queens are legally placed.
            result.add(new ArrayList<>(colPlacementForRow));
        } else {
            for (int col = 0; col < n; ++col) {
                colPlacementForRow.add(col);
                if (isValid(colPlacementForRow)) {
                    solveNQueens(n, row + 1, colPlacementForRow, result);
                }
                colPlacementForRow.removeLast();
            }
        }
    }

    private static boolean isValid(List<Integer> colPlacementForRow) {
        int rowID = colPlacementForRow.size() - 1;
        for (int i = 0; i < rowID; ++i) {
            int colDiff = Math.abs(colPlacementForRow.get(i) - colPlacementForRow.get(rowID));
            int rowDiff = rowID - i; // No need for abs as larger value is always rowID.
            boolean sameDiagonal = colDiff == rowDiff;
            if (colDiff == 0 || sameDiagonal) {
                return false;
            }
        }
        return true;
    }
}
