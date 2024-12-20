package java_prep;

import java.util.*;

public class Chapter15 {
  public static void main(String[] args) {
    System.out.println("15.1 -> " + computeHanoi(3, 3));
    System.out.println("15.3 -> " + nQueens(4));
    System.out.println("15.4 (swap) -> " + permutationsSwap(new ArrayList<>(List.of(1, 2, 3))));
    System.out.println("15.4 (backtracking) -> " + permutationsBt(new ArrayList<>(List.of(1, 2, 3))));
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

  private static void computeHanoiSteps(
      int numRingsToMove,
      ArrayList<ArrayDeque<Integer>> pegs,
      int fromPeg,
      int toPeg,
      int usePeg,
      List<List<Integer>> result) {
    if (numRingsToMove == 0) return;

    // Move n - 1 rings from "fromPeg" to "usePeg" (using toPeg as intermediary), leaving only 1 peg
    // on fromPeg
    computeHanoiSteps(numRingsToMove - 1, pegs, fromPeg, usePeg, toPeg, result);
    // n - 1 pegs are now in usePeg, and toPeg is empty now. Move the remaining peg to toPeg,
    // leaving fromPeg empty.
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

  private static void solveNQueens(
      int n, int row, List<Integer> colPlacementPerRow, List<List<Integer>> result) {
    if (row == n) {
      // All queens are legally placed.
      result.add(new ArrayList<>(colPlacementPerRow));
    } else {
      for (int col = 0; col < n; ++col) {
        colPlacementPerRow.add(col);
        if (isValid(colPlacementPerRow)) {
          solveNQueens(n, row + 1, colPlacementPerRow, result);
        }
        colPlacementPerRow.removeLast();
      }
    }
  }

  private static boolean isValid(List<Integer> colPlacementPerRow) {
    int rowID = colPlacementPerRow.size() - 1;
    for (int i = 0; i < rowID; ++i) {
      int colDiff = Math.abs(colPlacementPerRow.get(i) - colPlacementPerRow.get(rowID));
      int rowDiff = rowID - i; // No need for abs as larger value is always rowID.
      boolean sameDiagonal = colDiff == rowDiff;
      if (colDiff == 0 || sameDiagonal) {
        return false;
      }
    }
    return true;
  }

  // 15.4
  public static List<List<Integer>> permutationsSwap(List<Integer> A) {
    List<List<Integer>> result = new ArrayList<>();
    directedPermutationsSwap(0, A, result);
    return result;
  }

  public static List<List<Integer>> permutationsBt(List<Integer> A) {
    List<List<Integer>> results = new ArrayList<>();
    List<Integer> permutation = new ArrayList<>();
    directedPermutationsBt(A, results, permutation);
    return results;
  }

  private static void directedPermutationsBt(
          List<Integer> A,
          List<List<Integer>> result,
          List<Integer> permutation) {
    if (permutation.size() == A.size()) {
      result.add(List.copyOf(permutation));
    }

    for (int i = 0; i < A.size(); ++i) {
      if (permutation.contains(A.get(i))) {
        continue;
      }
      permutation.add(A.get(i));
      directedPermutationsBt(A, result, permutation);
      permutation.removeLast();
    }


  }

  private static void directedPermutationsSwap(
          int i, List<Integer> A, List<List<Integer>> result) {
    if (i == A.size() - 1) {
      result.add(new ArrayList<>(A));
      return;
    }

    for (int j = i; j < A.size(); ++j) {
      Collections.swap(A, i, j);
      directedPermutationsSwap(i + 1, A, result);
      Collections.swap(A, i, j);
    }
  }
}
