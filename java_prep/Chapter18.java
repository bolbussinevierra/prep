package java_prep;

import java.util.*;

public class Chapter18 {
    public static void main(String[] args) {
        // 18.1
        searchMaze(List.of(), new Coordinate(0, 0), new Coordinate(0, 0));

        // 18.7
        Set<String> D = new HashSet<>(List.of("bat", "cot", "dog", "dag", "dot", "cat"));
        String s = "cat";
        String t = "dog";
        System.out.println("18.7 -> " + transformString(D, s, t));
    }

    private record Coordinate(int x, int y) {}
    private record StringDistance(String candidate, Integer distance) {}

    public enum Color {WHITE, BLACK}

    public static List<Coordinate> searchMaze(List<List<Color>> maze,
                                              Coordinate s, Coordinate e) {
        List<Coordinate> path = new ArrayList<>();
        searchMazeHelper(maze, s, e, path);
        return path;
    }

    private static int transformString(Set<String> D, String s, String t) {
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
                String strEnd = i + 1 < str.length() ? str.substring(i + 1): "";
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
    private static boolean searchMazeHelper(List<List<Color>> maze, Coordinate c,
                                            Coordinate e, List<Coordinate> path) {
        // Ensure within maze and white cell
        if (c.x < 0 || c.x >= maze.size()
                || c.y < 0 || c.y >= maze.get(c.x).size() ||
                maze.get(c.x).get(c.y) != Color.WHITE) {
            return false;
        }
        path.add(c);
        maze.get(c.x).set(c.y, Color.BLACK);
        if (c.equals(e)) {
            return true;
        }

        for (Coordinate nextMove : List.of(new Coordinate(c.x, c.y + 1),
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
}
