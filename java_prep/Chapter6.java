package java_prep;

public class Chapter6 {
    public static void main(String[] args) {
        // 6.1
        System.out.println("6.1 (intToString) -> " + intToString(-341));
        System.out.println("6.1 (stringToInt) -> " + stringToInt("-341"));

        // 6.2
        System.out.println("6.2 -> " + convertBase("615", 7, 13));

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

}
