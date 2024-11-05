package java_prep;

public class Chapter6 {
    public static void main(String[] args) {
        // 6.1
        System.out.println("6.1 (intToString) -> " + intToString(-341));
        System.out.println("6.1 (stringToInt) -> " + stringToInt("-341"));

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
}
