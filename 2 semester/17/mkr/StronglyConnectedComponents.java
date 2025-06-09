package org.arcctg;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class StronglyConnectedComponents {

    private final int vertices;
    private final List<List<Integer>> adj;
    private final List<List<Integer>> adjTranspose;

    public StronglyConnectedComponents(int[][] matrix) {
        this.vertices = matrix.length;
        this.adj = new ArrayList<>(vertices);
        this.adjTranspose = new ArrayList<>(vertices);

        for (int i = 0; i < vertices; i++) {
            adj.add(new ArrayList<>());
            adjTranspose.add(new ArrayList<>());
        }

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (matrix[i][j] == 1) {
                    adj.get(i).add(j);
                    adjTranspose.get(j).add(i);
                }
            }
        }
    }

    private void fillOrder(int v, boolean[] visited, Stack<Integer> stack) {
        visited[v] = true;
        for (int neighbor : adj.get(v)) {
            if (!visited[neighbor]) {
                fillOrder(neighbor, visited, stack);
            }
        }
        stack.push(v);
    }

    private void collectComponent(int v, boolean[] visited, List<Integer> component) {
        visited[v] = true;
        component.add(v + 1);
        for (int neighbor : adjTranspose.get(v)) {
            if (!visited[neighbor]) {
                collectComponent(neighbor, visited, component);
            }
        }
    }

    public void findAndPrintSCCs() {
        Stack<Integer> stack = new Stack<>();
        boolean[] visited = new boolean[vertices];

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                fillOrder(i, visited, stack);
            }
        }

        Arrays.fill(visited, false);

        List<List<Integer>> sccList = new ArrayList<>();

        while (!stack.isEmpty()) {
            int v = stack.pop();
            if (!visited[v]) {
                List<Integer> component = new ArrayList<>();
                collectComponent(v, visited, component);
                sccList.add(component);
            }
        }

        sccList.sort((a, b) -> {
            if (a.size() != b.size()) {
                return Integer.compare(a.size(), b.size());
            }
            return Integer.compare(a.get(0), b.get(0));
        });

        System.out.println("Знайдені компоненти сильної зв'язності:");
        for (int i = 0; i < sccList.size(); i++) {
            List<Integer> scc = sccList.get(i);
            if (scc.size() > 1) Collections.sort(scc);

            String sccString = scc.toString().replaceAll("[\\[\\]]", "");
            System.out.printf("Компонента %d: %s%n", i + 1, sccString);
        }
    }

    public static void main(String[] args) {
        int[][] matrix = {
            {0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0}
        };

        StronglyConnectedComponents sccFinder = new StronglyConnectedComponents(matrix);
        sccFinder.findAndPrintSCCs();
    }
}
