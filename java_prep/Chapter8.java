package java_prep;

import java.util.ArrayDeque;
import java.util.Deque;

public class Chapter8 {
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
    }


}
