package java_prep;

import java.util.ArrayDeque;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Chapter14 {
  public static int rootIdx;

  public static void main(String[] args) {
    printTree("", makeBST());
    BST<Integer> lca = findLCA(makeBST(), new BST<>(2, null, null), new BST<>(107, null, null));
    System.out.println("14.4 -> " + lca.data);

    List<Integer> preorder = List.of(43, 23, 37, 29, 31, 41, 47, 53);
    BST<Integer> t = rebuildBSTFromPreorder(preorder);
    printTree("14.5", t);

    BST<Integer> balancedTree = buildMinHeightBST(List.of(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11));
    printTree("14.8", balancedTree);
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

  /** Helper utilities. */
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

  /** Make BST figure 14.2 on page 226 */
  private static BST<Integer> makeBST() {
    List<Integer> inorder = List.of(-14, -10, 2, 106, 107, 108, 243, 285, 286, 401);
    List<Integer> preorder = List.of(108, 106, -10, -14, 2, 107, 285, 243, 286, 401);
    return bstFrom(preorder, inorder);
  }

  public record BST<T>(T data, BST<T> left, BST<T> right) {}

  record DisplayState(BST<Integer> n, int level) {}
}
