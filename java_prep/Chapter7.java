package java_prep;

public class Chapter7 {
    static class ListNode<T> {
        public T data;
        public ListNode<T> next;
    }

    public static void main(String[] args) {
        // 7.1
        ListNode<Integer> L1 = makeLinkedList(new int[]{1, 4, 6});
        ListNode<Integer> L2 = makeLinkedList(new int[]{2, 3, 5});
        ListNode<Integer> sorted = mergeSorted(L1, L2);
        System.out.println(sorted);
    }

    static ListNode<Integer> mergeSorted(ListNode<Integer> L1,
                                         ListNode<Integer> L2) {
        // Make a dummyHead to simply starting condition.
        ListNode<Integer> dummyHead = new ListNode<>();
        ListNode<Integer> current = dummyHead;

        while (L1 != null && L2 != null) {
            if (L1.data <= L2.data) {
                current.next = L1;
                L1 = L1.next;
            } else {
                current.next = L2;
                L2 = L2.next;
            }
            current = current.next;
        }

        current.next = L1 != null ? L1 : L2;
        return dummyHead.next;
    }
    private static ListNode<Integer> makeLinkedList(int[] values) {
        ListNode<Integer> current = new ListNode<>();
        ListNode<Integer> head = current;
        for (int i = 0; i < values.length; i++) {
            current.data = values[i];
            // Tail element does not have a next.
            if (i < values.length - 1) {
                current.next = new ListNode<>();
                current = current.next;
            }
        }
        return head;
    }
}


