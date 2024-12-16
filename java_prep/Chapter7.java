package java_prep;

public class Chapter7 {
    static class ListNode<T> {
        public T data;
        public ListNode<T> next;

        public ListNode(T data, ListNode<T> next) {
            this.data = data;
            this.next = next;
        }
    }

    public static void main(String[] args) {
        // 7.1
        ListNode<Integer> L1 = makeLinkedList(new int[]{1, 4, 6});
        ListNode<Integer> L2 = makeLinkedList(new int[]{2, 3, 5});
        ListNode<Integer> sorted = mergeSorted(L1, L2);
        printList("7.1", sorted);

        // 7.4
        ListNode<Integer> list1 = makeLinkedList(new int[]{1, 2, 3, 4, 5});
        ListNode<Integer> list2 = makeLinkedList(new int[]{1, 2, 3});
        ListNode<Integer> tmp1 = list1;
        ListNode<Integer> tmp2 = list2;
        while (tmp1.data != 4) tmp1 = tmp1.next;
        while (tmp2.data != 3) tmp2 = tmp2.next;
        tmp2.next = tmp1;
        System.out.println("7.4 -> " + firstOverlappingNode(list1, list2).data);

        // 7.7
        ListNode<Integer> list3 = makeLinkedList(new int[]{6, 5, 4, 3, 2, 1});
        printList("7.7", removeKthLast(list3, 3));
    }

    private static ListNode<Integer> firstOverlappingNode(
            ListNode<Integer> listA,
            ListNode<Integer> listB) {
        // Determine the length and advance the longer one by the difference.
        int lengthA = getLength(listA), lengthB = getLength(listB);
        if (lengthA > lengthB) {
            listA = advanceListBy(lengthA - lengthB, listA);
        } else {
            listB = advanceListBy(lengthB - lengthA, listB);
        }

        while (listA != null && listB != null && listA != listB) {
            listA = listA.next;
            listB = listB.next;
        }
        return listA; // nullptr implies no overlap;
    }

    static int getLength(ListNode<Integer> l) {
        int length = 0;
        while (l != null) {
            ++length;
            l = l.next;
        }
        return length;
    }

    static ListNode<Integer> advanceListBy(int k, ListNode<Integer> l) {
        while (k-- > 0) {
            l = l.next;
        }
        return l;
    }

    static ListNode<Integer> mergeSorted(ListNode<Integer> L1,
                                         ListNode<Integer> L2) {
        // Make a dummyHead to simply starting condition.
        ListNode<Integer> dummyHead = new ListNode<>(0, null);
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
        ListNode<Integer> current = new ListNode<>(0, null);
        ListNode<Integer> head = current;
        for (int i = 0; i < values.length; i++) {
            current.data = values[i];
            // Tail element does not have a next.
            if (i < values.length - 1) {
                current.next = new ListNode<>(0, null);
                current = current.next;
            }
        }
        return head;
    }

    private static void printList(String tag, ListNode<Integer> l) {
        System.out.print("\n" + tag + " -> [ ");
        while (l != null) {
            System.out.print(l.data + " ");
            l = l.next;
        }
        System.out.print("]\n");
    }

    private static ListNode<Integer> removeKthLast(ListNode<Integer> l, int k) {
        ListNode<Integer> dummyHead = new ListNode<>(0, l);
        ListNode<Integer> first = dummyHead.next;

        while (k-- > 0) {
            first = first.next;
        }

        // Use of dummyHead here adds a +1 offset FYI
        ListNode<Integer> second = dummyHead;
        while (first != null) {
            second = second.next;
            first = first.next;
        }

        // Second points to the (k + 1)-th last node, deletes its successor
        second.next = second.next.next;
        return dummyHead.next;
    }
}


