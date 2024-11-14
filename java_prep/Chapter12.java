package java_prep;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Chapter12 {
    public static void main(String[] args) {
        List<String> dictionary = new ArrayList<>(
                Arrays.asList("debitcard", "elvis", "silent", "badcredit",
                        "lives", "freedom", "listen", "levis", "money"));
        System.out.println(findAnagrams(dictionary));
    }

    private static List<List<String>> findAnagrams(List<String> dictionary) {
        Map<String, List<String>> sortedStringToAnagrams = new HashMap<>();
        for (String s : dictionary) {
            String sortedStr =
                    Stream.of(s.split("")).sorted().collect(Collectors.joining());
            sortedStringToAnagrams.putIfAbsent(sortedStr, new ArrayList<String>());
            sortedStringToAnagrams.get(sortedStr).add(s);
        }
        return sortedStringToAnagrams.values()
                .stream()
                .filter(group -> group.size() >= 2)
                .collect(Collectors.toList());
    }
}
