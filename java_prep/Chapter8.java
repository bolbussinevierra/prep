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

        System.out.println("8.4 -> " + shortestEquivalentPath("sc//./../tc/awk/././"));
        System.out.println("8.5 -> " + getBuildingsWithSunsetView(List.of(1, 2, 4, 3).iterator()));

        Queue q = new Queue(5);
        q.enqueue(10);
        q.enqueue(11);
        q.enqueue(12);
        q.enqueue(13);
        System.out.println("8.7 -> " + q);

        Queue2 q2 = new Queue2();
        q2.enqueue(1);
        q2.enqueue(2);
        q2.enqueue(3);
        q2.enqueue(4);
        q2.enqueue(5);
        int count = 5;
        System.out.print("8.8 -> [ ");
        while (count-- > 0) {
            System.out.print(q2.dequeue() + " ");
        }
        System.out.println("]");
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

    // 8.4
    public static String shortestEquivalentPath(String path) {
        if (path.isEmpty()) {
            throw new IllegalArgumentException("Empty string is not a legal path");
        }

        Deque<String> pathNames = new ArrayDeque<>();
        // Special case: starts with "/", which is an absolute path.
        if (path.startsWith("/")) {
            pathNames.addFirst("/");
        }

        for (String token : path.split("/")) {
            if (token.equals("..")) {
                if (pathNames.isEmpty() || pathNames.peekFirst().equals("..")) {
                    pathNames.addFirst(token);
                } else {
                    if (pathNames.peekFirst().equals("/")) {
                        throw new IllegalArgumentException("Path error, trying to go up root " + path);
                    }
                    pathNames.removeFirst();
                }
            } else if (!token.equals(".") && !token.isEmpty()) { // Must be a name.
                pathNames.addFirst(token);
            }
        }

        StringBuilder result = new StringBuilder();
        if (!pathNames.isEmpty()) {
            Iterator<String> it = pathNames.descendingIterator();
            String prev = it.next();
            result.append(prev);

            while (it.hasNext()) {
                if (!prev.equals("/")) {
                    result.append("/");
                }
                prev = it.next();
                result.append(prev);
            }
        }
        return result.toString();
    }
    // 8.5
    private static List<Building> getBuildingsWithSunsetView(Iterator<Integer> sequence) {
        int id = 0;
        Deque<Building> candidates = new ArrayDeque<>();

        while (sequence.hasNext()) {
            int bldgHeight = sequence.next();
            while (!candidates.isEmpty() && bldgHeight >= candidates.peekFirst().height()) {
                candidates.removeFirst();
            }
            candidates.addFirst(new Building(id++, bldgHeight));
        }
        return candidates.stream().toList();
    }

    private record Building(int id, int height) {}

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

    // 8.8 : Queue based on stacks
    private static class Queue2 {
        private Deque<Integer> enqueue = new ArrayDeque<>();
        private Deque<Integer> dequeue = new ArrayDeque<>();

        public void enqueue(Integer x) {
            enqueue.addFirst(x);
        }

        public Integer dequeue() {
            while (dequeue.isEmpty()) {
                // Transfers the elements from enqueue to dequeue
                while (!enqueue.isEmpty()) {
                    dequeue.addFirst(enqueue.removeFirst());
                }
            }
            return dequeue.removeFirst();
        }
    }
}
