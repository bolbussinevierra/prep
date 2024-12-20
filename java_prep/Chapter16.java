package java_prep;

import java.util.Arrays;
import java.util.List;

public class Chapter16 {
  public static void main(String[] args) {
    // 16.1
    System.out.println("16.1 -> " + numCombinationsForFinalScore(4, List.of(1, 2, 3)));
    // 16.2
    System.out.println("16.2 -> " + editDistance("Carthorse", "Orchestra"));
    // 16.3
    System.out.println("16.3 -> " + numberOfWays(5, 5));
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
}
