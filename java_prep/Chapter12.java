package java_prep;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Chapter12 {
  public static void main(String[] args) {
    List<String> dictionary =
        new ArrayList<>(
            Arrays.asList(
                "debitcard",
                "elvis",
                "silent",
                "badcredit",
                "lives",
                "freedom",
                "listen",
                "levis",
                "money"));
    System.out.println(findAnagrams(dictionary));
    // 12.1
    System.out.println("12.1 (a) ->" + canFormPalindrome("rotator"));
    System.out.println("12.1 (b) ->" + canFormPalindrome("rotaator"));

    // 12.2
    System.out.println("12.2 (a) -> " + isLetterConstructibleFromMagazine("aaaa", "aa"));
    System.out.println("12.2 (b) -> " + isLetterConstructibleFromMagazine("aab", "aab"));

    // 12.5
    List<String> paragraph = List.of("a", "b", "a", "c", "c", "d");
    System.out.println("12.5 -> " + findNearestRepetition(paragraph));

    // 12.6
    List<String> paragraph2 =
        List.of(
            "apple", "banana", "apple", "apple", "dog", "cat", "apple", "dog", "banana", "apple",
            "cat", "dog");
    Set<String> cover = Set.of("banana", "cat");
    System.out.println("12.6 -> " + findSmallestSubarrayCoveringSet(paragraph2, cover));

    // 12.7
    List<String> paragraph3 = List.of("apple", "banana", "cat", "apple");
    List<String> cover3 = List.of("banana", "apple");
    System.out.println("12.7 -> " + findSmallestSequentiallyCoveringSubset(paragraph3, cover3));

    // 12.8
    List<Integer> entries = List.of(6, 19, 6, 5, 20, 23, 5, 14, 23, 5);
    System.out.println("12.8 -> " + longestSubarrayWithoutDuplicateEntries(entries));

    // 12.9
    List<Integer> A = List.of(10, 5, 3, 11, 6, 100, 4);
    System.out.println("12.9 -> " + longestContainedRange(A));
  }

  // 12.1
  private static boolean canFormPalindrome(String s) {
    Set<Character> charsWithOddFrequency = new HashSet<>();
    for (Character c : s.toCharArray()) {
      if (charsWithOddFrequency.contains(c)) {
        charsWithOddFrequency.remove(c);
      } else {
        charsWithOddFrequency.add(c);
      }
    }

    return charsWithOddFrequency.size() <= 1;
  }

  private static List<List<String>> findAnagrams(List<String> dictionary) {
    Map<String, List<String>> sortedStringToAnagrams = new HashMap<>();
    for (String s : dictionary) {
      String sortedStr = Stream.of(s.split("")).sorted().collect(Collectors.joining());
      sortedStringToAnagrams.putIfAbsent(sortedStr, new ArrayList<>());
      sortedStringToAnagrams.get(sortedStr).add(s);
    }
    return sortedStringToAnagrams.values().stream()
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

  // 12.6
  private static Subarray findSmallestSubarrayCoveringSet(
      List<String> paragraph, Set<String> keywords) {

    // Keywords to cover.
    Map<String, Long> keywordsToCover =
        keywords.stream()
            .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));

    // Sliding window tracking the characters in the current view.
    Map<String, Long> slidingWindow = new HashMap<>();

    int remainingToCover = keywordsToCover.size();

    Subarray result = new Subarray();
    int l = 0;
    for (int r = 0; r < paragraph.size(); ++r) {
      String wr = paragraph.get(r);
      // Slide the window front and if we encounter a relevant word, update the count
      // of words remaining to cover.
      if (keywordsToCover.containsKey(wr)) {
        slidingWindow.put(wr, slidingWindow.getOrDefault(wr, 0L) + 1);

        if (slidingWindow.get(wr) >= (keywordsToCover.get(wr))) {
          --remainingToCover;
        }
      }

      while (remainingToCover == 0) {
        if (result.notSet() || result.longerThan(l, r)) {
          result = new Subarray(l, r);
        }

        // Shrink the window from the back (left) as long as we retain coverage.
        String wl = paragraph.get(l);
        if (keywordsToCover.containsKey(wl)) {
          slidingWindow.put(wl, slidingWindow.get(wl) - 1);

          // Have we dropped a relevant word by shrinking left?
          if (slidingWindow.get(wl) < keywordsToCover.get(wl)) {
            ++remainingToCover;
          }
        }
        ++l;
      }
    }
    return result;
  }

  // 12.7
  private static Subarray findSmallestSequentiallyCoveringSubset(
      List<String> p, List<String> keywords) {
    Map<String, Integer> kwToIdx = new HashMap<>();
    List<Integer> latestOccurrence = new ArrayList<>(keywords.size());
    List<Integer> shortestSubarrayLength = new ArrayList<>(keywords.size());

    for (int i = 0; i < keywords.size(); ++i) {
      latestOccurrence.add(-1);
      shortestSubarrayLength.add(Integer.MAX_VALUE);
      kwToIdx.put(keywords.get(i), i);
    }

    int shortestDistance = Integer.MAX_VALUE;
    Subarray result = new Subarray(-1, -1);
    for (int i = 0; i < p.size(); ++i) {
      Integer kwIdx = kwToIdx.get(p.get(i));
      if (kwIdx != null) {
        if (kwIdx == 0) { // First keyword
          shortestSubarrayLength.set(0, 1);
        } else if (shortestSubarrayLength.get(kwIdx - 1) != Integer.MAX_VALUE) {
          int distanceToPrevKw = i - latestOccurrence.get(kwIdx - 1);
          shortestSubarrayLength.set(
              kwIdx, distanceToPrevKw + shortestSubarrayLength.get(kwIdx - 1));
        }
        latestOccurrence.set(kwIdx, i);

        // lastKeyword, look for improved subarray.
        if (kwIdx == keywords.size() - 1 && shortestSubarrayLength.getLast() < shortestDistance) {
          shortestDistance = shortestSubarrayLength.getLast();
          result = new Subarray(i - shortestSubarrayLength.getLast() + 1, i);
        }
      }
    }
    return result;
  }

  // 12.8
  public static int longestSubarrayWithoutDuplicateEntries(List<Integer> A) {
    Map<Integer, Integer> mostRecentOccurrence = new HashMap<>();
    int longestSubarrayStartIdx = 0, maxSubarrayLen = 0;
    for (int i = 0; i < A.size(); i++) {
      Integer dupeIdx = mostRecentOccurrence.put(A.get(i), i);
      if (dupeIdx != null) {
        // Since we are incrementing i by 1 even after we have jumped longestSubarrayStartIdx ahead.
        if (dupeIdx >= longestSubarrayStartIdx) {
          // Have already moved forward so don't need the +1 in (i - longest + 1). Would never find
          // duplicate in A.get(0) case anyway.
          maxSubarrayLen = Math.max(maxSubarrayLen, i - longestSubarrayStartIdx);
          // Start after the duplicated entry
          longestSubarrayStartIdx = dupeIdx + 1;
        }
      }
    }
    // In-case we get to the end without running into another duplicate, we might not update the
    // longest
    // sub array start before termination
    return Math.max(maxSubarrayLen, A.size() - longestSubarrayStartIdx);
  }

  // 12.9
  public static int longestContainedRange(List<Integer> A) {
    Set<Integer> unprocessed = new HashSet<>(A);

    int maxIntervalSize = 0;
    while (!unprocessed.isEmpty()) {
      int i = unprocessed.iterator().next();
      unprocessed.remove(i);

      int lowerBound = i - 1;
      while (unprocessed.contains(lowerBound)) {
        unprocessed.remove(lowerBound);
        --lowerBound;
      }

      int upperBound = i + 1;
      while (unprocessed.contains(upperBound)) {
        unprocessed.remove(upperBound);
        ++upperBound;
      }

      // NOTE: lowerbound and upperbound both terminate the above loops off by 1
      maxIntervalSize = Math.max(upperBound - lowerBound - 1, maxIntervalSize);
    }
    return maxIntervalSize;
  }

  // 12.6
  private record Subarray(int start, int end) {
    public Subarray() {
      this(-1, -1);
    }

    @Override
    public String toString() {
      return "[" + start + ", " + end + "]";
    }

    public boolean notSet() {
      return start == -1 && end == -1;
    }

    public boolean longerThan(int start, int end) {
      return this.end - this.start + 1 > end - start + 1;
    }
  }
}
