package org.arcctg;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class DFS {

    public static String dfs(int[][] adjMatrix) {
        int n = adjMatrix.length;
        if (n == 0) return "";

        boolean[] visited = new boolean[n];
        List<Integer> result = new ArrayList<>();

        dfsHelper(0, adjMatrix, visited, result);

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfsHelper(i, adjMatrix, visited, result);
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int vertex : result) {
            sb.append(vertex + 1).append(" ");
        }

        return sb.toString();
    }

    private static void dfsHelper(int vertex, int[][] adjMatrix, boolean[] visited, List<Integer> result) {
        visited[vertex] = true;
        result.add(vertex);

        for (int i = 0; i < adjMatrix.length; i++) {
            if (adjMatrix[vertex][i] == 1 && !visited[i]) {
                dfsHelper(i, adjMatrix, visited, result);
            }
        }
    }

    private static void printStack(Stack<Integer> stack) {
        if (stack.isEmpty()) {
            System.out.println("∅");
            return;
        }

        StringBuilder sb = new StringBuilder();
        for (int i = stack.size() - 1; i >= 0; i--) {
            sb.append(stack.get(i) + 1); // +1 для нумерації з 1
            if (i > 0) {
                sb.append(" ");
            }
        }
        System.out.println(sb);
    }

    public static void dfsTraversalWithStates(int[][] adjMatrix) {
        int numVertices = adjMatrix.length;

        Stack<Integer> stack = new Stack<>();
        boolean[] visited = new boolean[numVertices];

        printStack(stack);

        int startIndex = 0;

        stack.push(startIndex);
        visited[startIndex] = true;

        printStack(stack);

        while (!stack.isEmpty()) {
            int currentVertex = stack.peek();

            int nextUnvisitedNeighbor = -1;
            for (int neighborIndex = 0; neighborIndex < numVertices; neighborIndex++) {
                if (adjMatrix[currentVertex][neighborIndex] == 1 && !visited[neighborIndex]) {
                    nextUnvisitedNeighbor = neighborIndex;
                    break;
                }
            }

            if (nextUnvisitedNeighbor != -1) {
                visited[nextUnvisitedNeighbor] = true;

                stack.push(nextUnvisitedNeighbor);

                printStack(stack);
            } else {
                stack.pop();

                printStack(stack);
            }
        }
    }

    public static void main(String[] args) {
        int[][] adjMatrix = {
            {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
            {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 1, 0, 1, 0}
        };

        String result = dfs(adjMatrix);
        System.out.println("Результат DFS: " + result);

        dfsTraversalWithStates(adjMatrix);
    }
}