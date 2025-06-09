package org.arcctg;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class PruferCodeConverter {

    public static List<Integer> graphToPrufer(int n, List<int[]> edges) {
        if (n <= 2) {
            return new ArrayList<>();
        }

        List<Set<Integer>> adj = new ArrayList<>();
        int[] degree = new int[n + 1];

        for (int i = 0; i <= n; i++) {
            adj.add(new HashSet<>());
        }

        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }

        List<Integer> pruferCode = new ArrayList<>();

        for (int k = 0; k < n - 1; k++) {
            for (int i = 1; i <= n; i++) {
                if (degree[i] == 1) {
                    int neighbor = adj.get(i).iterator().next();
                    pruferCode.add(neighbor);

                    degree[i]--;
                    degree[neighbor]--;
                    adj.get(neighbor).remove(i);
                    break;
                }
            }
        }

        return pruferCode;
    }

    public static List<int[]> pruferToGraph(List<Integer> pruferCode) {
        int n = pruferCode.size() + 1;
        List<int[]> edges = new ArrayList<>();
        List<Integer> code = new ArrayList<>(pruferCode);

        List<Integer> vertices = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            vertices.add(i);
        }

        while (!code.isEmpty()) {
            int leaf = -1;
            for (Integer v : vertices) {
                if (!code.contains(v)) {
                    leaf = v;
                    break;
                }
            }

            int neighbor = code.get(0);
            edges.add(new int[]{leaf, neighbor});

            vertices.remove(Integer.valueOf(leaf));
            code.remove(0);
        }

        return edges;
    }

    public static void main(String[] args) {
        System.out.println("Завдання 1: Граф -> Код Прюфера");
        int n1 = 6;

        List<int[]> edges1 = Arrays.asList(
            new int[]{1, 2},
            new int[]{1, 4},
            new int[]{3, 5},
            new int[]{4, 5},
            new int[]{5, 6}
        );

        List<Integer> correctCode = graphToPrufer(n1, edges1);
        System.out.println("Код Прюфера: " + correctCode);

        System.out.println("\n------------------------------------------\n");

        System.out.println("Завдання 2: Код Прюфера -> Граф");
        List<Integer> codeToDecode = Arrays.asList(2,2,5,5,6);
        List<int[]> restoredEdges = pruferToGraph(codeToDecode);

        System.out.println("Відновлені ребра:");
        restoredEdges.forEach(e -> System.out.println(Arrays.toString(e)));
    }
}