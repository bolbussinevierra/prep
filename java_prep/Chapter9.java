package java_prep;

import java.util.ArrayDeque;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Chapter9 {
    public static class BTN<T> {
        public T data;
        public BTN<T> left, right;

        public BTN(T data, BTN<T> left, BTN<T> right) {
            this.data = data;
            this.left = left;
            this.right = right;
        }
    }

    public static void main(String[] args) {
        // 9.11
        List<Integer> inorder = List.of(6, 2, 1, 5, 8, 3, 4, 9, 7);
        List<Integer> preorder =  List.of(8, 2, 6, 5, 1, 3, 4, 7, 9);
        BTN<Integer> tree = bTreeFrom(preorder, inorder);
        printTree(tree);

    }

    // 9.11
    private static BTN<Integer> bTreeFrom(List<Integer> preOrder, List<Integer> inOrder) {
        return bTreeFrom(preOrder, /*preorderStart=*/0, preOrder.size(), /*inorderStart=*/0, inOrder.size(),
                IntStream.range(0, inOrder.size())
                        .boxed().collect(Collectors.toMap(inOrder::get, i -> i)));
    }

    private static BTN<Integer> bTreeFrom(List<Integer> preorder, int preorderStart, int preOrderEnd,
                                          int inOrderStart, int inOrderEnd, Map<Integer, Integer> mapInorder) {
        if (preOrderEnd <= preorderStart || inOrderEnd <= inOrderStart) {
            return null;
        }
        int rootInorder = mapInorder.get(preorder.get(preorderStart));
        int leftTreeSize = rootInorder - inOrderStart;

        return new BTN<>(
                preorder.get(preorderStart),
                bTreeFrom(preorder, preorderStart + 1, preorderStart + 1 + leftTreeSize,
                        inOrderStart, rootInorder, mapInorder),
                bTreeFrom(preorder, preorderStart + 1 + leftTreeSize, preOrderEnd,
                        rootInorder + 1, inOrderEnd, mapInorder));

    }

    private static void printTree(BTN<Integer> t) {
        ArrayDeque<BTN<Integer>> bfs = new ArrayDeque<>();
        bfs.addFirst(t);

        while (!bfs.isEmpty()) {
            BTN<Integer> c = bfs.removeFirst();
            System.out.println((char)('A' + c.data - 1));
            if (c.left != null) bfs.addLast(c.left);
            if (c.right != null) bfs.addLast(c.right);
        }
    }
}
