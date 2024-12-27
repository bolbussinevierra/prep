package java_prep;

import java.util.*;
import java.util.function.ToIntBiFunction;

public class Chapter8 {
    public static void main(String[] args) {
        Stack s = new Stack();
        s.push(1); // max 1;
        s.push(2); // max 2;
        s.push(4); // max 4
        s.push(3); // max 4
        while (!s.empty()) {
            System.out.println("i = " + s.peek() + " max = " + s.max());
            s.pop();
        }

        System.out.println("8.2 -> " + eval("3,4,+,2,*,1,+"));

        System.out.println("8.3 (a) -> " + isValid("[{}]()"));
        System.out.println("8.3 (b) -> " + isValid("{]()"));

        Queue q = new Queue(5);
        q.enqueue(10);
        q.enqueue(11);
        q.enqueue(12);
        q.enqueue(13);
        System.out.println("8.7 -> " + q);
    }

    public static int eval(String expression) {
        Deque<Integer> s = new ArrayDeque<>();  // stack;
        final String DELIMITER = ",";
        final Map<String, ToIntBiFunction<Integer, Integer>> OPERATORS = Map.of(
          "+", (y, x) -> x + y,
          "-", (y, x) -> x - y,
          "*", (y, x) -> x * y,
          "/", (y, x) -> x / y
        );

        for (String token : expression.split(DELIMITER)) {
            if (OPERATORS.get(token) != null) {
                // Token is an operation
                s.addFirst(OPERATORS.get(token).applyAsInt(s.removeFirst(), s.removeFirst()));
            } else {
                // Token is a number
                s.addFirst(Integer.parseInt(token));
            }
        }

        return s.removeFirst();
    }

    // 8.3
    public static boolean isValid(String s) {
        Deque<Character> leftChars = new ArrayDeque<>();
        final Map<Character, Character> LOOKUP = Map.of('(', ')', '{','}', '[', ']');
        for (int i = 0; i < s.length(); ++i) {
            if (LOOKUP.get(s.charAt(i)) != null) {
                // i points to a left char.
                leftChars.addFirst(s.charAt(i));
            } else if ( leftChars.isEmpty() ||
                    // i points to a right char. Make sure it is the right char expected
                    // by the left char at the top of the stack.
                    LOOKUP.get(leftChars.removeFirst()) != s.charAt(i)) {
                return false; // unmatched right char.
            }
        }
        return leftChars.isEmpty();
    }

    private static class ElementWithCachedMax {
        public Integer element;
        public Integer max;

        public ElementWithCachedMax(Integer element, Integer max) {
            this.element = element;
            this.max = max;
        }
    }

    private static class Stack {
        private final Deque<ElementWithCachedMax> elements = new ArrayDeque<>();

        public boolean empty() {
            return elements.isEmpty();
        }

        public Integer max() {
            return elements.peek().max;
        }

        public Integer peek() {
            return elements.peek().element;
        }

        public Integer pop() {
            return elements.removeFirst().element;
        }

        public void push(Integer i) {
            elements.addFirst(new ElementWithCachedMax(i,
                    Math.max(i, empty() ? i : max())));
        }
    }

    // 8.7
    private static class Queue {
        private static final int SCALE_FACTOR = 2;
        private int head = 0, tail = 0, count = 0;
        private Integer[] entries;

        public Queue(int capacity) {
            entries = new Integer[capacity];
        }

        public void enqueue(Integer x) {
            if (count == entries.length) {  // Need to resize.
                // Makes the elements appear consecutively.
                Collections.rotate(Arrays.asList(entries), -head);
                // Resets head and tail.
                head = 0;
                tail = count;  // Where next element is to be inserted at back.
                entries = Arrays.copyOf(entries, count * SCALE_FACTOR);
            }

            entries[tail] = x;
            tail = (tail + 1) % entries.length;
            ++count;
        }

        public Integer dequeue() {
            --count;
            Integer result = entries[head];
            head = (head + 1) % entries.length;
            return result;
        }

        public int size() {
            return count;
        }

        @Override
        public String toString() {
            return "Queue{"
                    + "head=" + head + ", tail=" + tail +
                    ", entries=" + Arrays.toString(entries) + '}';
        }
    }
}
