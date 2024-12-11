package java_prep;

import java.util.ArrayList;
import java.util.List;

public class Chapter18 {
    public static void main(String[] args) {

    }
    private static class Coordinate {
        private final int x, y;

        public Coordinate(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || o.getClass() != getClass()) return false;

            Coordinate that = (Coordinate) o;
            if (x != that.x || y != that.y) return false;
            return true;
        }
    }

    public enum Color {WHITE, BLACK}

    public static List<Coordinate> searchMaze(List<List<Color>> maze,
                                              Coordinate s, Coordinate e) {
        List<Coordinate> path = new ArrayList<>();
        searchMazeHelper(maze, s, e, path);
        return path;
    }

    // Perform a DFS to find a feasible path
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
