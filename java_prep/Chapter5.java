package java_prep;

import java.util.*;

public class Chapter5 {
  public static void main(String[] args) {
    // 5.1
    ArrayList<Integer> arr1 = new ArrayList<>(Arrays.asList(3, 4, 1, 0, -1));
    System.out.println("5.1 -> " + dutchFlags(2, arr1));

    // 5.2
    System.out.println("5.2 -> " + plusOne(new ArrayList<>(List.of(9, 9, 9))));

    // 5.3
    System.out.println("5.3 -> " + multiply(Arrays.asList(1, 2, 3), Arrays.asList(9, 8, 7)));

    // 5.4
    System.out.println("5.4 (a) -> " + canReachEnd(List.of(3, 3, 1, 0, 2, 0, 1)));
    System.out.println("5.4 (b) -> " + canReachEnd(List.of(3, 2, 0, 0, 2, 0, 1)));

    // 5.5
    System.out.println(
        "5.5 -> "
            + deletedDuplicates(new ArrayList<>(Arrays.asList(2, 3, 5, 5, 7, 11, 11, 11, 13))));

    // 5.6
    ArrayList<Double> arr2 =
        new ArrayList<>(
            Arrays.asList(310.0, 315.0, 275.0, 295.0, 260.0, 270.0, 290.0, 230.0, 255.0, 250.0));
    System.out.println("5.6 -> " + computeMaxProfit(arr2));

    // 5.7
    System.out.println(
        "5.7 -> "
            + buyAndSellAStockTwice(List.of(12.0, 11.0, 13.0, 9.0, 12.0, 8.0, 14.0, 13.0, 15.0)));
    // 5.8
    List<Integer> r = Arrays.asList(3, 2, 9, 1, 8, 5, 4, 6, 7);
    rearrange(r);
    System.out.print("5.8 -> ");
    System.out.println(r);

    // 5.9
    System.out.println("5.9 -> " + generatePrimes(50));

    // 5.10
    List<Character> arr4 = Arrays.asList('a', 'b', 'c', 'd');
    applyPermutation(Arrays.asList(2, 0, 1, 3), arr4);
    System.out.println("5.10 -> " + arr4);

    // 5.12
    ArrayList<Integer> arr3 = new ArrayList<>(Arrays.asList(3, 5, 7, 11));
    randomSampling(3, arr3);
    System.out.println("5.12 -> " + arr3);

    // 5.15
    System.out.println("5.15 -> " + randomSubset(6, 5));

    // 5.17
    ArrayList<List<Integer>> sudoku =
        new ArrayList<>() {
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
    matrix2.add(new ArrayList<>(Arrays.asList(1, 2, 3, 4)));
    matrix2.add(new ArrayList<>(Arrays.asList(5, 6, 7, 8)));
    matrix2.add(new ArrayList<>(Arrays.asList(9, 10, 11, 12)));
    matrix2.add(new ArrayList<>(Arrays.asList(13, 14, 15, 16)));
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

  // 5.3
  public static List<Integer> multiply(List<Integer> num1, List<Integer> num2) {
    final int sign = num1.getFirst() < 0 ^ num2.getFirst() < 0 ? -1 : 1;
    num1.set(0, Math.abs(num1.getFirst()));
    num2.set(0, Math.abs(num2.getFirst()));

    List<Integer> result = new ArrayList<>(Collections.nCopies(num1.size() + num2.size(), 0));
    for (int i = num1.size() - 1; i >= 0; --i) {
      for (int j = num2.size() - 1; j >= 0; --j) {
        result.set(i + j + 1, result.get(i + j + 1) + num1.get(i) * num2.get(j));
        result.set(i + j, result.get(i + j) + result.get(i + j + 1) / 10);
        result.set(i + j + 1, result.get(i + j + 1) % 10);
      }
    }
    // Remove the leading zeroes.
    int firstNonZero = 0;
    while (firstNonZero < result.size() && result.get(firstNonZero) == 0) {
      ++firstNonZero;
    }
    result = result.subList(firstNonZero, result.size());
    if (result.isEmpty()) {
      return List.of(0);
    }
    result.set(0, result.getFirst() * sign);
    return result;
  }

  // 5.4
  public static boolean canReachEnd(List<Integer> maxSteps) {
    int maxReachSoFar = 0;
    int lastIndex = maxSteps.size() - 1;
    // Consider i within reach so far, and only if we have already proved we can reach
    // the last index.
    for (int i = 0; i <= maxReachSoFar && maxReachSoFar < lastIndex; ++i) {
      maxReachSoFar = Math.max(maxReachSoFar, i + maxSteps.get(i));
    }
    return maxReachSoFar >= lastIndex;
  }

  // 5.5
  // returns valid count of elements
  public static int deletedDuplicates(List<Integer> A) {
    if (A.isEmpty()) return 0;

    int writeIdx = 1;
    for (int i = 1; i < A.size(); ++i) {
      if (!A.get(writeIdx - 1).equals(A.get(i))) {
        A.set(writeIdx++, A.get(i));
      }
    }
    System.out.println(A);
    return writeIdx;
  }

  // 5.7
  public static double buyAndSellAStockTwice(List<Double> prices) {
    List<Double> firstBuyProfits = new ArrayList<>();
    double minBuyPriceSoFar = Double.MAX_VALUE;
    double maxTotalProfit = 0.0;

    // First: calculate max profit for first buy; for each index, we calculate max profit
    // selling on that day.
    for (int i = 0; i < prices.size(); ++i) {
      minBuyPriceSoFar = Math.min(minBuyPriceSoFar, prices.get(i));
      maxTotalProfit = Math.max(maxTotalProfit, prices.get(i) - minBuyPriceSoFar);
      firstBuyProfits.add(maxTotalProfit);
    }

    // Second: working backwards, calculate max profit for second buy. For each index, we
    // calculate max profit from buying on that day and selling on a future date.
    double maxSellPriceSoFar = Double.MIN_VALUE;
    for (int i = prices.size() - 1; i > 0; --i) {
      maxSellPriceSoFar = Math.max(maxSellPriceSoFar, prices.get(i));
      maxTotalProfit =
          Math.max(maxTotalProfit, maxSellPriceSoFar - prices.get(i) + firstBuyProfits.get(i));
    }
    return maxTotalProfit;
  }

  // 5.8
  public static void rearrange(List<Integer> A) {
    for (int i = 1; i < A.size(); ++i) {
      if (((i % 2) == 0 && A.get(i - 1) < A.get(i)) || ((i % 2) != 0 && A.get(i - 1) > A.get(i))) {
        Collections.swap(A, i - 1, i);
      }
    }
  }

  // 5.9
  public static List<Integer> generatePrimes(int n) {
    List<Integer> primes = new ArrayList<>();
    List<Boolean> isPrime = new ArrayList<>(Collections.nCopies(n + 1, true));
    isPrime.set(0, false);
    isPrime.set(0, false);
    for (int p = 2; p <= n; ++p) {
      if (isPrime.get(p)) {
        primes.add(p);
        // Sieve out multiples of the prime.
        for (int i = p * 2; i <= n; i += p) {
          isPrime.set(i, false);
        }
      }
    }
    return primes;
  }

  // 5.10
  public static void applyPermutation(List<Integer> perm, List<Character> A) {
    for (int i = 0; i < A.size(); ++i) {
      while (perm.get(i) != i) {
        Collections.swap(A, i, perm.get(i));
        Collections.swap(perm, i, perm.get(i));
      }
    }
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

  // 5.15
  public static List<Integer> randomSubset(int n, int k) {
    Map<Integer, Integer> changedElements = new HashMap<>();
    Random randIdxGen = new Random();
    for (int i = 0; i < k; ++i) {
      // Generate random int in [i, n - 1].
      int randIdx = i + randIdxGen.nextInt(n - i);
      Integer ptr1 = changedElements.get(randIdx);
      Integer ptr2 = changedElements.get(i);

      if (ptr1 == null && ptr2 == null) {
        changedElements.put(randIdx, i);
        changedElements.put(i, randIdx);
      } else if (ptr1 == null && ptr2 != null) {
        changedElements.put(randIdx, ptr2);
        changedElements.put(i, randIdx);
      } else if (ptr1 != null && ptr2 == null) {
        changedElements.put(i, ptr1);
        changedElements.put(randIdx, i);
      } else {
        changedElements.put(i, ptr1);
        changedElements.put(randIdx, ptr2);
      }
    }

    List<Integer> result = new ArrayList<>(k);
    for (int i = 0; i < k; ++i) {
      result.add(changedElements.get(i));
    }
    return result;
  }

  // 5.18 (uses neet code Spiral Matrix II solution)
  public static List<Integer> spiralOrder(List<List<Integer>> matrix) {
    List<Integer> spiralOrder = new ArrayList<>();
    int left = 0, right = matrix.size() - 1;
    int top = 0, bottom = matrix.size() - 1;

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
      if (hasDuplicate(partialAssignment, i, i + 1, 0, partialAssignment.size())) {
        return false;
      }
    }
    // Check column constraints.
    for (int j = 0; j < partialAssignment.size(); ++j) {
      if (hasDuplicate(partialAssignment, 0, partialAssignment.size(), j, j + 1)) {
        return false;
      }
    }
    // Check region constraints.
    int regionSize = (int) Math.sqrt(partialAssignment.size());
    for (int I = 0; I < regionSize; ++I) {
      for (int J = 0; J < regionSize; ++J) {
        if (hasDuplicate(
            partialAssignment,
            regionSize * I,
            regionSize * (I + 1),
            regionSize * J,
            regionSize * (J + 1))) {
          return false;
        }
      }
    }
    return true;
  }

  private static boolean hasDuplicate(
      List<List<Integer>> partialAssignment, int startRow, int endRow, int startCol, int endCol) {
    // [1, 9], +1 due to 0 indexed.
    boolean[] isPresent = new boolean[partialAssignment.size() + 1];
    for (int i = startRow; i < endRow; ++i) {
      for (int j = startCol; j < endCol; ++j) {
        if (partialAssignment.get(i).get(j) != 0 && isPresent[partialAssignment.get(i).get(j)]) {
          return true;
        }
        isPresent[partialAssignment.get(i).get(j)] = true;
      }
    }
    return false;
  }
}
