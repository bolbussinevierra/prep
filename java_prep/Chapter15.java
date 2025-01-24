package java_prep;

import java.util.*;

public class Chapter15 {
  private static final int EMPTY_ENTRY = 0;

  public static void main(String[] args) {
    System.out.println("15.1 -> " + computeHanoi(3, 3));
    System.out.println("15.3 -> " + nQueens(4));
    System.out.println("15.4 (swap) -> " + permutationsSwap(new ArrayList<>(List.of(1, 2, 3))));
    System.out.println(
        "15.4 (backtracking) -> " + permutationsBt(new ArrayList<>(List.of(1, 2, 3))));
    System.out.println("15.5 (backtracking) -> " + generatePowerSetRecursive(List.of(1, 2, 3)));
    System.out.println("15.5 (iterative) -> " + generatePowerSetIterative(List.of(1, 2, 3)));

    System.out.println("15.7 -> " + generateParens(3));

    // 15.10
    List<List<Integer>> partialAssignment =
        List.of(
            Arrays.asList(5, 3, 0, 0, 7, 0, 0, 0, 0),
            Arrays.asList(6, 0, 0, 1, 9, 5, 0, 0, 0),
            Arrays.asList(0, 9, 8, 0, 0, 0, 0, 6, 0),
            Arrays.asList(8, 0, 0, 0, 6, 0, 0, 0, 3),
            Arrays.asList(4, 0, 0, 8, 0, 3, 0, 0, 1),
            Arrays.asList(7, 0, 0, 0, 2, 0, 0, 0, 6),
            Arrays.asList(0, 6, 0, 0, 0, 0, 2, 8, 0),
            Arrays.asList(0, 0, 0, 4, 1, 9, 0, 0, 5),
            Arrays.asList(0, 0, 0, 0, 8, 0, 0, 7, 9));
    System.out.println("15.10 [---");
    System.out.println(solveSudoku(partialAssignment));
    System.out.println("---]");

    // 15.11
    grayCode(3);
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

  // 15.5
  public static List<List<Integer>> generatePowerSetRecursive(List<Integer> inputSet) {
    List<List<Integer>> powerSet = new ArrayList<>();
    directedPowerSetRecursive(inputSet, 0, new ArrayList<>(), powerSet);
    return powerSet;
  }

  public static List<List<Integer>> generatePowerSetIterative(List<Integer> inputSet) {
    List<List<Integer>> powerSet = new ArrayList<>();
    for (int i = 0; i < (1 << inputSet.size()); ++i) {
      int bitArray = i;
      List<Integer> subset = new ArrayList<>();
      while (bitArray != 0) {
        subset.add(inputSet.get(Integer.numberOfTrailingZeros(bitArray)));
        bitArray &= bitArray - 1;
      }
      powerSet.add(subset);
    }
    return powerSet;
  }

  // 15.7
  public static List<String> generateParens(int numPairs) {
    List<String> result = new ArrayList<>();
    directedGenerateParens(numPairs, numPairs, "", result);
    return result;
  }

  private static void directedGenerateParens(
      int openRemaining, int closedRemaining, String generated, List<String> result) {
    if (closedRemaining == 0) {
      result.add(generated);
      return;
    }
    if (openRemaining > 0) {
      directedGenerateParens(openRemaining - 1, closedRemaining, generated + "(", result);
    }

    if (closedRemaining > openRemaining) {
      directedGenerateParens(openRemaining, closedRemaining - 1, generated + ")", result);
    }
  }

  // 15.10
  public static boolean solveSudoku(List<List<Integer>> partialAssignment) {
    if (solvePartialSudoku(0, 0, partialAssignment)) {
      partialAssignment.forEach(System.out::println);
      return true;
    }
    return false;
  }

  // 15.11
  public static List<Integer> grayCode(int numBits) {
    if (numBits == 0) return new ArrayList<>(List.of(0));

    // These implicitly begin with 0 at bit-index (numBIts - 1)
    List<Integer> grayCodeNumBitsMinus1 = grayCode(numBits - 1);

    int leadingBitsOne = 1 << (numBits - 1);
    // Process the reverse order to achieve reflection of grayCodeNumBitsMinus1
    for (int i = grayCodeNumBitsMinus1.size() - 1; i >= 0; --i) {
      grayCodeNumBitsMinus1.add(leadingBitsOne | grayCodeNumBitsMinus1.get(i));
    }
    System.out.println("numBits = " + numBits);
    grayCodeNumBitsMinus1.forEach(i -> System.out.print(Integer.toBinaryString(i) + " "));
    System.out.print("\n");
    return grayCodeNumBitsMinus1;
  }


  private static boolean solvePartialSudoku(int i, int j, List<List<Integer>> partialAssignment) {
    if (i == partialAssignment.size()) {
      // Start new row
      i = 0;
      if (++j == partialAssignment.get(i).size()) {
        return true; // Entire matrix has been filled without conflict.
      }
    }

    // Skip non-empty entries.
    if (partialAssignment.get(i).get(j) != EMPTY_ENTRY) {
      return solvePartialSudoku(i + 1, j, partialAssignment);
    }

    for (int val = 1; val <= partialAssignment.size(); ++val) {
      if (validToAddVal(partialAssignment, i, j, val)) {
        partialAssignment.get(i).set(j, val);
        if (solvePartialSudoku(i + 1, j, partialAssignment)) {
          return true;
        }
      }
    }

    partialAssignment.get(i).set(j, EMPTY_ENTRY); // Undo assignment for backtracking.
    return false;
  }

  private static boolean validToAddVal(
      List<List<Integer>> partialAssignment, int i, int j, int val) {
    // Check row constraints.
    if (partialAssignment.stream().anyMatch(row -> row.get(j) == val)) {
      return false;
    }

    // Check column constraints.
    if (partialAssignment.get(i).contains(val)) {
      return false;
    }

    // Check region constraints.
    int regionSize = (int) Math.sqrt(partialAssignment.size());
    int I = i / regionSize, J = j / regionSize;
    for (int a = 0; a < regionSize; ++a) {
      for (int b = 0; b < regionSize; ++b) {
        if (val == partialAssignment.get(regionSize * I + a).get(regionSize * J + b)) {
          return false;
        }
      }
    }
    return true;
  }

  private static void directedPowerSetRecursive(
      List<Integer> inputSet,
      int select,
      List<Integer> selectedSoFar,
      List<List<Integer>> powerSet) {
    if (select == inputSet.size()) {
      powerSet.add(new ArrayList<>(selectedSoFar));
      return;
    }

    // Include.
    selectedSoFar.add(inputSet.get(select));
    directedPowerSetRecursive(inputSet, select + 1, selectedSoFar, powerSet);

    // Exclude.
    selectedSoFar.removeLast();
    directedPowerSetRecursive(inputSet, select + 1, selectedSoFar, powerSet);
  }

  private static void directedPermutationsBt(
      List<Integer> A, List<List<Integer>> result, List<Integer> permutation) {
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

  private static void directedPermutationsSwap(int i, List<Integer> A, List<List<Integer>> result) {
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
