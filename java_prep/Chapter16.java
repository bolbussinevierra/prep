package java_prep;

import java.util.*;

public class Chapter16 {
  public static void main(String[] args) {
    // 16.1
    System.out.println("16.1 -> " + numCombinationsForFinalScore(4, List.of(1, 2, 3)));
    // 16.2
    System.out.println("16.2 -> " + editDistance("Carthorse", "Orchestra"));
    // 16.3
    System.out.println("16.3 -> " + numberOfWays(5, 5));
    // 16.4
    System.out.println("16.4 -> " + computeBinomialCoefficient(5, 2));
    // 16.5
    List<Integer> pattern = List.of(1, 3, 4, 6);
    List<List<Integer>> grid = List.of(List.of(1, 2, 3), List.of(3, 4, 5), List.of(5, 6, 7));
    System.out.println("16.5 -> " + isPatternContainedInGrid(grid, pattern));

    // 16.6
    List<Item> items = List.of(new Item(5, 60), new Item(3, 50), new Item(4, 70), new Item(2, 30));
    System.out.println("16.6 -> " + optimumKnapsack(items, 5));
    // 16.7
    System.out.println(
        "16.7 -> "
            + decomposeIntoDictionaryWords(
                "amanaplanacanal", Set.of("a", "man", "plan", "canal", "foo")));
    // 16.12
    System.out.println("16.12 -> " + longestNonDecreasingSubsequence(List.of(0, 8, 4, 12, 2, 10, 6, 14, 1, 9)));
  }

  // 16.1
  public static int numCombinationsForFinalScore(int finalScore, List<Integer> plays) {
    int[][] combinations = new int[plays.size()][finalScore + 1];
    for (int i = 0; i < plays.size(); ++i) {
      combinations[i][0] = 1; // One way to reach 0 (None). Base case to sum up.
      for (int j = 1; j <= finalScore; ++j) {
        int withoutThisPlay = i - 1 >= 0 ? combinations[i - 1][j] : 0;
        int withThisPlay = j >= plays.get(i) ? combinations[i][j - plays.get(i)] : 0;
        combinations[i][j] = withThisPlay + withoutThisPlay;
      }
    }
    return combinations[plays.size() - 1][finalScore];
  }

  // 16.2
  public static int editDistance(String a, String b) {
    int[][] m = new int[a.length()][b.length()];
    for (int[] row : m) {
      Arrays.fill(row, -1);
    }
    return editDistanceHelper(a, a.length() - 1, b, b.length() - 1, m);
  }

  private static int editDistanceHelper(String a, int aPos, String b, int bPos, int[][] m) {
    if (aPos < 0) return bPos + 1;
    if (bPos < 0) return aPos + 1;

    if (m[aPos][bPos] == -1) {
      if (a.charAt(aPos) == b.charAt(bPos)) {
        return editDistanceHelper(a, aPos - 1, b, bPos - 1, m);
      }

      // Make a - 1 and b - 1 match then substitute last character
      int substitute = editDistanceHelper(a, aPos - 1, b, bPos - 1, m);
      // Make a match b - 1, then add last b character to a
      int addLast = editDistanceHelper(a, aPos, b, bPos - 1, m);
      // make a - 1 match b, then delete last a character
      int deleteLast = editDistanceHelper(a, aPos - 1, b, bPos, m);
      m[aPos][bPos] = 1 + Math.min(substitute, Math.min(addLast, deleteLast));
    }
    return m[aPos][bPos];
  }

  // 16.3
  public static int numberOfWays(int n, int m) {
    return computeNumberOfWaysTo(n - 1, m - 1, new int[n][m]);
  }

  // 16.4
  public static int computeBinomialCoefficient(int n, int k) {
    return computeXChooseY(n, k, new int[n + 1][k + 1]);
  }

  private static int computeXChooseY(int x, int y, int[][] xChooseY) {
    if (y == 0 || x == y) return 1;

    if (xChooseY[x][y] == 0) {
      int withY = computeXChooseY(x - 1, y - 1, xChooseY);
      int withoutY = computeXChooseY(x - 1, y, xChooseY);
      xChooseY[x][y] = withY + withoutY;
    }

    return xChooseY[x][y];
  }

  private static int computeNumberOfWaysTo(int x, int y, int[][] numberOfWays) {
    if (x == 0 && y == 0) {
      return 1;
    }
    if (numberOfWays[x][y] == 0) {
      int waysTop = x == 0 ? 0 : computeNumberOfWaysTo(x - 1, y, numberOfWays);
      int waysLeft = y == 0 ? 0 : computeNumberOfWaysTo(x, y - 1, numberOfWays);
      numberOfWays[x][y] = waysLeft + waysTop;
    }
    return numberOfWays[x][y];
  }

  // 16.5
  public static boolean isPatternContainedInGrid(List<List<Integer>> grid, List<Integer> pattern) {
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid.get(i).size(); ++j) {
        if (isPatternSuffixContainedStartingAtXY(
            grid, i, j, pattern, /* offset= */ 0, new HashSet<>())) {
          return true;
        }
      }
    }
    return false;
  }

  private static boolean isPatternSuffixContainedStartingAtXY(
      List<List<Integer>> grid,
      int x,
      int y,
      List<Integer> pattern,
      int offset,
      Set<Attempt> previousAttempts) {
    if (pattern.size() == offset) return true;

    if (x < 0
        || x >= grid.size()
        || y < 0
        || y >= grid.get(x).size()
        || previousAttempts.contains(new Attempt(x, y, offset))
        || !grid.get(x).get(y).equals(pattern.get(offset))) {
      return false;
    }

    for (List<Integer> nextXY :
        List.of(List.of(x - 1, y), List.of(x + 1, y), List.of(x, y - 1), List.of(x, y + 1))) {
      if (isPatternSuffixContainedStartingAtXY(
          grid, nextXY.get(0), nextXY.get(1), pattern, offset + 1, previousAttempts)) {
        return true;
      }
    }

    previousAttempts.add(new Attempt(x, y, offset));
    return false;
  }

  // 16.6
  public static int optimumKnapsack(List<Item> items, int capacity) {
    // V[i][j] holds the optimum value when we chose from items i and have a
    // capacity j.
    int[][] V = new int[items.size()][capacity + 1];
    for (int[] v : V) {
      Arrays.fill(v, -1);
    }
    return optimumKnapsackHelper(items, items.size() - 1, capacity, V);
  }

  // 16.7
  public static List<String> decomposeIntoDictionaryWords(String domain, Set<String> dict) {
    // lastLength[i] != -1 indicates domain.substring(0, i + 1) has a valid decomposition, and the
    // length of the last string in the decomposition will be lastLength[i].
    int[] lastLength = new int[domain.length()];
    Arrays.fill(lastLength, -1);

    for (int i = 0; i < domain.length(); ++i) {
      if (dict.contains(domain.substring(0, i + 1))) {
        lastLength[i] = i + 1;
        continue;
      }

      for (int j = 0; j < i; ++j) {
        if (lastLength[j] != -1 && dict.contains(domain.substring(j + 1, i + 1))) {
          lastLength[i] = i - j;
          break;
        }
      }
    }

    List<String> decompositions = new ArrayList<>();
    if (lastLength[lastLength.length - 1] != -1) {
      int idx = domain.length() - 1;
      while (idx >= 0) {
        decompositions.add(domain.substring(idx + 1 - lastLength[idx], idx + 1));
        idx -= lastLength[idx];
      }
      Collections.reverse(decompositions);
    }
    return decompositions;
  }

  // 16.12
  private static int longestNonDecreasingSubsequence(List<Integer> A) {
    Integer[] maxLength = new Integer[A.size()];
    Arrays.fill(maxLength, 1);

    for (int i = 1; i < A.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (A.get(i) >= A.get(j)) {
          maxLength[i] = Math.max(maxLength[i], maxLength[j] + 1);
        }
      }
    }
    return Collections.max(List.of(maxLength));
  }

  private static int optimumKnapsackHelper(
      List<Item> items, int k, int availableCapacity, int[][] V) {
    if (k < 0) {
      // No items can be chosen.
      return 0;
    }

    if (V[k][availableCapacity] == -1) {
      int without = optimumKnapsackHelper(items, k - 1, availableCapacity, V);
      int with =
          availableCapacity < items.get(k).weight
              ? 0
              : items.get(k).value
                  + optimumKnapsackHelper(items, k - 1, availableCapacity - items.get(k).weight, V);
      V[k][availableCapacity] = Math.max(without, with);
    }
    return V[k][availableCapacity];
  }

  public record Item(int weight, int value) {}

  public record Attempt(int x, int y, int offset) {}
}
