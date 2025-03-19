package java_prep;

import java.util.*;

public class Chapter18 {
  public static void main(String[] args) {
    // 18.1
    searchMaze(List.of(), new Coordinate(0, 0), new Coordinate(0, 0));

    // 18.2
    flipColor(0, 0, List.of(new ArrayList<>(List.of(Boolean.FALSE))));

    // 18.3
    List<List<Character>> board =
        List.of(
            Arrays.asList('B', 'B', 'B', 'B'),
            Arrays.asList('W', 'B', 'W', 'B'),
            Arrays.asList('B', 'W', 'W', 'B'),
            Arrays.asList('B', 'B', 'B', 'B'));
    fillSorroundedRegions(board);
    System.out.println("--- 18.3 ----");
    for (int row = 0; row < board.size(); ++row) {
      System.out.println(board.get(row));
    }
    System.out.println("-------------");

    // 18.4
    Vertex A = new Vertex('A');
    Vertex B = new Vertex('B');
    Vertex C = new Vertex('C');
    A.edges.add(B);
    C.edges.add(B);
    System.out.println("18.4a -> " + isDeadlocked(List.of(A, B, C)));

    A.edges.clear();
    B.edges.clear();
    C.edges.clear();
    A.edges.add(B);
    B.edges.add(C);
    C.edges.add(A);
    System.out.println("18.4b -> " + isDeadlocked(List.of(A, B, C)));

    // 18.5
    Vertex one = new Vertex(1);
    Vertex two = new Vertex(2);
    Vertex three = new Vertex(3);
    one.edges.add(two);
    two.edges.add(three);
    three.edges.add(one);

    Vertex cloned = cloneGraph(one);
    System.out.println("18.5 -> " + cloned.edges + " " + cloned.edges.getFirst().edges);

    // 18.6
    System.out.println("18.6 -> " + isBipartite(List.of(makeFigure188())));

    // 18.7
    Set<String> D = new HashSet<>(List.of("bat", "cot", "dog", "dag", "dot", "cat"));
    String s = "cat";
    String t = "dog";
    System.out.println("18.7 -> " + transformString(D, s, t));
  }

  // 18.1
  public static List<Coordinate> searchMaze(List<List<Color>> maze, Coordinate s, Coordinate e) {
    List<Coordinate> path = new ArrayList<>();
    searchMazeHelper(maze, s, e, path);
    return path;
  }

  // 18.2
  public static void flipColor(int x, int y, List<List<Boolean>> image) {
    boolean color = image.get(x).get(y);

    Queue<Coordinate> q = new ArrayDeque<>();
    image.get(x).set(y, !color); // Flips
    q.add(new Coordinate(x, y));

    while (!q.isEmpty()) {
      Coordinate c = q.remove();
      for (Coordinate next :
          List.of(
              new Coordinate(c.x, c.y + 1),
              new Coordinate(c.x, c.y - 1),
              new Coordinate(c.x + 1, c.y),
              new Coordinate(c.x - 1, c.y))) {
        if (next.x >= 0
            && next.x < image.size()
            && next.y >= 0
            && next.y < image.get(next.x).size()
            && image.get(next.x).get(next.y) == color) {
          image.get(next.x).set(next.y, !color);
          q.add(next);
        }
      }
    }
  }

  // 18.3
  public static void fillSorroundedRegions(List<List<Character>> board) {
    // Identify regions reachable via white path starting from the first or last columns.
    for (int row = 0; row < board.size(); ++row) {
      markBoundaryRegion(row, /* col= */ 0, board);
      markBoundaryRegion(row, /* col= */ board.get(row).size() - 1, board);
    }

    // Identify regions reachable via white path starting from the first or last rows
    for (int col = 0; col < board.getFirst().size(); ++col) {
      markBoundaryRegion(/* row= */ 0, col, board);
      markBoundaryRegion(/* row= */ board.size() - 1, col, board);
    }

    // Mark the unreachable regions as black.
    for (int row = 0; row < board.size(); ++row) {
      for (int col = 0; col < board.get(row).size(); ++col) {
        board.get(row).set(col, board.get(row).get(col) != 'R' ? 'B' : 'W');
      }
    }
  }

  // 18.4
  public static boolean isDeadlocked(List<Vertex> graph) {
    Set<Vertex> processed = new HashSet<>();
    Set<Vertex> processing = new HashSet<>();
    return graph.stream().anyMatch(v -> hasCycle(v, processing, processed));
  }

  private static boolean hasCycle(Vertex v, Set<Vertex> processing, Set<Vertex> processed) {
    if (processing.contains(v)) return true;

    processing.add(v);
    if (v.edges.stream()
        .anyMatch(u -> !processed.contains(u) && hasCycle(u, processing, processed))) {
      return true;
    }
    processing.remove(v);
    processed.add(v);
    return false;
  }

  private static void markBoundaryRegion(int row, int col, List<List<Character>> board) {
    Queue<Coordinate> q = new ArrayDeque<>();
    q.add(new Coordinate(row, col));
    // Uses BFS to traverse this region.
    while (!q.isEmpty()) {
      Coordinate curr = q.poll();
      if (curr.x >= 0
          && curr.x < board.size()
          && curr.y >= 0
          && curr.y < board.get(curr.x).size()
          && board.get(curr.x).get(curr.y) == 'W') {
        board.get(curr.x).set(curr.y, 'R');
        q.add(new Coordinate(curr.x - 1, curr.y));
        q.add(new Coordinate(curr.x + 1, curr.y));
        q.add(new Coordinate(curr.x, curr.y - 1));
        q.add(new Coordinate(curr.x, curr.y + 1));
      }
    }
  }

  // 18.5
  public static Vertex cloneGraph(Vertex graph) {
    if (graph == null) return null;
    Map<Vertex, Vertex> vertexMap = new HashMap<>();
    Queue<Vertex> q = new ArrayDeque<>();

    q.add(graph);
    vertexMap.put(graph, new Vertex(graph.label));

    while (!q.isEmpty()) {
      Vertex v = q.remove();
      for (Vertex e : v.edges) {
        if (vertexMap.putIfAbsent(e, new Vertex(e.label)) == null) {
          q.add(e);
        }
        // Copy edge.
        vertexMap.get(v).edges.add(vertexMap.get(e));
      }
    }
    return vertexMap.get(graph);
  }

  // 18.6
  public static boolean isBipartite(List<Vertex> g) {
    return g.stream().allMatch(v -> v.label != -1 || isBipartiteHelperBfs(v));
  }

  private static boolean isBipartiteHelperBfs(Vertex v) {
    v.label = 0; // even (vs odd for children)
    Queue<Vertex> q = new ArrayDeque<>();
    q.add(v);

    while (!q.isEmpty()) {
      for (Vertex u : q.peek().edges) {
        if (u.label == -1) { // unvisited
          u.label = q.peek().label + 1;
          q.add(u);
        } else if (u.label == q.peek().label) {
          return false;
        }
      }
      q.remove();
    }
    return true;
  }

  // 18.7
  public static int transformString(Set<String> D, String s, String t) {
    Set<String> unvisited = new HashSet<>(D);
    Queue<StringDistance> q = new ArrayDeque<>();
    unvisited.remove(s);
    q.add(new StringDistance(s, 0));

    StringDistance f;
    while ((f = q.poll()) != null) {
      // Are we done?
      if (f.candidate().equals(t)) {
        return f.distance();
      }

      // Try all children that are 1 character transformation away
      String str = f.candidate();
      for (int i = 0; i < str.length(); ++i) {
        String strStart = i == 0 ? "" : str.substring(0, i);
        String strEnd = i + 1 < str.length() ? str.substring(i + 1) : "";
        for (char c = 'a'; c <= 'z'; ++c) {
          String newCandidate = strStart + c + strEnd;
          if (unvisited.contains(newCandidate)) {
            unvisited.remove(newCandidate);
            q.add(new StringDistance(newCandidate, f.distance() + 1));
          }
        }
      }
    }
    return -1; // Cannot find a transformation.
  }

  // Perform a DFS to find a feasible path.
  private static boolean searchMazeHelper(
      List<List<Color>> maze, Coordinate c, Coordinate e, List<Coordinate> path) {
    // Ensure within maze and white cell
    if (c.x < 0
        || c.x >= maze.size()
        || c.y < 0
        || c.y >= maze.get(c.x).size()
        || maze.get(c.x).get(c.y) != Color.WHITE) {
      return false;
    }
    path.add(c);
    maze.get(c.x).set(c.y, Color.BLACK);
    if (c.equals(e)) {
      return true;
    }

    for (Coordinate nextMove :
        List.of(
            new Coordinate(c.x, c.y + 1),
            new Coordinate(c.x, c.y - 1),
            new Coordinate(c.x + 1, c.y),
            new Coordinate(c.x - 1, c.y))) {
      if (searchMazeHelper(maze, nextMove, e, path)) {
        return true;
      }
    }
    // Cannot find a path, remove the entry added to path.
    path.removeLast();
    return false;
  }

  public enum Color {
    WHITE,
    BLACK
  }

  public static class Vertex {
    public int label;
    public List<Vertex> edges;

    public Vertex(int label) {
      this.label = label;
      edges = new ArrayList<>();
    }
  }

  public record Coordinate(int x, int y) {}

  private record StringDistance(String candidate, Integer distance) {}

  private static Vertex makeFigure188() {
    Vertex A = new Vertex(-1);
    Vertex B = new Vertex(-1);
    Vertex C = new Vertex(-1);
    Vertex D = new Vertex(-1);
    Vertex E = new Vertex(-1);
    Vertex F = new Vertex(-1);
    Vertex G = new Vertex(-1);
    Vertex H = new Vertex(-1);
    Vertex I = new Vertex(-1);
    Vertex J = new Vertex(-1);
    Vertex K = new Vertex(-1);
    Vertex L = new Vertex(-1);
    Vertex M = new Vertex(-1);
    Vertex N = new Vertex(-1);
    Vertex O = new Vertex(-1);
    Vertex P = new Vertex(-1);
    Vertex Q = new Vertex(-1);
    Vertex R = new Vertex(-1);
    Vertex S = new Vertex(-1);
    Vertex T = new Vertex(-1);
    Vertex U = new Vertex(-1);
    Vertex V = new Vertex(-1);

    A.edges.addAll(List.of(B, J));
    B.edges.addAll(List.of(C, K));
    C.edges.addAll(List.of(D, L));
    D.edges.addAll(List.of(E, M));
    E.edges.add(F);
    F.edges.addAll(List.of(G, N));
    G.edges.add(H);
    H.edges.addAll(List.of(I, N));
    I.edges.addAll(List.of(H, V));
    J.edges.addAll(List.of(K, O));
    K.edges.addAll(List.of(P, L));
    L.edges.addAll(List.of(M, Q));
    M.edges.addAll(List.of(R, F));
    N.edges.addAll(List.of(F, H, T));
    O.edges.addAll(List.of(J, P));
    P.edges.addAll(List.of(K, Q));
    Q.edges.addAll(List.of(P, L, R));
    R.edges.addAll(List.of(M, S));
    S.edges.addAll(List.of(R, T));
    T.edges.addAll(List.of(S, N, U));
    U.edges.addAll(List.of(T, V));
    V.edges.addAll(List.of(U, N, I));

    return A;
  }
}
