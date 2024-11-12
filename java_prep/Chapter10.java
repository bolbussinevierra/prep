package java_prep;

import java.util.*;

public class Chapter10 {
    private static class ArrayEntry {
        public int value;
        public int arrayId;

        public ArrayEntry(int value, int arrayId) {
            this.value = value;
            this.arrayId = arrayId;
        }
    }

    public static void main(String[] args) {
        ArrayList<String> strings = new ArrayList<>(
                Arrays.asList("1", "11", "111", "1111", "11111"));
        List<String> results = topK(3, strings.iterator());
        System.out.println(results);

        ArrayList<Integer> a1 = new ArrayList<>(Arrays.asList(3, 5, 7));
        ArrayList<Integer> a2 = new ArrayList<>(Arrays.asList(0, 6));
        ArrayList<Integer> a3 = new ArrayList<>(Arrays.asList(0, 6, 28));
        System.out.println("10.1 -> " + mergeSortedArrays(Arrays.asList(a1, a2, a3)));
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
}
