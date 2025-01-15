package java_prep;

import java.util.Map;
import java.util.Set;

public class Chapter6 {
  public static void main(String[] args) {
    // 6.1
    System.out.println("6.1 (intToString) -> " + intToString(-341));
    System.out.println("6.1 (stringToInt) -> " + stringToInt("-341"));

    // 6.2
    System.out.println("6.2 -> " + convertBase("615", 7, 13));

    // 6.4
    char[] s = new char[] {'a', 'c', 'd', 'b', 'b', 'c', 'a'};
    replaceAndRemove(s.length, s);
    System.out.println("6.4 -> " + new String(s));

    // 6.5
    System.out.println("6.5 -> " + isPalindrome("A man, a plan, a canal, Panama."));

    // 6.6
    char[] str = "ram is costly".toCharArray();
    reverseWords(str);
    System.out.println("6.6 -> " + new String(str));

    // 6.7
    System.out.println("6.7 -> " + countAndSay(8));

    // 6.8
    System.out.println("6.8 (a) -> " + romanToInt("LIX"));
    // System.out.println("6.8 (b) -> " + romanToInt("IC")); // Expected: Throws illegalArgumentException.

    // 6.10
    System.out.println("6.10 -> " + snakeString("Hello World!"));
  }

  public static String intToString(int x) {
    boolean isNegative = x < 0;
    StringBuilder s = new StringBuilder();
    x = Math.abs(x);
    do {
      s.append((char) ('0' + x % 10));
      x /= 10;
    } while (x != 0);
    return s.append(isNegative ? "-" : "").reverse().toString();
  }

  public static int stringToInt(String x) {
    return (x.charAt(0) == '-' ? -1 : 1)
        * x.substring(x.charAt(0) == '-' || x.charAt(0) == '+' ? 1 : 0)
            .chars()
            .reduce(
                0,
                (rSum, c) -> {
                  if (c - '0' > 9) {
                    throw new RuntimeException();
                  }
                  return rSum * 10 + c - '0';
                });
  }

  // 6.2
  public static String convertBase(String num, int b1, int b2) {
    boolean isNegative = num.startsWith("-");
    int numDec =
        num.substring(isNegative ? 1 : 0)
            .chars()
            .reduce(0, (x, c) -> x * b1 + (Character.isDigit(c) ? c - '0' : c - 'A' + 10));
    if (numDec == 0) return "0";

    return (isNegative ? "-" : "") + constructFromBase(numDec, b2);
  }

  public static String constructFromBase(int num, int b) {
    if (num == 0) return "";
    int rem = num % b;
    return constructFromBase(num / b, b) + (char) (rem >= 10 ? 'A' + rem - 10 : '0' + rem);
  }

  // 6.4
  public static void replaceAndRemove(int size, char[] s) {
    // Forward iteration: remove b's and count a's
    int writeIdx = 0, aCount = 0;
    for (int i = 0; i < size; ++i) {
      if (s[i] != 'b') {
        s[writeIdx++] = s[i];
      }
      if (s[i] == 'a') {
        ++aCount;
      }
    }
    // Backward iteration: replace a's with dd's starting at the end
    int end = writeIdx - 1; // writeIdx terminated at off by +1 above
    writeIdx = end + aCount;
    for (int readIdx = end; readIdx >= 0; --readIdx) {
      if (s[readIdx] == 'a') {
        s[writeIdx--] = 'd';
        s[writeIdx--] = 'd';
      } else {
        s[writeIdx--] = s[readIdx];
      }
    }
  }

  // 6.5
  public static boolean isPalindrome(String s) {
    int i = 0, j = s.length() - 1;
    while (i < j) {
      while (i < j && !Character.isLetterOrDigit(s.charAt(i))) {
        ++i;
      }
      while (i < j && !Character.isLetterOrDigit(s.charAt(j))) {
        --j;
      }
      if (Character.toLowerCase(s.charAt(i++)) != Character.toLowerCase(s.charAt(j--))) {
        return false;
      }
    }
    return true;
  }

  // 6.6
  public static void reverseWords(char[] input) {
    // Reverse the whole string
    int end = input.length;
    reverse(input, 0, end - 1);

    // Reverse-restore each of the words.
    int ws = 0; // Starting letter of a word.
    int we = 0; // Space terminating the word.
    while (ws < end) {
      // Skip leading spaces, or pass we to the start of the next word.
      while (ws < end && input[ws] == ' ' || ws < we) {
        ++ws;
      }
      // Skip non-space chars
      while (we < ws || we < end && input[we] != ' ') {
        ++we;
      }
      reverse(input, ws, we - 1);
    }
  }

  public static void reverse(char[] input, int start, int end) {
    while (start < end) {
      char tmp = input[start];
      input[start++] = input[end];
      input[end--] = tmp;
    }
  }

  // 6.7
  public static String countAndSay(int n) {
    if (n <= 0) return "";

    String s = "1";
    for (int i = 1; i < n; ++i) {
      s = nextNumber(s);
    }
    return s;
  }

  // 6.8
  public static int romanToInt(String s) {
    Map<Character, Integer> T =
        Map.of('I', 1, 'V', 5, 'X', 10, 'L', 50, 'C', 50, 'D', 500, 'M', 100);
    // Valid precedence exceptions.
    Map<Character, Set<Character>> P =
        Map.of('I', Set.of('V', 'X'), 'X', Set.of('L', 'C'), 'C', Set.of('D', 'M'));

    int sum = T.get(s.charAt(s.length() - 1));
    for (int i = s.length() - 2; i >= 0; --i) {
      if (T.get(s.charAt(i)) < T.get(s.charAt(i + 1))) {
        if (!P.get(s.charAt(i)).contains(s.charAt(i + 1))) {
          throw new IllegalArgumentException();
        }
        sum -= T.get(s.charAt(i));
      } else {
        sum += T.get(s.charAt(i));
      }
    }
    return sum;
  }

  // 6.10
  public static String snakeString(String s) {
    StringBuilder builder = new StringBuilder();
    for (int i = 1; i < s.length(); i += 4) {
      builder.append(s.charAt(i));
    }
    for (int i = 0; i < s.length(); i += 2) {
      builder.append(s.charAt(i));
    }
    for (int i = 3; i < s.length(); i += 4) {
      builder.append(s.charAt(i));
    }
    return builder.toString();
  }

  public static String nextNumber(String s) {
    StringBuilder result = new StringBuilder();
    for (int i = 0; i < s.length(); ++i) {
      int count = 1;
      while (i + 1 < s.length() && s.charAt(i) == s.charAt(i + 1)) {
        ++i;
        ++count;
      }
      result.append(count).append(s.charAt(i));
    }
    return result.toString();
  }
}
