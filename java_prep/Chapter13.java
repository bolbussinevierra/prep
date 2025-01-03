package java_prep;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Chapter13 {
    public static void main(String[] args) {
        List<Integer> A = new ArrayList<>(Arrays.asList(1, 2, 3, 5, 7));
        List<Integer> B = new ArrayList<>(Arrays.asList(2, 5, 9));
        System.out.println("13.1 -> " + intersect(A, B));

        // 13.2
        List<Integer> C = new ArrayList<>(7);
        // trailing zeros are placeholders; accounted for by size passed in.
        C.addAll(List.of(3, 13, 17, 0, 0, 0, 0));
        List<Integer> D = new ArrayList<>(Arrays.asList(3, 7, 11, 19));
        mergeTwoSortedArrays(C, 3, D, 4);
        System.out.println("13.2 -> " + C);

        // 13.6
        List<Event> events = List.of(
          new Event("E1", 1, 5),
          new Event("E2", 2, 7),
          new Event("E8", 4, 5),
          new Event("E2", 6, 10),
          new Event("E6", 8, 9),
          new Event("E9", 9, 17),
          new Event("E3", 11, 13),
          new Event("E7", 12, 15),
          new Event("E4", 14, 15)
        );
        System.out.println("13.6 -> " + findMaxSimultaneousEvents(events));
    }

    public static List<Integer> intersect(List<Integer> A, List<Integer> B) {
        List<Integer> intersectionAB = new ArrayList<>();
        int i = 0, j = 0;
        while (i < A.size() && j < B.size()) {
            if (A.get(i).equals(B.get(j)) &&
                    (i == 0 || !A.get(i).equals(A.get(i - 1)))) {
                intersectionAB.add(A.get(i));
                ++i;
                ++j;
            } else if (A.get(i) < B.get(j)) {
                ++i;
            } else {
                ++j;
            }
        }
        return intersectionAB;
    }

    // 13.2
    public static void mergeTwoSortedArrays(List<Integer> A, int aCount, List<Integer> B, int bCount) {
        int a = aCount - 1, b = bCount - 1, writeIdx = aCount + bCount - 1;
        while (a >= 0 && b >= 0) {
            A.set(writeIdx--, A.get(a) > B.get(b) ? A.get(a--) : B.get(b--));
        }

        while (b >= 0) {
            A.set(writeIdx--, B.get(b--));
        }
    }

    // 13.6
    public static int findMaxSimultaneousEvents(List<Event> A) {
        // Builds an array of all endpoints
        List<Endpoint> events = A.stream()
                .map(e -> List.of(new Endpoint(e.start, true),
                                  new Endpoint(e.finish, false)))
                .flatMap(List::stream)
        .collect(Collectors.toList());

        // Sorts the endpoint array according to the time, breaking ties by putting
        // start times before end times.
        events.sort((a, b) -> {
            if (a.time != b.time) {
                return Integer.compare(a.time, b.time);
            }
            // If times are equal, endpoint that starts at the interval comes first.
            return a.isStart && !b.isStart ? -1 : !a.isStart && b.isStart ? 1 : 0;
        });

        // Track the number of simultaneous events, and record the maximum number of
        // simultaneous events. Note that after the sort operation above, all the
        // starts come before all the ends which the below relies on.
        int maxOverlap = 0, currentOverlap = 0;
        for (Endpoint e : events) {
            if (e.isStart) {
                ++currentOverlap;
                maxOverlap = Math.max(currentOverlap, maxOverlap);
            } else {
                --currentOverlap;
            }
        }
        return maxOverlap;
    }

    public record Event(String tag, int start, int finish) {
    }

    record Endpoint(int time, boolean isStart) {
    }
}
