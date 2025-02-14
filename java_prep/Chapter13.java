package java_prep;

import java_prep.Chapter7.ListNode;

import java.util.*;
import java.util.stream.Collectors;

public class Chapter13 {
  public static void main(String[] args) {
    // 13.1
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

    // 13.3
    System.out.println("13.3 -> " + hIndex(Arrays.asList(2, 4, 6, 8, 10, 12)));

    // 13.6
    List<Event> events =
        List.of(
            new Event("E1", 1, 5),
            new Event("E2", 2, 7),
            new Event("E8", 4, 5),
            new Event("E2", 6, 10),
            new Event("E6", 8, 9),
            new Event("E9", 9, 17),
            new Event("E3", 11, 13),
            new Event("E7", 12, 15),
            new Event("E4", 14, 15));
    System.out.println("13.6 -> " + findMaxSimultaneousEvents(events));

    // 13.8
    List<Interval> intervals = new ArrayList<>(List.of(
            new Interval(0, false, 3, false),
            new Interval(1, true, 1, true),
            new Interval(2, true, 4, true),
            new Interval(3, true, 4, false),
            new Interval(5, true, 7, false),
            new Interval(7, true, 8, false),
            new Interval(8, true, 11, false),
            new Interval(9, false, 11, true),
            new Interval(12, true, 14, true),
            new Interval(12, false, 16, true),
            new Interval(13, false, 15, false),
            new Interval(16, false, 17, false)
    ));
    System.out.println("13.8 -> " + unionOfIntervals(intervals));

    // 13.9
    List<Person> people = Arrays.asList(
            new Person(14, "Greg"),
            new Person(12, "John"),
            new Person(11, "Andy"),
            new Person(13, "Jim"),
            new Person(12, "Phil"),
            new Person(13, "Bob"),
            new Person(13, "Chip"),
            new Person(14, "Tim"));
    groupByAge(people);
    System.out.println("13.9 -> " + people);

    // 13.11
    ListNode<Integer> list = Chapter7.makeLinkedList(new int[]{10, 8, 9, 6, 7, 4, 5, 1, 3, 2});
    Chapter7.printList("13.11 ", stableSort(list));
  }

  public static List<Integer> intersect(List<Integer> A, List<Integer> B) {
    List<Integer> intersectionAB = new ArrayList<>();
    int i = 0, j = 0;
    while (i < A.size() && j < B.size()) {
      if (A.get(i).equals(B.get(j)) && (i == 0 || !A.get(i).equals(A.get(i - 1)))) {
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
  public static void mergeTwoSortedArrays(
      List<Integer> A, int aCount, List<Integer> B, int bCount) {
    int a = aCount - 1, b = bCount - 1, writeIdx = aCount + bCount - 1;
    while (a >= 0 && b >= 0) {
      A.set(writeIdx--, A.get(a) > B.get(b) ? A.get(a--) : B.get(b--));
    }

    while (b >= 0) {
      A.set(writeIdx--, B.get(b--));
    }
  }

  // 13.3
  public static int hIndex(List<Integer> citations) {
    Collections.sort(citations);
    final int n = citations.size();
    for (int i = 0; i < n; ++i) {
      if (citations.get(i) >= n - i) {
        return n - i;
      }
    }
    return 0;
  }

  // 13.6
  public static int findMaxSimultaneousEvents(List<Event> A) {
    // Builds an array of all endpoints
    @SuppressWarnings("FuseStreamOperations") List<Endpoint> events =
        A.stream()
            .map(e -> List.of(new Endpoint(e.start, true), new Endpoint(e.finish, false)))
            .flatMap(List::stream)
            .collect(Collectors.toList());

    // Sorts the endpoint array according to the time, breaking ties by putting
    // start times before end times.
    events.sort(
        (a, b) -> {
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

  // 13.8
  public static List<Interval> unionOfIntervals(List<Interval> intervals) {
    // Empty input.
    if (intervals.isEmpty()) {
      return Collections.emptyList();
    }

    // Sort the intervals according to the left endpoints of intervals
    intervals.sort(
        (a, b) -> {
          if (a.left.val != b.left.val) {
            return a.left.val - b.left.val;
          }

          // Left endpoints are equal, so now see if one is closed and the other is open.
          // Closed intervals appear first.
          if (a.left.isClosed && !b.left.isClosed) {
            return -1;
          } else if (!a.left.isClosed && b.left.isClosed) {
            return 1;
          } else {
            return 0;
          }
        });

    // Start with the first interval.
    List<Interval> result = new ArrayList<>(List.of(intervals.getFirst()));

    // Because we have already sorted all the left intervals relative to each other, we can now
    // consider only left intervals relative to right ones.
    for (Interval i : intervals) {
      if (!result.isEmpty()
          && (i.left.val < result.getLast().right.val
              || (i.left.val == result.getLast().right.val
                  && (i.left.isClosed || result.getLast().right.isClosed)))) {
        // Check if we need to extend the right of the current interval (otherwise, it already
        // covers the interval we are considering.
        if (i.right.val > result.getLast().right.val
            || (i.right.val == result.getLast().right.val && i.right.isClosed)) {
          result.getLast().right = i.right;
        }
      } else {
        result.add(i);
      }
    }
    return result;
  }

  // 13.9
  public static void groupByAge(List<Person> people) {
    Map<Integer, Integer> ageToCount = new HashMap<>();

    for (Person p : people) {
      ageToCount.put(p.age(), ageToCount.getOrDefault(p.age(), 0) + 1);
    }

    int offset = 0;
    Map<Integer, Integer> ageToOffset = new HashMap<>();
    for (Map.Entry<Integer, Integer> kc : ageToCount.entrySet()) {
      ageToOffset.put(kc.getKey(), offset);
      offset += kc.getValue();
    }

    while (!ageToOffset.isEmpty()) {
      Map.Entry<Integer, Integer> from = ageToOffset.entrySet().iterator().next();
      Integer fromIndex = from.getValue();
      Integer toAge = people.get(fromIndex).age;  // object sitting where we want to move.
      Integer toIndex = ageToOffset.get(toAge);
      Collections.swap(people, from.getValue(), toIndex);
      // Use ageToCount to see when we are finished with a particular age.
      Integer count = ageToCount.get(toAge) - 1;
      ageToCount.put(toAge, count);
      if (count > 0) {
        ageToOffset.put(toAge, toIndex + 1);  // shift offset forward by 1;
      } else {
        ageToOffset.remove(toAge);
      }
    }
  }

  // 13.11
  public static ListNode<Integer> stableSort(ListNode<Integer> L) {
    // Base case; L is empty or a single node, nothing to do.
    if (L == null || L.next == null) {
      return L;
    }

    // Find the midpoint of L using a slow and fast pointer. Also a pointer to split
    // the list into two behind the slow pointer.
    ListNode<Integer> preSlow = null, slow = L, fast = L;
    while (fast != null && fast.next != null) {
      preSlow = slow;
      slow = slow.next;
      fast = fast.next.next;
    }

    // Split the list into two parts
    preSlow.next = null;

    // Merge the sorted lists, recursively.
    return Chapter7.mergeSorted(stableSort(L), stableSort(slow));
  }

  public record Person(int age, String name) {}

  public record Event(String tag, int start, int finish) {}

  record Endpoint(int time, boolean isStart) {}

  public static class Interval {
    public Interval.Endpoint left;
    public Interval.Endpoint right;

    public Interval(int left, boolean leftClosed, int right, boolean rightClosed) {
      this.left = new Endpoint(left, leftClosed);
      this.right = new Endpoint(right, rightClosed);
    }

    @Override
    public String toString() {
        return (left.isClosed ? "[" : "(") +
                left.val +
                ", " +
                right.val +
                (right.isClosed ? "]" : ")");
    }

    public static class Endpoint {
      public int val;
      public boolean isClosed;

      public Endpoint(int val, boolean isClosed) {
        this.val = val;
        this.isClosed = isClosed;
      }
    }
  }
}
