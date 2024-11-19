package java_prep;

import java.util.List;

public class Chapter16 {
    public static void main(String[] args) {
        // 16.1
        System.out.println("16.1 -> " + numCombinationsForFinalScore(4, List.of(1, 2, 3)));
    }

    public static int numCombinationsForFinalScore(int finalScore, List<Integer> plays) {
        int[][] combinations = new int[plays.size()][finalScore + 1];
        for (int i = 0; i < plays.size(); ++i) {
            combinations[i][0] = 1; // One way to reach 0 (None). Base case to sum up.
            for (int j = 1; j <= finalScore; ++j) {
                int withoutThisPlay =
                        i - 1 >= 0 ? combinations[i - 1][j] : 0;
                int withThisPlay =
                        j >= plays.get(i) ? combinations[i][j - plays.get(i)] : 0;
                combinations[i][j] = withThisPlay + withoutThisPlay;
            }
        }
        return combinations[plays.size() - 1][finalScore];
    }
}
