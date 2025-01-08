package java_prep;

import java.util.HashSet;
import java.util.Iterator;
import java.util.List;

public class Chapter17 {
  public static void main(String[] args) {
    System.out.println("TwoSum -> " + hasTwoSum(List.of(1, 5, 7, 9), 14));
    System.out.println("TwoSumSorted -> " + hasTwoSumSorted(List.of(1, 5, 7, 9), 14));

    // 17.4
    System.out.println("17.4 -> " + hasThreeSum(List.of(1, 5, 7, 9), 15));

    // 17.5
    List<String> e = List.of("b", "a", "c", "a", "a", "b", "a", "a", "c", "a");
    System.out.println("17.5 -> " + majorityElement(e.iterator()));

    //        // 17.6
    //        List<Integer> g = List.of(50, 20, 5, 30, 25, 10 ,10);
    //        List<Integer> d = List.of(900, 600, 200, 400, 600, 200, 100);
    //        System.out.println("17.6 -> " + findAmpleCity(g, d, 20));

    // 17.7
    System.out.println(
        "17.7 -> "
            + getMaxTrappedWater(List.of(1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1)));
  }

  //    private static int findAmpleCity(List<Integer> gallons, List<Integer> distances, int mpg) {
  //        List<Integer> cost = IntStream.range(0, gallons.size())
  //                .mapToObj(i -> gallons.get(i) - (distances.get(i)/mpg))
  //                .collect(Collectors.toList());
  //
  //        int numCities = gallons.size();
  //        int remainingGas = 0;
  //        int currentSum = 0;
  //        int ampleCity = -1;
  //        for (int i = 0; i < numCities; ++i) {
  //            remainingGas += gallons.get(i) - cost.get(i);
  //            if (remainingGas < currentSum) {
  //                currentSum = remainingGas ;
  //                ampleCity = i+1;
  //            }
  //        }
  //        return ampleCity;
  //    }
  private static boolean hasTwoSum(List<Integer> a, int s) {
    HashSet<Integer> prev = new HashSet<>();
    for (int i : a) {
      int diff = s - i;
      if (prev.contains(diff)) {
        return true;
      }
      prev.add(i);
    }
    return false;
  }

  private static boolean hasTwoSumSorted(List<Integer> a, int s) {
    int l = 0, r = a.size() - 1;
    while (l < r) {
      int currentSum = a.get(l) + a.get(r);
      if (currentSum == s) {
        return true;
      } else if (currentSum > s) {
        --r;
      } else {
        ++l;
      }
    }
    return false;
  }

  private static boolean hasThreeSum(List<Integer> a, int s) {
    return a.stream().anyMatch(i -> hasTwoSum(a, s - i));
  }

  // 17.5
  private static String majorityElement(Iterator<String> stream) {
    String candidate = "";
    int candidateCount = 0;
    while (stream.hasNext()) {
      String it = stream.next();
      if (candidateCount == 0) {
        candidate = it;
        candidateCount = 1;
      } else if (candidate.equals(it)) {
        candidateCount++;
      } else {
        candidateCount--;
      }
    }
    return candidate;
  }

  // 17.7
  public static int getMaxTrappedWater(List<Integer> heights) {
    int left = 0, right = heights.size() - 1, maxWater = 0;
    while (left < right) {
      int width = right - left;
      maxWater = Math.max(maxWater, width * Math.min(heights.get(left), heights.get(right)));
      if (heights.get(left) > heights.get(right)) {
        --right;
      } else {
        ++left;
      }
    }
    return maxWater;
  }
}
