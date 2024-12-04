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

        // 12.2
        System.out.println("12.2 (a) -> " + isLetterConstructibleFromMagazine("aaaa", "aa"));
        System.out.println("12.2 (b) -> " + isLetterConstructibleFromMagazine("aab", "aab"));

        // 12.5
        List<String> paragraph = List.of("a", "b", "a", "c", "c", "d");
        System.out.println("12.5 -> " + findNearestRepetition(paragraph));
    }

    private static List<List<String>> findAnagrams(List<String> dictionary) {
        Map<String, List<String>> sortedStringToAnagrams = new HashMap<>();
        for (String s : dictionary) {
            String sortedStr =
                    Stream.of(s.split("")).sorted().collect(Collectors.joining());
            sortedStringToAnagrams.putIfAbsent(sortedStr, new ArrayList<>());
            sortedStringToAnagrams.get(sortedStr).add(s);
        }
        return sortedStringToAnagrams.values()
                .stream()
                .filter(group -> group.size() >= 2)
                .collect(Collectors.toList());
    }

    // 12.2
    private static boolean isLetterConstructibleFromMagazine(String letter, String magazine) {
        // Make a frequency table for characters in the letter.
        Map<Character, Long> charFrequencyForLetter = new HashMap<>();
        for (char l : letter.toCharArray()) {
            if (charFrequencyForLetter.containsKey(l)) {
                charFrequencyForLetter.put(l, charFrequencyForLetter.get(l) + 1);
            } else {
                charFrequencyForLetter.put(l, 1L);
            }
        }

        // Check if the character counts are satisfiable by the magazine
        for (char c : magazine.toCharArray()) {
            if (charFrequencyForLetter.isEmpty()) {
                break;
            }
            if (charFrequencyForLetter.containsKey(c)) {
                long countLeft = charFrequencyForLetter.get(c) - 1;
                if (countLeft == 0) {
                    charFrequencyForLetter.remove(c);
                } else {
                    charFrequencyForLetter.put(c, countLeft);
                }
            }
        }
        return charFrequencyForLetter.isEmpty();
    }

    // 12.5
    public static int findNearestRepetition(List<String> paragraph) {
        Map<String, Integer> entryToLastIndex = new HashMap<>();
        int nearestDist = Integer.MAX_VALUE;
        for (int i = 0; i < paragraph.size(); ++i) {
            if (entryToLastIndex.containsKey(paragraph.get(i))) {
                nearestDist = Math.min(nearestDist, i - entryToLastIndex.get(paragraph.get(i)));
            }
            entryToLastIndex.put(paragraph.get(i), i);
        }
        return nearestDist == Integer.MAX_VALUE ? -1 : nearestDist;
    }
}
