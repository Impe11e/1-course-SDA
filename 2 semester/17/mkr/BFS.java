package org.arcctg;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class BFS {

    public static void bfsTraversalWithStates(int[][] adjMatrix, int startVertex) {
        int numVertices = adjMatrix.length;
        List<Integer> order = new ArrayList<>();

        Queue<Integer> bfsQueue = new LinkedList<>();
        Queue<Integer> printQueue = new LinkedList<>();
        boolean[] visited = new boolean[numVertices + 1];

        System.out.println(formatQueueForTable(printQueue));

        visited[startVertex] = true;
        bfsQueue.offer(startVertex);
        printQueue.offer(startVertex);

        System.out.println(formatQueueForTable(printQueue));

        while (!bfsQueue.isEmpty()) {
            int currentVertex = bfsQueue.poll();

            order.add(currentVertex);

            for (int neighbor = 1; neighbor <= numVertices; neighbor++) {
                if (adjMatrix[currentVertex - 1][neighbor - 1] == 1 && !visited[neighbor]) {
                    visited[neighbor] = true;
                    bfsQueue.offer(neighbor);
                    printQueue.offer(neighbor);

                    System.out.println(formatQueueForTable(printQueue));
                }
            }

            if (!printQueue.isEmpty() && printQueue.peek() == currentVertex) {
                printQueue.poll();
            }

            if (!printQueue.isEmpty() || bfsQueue.isEmpty()) {
                System.out.println(formatQueueForTable(printQueue));
            }
        }

        System.out.println("Порядок обходу BFS: " + order.toString().replace("[", "").replace("]", ""));
    }

    private static String formatQueueForTable(Queue<Integer> queue) {
        if (queue.isEmpty()) {
            return "∅";
        }

        StringBuilder sb = new StringBuilder();

        for (int vertex : queue) {
            sb.insert(0, vertex + " ");
        }

        return sb.toString().trim();
    }

    public static void main(String[] args) {
        int[][] adjMatrix = {
            {0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0}
        };
        int start = 1;

        System.out.println("Послідовність станів черги для BFS:");
        bfsTraversalWithStates(adjMatrix, start);
    }
}
