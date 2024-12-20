package java_prep;

import java.util.ArrayDeque;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Chapter14 {
    public record BST<T>(T data, BST<T> left, BST<T> right) {
    }

    public static void main(String[] args) {
        BST<Integer> lca = findLCA(makeBST(), new BST<>(2, null, null), new BST<>(107, null, null));
        System.out.println("14.4 -> " + lca.data);
    }

    // 14.4
    public static BST<Integer> findLCA(
            BST<Integer> t,
            BST<Integer> A,
            BST<Integer> B) {
        // Identify which is smaller/bigger
        BST<Integer> s = A.data < B.data ? A : B;
        BST<Integer> b = s == A ? B: A;

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

    private static BST<Integer> bstFrom(
            List<Integer> preOrder, List<Integer> inOrder) {
        return bstFrom(
                preOrder,
                /*preorderStart=*/0,
                preOrder.size(),
                /*inorderStart=*/0,
                inOrder.size(),
                IntStream.range(0, inOrder.size())
                        .boxed()
                        .collect(Collectors.toMap(inOrder::get, i -> i)));
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
                bstFrom(preorder, preorderStart + 1, preorderStart + 1 + leftTreeSize,
                        inOrderStart, rootInorder, mapInorder),
                bstFrom(preorder, preorderStart + 1 + leftTreeSize, preOrderEnd,
                        rootInorder + 1, inOrderEnd, mapInorder));

    }

    private static void printTree(BST<Integer> t) {
        ArrayDeque<BST<Integer>> bfs = new ArrayDeque<>();
        bfs.addFirst(t);

        while (!bfs.isEmpty()) {
            BST<Integer> c = bfs.removeFirst();
            System.out.println(c.data);
            if (c.left != null) bfs.addLast(c.left);
            if (c.right != null) bfs.addLast(c.right);
        }
    }

    /** Make BST figure 14.2 on page 226 */
    private static BST<Integer> makeBST() {
        List<Integer> inorder =   List.of(-14, -10,   2, 106, 107, 108, 243, 285, 286, 401);
        List<Integer> preorder =  List.of(108, 106, -10, -14,   2, 107, 285, 243, 286, 401);
        return bstFrom(preorder, inorder);
    }
}
