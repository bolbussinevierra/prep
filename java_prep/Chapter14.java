package java_prep;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Chapter14 {
  public static int rootIdx;

  public static void main(String[] args) {
    printTree("", makeFigure142());
    BST<Integer> lca =
        findLCA(makeFigure142(), new BST<>(2, null, null), new BST<>(107, null, null));
    System.out.println("14.4 -> " + lca.data);

    List<Integer> preorder = List.of(43, 23, 37, 29, 31, 41, 47, 53);
    BST<Integer> t = rebuildBSTFromPreorder(preorder);
    printTree("14.5", t);

    // 14.6
    List<List<Integer>> lists = new ArrayList<>();
    lists.add(List.of(5, 10, 15));
    lists.add(List.of(3, 6, 9, 12, 15));
    lists.add(List.of(8, 16, 24));
    System.out.println("14.6 -> " + shortedIntervalContainingItemInEachArray(lists));

    // 14.7
    System.out.println("14.7 (klogk)  -> " + generateFirstKABSqrt(10));
    System.out.println("14.7 (linear) -> " + generateFirstKABSqrtLinear(10));

    BST<Integer> balancedTree = buildMinHeightBST(List.of(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11));
    printTree("14.8", balancedTree);

    // 14.9
    BST<Integer> A = makeFigure141();
    BST<Integer> I = A.right;
    BST<Integer> K = I.left.right;
    BST<Integer> M = K.left.right;
    BST<Integer> middle = I.left;
    System.out.println("14.9a -> " + pairIncludesAncestorAndDescendantOfM(A, K, middle));
    System.out.println("14.9b -> " + pairIncludesAncestorAndDescendantOfM(I, M, middle));

    // 14.10
    System.out.println("14.10 -> " + rangeLookupInBST(makeFigure141(), new Interval(16, 31)));
  }

  // 14.4
  public static BST<Integer> findLCA(BST<Integer> t, BST<Integer> A, BST<Integer> B) {
    // Identify which is smaller/bigger
    BST<Integer> s = A.data < B.data ? A : B;
    BST<Integer> b = s == A ? B : A;

    // Use BST property to find which subtree the nodes are in
    while (t.data < s.data || t.data > b.data) {
      while (t.data < s.data) {
        // Smaller key bigger than root, LCA must be on the RHS
        t = t.right;
      }
      while (t.data > b.data) {
        // Bigger key smaller than root, LCA must be on LHS
        t = t.left;
      }
    }
    return t;
  }

  // 14.5
  public static BST<Integer> rebuildBSTFromPreorder(List<Integer> preorder) {
    rootIdx = 0;
    return rebuildBSTFromPreorderOnValueRange(preorder, Integer.MIN_VALUE, Integer.MAX_VALUE);
  }

  private static BST<Integer> rebuildBSTFromPreorderOnValueRange(
      List<Integer> preorder, Integer lowerBound, Integer upperBound) {
    if (rootIdx == preorder.size()) return null;

    Integer root = preorder.get(rootIdx);
    if (root < lowerBound || root > upperBound) {
      return null;
    }
    ++rootIdx;

    BST<Integer> leftSubtree = rebuildBSTFromPreorderOnValueRange(preorder, lowerBound, root);
    BST<Integer> rightSubtree = rebuildBSTFromPreorderOnValueRange(preorder, root, upperBound);
    return new BST<>(root, leftSubtree, rightSubtree);
  }

  // 14.6
  public static Integer shortedIntervalContainingItemInEachArray(List<List<Integer>> A) {
    PriorityQueue<ArrayData> minHeap = new PriorityQueue<>(A.size(), ArrayData::compareTo);
    int maxElementInInterval = Integer.MIN_VALUE;
    int shortestInterval = Integer.MAX_VALUE;

    for (int i = 0; i < A.size(); ++i) {
      int firstValue = A.get(i).getFirst();
      maxElementInInterval = Math.max(maxElementInInterval, firstValue);
      minHeap.add(new ArrayData(firstValue, 0, i));
    }

    ArrayData smallestElement = minHeap.peek();
    shortestInterval = Math.min(shortestInterval, maxElementInInterval - smallestElement.val());

    // if the array containing the smallest element is finished, then
    // we have can't move further.
    while (smallestElement.idx() != A.get(smallestElement.arrayId()).size() - 1) {
      // Drop the smallest item and fetch the next from the same array
      minHeap.remove();
      int arrayId = smallestElement.arrayId();
      int nextIndex = smallestElement.idx() + 1;
      int nextValue = A.get(arrayId).get(nextIndex);
      maxElementInInterval = Math.max(maxElementInInterval, nextValue);
      minHeap.add(new ArrayData(nextValue, nextIndex, arrayId));
      smallestElement = minHeap.peek();
      shortestInterval = Math.min(shortestInterval, maxElementInInterval - smallestElement.val());
    }
    System.out.println(minHeap.stream().toList());
    return shortestInterval;
  }

  // 14.7
  public static List<Double> generateFirstKABSqrt(int k) {
    // NOTE: Using TreeSet instead of PriorityQueue (minheap) since TreeSet does not allow
    // duplicated elements
    // i.e. "Set" part).
    SortedSet<ABSqrt2Number> candidates = new TreeSet<>((a, b) -> Double.compare(a.val, b.val));
    // Initial for 0 + 0 * sqrt(2);
    candidates.add(new ABSqrt2Number(0, 0));

    List<Double> result = new ArrayList<>();
    while (result.size() < k) {
      ABSqrt2Number nextSmallest = candidates.first();
      result.add(nextSmallest.val);

      // Add the next two numbers derived from next smallest.
      candidates.add(new ABSqrt2Number(nextSmallest.a + 1, nextSmallest.b));
      candidates.add(new ABSqrt2Number(nextSmallest.a, nextSmallest.b + 1));
      candidates.remove(nextSmallest);
    }
    return result;
  }

  // 14.7 (version two, linear)
  public static List<Double> generateFirstKABSqrtLinear(int k) {
    List<ABSqrt2Number> result = new ArrayList<>();
    result.add(new ABSqrt2Number(0, 0));
    int i = 0, j = 0;

    for (int n = 1; n < k; ++n) {
      ABSqrt2Number iPlus1 = new ABSqrt2Number(result.get(i).a + 1, result.get(i).b);
      ABSqrt2Number jPlusSqrt2 = new ABSqrt2Number(result.get(j).a, result.get(j).b + 1);
      result.add(iPlus1.val < jPlusSqrt2.val ? iPlus1 : jPlusSqrt2);

      // NOTE: values from both i and j may land on the same value so need to increment both.
      if (Double.compare(iPlus1.val, result.getLast().val) == 0) ++i;
      if (Double.compare(jPlusSqrt2.val, result.getLast().val) == 0) ++j;
    }
    return result.stream().map(c -> c.val).toList();
  }

  // 14.8
  public static BST<Integer> buildMinHeightBST(List<Integer> A) {
    return buildMinHeightBST(A, 0, A.size());
  }

  private static BST<Integer> buildMinHeightBST(List<Integer> A, int start, int exclusiveEnd) {
    if (start >= exclusiveEnd) return null;

    int rootIdx = start + ((exclusiveEnd - start) / 2);
    return new BST<>(
        A.get(rootIdx),
        buildMinHeightBST(A, start, rootIdx),
        buildMinHeightBST(A, rootIdx + 1, exclusiveEnd));
  }

  private static BST<Integer> bstFrom(List<Integer> preOrder, List<Integer> inOrder) {
    return bstFrom(
        preOrder,
        /* preorderStart= */ 0,
        preOrder.size(),
        /* inorderStart= */ 0,
        inOrder.size(),
        IntStream.range(0, inOrder.size()).boxed().collect(Collectors.toMap(inOrder::get, i -> i)));
  }

  // 14.9
  public static boolean pairIncludesAncestorAndDescendantOfM(
      BST<Integer> possibleAncOrDec0, BST<Integer> possibleAncOrDec1, BST<Integer> middle) {
    BST<Integer> search0 = possibleAncOrDec0, search1 = possibleAncOrDec1;
    // Perform interleaved searching from either of the above for middle.
    while (search0 != possibleAncOrDec1
        && search0 != middle
        && search1 != possibleAncOrDec0
        && search1 != middle
        && (search0 != null || search1 != null)) {
      if (search0 != null) {
        search0 = search0.data > middle.data ? search0.left : search0.right;
      }

      if (search1 != null) {
        search1 = search1.data > middle.data ? search1.left : search1.right;
      }
    }

    // If we arrived from one of the starter nodes to the other, or did not find the middle from
    // either
    // search, middle cannot lie in between.
    if (search0 == possibleAncOrDec1
        || search1 == possibleAncOrDec0
        || (search0 != middle && search1 != middle)) {
      return false;
    }

    // if we get here, one of the searches found the middle. So look for either nodes from middle.
    return search0 == middle
        ? searchTarget(middle, possibleAncOrDec1)
        : searchTarget(middle, possibleAncOrDec0);
  }

  // 14.10
  private static List<Integer> rangeLookupInBST(BST<Integer> tree, Interval interval) {
    List<Integer> result = new ArrayList<>();
    rangeLookupInBSTHelper(tree, interval, result);
    return result;
  }

  private static void rangeLookupInBSTHelper(
      BST<Integer> tree, Interval interval, List<Integer> result) {
    if (tree == null) return;

    if (interval.left <= tree.data) {
      rangeLookupInBSTHelper(tree.left, interval, result);
    }

    if (interval.left <= tree.data && tree.data <= interval.right) {
      result.add(tree.data);
    }

    if (interval.right >= tree.data) {
      rangeLookupInBSTHelper(tree.right, interval, result);
    }
  }

  /** Helper utilities. */
  private static boolean searchTarget(BST<Integer> from, BST<Integer> target) {
    while (from != null && from != target) {
      from = from.data > target.data ? from.left : from.right;
    }
    return from == target;
  }

  private static BST<Integer> bstFrom(
      List<Integer> preorder,
      int preorderStart,
      int preOrderEnd,
      int inOrderStart,
      int inOrderEnd,
      Map<Integer, Integer> mapInorder) {
    if (preOrderEnd <= preorderStart || inOrderEnd <= inOrderStart) {
      return null;
    }
    int rootInorder = mapInorder.get(preorder.get(preorderStart));
    int leftTreeSize = rootInorder - inOrderStart;

    return new BST<>(
        preorder.get(preorderStart),
        bstFrom(
            preorder,
            preorderStart + 1,
            preorderStart + 1 + leftTreeSize,
            inOrderStart,
            rootInorder,
            mapInorder),
        bstFrom(
            preorder,
            preorderStart + 1 + leftTreeSize,
            preOrderEnd,
            rootInorder + 1,
            inOrderEnd,
            mapInorder));
  }

  private static void printTree(String tag, BST<Integer> t) {
    if (!tag.isEmpty()) System.out.println(" -> [ " + tag + " ------");

    ArrayDeque<DisplayState> bfs = new ArrayDeque<>();
    bfs.addFirst(new DisplayState(t, 0));

    while (!bfs.isEmpty()) {
      DisplayState c = bfs.removeFirst();
      System.out.println("h" + c.level + ":" + c.n.data);
      if (c.n.left != null) {
        bfs.addLast(new DisplayState(c.n.left, c.level + 1));
      }
      if (c.n.right != null) {
        bfs.addLast(new DisplayState(c.n.right, c.level + 1));
      }
    }

    if (!tag.isEmpty()) System.out.println("---- " + tag + " ]");
  }

  private static BST<Integer> makeFigure141() {
    BST<Integer> A = new BST<>(19);
    BST<Integer> B = new BST<>(7);
    BST<Integer> C = new BST<>(3);
    BST<Integer> D = new BST<>(2);
    BST<Integer> E = new BST<>(5);
    BST<Integer> F = new BST<>(11);
    BST<Integer> G = new BST<>(17);
    BST<Integer> H = new BST<>(11);
    BST<Integer> I = new BST<>(43);
    BST<Integer> J = new BST<>(23);
    BST<Integer> K = new BST<>(37);
    BST<Integer> L = new BST<>(29);
    BST<Integer> M = new BST<>(31);
    BST<Integer> N = new BST<>(41);
    BST<Integer> O = new BST<>(47);
    BST<Integer> P = new BST<>(53);

    A.left = B;
    A.right = I;
    B.left = C;
    B.right = F;
    C.left = D;
    C.right = E;
    F.right = G;
    G.left = H;
    I.left = J;
    I.right = O;
    J.right = K;
    K.left = L;
    K.right = N;
    L.right = M;
    O.right = P;

    return A;
  }

  /** Make BST figure 14.2 on page 226 */
  private static BST<Integer> makeFigure142() {
    List<Integer> inorder = List.of(-14, -10, 2, 106, 107, 108, 243, 285, 286, 401);
    List<Integer> preorder = List.of(108, 106, -10, -14, 2, 107, 285, 243, 286, 401);
    return bstFrom(preorder, inorder);
  }

  public static class ABSqrt2Number {
    public final int a, b;
    public final double val;

    public ABSqrt2Number(int a, int b) {
      this.a = a;
      this.b = b;
      val = a + b * Math.sqrt(2);
    }
  }

  public static class BST<T> {
    T data;
    BST<T> left, right;

    public BST(T data, BST<T> left, BST<T> right) {
      this.data = data;
      this.left = left;
      this.right = right;
    }

    public BST(T data) {
      this(data, null, null);
    }
  }

  record Interval(int left, int right) {}

  record DisplayState(BST<Integer> n, int level) {}

  record ArrayData(int val, int idx, int arrayId) implements Comparable<ArrayData> {
    @Override
    public int compareTo(ArrayData o) {
      int result = Integer.compare(val, o.val);
      if (result == 0) {
        result = Integer.compare(idx, o.val);
      }
      return result;
    }
  }
}
