package org.arcctg;

import java.util.Arrays;

public class DijkstraAlgorithm {

    private static final int VERTEX_COUNT = 10;
    private static final int INFINITY = 99;

    private int minDistance(int[] dist, boolean[] sptSet) {
        int minValue = INFINITY;
        int minIndex = -1;

        for (int vertexIndex = 0; vertexIndex < VERTEX_COUNT; vertexIndex++) {
            if (!sptSet[vertexIndex] && dist[vertexIndex] < minValue) {
                minValue = dist[vertexIndex];
                minIndex = vertexIndex;
            }
        }
        return minIndex;
    }

    private void printStep(int[] distances) {
        for (int vertexIndex = 0; vertexIndex < VERTEX_COUNT; vertexIndex++) {
            if (distances[vertexIndex] == Integer.MAX_VALUE) {
                System.out.print(INFINITY);
            } else {
                System.out.print(distances[vertexIndex]);
            }
            if (vertexIndex < VERTEX_COUNT - 1) {
                System.out.print(", ");
            }
        }
       
        System.out.println();
        System.out.println();
    }

    public void dijkstra(int[][] graph, int src) {
        int[] distances = new int[VERTEX_COUNT];

        boolean[] sptSet = new boolean[VERTEX_COUNT];

        Arrays.fill(distances, INFINITY);
        Arrays.fill(sptSet, false);

        distances[src] = 0;

        System.out.println("Крок 0 (Початковий стан):");
        printStep(distances);

        for (int count = 0; count < VERTEX_COUNT; count++) {
            int u = minDistance(distances, sptSet);

            if (u == -1) break;

            sptSet[u] = true;

            for (int neighborVertex = 0; neighborVertex < VERTEX_COUNT; neighborVertex++) {
                if (!sptSet[neighborVertex] && graph[u][neighborVertex] != 0
                    && distances[u] != INFINITY
                    && distances[u] + graph[u][neighborVertex] < distances[neighborVertex]) {
                    distances[neighborVertex] = distances[u] + graph[u][neighborVertex];
                }
            }

            System.out.printf("Крок %d (Відвідуємо вершину %d):\n", count + 1, u + 1);
            printStep(distances);
        }
    }

    public static void main(String[] args) {
        int[][] graph = new int[][]{
            {0, 5, 0, 13, 5, 2, 0, 0, 0, 0},
            {5, 0, 22, 0, 0, 19, 0, 0, 0, 0},
            {0, 22, 0, 0, 0, 0, 1, 0, 0, 0},
            {13, 0, 0, 0, 0, 0, 0, 3, 0, 0},
            {5, 0, 0, 0, 0, 0, 0, 0, 8, 0},
            {2, 19, 0, 0, 0, 0, 14, 0, 0, 2},
            {0, 0, 1, 0, 0, 14, 0, 0, 0, 6},
            {0, 0, 0, 3, 0, 0, 0, 0, 14, 0},
            {0, 0, 0, 0, 8, 0, 0, 14, 0, 16},
            {0, 0, 0, 0, 0, 2, 6, 0, 16, 0}
        };

        DijkstraAlgorithm t = new DijkstraAlgorithm();

        t.dijkstra(graph, 0);
    }
}
