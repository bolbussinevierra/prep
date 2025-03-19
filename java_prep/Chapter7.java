package java_prep;

import java.util.Arrays;
import java.util.List;

public class Chapter7 {
  public static void main(String[] args) {
    // 7.1
    ListNode<Integer> list71_i = makeLinkedList(new int[] {1, 4, 6});
    ListNode<Integer> list71_ii = makeLinkedList(new int[] {2, 3, 5});
    ListNode<Integer> ans71 = mergeSorted(list71_i, list71_ii);
    printList("7.1", ans71);

    // 7.4
    ListNode<Integer> list74_i = makeLinkedList(new int[] {1, 2, 3, 4, 5});
    ListNode<Integer> list74_ii = makeLinkedList(new int[] {1, 2, 3});
    ListNode<Integer> tmp1 = list74_i;
    ListNode<Integer> tmp2 = list74_ii;
    while (tmp1.data != 4) tmp1 = tmp1.next;
    while (tmp2.data != 3) tmp2 = tmp2.next;
    tmp2.next = tmp1;
    System.out.println("7.4 -> " + firstOverlappingNode(list74_i, list74_ii).data);

    // 7.7
    ListNode<Integer> list77 = makeLinkedList(new int[] {6, 5, 4, 3, 2, 1});
    printList("7.7", removeKthLast(list77, 3));

    // 7.8
    ListNode<Integer> list78 = makeLinkedList(new int[] {1, 2, 2, 3, 4, 4, 4, 5, 6});
    removeDuplicates(list78);
    printList("7.8", list78);

    // 7.10
    ListNode<Integer> list710 = makeLinkedList(new int[] {0, 1, 2, 3, 4, 5, 6, 7});
    printList("7.10", evenOddMerge(list710));

    ListNode<Integer> list711 = makeLinkedList(new int[] {2, 3, 5, 3, 2});
    System.out.println("7.11 -> " + isLinkedListPalindrome(list711));
  }

  private static ListNode<Integer> firstOverlappingNode(
      ListNode<Integer> listA, ListNode<Integer> listB) {
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

  public static ListNode<Integer> mergeSorted(ListNode<Integer> L1, ListNode<Integer> L2) {
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

  // 7.8
  static void removeDuplicates(ListNode<Integer> L) {
    ListNode<Integer> iter = L;
    while (iter != null) {
      ListNode<Integer> nextDistinct = iter.next;
      while (nextDistinct != null && nextDistinct.data.equals(iter.data)) {
        nextDistinct = nextDistinct.next;
      }
      iter.next = nextDistinct;
      iter = nextDistinct;
    }
  }

  // 7.10
  static ListNode<Integer> evenOddMerge(ListNode<Integer> L) {
    if (L == null) return null;

    ListNode<Integer> evenDummyHead = new ListNode<>(0, null);
    ListNode<Integer> oddDummyHead = new ListNode<>(0, null);

    // Keep reference to the tails of the lists.
    List<ListNode<Integer>> tails = Arrays.asList(evenDummyHead, oddDummyHead);
    int turn = 0; // Starts even.
    for (ListNode<Integer> node = L; node != null; node = node.next) {
      // Make the new even/odd tail at position 0, 1.
      tails.get(turn).next = node;
      tails.set(turn, tails.get(turn).next);
      turn ^= 1;
    }
    // Odd tail is the real tail.
    tails.get(1).next = null;
    // Even tail points to the odd tail.
    tails.get(0).next = oddDummyHead.next;
    return evenDummyHead.next;
  }

  // 7.11
  public static boolean isLinkedListPalindrome(ListNode<Integer> L) {
    ListNode<Integer> slow = L, fast = L;
    while (fast != null && fast.next != null) {
      fast = fast.next.next;
      slow = slow.next;
    }

    ListNode<Integer> firstHalfIter = L;
    ListNode<Integer> secondHalfIter = reverseList(slow);
    ListNode<Integer> reversedSecondHalf = secondHalfIter; // to help restore the reversal.
    while (secondHalfIter != null && firstHalfIter != null) {
      if (!secondHalfIter.data.equals(firstHalfIter.data)) {
        // Restore reversal.
        reverseList(reversedSecondHalf);
        return false;
      }
      secondHalfIter = secondHalfIter.next;
      firstHalfIter = firstHalfIter.next;
    }

    // restore reversed list.
    reverseList(reversedSecondHalf);
    return true;
  }

  public static ListNode<Integer> makeLinkedList(int[] values) {
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

  public static void printList(String tag, ListNode<Integer> l) {
    System.out.print("\n" + tag + " -> [ ");
    while (l != null) {
      System.out.print(l.data + " ");
      l = l.next;
    }
    System.out.print("]\n");
  }

  private static ListNode<Integer> reverseList(ListNode<Integer> l) {
    if (l.next == null) return l;

    ListNode<Integer> prev = null;
    ListNode<Integer> curr = l;
    ListNode<Integer> next = null;

    while (curr != null) {
      next = curr.next;
      curr.next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
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

  public static class ListNode<T> {
    public T data;
    public ListNode<T> next;

    public ListNode(T data, ListNode<T> next) {
      this.data = data;
      this.next = next;
    }
  }
}
