package java_prep;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Chapter9 {
  // 9.12
  private static Integer subtreeIdx;

  public static void main(String[] args) {
    // 9.3
    System.out.println("9.3");
    List<Integer> inorder = List.of(3, 2, 4, 1, 5);
    List<Integer> preorder = List.of(1, 2, 3, 4, 5);
    BTN<Integer> tree = bTreeFrom(preorder, inorder);
    printTree(tree);
    System.out.println("9.3 lca -> " + lca(tree, tree.left.left, tree.right).data);

    // 9.5
    System.out.println("9.5");
    BTN<Integer> A = new BTN<>(1);
    BTN<Integer> B = new BTN<>(0);
    BTN<Integer> C = new BTN<>(0);
    BTN<Integer> D = new BTN<>(0);
    BTN<Integer> E = new BTN<>(1);
    BTN<Integer> F = new BTN<>(1);
    BTN<Integer> G = new BTN<>(1);
    BTN<Integer> H = new BTN<>(0);
    BTN<Integer> I = new BTN<>(1);
    BTN<Integer> J = new BTN<>(0);
    BTN<Integer> K = new BTN<>(0);
    BTN<Integer> L = new BTN<>(1);
    BTN<Integer> M = new BTN<>(1);
    BTN<Integer> N = new BTN<>(0);
    BTN<Integer> O = new BTN<>(0);
    BTN<Integer> P = new BTN<>(0);
    tree = A;
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
    O.right = P;
    K.left = L;
    K.right = N;
    L.right = M;
    printTree(tree, /* characterize= */ false);
    System.out.println("9.5 -> " + sumRootToLeafPaths(tree));

    // 9.6
    System.out.println("9.6 -> " + hasPathSum(makeFigure91(), 591));

    // 9.11
    System.out.println("9.11");
    inorder = List.of(6, 2, 1, 5, 8, 3, 4, 9, 7);
    preorder = List.of(8, 2, 6, 5, 1, 3, 4, 7, 9);
    tree = bTreeFrom(preorder, inorder);
    printTree(tree);

    // 9.12
    System.out.println("9.12");
    preorder =
        Arrays.asList(
            8, 2, 6, null, null, 5, 1, null, null, null, 3, null, 4, null, 7, 9, null, null, null);
    printTree(reconstructPreorder(preorder));
  }

  // 9.3
  private static BTN<Integer> lca(BTN<Integer> tree, BTN<Integer> n0, BTN<Integer> n1) {
    return lcaHelper(tree, n0, n1).lca();
  }

  // 9.5
  public static int sumRootToLeafPaths(BTN<Integer> tree) {
    return sumRootToLeafPathsHelper(tree, 0);
  }

  public static int sumRootToLeafPathsHelper(BTN<Integer> tree, int partialSum) {
    if (tree == null) {
      return 0;
    }

    partialSum = partialSum << 1 | tree.data;

    // Leaf
    if (tree.left == null && tree.right == null) {
      System.out.println("<tree_value> = " + partialSum);
      return partialSum;
    }
    // Non-leaf
    return sumRootToLeafPathsHelper(tree.left, partialSum)
        + sumRootToLeafPathsHelper(tree.right, partialSum);
  }

  // 9.6
  public static boolean hasPathSum(BTN<Integer> tree, int sumTo) {
    if (tree == null) return false;
    if (tree.left == null && tree.right == null) return tree.data == sumTo;
    return hasPathSum(tree.left, sumTo - tree.data) || hasPathSum(tree.right, sumTo - tree.data);
  }

  private static LcaResult lcaHelper(BTN<Integer> tree, BTN<Integer> n0, BTN<Integer> n1) {
    if (tree == null) return new LcaResult(0, null);

    LcaResult leftResult = lcaHelper(tree.left, n0, n1);
    if (leftResult.numFound == 2) return leftResult;
    LcaResult rightResult = lcaHelper(tree.right, n0, n1);
    if (rightResult.numFound == 2) return rightResult;

    int numFound =
        leftResult.numFound()
            + rightResult.numFound()
            + (tree == n0 ? 1 : 0)
            + (tree == n1 ? 1 : 0);
    return new LcaResult(numFound, numFound == 2 ? tree : null);
  }

  // 9.11
  private static BTN<Integer> bTreeFrom(List<Integer> preOrder, List<Integer> inOrder) {
    return bTreeFrom(
        preOrder,
        /* preorderStart= */ 0,
        preOrder.size(),
        /* inorderStart= */ 0,
        inOrder.size(),
        IntStream.range(0, inOrder.size()).boxed().collect(Collectors.toMap(inOrder::get, i -> i)));
  }

  // 9.12
  public static BTN<Integer> reconstructPreorder(List<Integer> preorder) {
    subtreeIdx = 0;
    return reconstructPreorderSubtree(preorder);
  }

  private static BTN<Integer> reconstructPreorderSubtree(List<Integer> preorder) {
    Integer subtreeKey = preorder.get(subtreeIdx);
    ++subtreeIdx;
    System.out.printf("%d : (%s)%n", subtreeIdx, subtreeKey == null ? "null" : subtreeKey);
    if (subtreeKey == null) return null;
    BTN<Integer> left = reconstructPreorderSubtree(preorder);
    BTN<Integer> right = reconstructPreorderSubtree(preorder);
    return new BTN<>(subtreeKey, left, right);
  }

  private static BTN<Integer> bTreeFrom(
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

    return new BTN<>(
        preorder.get(preorderStart),
        bTreeFrom(
            preorder,
            preorderStart + 1,
            preorderStart + 1 + leftTreeSize,
            inOrderStart,
            rootInorder,
            mapInorder),
        bTreeFrom(
            preorder,
            preorderStart + 1 + leftTreeSize,
            preOrderEnd,
            rootInorder + 1,
            inOrderEnd,
            mapInorder));
  }

  private static void printTree(BTN<Integer> t) {
    printTree(t, /* characterize= */ true);
  }

  private static void printTree(BTN<Integer> t, boolean characterize) {
    ArrayDeque<BTN<Integer>> bfs = new ArrayDeque<>();
    bfs.addFirst(t);

    while (!bfs.isEmpty()) {
      BTN<Integer> c = bfs.removeFirst();

      System.out.println(characterize ? (char) ('A' + c.data - 1) : c.data);
      if (c.left != null) bfs.addLast(c.left);
      if (c.right != null) bfs.addLast(c.right);
    }
  }

  private static BTN<Integer> makeFigure91() {
    BTN<Integer> A = new BTN<>(314);
    BTN<Integer> B = new BTN<>(6);
    BTN<Integer> C = new BTN<>(271);
    BTN<Integer> D = new BTN<>(28);
    BTN<Integer> E = new BTN<>(0);
    BTN<Integer> F = new BTN<>(561);
    BTN<Integer> G = new BTN<>(3);
    BTN<Integer> H = new BTN<>(17);
    BTN<Integer> I = new BTN<>(6);
    BTN<Integer> J = new BTN<>(2);
    BTN<Integer> K = new BTN<>(1);
    BTN<Integer> L = new BTN<>(401);
    BTN<Integer> M = new BTN<>(641);
    BTN<Integer> N = new BTN<>(257);
    BTN<Integer> O = new BTN<>(271);
    BTN<Integer> P = new BTN<>(28);
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

  private record LcaResult(int numFound, BTN<Integer> lca) {}

  public static class BTN<T> {
    public T data;
    public BTN<T> left, right;

    public BTN(T data) {
      this.data = data;
      left = null;
      right = null;
    }

    public BTN(T data, BTN<T> left, BTN<T> right) {
      this.data = data;
      this.left = left;
      this.right = right;
    }
  }
}
