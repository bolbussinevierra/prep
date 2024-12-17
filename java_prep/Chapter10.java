package java_prep;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Chapter10 {
    private static class ArrayEntry {
        public int value;
        public int arrayId;

        public ArrayEntry(int value, int arrayId) {
            this.value = value;
            this.arrayId = arrayId;
        }
    }

    private static class Star implements Comparable<Star> {
        private final double x, y, z;

        public Star(double x, double y, double z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public double distance() {
            return Math.sqrt(x * x + y * y + z * z);
        }

        @Override
        public int compareTo(Star that) {
            return Double.compare(this.distance(), that.distance());
        }

        @Override
        public String toString() {
            return String.format("(%.1f, %.1f, %.1f)", x, y, z);
        }
    }

    public static void main(String[] args) {
        ArrayList<String> strings = new ArrayList<>(
                Arrays.asList("1", "11", "111", "1111", "11111"));
        List<String> results = topK(3, strings.iterator());
        System.out.println(results);

        //10.1
        ArrayList<Integer> a1 = new ArrayList<>(Arrays.asList(3, 5, 7));
        ArrayList<Integer> a2 = new ArrayList<>(Arrays.asList(0, 6));
        ArrayList<Integer> a3 = new ArrayList<>(Arrays.asList(0, 6, 28));
        System.out.println("10.1 -> " + mergeSortedArrays(Arrays.asList(a1, a2, a3)));

        // 10.3
        List<Integer> l1 = List.of(3, -1, 2, 6, 4, 5, 8);
        System.out.println("10.3 -> " + sortApproximatelySorted(l1.iterator(), 2));

        // 10.4
        List<Star> stars = List.of(new Star(1, 1, 1), new Star(2, 2, 2),
                new Star(3, 3, 3), new Star(4, 4, 4));
        System.out.println("10.4 -> " + findClosestKStars(stars.iterator(), 2));
    }

    // 10.1
    public static List<Integer> mergeSortedArrays(List<List<Integer>> sortedArrays) {
        List<Iterator<Integer>> iters = new ArrayList<>(sortedArrays.size());
        for (List<Integer> l : sortedArrays) {
            iters.add(l.iterator());
        }
        PriorityQueue<ArrayEntry> minHeap = new PriorityQueue<>(
                sortedArrays.size(), (o1, o2) -> Integer.compare(o1.value, o2.value));
        // Add the first element of each sorted array to minHeap
        for (int i = 0; i < iters.size(); ++i) {
            if (iters.get(i).hasNext()) {
                minHeap.add(new ArrayEntry(iters.get(i).next(), i));
            }
        }

        List<Integer> result = new ArrayList<>();
        while (!minHeap.isEmpty()) {
            ArrayEntry headEntry = minHeap.poll();
            result.add(headEntry.value);
            int arrayId = headEntry.arrayId;
            if (iters.get(headEntry.arrayId).hasNext()) {
                minHeap.add(new ArrayEntry(iters.get(arrayId).next(), arrayId));
            }
        }
        return result;
    }

    public static List<String> topK(int k, Iterator<String> iter) {
        PriorityQueue<String> minHeap = new PriorityQueue<>(
                k, (s1, s2) -> Integer.compare(s1.length(), s2.length()));
        while (iter.hasNext()) {
            minHeap.add(iter.next());
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }
        return new ArrayList<>(minHeap);
    }
    // 10.3
    private static List<Integer> sortApproximatelySorted(Iterator<Integer> s, int k) {
        PriorityQueue<Integer> minH = new PriorityQueue<>();

        // Load k items in minHeap
        for (int i = 0; i < k && s.hasNext(); ++i) {
            minH.add(s.next());
        }

        // Add 1 item to go to k+1 then start removing items in smallest->largest order
        List<Integer> result = new ArrayList<>();
        while (s.hasNext()) {
            minH.add(s.next());
            result.add(minH.remove());
        }

        // Remaining tail of elements lef tin minHeap
        result.addAll(Stream.generate(minH::remove)
                .limit(minH.size())
                .toList());
        return result;
    }

    // 10.4
    private static List<Star> findClosestKStars(Iterator<Star> stars, int k) {
        // Max heap to store the k closest stars seen right now
        PriorityQueue<Star> maxHeap = new PriorityQueue<>(k, Collections.reverseOrder());
        // Store all the stars in the heap, evicting largest at k+1
        while (stars.hasNext()) {
            maxHeap.add(stars.next());
            if (maxHeap.size() == k + 1) {
                maxHeap.remove();
            }
        }

        return Stream.generate(maxHeap::remove)
                .limit(maxHeap.size())
                .collect(Collectors.toList());

    }
}
