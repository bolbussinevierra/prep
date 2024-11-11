package java_prep;

import java.util.*;

public class Chapter10 {
    public static void main(String[] args) {
        ArrayList<String> strings = new ArrayList<>(
                Arrays.asList("1", "11", "111", "1111", "11111"));
        List<String> results = topK(3, strings.iterator());
        System.out.println(results);
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
