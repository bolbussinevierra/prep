package java_prep;

public class Chapter4 {
    public static void main(String[] args) {
        // 4.3
        System.out.println("4.3 -> " + Long.toBinaryString(12L) + " -> " + Long.toBinaryString(reverseBits(12L)));
        // 4.8
        System.out.println("4.8 -> " + reverse(-4326));
        // 4.11
        Rect r1 = new Rect(2, 1, 2, 2);
        Rect r2 = new Rect(1, 1, 2, 1);
        System.out.println("4.11 -> " + intersectRectange(r1, r2));

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
            return new Rect(0, 0, -1, -1);  // No intersection.
        }
        return new Rect(
                Math.max(r1.x(), r2.x()), Math.max(r1.y(), r2.y()),
                Math.min(r1.x() + r1.width(), r2.x() + r2.width()) - Math.max(r1.x(), r2.x()),
                Math.min(r1.y() + r1.height(), r2.y() + r2.height()) - Math.max(r1.y(), r2.y()));

    }
    private static boolean doIntersect(Rect r1, Rect r2) {
        return r1.x() <= r2.x() + r2.width() && r1.x() + r1.width() >= r2.x() &&
                r1.y() <= r2.y() + r2.height() && r1.y() + r1.height() >= r2.y();
    }

}

record Rect(int x, int y, int width, int height) {
    @Override
    public String toString() {
        return (x + " " + y + " " + width + " " + height);
    }
}
