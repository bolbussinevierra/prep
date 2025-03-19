package java_prep;

import java.util.*;
import java.util.stream.IntStream;

public class Chapter17 {
    public static void main(String[] args) {
        System.out.println("TwoSum -> " + hasTwoSum(List.of(1, 5, 7, 9), 14));
        System.out.println("TwoSumSorted -> " + hasTwoSumSorted(List.of(1, 5, 7, 9), 14));
        // 17.1
        System.out.println("17.1a -> " + optimumTaskAssignments(Arrays.asList(5, 2, 1, 6, 4, 4)));
        System.out.println("17.1b -> " + optimumTaskAssignments(Arrays.asList(1, 8, 9, 10)));
        // 17.2
        System.out.println("17.2 -> " + minimumTotalWaitTime(Arrays.asList(1, 2, 3, 5)));
        // 17.3
        List<Interval> intervals = Arrays.asList(
                new Interval(1, 2),
                new Interval(2, 3),
                new Interval(3, 4),
                new Interval(2, 3),
                new Interval(3, 4),
                new Interval(4, 5)
        );
        System.out.println("17.3 -> " + findMinimumVisits(intervals));

        // 17.4
        System.out.println("17.4 -> " + hasThreeSum(List.of(1, 5, 7, 9), 15));

        // 17.5
        List<String> e = List.of("b", "a", "c", "a", "a", "b", "a", "a", "c", "a");
        System.out.println("17.5 -> " + majorityElement(e.iterator()));

        // 17.6
        List<Integer> g = List.of(50, 20, 5, 30, 25, 10, 10);
        List<Integer> d = List.of(900, 600, 200, 400, 600, 200, 100);
        System.out.println("17.6 -> " + findAmpleCity(g, d, 20));

        // 17.7
        System.out.println(
                "17.7 -> "
                        + getMaxTrappedWater(List.of(1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1)));

        // 17.8
        System.out.println(
                "17.8 -> " + calculateLargestRectangle(List.of(1, 4, 2, 5, 6, 3, 2, 6, 6, 5, 2, 1, 3)));
    }

    // 17.1
    private static List<PairedTasks> optimumTaskAssignments(List<Integer> taskDurations) {
        Collections.sort(taskDurations);
        List<PairedTasks> assignments = new ArrayList<>();
        for (int i = 0, j = taskDurations.size() - 1; i < j; ++i, --j) {
            assignments.add(new PairedTasks(taskDurations.get(i), taskDurations.get(j)));
        }
        return assignments;
    }

    // 17.2
    private static int minimumTotalWaitTime(List<Integer> serviceTimes) {
        Collections.sort(serviceTimes);

        // No wait time for first query.
        int totalWaitTime = 0;

        // Service times for item i adds wait time for subsequent items, except the i = last
        for (int i = 0; i < serviceTimes.size(); ++i) {
            int remainingItems = serviceTimes.size() - (i + 1);
            totalWaitTime += serviceTimes.get(i) * remainingItems;
        }
        return totalWaitTime;
    }

    // 17.3
    private static int findMinimumVisits(List<Interval> intervals) {
        // Sort intervals based on the right endpoint
        intervals.sort((i1, i2) -> Integer.compare(i1.right, i2.right));
        Integer lastVisitTime = Integer.MIN_VALUE;
        int numVisits = 0;
        for (Interval interval : intervals) {
            if (interval.left > lastVisitTime) {
                lastVisitTime = interval.right;
                ++numVisits;
            }
        }
        return numVisits;
    }

    private static int findAmpleCity(List<Integer> gallons, List<Integer> distances, int mpg) {
        // Cost to get to i+1 city from i
        List<Integer> cost =
                IntStream.range(0, gallons.size()).mapToObj(i -> distances.get(i) / mpg).toList();

        // Ensure there is a solution (total gas must at least be as much as total cost).
        int totalGas = gallons.stream().reduce(Integer::sum).orElse(0);
        int totalCost = cost.stream().reduce(Integer::sum).orElse(0);
        if (totalGas == 0 || totalCost == 0 || totalGas < totalCost) return -1;

        System.out.println("gas:  " + gallons);
        System.out.println("cost: " + cost);
        int numCities = gallons.size();
        int remainingGas = 0;
        int ampleCity = -1;
        for (int i = 0; i < numCities; ++i) {
            remainingGas += gallons.get(i) - cost.get(i);
            if (remainingGas < 0) {
                remainingGas = 0;
                ampleCity = i + 1;
            }
        }
        return ampleCity;
    }

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

    // 17.8
    public static int calculateLargestRectangle(List<Integer> heights) {
        Deque<Integer> pillarIndices = new ArrayDeque<>();
        int maxRectangleArea = 0;

        // Iterate to heights.size() instead of heights.size() - i, to uniformly handle computation by
        // rectangle area calculation.
        for (int i = 0; i <= heights.size(); ++i) {
            while (!pillarIndices.isEmpty() && isNewPillarOrEnd(heights, i, pillarIndices.peekFirst())) {
                int height = heights.get(pillarIndices.removeFirst());
                int width = pillarIndices.isEmpty() ? i : i - pillarIndices.peekFirst() - 1;
                maxRectangleArea = Math.max(maxRectangleArea, height * width);
            }
            pillarIndices.addFirst(i);
        }
        return maxRectangleArea;
    }

    private static boolean isNewPillarOrEnd(List<Integer> heights, int currIdx, int lastPillarIdx) {
        return currIdx >= heights.size() || heights.get(lastPillarIdx) >= heights.get(currIdx);
    }

    record Interval(int left, int right) {
    }

    record PairedTasks(int task1, int task2) {
    }

    //
}
