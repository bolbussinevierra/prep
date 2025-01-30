package java_prep;

public class Chapter4 {
  public static void main(String[] args) {
    // 4.3
    System.out.println(
        "4.3 -> " + Long.toBinaryString(12L) + " -> " + Long.toBinaryString(reverseBits(12L)));
    // 4.7
    for (int i = 1; i <= 5; ++i) {
      System.out.println("4.7 -> " + power(4.0, i) + " " + powerIter(4.0, i));
      System.out.println("4.7 -> " + power(4.0, -i) + " " + powerIter(4.0, -i));
    }

    // 4.8
    System.out.println("4.8 -> " + reverse(-4326));
    // 4.9
    System.out.println("4.9 -> " + isPalindromeNumber(157751));

    // 4.11
    Rect r1 = new Rect(2, 1, 2, 2);
    Rect r2 = new Rect(1, 1, 2, 1);
    System.out.println("4.11 -> " + intersectRectange(r1, r2));
  }

  // 4.7
  public static double power(double x, int power) {
    if (x == 0) return 0;
    if (power == 0) return 1;
    if (power == 1) return x;

    double result = power(x*x, Math.abs(power/2));
    // Account for odd power (since odd does not divide cleanly by 2)
    result = power % 2 == 0 ? result : x * result;
    // Negative power?
    return power > 0 ? result : 1/result;
  }

  public static double powerIter(double x, int power) {
    if (power < 0) {
      x = 1/x;
      power = Math.abs(power);
    }
    double result = 1.0;

    while (power != 0) {
      if (power % 2 == 1) {
        result *= x;
      }
      x *= x;
      power /= 2;
    }

    return result;
  }

  // 4.8
  public static long reverse(long n) {
    long res = 0;
    while (n != 0) {
      res = res * 10 + (n % 10);
      n /= 10;
    }
    return res;
  }

  // 4.9
  public static boolean isPalindromeNumber(int x) {
    if (x <= 0) return x == 0; // negative number is never palindromic.

    // Since we are only considering positive numbers here, we can cast rather than
    // floor
    final int numDigits = (int) Math.log10(x) + 1;
    int msdMask = (int) Math.pow(10, numDigits - 1);
    for (int i = 0; i < (numDigits / 2); ++i) {
      if (x / msdMask != x % 10) {
        return false;
      }
      x %= msdMask; // Remove the most significant digit.
      x /= 10; // Remove the least significant digit.
      msdMask /= 100;  // Since we just removed two digits.
    }
    return true;
  }

  // 4.3
  public static long reverseBits(long x) {
    long reversed = 0;
    while (x > 0) {
      reversed = (reversed << 1) | x & 1;
      x >>= 1;
    }
    return reversed;
  }

  // 4.11
  public static Rect intersectRectange(Rect r1, Rect r2) {
    if (!doIntersect(r1, r2)) {
      return new Rect(0, 0, -1, -1); // No intersection.
    }
    return new Rect(
        Math.max(r1.x(), r2.x()),
        Math.max(r1.y(), r2.y()),
        Math.min(r1.x() + r1.width(), r2.x() + r2.width()) - Math.max(r1.x(), r2.x()),
        Math.min(r1.y() + r1.height(), r2.y() + r2.height()) - Math.max(r1.y(), r2.y()));
  }

  private static boolean doIntersect(Rect r1, Rect r2) {
    return r1.x() <= r2.x() + r2.width()
        && r1.x() + r1.width() >= r2.x()
        && r1.y() <= r2.y() + r2.height()
        && r1.y() + r1.height() >= r2.y();
  }
}

record Rect(int x, int y, int width, int height) {
  @Override
  public String toString() {
    return (x + " " + y + " " + width + " " + height);
  }
}
