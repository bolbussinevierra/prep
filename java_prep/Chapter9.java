package java_prep;

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
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

  private static LcaResult lcaHelper(BTN<Integer> tree, BTN<Integer> n0, BTN<Integer> n1) {
    if (tree == null) return new LcaResult(0, null);

    LcaResult leftResult = lcaHelper(tree.left, n0, n1);
    if (leftResult.numFound == 2) return leftResult;
    LcaResult rightResult = lcaHelper(tree.right, n0, n1);
    if (rightResult.numFound == 2) return rightResult;

    int numFound = leftResult.numFound() + rightResult.numFound() + (tree == n0 ? 1 : 0) + (tree == n1 ? 1: 0);
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

  private record LcaResult(int numFound, BTN<Integer> lca) {}

  private static void printTree(BTN<Integer> t) {
    ArrayDeque<BTN<Integer>> bfs = new ArrayDeque<>();
    bfs.addFirst(t);

    while (!bfs.isEmpty()) {
      BTN<Integer> c = bfs.removeFirst();

      System.out.println((char) ('A' + c.data - 1));
      if (c.left != null) bfs.addLast(c.left);
      if (c.right != null) bfs.addLast(c.right);
    }
  }

  public static class BTN<T> {
    public T data;
    public BTN<T> left, right;

    public BTN(T data, BTN<T> left, BTN<T> right) {
      this.data = data;
      this.left = left;
      this.right = right;
    }
  }
}
