package java_prep;

public class Chapter6 {
    public static void main(String[] args) {
        // 6.1
        System.out.println("6.1 (intToString) -> " + intToString(-341));
        System.out.println("6.1 (stringToInt) -> " + stringToInt("-341"));

        // 6.2
        System.out.println("6.2 -> " + convertBase("615", 7, 13));

        // 6.4
        char[] s = new char[]{'a', 'c', 'd', 'b', 'b', 'c', 'a'};
        replaceAndRemove(s.length, s);
        System.out.println("6.4 -> " + new String(s));

        // 6.5
        System.out.println("6.5 -> " + isPalindrome("A man, a plan, a canal, Panama."));
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
        return (x.charAt(0) == '-' ? -1 : 1) *
                x.substring(x.charAt(0) == '-' || x.charAt(0) == '+' ? 1 : 0)
                        .chars()
                        .reduce(0, (rSum, c) -> {
                            if (c - '0' > 9) {
                                throw new RuntimeException();
                            }
                            return rSum * 10 + c - '0';
                        });
    }

    // 6.2
    public static String convertBase(String num, int b1, int b2) {
        boolean isNegative = num.startsWith("-");
        int numDec = num.substring(isNegative ? 1 : 0)
                .chars()
                .reduce(0, (x, c) -> x * b1 + (Character.isDigit(c) ? c - '0' : c - 'A' + 10));
        if (numDec == 0) return "0";

        return (isNegative ? "-" : "") + constructFromBase(numDec, b2);

    }

    public static String constructFromBase(int num, int b) {
        if (num == 0) return "";
        int rem = num % b;
        return constructFromBase(num / b, b) +
                (char) (rem >= 10 ? 'A' + rem - 10 : '0' + rem);
    }

    // 6.4
    public static void replaceAndRemove(int size, char[] s) {
        // Forward iteration: remove b's and count a's
        int writeIdx= 0, aCount = 0;
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
            if (Character.toLowerCase(s.charAt(i++)) !=
                Character.toLowerCase(s.charAt(j--))) {
                return false;
            }
        }
        return true;
    }
}
