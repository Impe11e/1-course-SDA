using SFML.Graphics;
using SFML.Window;
using SFML.System;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GraphVisualization
{
    public class Graph
    {
        private const int WindowWidth = 800;
        private const int WindowHeight = 600;
        private const int VertexRadius = 20;
        private const float ArrowLength = 10f;

        private readonly int n;
        private readonly int n3;
        private readonly int n4;
        private readonly int variantNumber;
        
        private int[,] directedMatrix;
        private int[,] undirectedMatrix;
        private int[,] modifiedDirectedMatrix;
        private int[,] reachabilityMatrix;
        private int[,] strongConnectivityMatrix;
        private int[,] condensationMatrix;
        
        private Vector2f[] vertexPositions;
        private List<List<int>> stronglyConnectedComponents;
        
        private int viewMode = 0; // 0 - original directed, 1 - original undirected, 2 - modified directed, 3 - paths, 4 - condensation

        private RenderWindow window;
        private Font font;

        public Graph()
        {
            n3 = 1; // From variant 4313
            n4 = 3; // From variant 4313
            n = 10 + n3; // n = 11
            variantNumber = 4313;
            
            directedMatrix = new int[n, n];
            undirectedMatrix = new int[n, n];
            modifiedDirectedMatrix = new int[n, n];
            vertexPositions = new Vector2f[n];

            InitializeWindow();
            InitializeVertexPositions();
            GenerateAdjacencyMatrices();
        }

        private void InitializeWindow()
        {
            var mode = new VideoMode(WindowWidth, WindowHeight);
            window = new RenderWindow(mode, "Lab 4 - Graph Characteristics and Connectivity");
            
            window.Closed += (s, e) => window.Close();
            window.KeyPressed += (s, e) =>
            {
                if (e.Code == Keyboard.Key.Right || e.Code == Keyboard.Key.Space)
                {
                    viewMode = (viewMode + 1) % 5;
                }
                else if (e.Code == Keyboard.Key.Left)
                {
                    viewMode = (viewMode + 4) % 5;
                }
                else if (e.Code == Keyboard.Key.Escape)
                {
                    window.Close();
                }
                else if (e.Code == Keyboard.Key.S)
                {
                    TakeScreenshot();
                }
            };

            try
            {
                string fontPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Fonts), "arial.ttf");
                font = new Font(fontPath);
            }
            catch (Exception)
            {
                Console.WriteLine("Could not load font. Text rendering will be disabled.");
            }
        }

        private void InitializeVertexPositions()
        {
            float marginX = 100;
            float marginY = 100;
            float width = WindowWidth - 2 * marginX;
            float height = WindowHeight - 2 * marginY;
            
            vertexPositions[0] = new Vector2f(marginX, marginY); // 1
            vertexPositions[1] = new Vector2f(marginX + width/3, marginY); // 2
            vertexPositions[2] = new Vector2f(marginX + 2*width/3, marginY); // 3
            vertexPositions[3] = new Vector2f(marginX + width, marginY); // 4
            
            vertexPositions[4] = new Vector2f(marginX + width, marginY + height/3); // 5
            vertexPositions[5] = new Vector2f(marginX + width, marginY + 2*height/3); // 6
            
            vertexPositions[6] = new Vector2f(marginX + width, marginY + height); // 7
            vertexPositions[7] = new Vector2f(marginX + width/2, marginY + height); // 8
            vertexPositions[8] = new Vector2f(marginX, marginY + height); // 9
            
            vertexPositions[9] = new Vector2f(marginX, marginY + 2*height/3); // 10
            vertexPositions[10] = new Vector2f(marginX, marginY + height/3); // 11
        }
        
        private void GenerateAdjacencyMatrices()
        {
            // Generate original directed matrix with coefficient k = 1.0 - n3 * 0.01 - n4 * 0.01 - 0.3
            Random rand = new Random(variantNumber);
            double[,] tempMatrix = new double[n, n];
            
            // Fill with random values in range [0, 2.0)
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    tempMatrix[i, j] = rand.NextDouble() * 2.0;
                }
            }
            
            // Original coefficient k = 1.0 - n3 * 0.01 - n4 * 0.01 - 0.3
            double k1 = 1.0 - n3 * 0.01 - n4 * 0.01 - 0.3;
            Console.WriteLine($"Original coefficient k1 = {k1}");
            
            // Round values
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    directedMatrix[i, j] = tempMatrix[i, j] * k1 >= 1.0 ? 1 : 0;
                }
            }
            
            // Generate undirected matrix from directed matrix
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    undirectedMatrix[i, j] = (directedMatrix[i, j] == 1 || directedMatrix[j, i] == 1) ? 1 : 0;
                }
            }
            
            // Generate modified directed matrix with coefficient k = 1.0 - n3 * 0.005 - n4 * 0.005 - 0.27
            double k2 = 1.0 - n3 * 0.005 - n4 * 0.005 - 0.27;
            Console.WriteLine($"Modified coefficient k2 = {k2}");
            
            // Round values for modified matrix
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    modifiedDirectedMatrix[i, j] = tempMatrix[i, j] * k2 >= 1.0 ? 1 : 0;
                }
            }
            
            // Print matrices
            PrintMatrix(directedMatrix, "Original Directed Matrix");
            PrintMatrix(undirectedMatrix, "Undirected Matrix");
            PrintMatrix(modifiedDirectedMatrix, "Modified Directed Matrix");
            
            // Calculate and analyze all required graph properties
            AnalyzeGraphs();
        }
        
        private void AnalyzeGraphs()
        {
            // Part 1: Original Graph Analysis
            Console.WriteLine("\n=== PART 1: ORIGINAL GRAPH ANALYSIS ===");
            
            // Calculate degrees
            var (inDegrees, outDegrees) = CalculateDirectedDegrees(directedMatrix);
            var undirectedDegrees = CalculateUndirectedDegrees(undirectedMatrix);
            
            // Print degrees
            Console.WriteLine("\nDirected Graph Degrees:");
            Console.WriteLine("Vertex | In-degree | Out-degree");
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine($"{i+1,6} | {inDegrees[i],9} | {outDegrees[i],10}");
            }
            
            Console.WriteLine("\nUndirected Graph Degrees:");
            Console.WriteLine("Vertex | Degree");
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine($"{i+1,6} | {undirectedDegrees[i],6}");
            }
            
            // Check if graphs are regular
            bool isDirectedRegular = IsRegular(inDegrees, outDegrees);
            bool isUndirectedRegular = IsRegular(undirectedDegrees);
            
            Console.WriteLine("\nRegularity Analysis:");
            if (isDirectedRegular)
            {
                Console.WriteLine($"Directed graph is regular with degree {inDegrees[0]}");
            }
            else
            {
                Console.WriteLine("Directed graph is not regular");
            }
            
            if (isUndirectedRegular)
            {
                Console.WriteLine($"Undirected graph is regular with degree {undirectedDegrees[0]}");
            }
            else
            {
                Console.WriteLine("Undirected graph is not regular");
            }
            
            // Find special vertices
            var (dirHanging, dirIsolated) = FindSpecialVertices(directedMatrix, true);
            var (undirHanging, undirIsolated) = FindSpecialVertices(undirectedMatrix, false);
            
            Console.WriteLine("\nSpecial Vertices:");
            Console.WriteLine("Directed Graph:");
            Console.WriteLine($"Hanging vertices: {string.Join(", ", dirHanging)}");
            Console.WriteLine($"Isolated vertices: {string.Join(", ", dirIsolated)}");
            
            Console.WriteLine("\nUndirected Graph:");
            Console.WriteLine($"Hanging vertices: {string.Join(", ", undirHanging)}");
            Console.WriteLine($"Isolated vertices: {string.Join(", ", undirIsolated)}");
            
            // Part 2: Modified Graph Analysis
            Console.WriteLine("\n=== PART 2: MODIFIED GRAPH ANALYSIS ===");
            
            // Calculate semi-degrees for modified graph
            var (modInDegrees, modOutDegrees) = CalculateDirectedDegrees(modifiedDirectedMatrix);
            
            Console.WriteLine("\nModified Directed Graph Semi-Degrees:");
            Console.WriteLine("Vertex | In-degree | Out-degree");
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine($"{i+1,6} | {modInDegrees[i],9} | {modOutDegrees[i],10}");
            }
            
            // Find paths of length 2 and 3
            var paths2 = FindPathsOfLength(modifiedDirectedMatrix, 2);
            var paths3 = FindPathsOfLength(modifiedDirectedMatrix, 3);
            
            Console.WriteLine($"\nPaths of length 2 ({paths2.Count} paths):");
            foreach (var path in paths2)
            {
                Console.WriteLine(FormatPath(path));
            }
            
            Console.WriteLine($"\nPaths of length 3 ({paths3.Count} paths):");
            foreach (var path in paths3)
            {
                Console.WriteLine(FormatPath(path));
            }
            
            // Calculate reachability matrix
            reachabilityMatrix = CalculateReachabilityMatrix(modifiedDirectedMatrix);
            PrintMatrix(reachabilityMatrix, "Reachability Matrix");
            
            // Calculate strong connectivity matrix
            strongConnectivityMatrix = CalculateStrongConnectivityMatrix(reachabilityMatrix);
            PrintMatrix(strongConnectivityMatrix, "Strong Connectivity Matrix");
            
            // Find strongly connected components
            stronglyConnectedComponents = FindStronglyConnectedComponents(strongConnectivityMatrix);
            
            Console.WriteLine("\nStrongly Connected Components:");
            for (int i = 0; i < stronglyConnectedComponents.Count; i++)
            {
                Console.WriteLine($"Component {i+1}: {string.Join(", ", stronglyConnectedComponents[i])}");
            }
            
            // Create condensation graph
            condensationMatrix = CreateCondensationMatrix(modifiedDirectedMatrix, stronglyConnectedComponents);
            PrintMatrix(condensationMatrix, "Condensation Graph Matrix");
        }
        
        private (int[] inDegrees, int[] outDegrees) CalculateDirectedDegrees(int[,] matrix)
        {
            int[] inDegrees = new int[n];
            int[] outDegrees = new int[n];
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matrix[i, j] == 1)
                    {
                        outDegrees[i]++;
                        inDegrees[j]++;
                    }
                }
            }
            
            return (inDegrees, outDegrees);
        }
        
        private int[] CalculateUndirectedDegrees(int[,] matrix)
        {
            int[] degrees = new int[n];
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matrix[i, j] == 1)
                    {
                        degrees[i]++;
                    }
                }
            }
            
            return degrees;
        }
        
        private bool IsRegular(int[] inDegrees, int[] outDegrees)
        {
            // A directed graph is regular if all vertices have the same in-degree = out-degree
            int firstInDegree = inDegrees[0];
            int firstOutDegree = outDegrees[0];
            
            if (firstInDegree != firstOutDegree)
                return false;
                
            for (int i = 1; i < n; i++)
            {
                if (inDegrees[i] != firstInDegree || outDegrees[i] != firstOutDegree)
                    return false;
            }
            
            return true;
        }
        
        private bool IsRegular(int[] degrees)
        {
            // An undirected graph is regular if all vertices have the same degree
            int firstDegree = degrees[0];
            
            for (int i = 1; i < n; i++)
            {
                if (degrees[i] != firstDegree)
                    return false;
            }
            
            return true;
        }
        
        private (List<int> hanging, List<int> isolated) FindSpecialVertices(int[,] matrix, bool isDirected)
        {
            List<int> hanging = new List<int>();
            List<int> isolated = new List<int>();
            
            if (isDirected)
            {
                var (inDegrees, outDegrees) = CalculateDirectedDegrees(matrix);
                
                for (int i = 0; i < n; i++)
                {
                    // Isolated vertex has in-degree = out-degree = 0
                    if (inDegrees[i] == 0 && outDegrees[i] == 0)
                    {
                        isolated.Add(i + 1); // 1-indexed for output
                    }
                    // Hanging vertex has total degree = 1
                    else if (inDegrees[i] + outDegrees[i] == 1)
                    {
                        hanging.Add(i + 1); // 1-indexed for output
                    }
                }
            }
            else
            {
                int[] degrees = CalculateUndirectedDegrees(matrix);
                
                for (int i = 0; i < n; i++)
                {
                    // Isolated vertex has degree = 0
                    if (degrees[i] == 0)
                    {
                        isolated.Add(i + 1); // 1-indexed for output
                    }
                    // Hanging vertex has degree = 1
                    else if (degrees[i] == 1)
                    {
                        hanging.Add(i + 1); // 1-indexed for output
                    }
                }
            }
            
            return (hanging, isolated);
        }
        
        private int[,] MatrixPower(int[,] matrix, int power)
        {
            if (power == 1)
                return (int[,])matrix.Clone();
                
            int[,] result = (int[,])matrix.Clone();
            
            for (int p = 1; p < power; p++)
            {
                int[,] temp = new int[n, n];
                
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        for (int k = 0; k < n; k++)
                        {
                            if (result[i, k] == 1 && matrix[k, j] == 1)
                            {
                                temp[i, j] = 1;
                                break;
                            }
                        }
                    }
                }
                
                result = temp;
            }
            
            return result;
        }
        
        private List<List<int>> FindPathsOfLength(int[,] matrix, int length)
        {
            List<List<int>> paths = new List<List<int>>();
            int[,] matrixPower = MatrixPower(matrix, length);
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matrixPower[i, j] == 1)
                    {
                        // Find all paths from i to j of length 'length'
                        List<int> currentPath = new List<int> { i };
                        FindAllPathsOfLength(matrix, i, j, length, currentPath, paths);
                    }
                }
            }
            
            return paths;
        }
        
        private void FindAllPathsOfLength(int[,] matrix, int start, int end, int length, List<int> currentPath, List<List<int>> paths)
        {
            if (currentPath.Count == length + 1)
            {
                if (currentPath[currentPath.Count - 1] == end)
                {
                    paths.Add(new List<int>(currentPath));
                }
                return;
            }
            
            int current = currentPath[currentPath.Count - 1];
            
            for (int next = 0; next < n; next++)
            {
                if (matrix[current, next] == 1)
                {
                    currentPath.Add(next);
                    FindAllPathsOfLength(matrix, start, end, length, currentPath, paths);
                    currentPath.RemoveAt(currentPath.Count - 1); // Backtrack
                }
            }
        }
        
        private string FormatPath(List<int> path)
        {
            // Convert to 1-indexed and format with dashes
            return string.Join(" – ", path.Select(v => (v + 1).ToString()));
        }
        
        private int[,] CalculateReachabilityMatrix(int[,] matrix)
        {
            int[,] result = new int[n, n];
            
            // Copy original matrix
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    result[i, j] = matrix[i, j];
                }
                // Add self-loops
                result[i, i] = 1;
            }
            
            // Warshall's algorithm for transitive closure
            for (int k = 0; k < n; k++)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (result[i, k] == 1 && result[k, j] == 1)
                        {
                            result[i, j] = 1;
                        }
                    }
                }
            }
            
            return result;
        }
        
        private int[,] CalculateStrongConnectivityMatrix(int[,] reachabilityMatrix)
        {
            int[,] result = new int[n, n];
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    // Vertices i and j are strongly connected if i can reach j and j can reach i
                    if (reachabilityMatrix[i, j] == 1 && reachabilityMatrix[j, i] == 1)
                    {
                        result[i, j] = 1;
                    }
                }
            }
            
            return result;
        }
        
        private List<List<int>> FindStronglyConnectedComponents(int[,] strongConnectivityMatrix)
        {
            List<List<int>> components = new List<List<int>>();
            bool[] visited = new bool[n];
            
            for (int vertex = 0; vertex < n; vertex++)
            {
                if (!visited[vertex])
                {
                    List<int> component = new List<int>();
                    DFSComponent(vertex, strongConnectivityMatrix, visited, component);
                    components.Add(component);
                }
            }
            
            return components;
        }
        
        private void DFSComponent(int vertex, int[,] matrix, bool[] visited, List<int> component)
        {
            visited[vertex] = true;
            component.Add(vertex + 1); // Add 1-indexed vertex
            
            for (int next = 0; next < n; next++)
            {
                if (matrix[vertex, next] == 1 && !visited[next])
                {
                    DFSComponent(next, matrix, visited, component);
                }
            }
        }
        
        private int[,] CreateCondensationMatrix(int[,] matrix, List<List<int>> components)
        {
            int numComponents = components.Count;
            int[,] condensationMatrix = new int[numComponents, numComponents];
            
            for (int i = 0; i < numComponents; i++)
            {
                for (int j = 0; j < numComponents; j++)
                {
                    if (i != j)
                    {
                        // Check if there's an edge from any vertex in component i to any vertex in component j
                        foreach (int v1 in components[i])
                        {
                            foreach (int v2 in components[j])
                            {
                                if (matrix[v1 - 1, v2 - 1] == 1) // Adjust for 1-indexing
                                {
                                    condensationMatrix[i, j] = 1;
                                    break;
                                }
                            }
                            if (condensationMatrix[i, j] == 1)
                                break;
                        }
                    }
                }
            }
            
            return condensationMatrix;
        }
        
        private void PrintMatrix(int[,] matrix, string title)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);
            
            Console.WriteLine($"\n{title}:");
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Console.Write($"{matrix[i, j]} ");
                }
                Console.WriteLine();
            }
        }
        
        private void TakeScreenshot()
        {
            string filename = $"graph_view_{viewMode}.png";
            Texture texture = new Texture(window.Size.X, window.Size.Y);
            texture.Update(window);
            texture.CopyToImage().SaveToFile(filename);
            Console.WriteLine($"Screenshot saved as {filename}");
        }
        
        public void Run()
        {
            while (window.IsOpen)
            {
                window.DispatchEvents();
                window.Clear(Color.White);
                
                switch (viewMode)
                {
                    case 0:
                        DrawGraph(directedMatrix, true, "Original Directed Graph");
                        break;
                    case 1:
                        DrawGraph(undirectedMatrix, false, "Original Undirected Graph");
                        break;
                    case 2:
                        DrawGraph(modifiedDirectedMatrix, true, "Modified Directed Graph");
                        break;
                    case 3:
                        DrawPathsInfo();
                        break;
                    case 4:
                        DrawCondensationGraph();
                        break;
                }
                
                window.Display();
            }
        }
        
        private void DrawGraph(int[,] matrix, bool isDirected, string title)
        {
            DrawInfoText(title);
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matrix[i, j] == 1)
                    {
                        if (i == j)
                        {
                            DrawLoop(vertexPositions[i], Color.Blue);
                        }
                        else if (isDirected)
                        {
                            DrawArrow(vertexPositions[i], vertexPositions[j], Color.Blue);
                        }
                        else if (i <= j) // For undirected graph, draw each edge only once
                        {
                            DrawLine(vertexPositions[i], vertexPositions[j], Color.Blue);
                        }
                    }
                }
            }
            
            for (int i = 0; i < n; i++)
            {
                DrawVertex(vertexPositions[i], (i + 1).ToString());
            }
        }
        
        private void DrawPathsInfo()
        {
            DrawInfoText("Paths Analysis");
            
            if (font != null)
            {
                var paths2Count = FindPathsOfLength(modifiedDirectedMatrix, 2).Count;
                var paths3Count = FindPathsOfLength(modifiedDirectedMatrix, 3).Count;
                
                var text = new Text(
                    $"Paths of length 2: {paths2Count}\n" +
                    $"Paths of length 3: {paths3Count}\n\n" +
                    "Full path lists are displayed in the console.",
                    font,
                    16
                )
                {
                    Position = new Vector2f(WindowWidth / 2 - 150, WindowHeight / 2 - 50),
                    FillColor = Color.Black
                };
                window.Draw(text);
            }
            else
            {
                // Draw a box if font is not available
                var rect = new RectangleShape(new Vector2f(300, 100))
                {
                    Position = new Vector2f(WindowWidth / 2 - 150, WindowHeight / 2 - 50),
                    FillColor = new Color(240, 240, 240),
                    OutlineColor = new Color(0, 0, 0),
                    OutlineThickness = 2
                };
                window.Draw(rect);
            }
        }
        
        private void DrawCondensationGraph()
        {
            DrawInfoText("Condensation Graph");
            
            if (stronglyConnectedComponents == null || stronglyConnectedComponents.Count == 0)
                return;
                
            int numComponents = stronglyConnectedComponents.Count;
            Vector2f[] componentPositions = new Vector2f[numComponents];
            
            // Calculate positions in a circle
            float radius = Math.Min(WindowWidth, WindowHeight) * 0.3f;
            Vector2f center = new Vector2f(WindowWidth / 2, WindowHeight / 2);
            
            for (int i = 0; i < numComponents; i++)
            {
                float angle = 2 * (float)Math.PI * i / numComponents;
                componentPositions[i] = new Vector2f(
                    center.X + radius * (float)Math.Cos(angle),
                    center.Y + radius * (float)Math.Sin(angle)
                );
            }
            
            // Draw edges
            for (int i = 0; i < numComponents; i++)
            {
                for (int j = 0; j < numComponents; j++)
                {
                    if (condensationMatrix[i, j] == 1)
                    {
                        DrawArrow(componentPositions[i], componentPositions[j], Color.Red);
                    }
                }
            }
            
            // Draw component vertices
            for (int i = 0; i < numComponents; i++)
            {
                DrawCondensationVertex(componentPositions[i], i + 1, stronglyConnectedComponents[i]);
            }
        }
        
        private void DrawCondensationVertex(Vector2f position, int componentNumber, List<int> vertices)
        {
            var circle = new CircleShape(VertexRadius * 1.5f)
            {
                Position = new Vector2f(position.X - VertexRadius * 1.5f, position.Y - VertexRadius * 1.5f),
                FillColor = new Color(200, 255, 200),
                OutlineColor = new Color(0, 128, 0),
                OutlineThickness = 2
            };
            window.Draw(circle);
            
            if (font != null)
            {
                // Component number
                var numberText = new Text($"C{componentNumber}", font, 16)
                {
                    Position = new Vector2f(position.X - 9, position.Y - 20),
                    FillColor = Color.Black
                };
                window.Draw(numberText);
                
                // List of vertices in the component
                string vertexList = string.Join(",", vertices);
                if (vertexList.Length > 10)
                    vertexList = vertexList.Substring(0, 10) + "...";
                    
                var verticesText = new Text(vertexList, font, 12)
                {
                    Position = new Vector2f(position.X - VertexRadius, position.Y + 5),
                    FillColor = Color.Black
                };
                window.Draw(verticesText);
            }
        }
        
        private void DrawInfoText(string title)
        {
            if (font != null)
            {
                var infoText = new Text(
                    title + "\n" +
                    "Use LEFT/RIGHT arrows or SPACE to switch views\n" +
                    "Press S to save screenshot, ESC to exit",
                    font,
                    14
                )
                {
                    Position = new Vector2f(10, 10),
                    FillColor = Color.Black
                };
                window.Draw(infoText);
                
                // Current view indicator
                var viewText = new Text(
                    $"View {viewMode + 1}/5: {title}",
                    font,
                    12
                )
                {
                    Position = new Vector2f(WindowWidth - 200, WindowHeight - 30),
                    FillColor = Color.Black
                };
                window.Draw(viewText);
            }
            else
            {
                // Draw rectangles if font is not available
                var rect = new RectangleShape(new Vector2f(WindowWidth, 40))
                {
                    Position = new Vector2f(0, 0),
                    FillColor = new Color(240, 240, 240)
                };
                window.Draw(rect);
                
                var bottomRect = new RectangleShape(new Vector2f(200, 20))
                {
                    Position = new Vector2f(WindowWidth - 200, WindowHeight - 30),
                    FillColor = new Color(240, 240, 240)
                };
                window.Draw(bottomRect);
            }
        }
        
        private void DrawLine(Vector2f start, Vector2f end, Color color)
        {
            float angle = (float)Math.Atan2(end.Y - start.Y, end.X - start.X);
            Vector2f actualStart = new Vector2f(
                start.X + VertexRadius * (float)Math.Cos(angle),
                start.Y + VertexRadius * (float)Math.Sin(angle)
            );
            Vector2f actualEnd = new Vector2f(
                end.X - VertexRadius * (float)Math.Cos(angle),
                end.Y - VertexRadius * (float)Math.Sin(angle)
            );

            var line = new Vertex[]
            {
                new Vertex(actualStart, color),
                new Vertex(actualEnd, color)
            };
            window.Draw(line, PrimitiveType.Lines);
        }

        private void DrawArrow(Vector2f start, Vector2f end, Color color)
        {
            float angle = (float)Math.Atan2(end.Y - start.Y, end.X - start.X);
            Vector2f actualStart = new Vector2f(
                start.X + VertexRadius * (float)Math.Cos(angle),
                start.Y + VertexRadius * (float)Math.Sin(angle)
            );
            Vector2f actualEnd = new Vector2f(
                end.X - VertexRadius * (float)Math.Cos(angle),
                end.Y - VertexRadius * (float)Math.Sin(angle)
            );
            
            var line = new Vertex[]
            {
                new Vertex(actualStart, color),
                new Vertex(actualEnd, color)
            };
            window.Draw(line, PrimitiveType.Lines);
            
            float arrowAngle = (float)(Math.PI / 6); 
            Vector2f arrowPoint1 = new Vector2f(
                actualEnd.X - ArrowLength * (float)Math.Cos(angle - arrowAngle),
                actualEnd.Y - ArrowLength * (float)Math.Sin(angle - arrowAngle)
            );
            Vector2f arrowPoint2 = new Vector2f(
                actualEnd.X - ArrowLength * (float)Math.Cos(angle + arrowAngle),
                actualEnd.Y - ArrowLength * (float)Math.Sin(angle + arrowAngle)
            );

            var arrow = new Vertex[]
            {
                new Vertex(actualEnd, color),
                new Vertex(arrowPoint1, color),
                new Vertex(arrowPoint2, color)
            };
            window.Draw(arrow, PrimitiveType.Triangles);
        }

        private void DrawVertex(Vector2f position, string label)
        {
            var circle = new CircleShape(VertexRadius)
            {
                Position = new Vector2f(position.X - VertexRadius, position.Y - VertexRadius),
                FillColor = Color.White,
                OutlineColor = Color.Black,
                OutlineThickness = 2
            };
            window.Draw(circle);
            
            if (font != null)
            {
                // Numbers start from 1
                var text = new Text(label, font, 14)
                {
                    Position = new Vector2f(
                        position.X - (label.Length > 1 ? 8 : 4),
                        position.Y - 10
                    ),
                    FillColor = Color.Black
                };
                window.Draw(text);
            }
            else
            {
                // Draw a small dot in the center if font is not available
                var centerDot = new CircleShape(3)
                {
                    Position = new Vector2f(position.X - 3, position.Y - 3),
                    FillColor = Color.Black
                };
                window.Draw(centerDot);
            }
        }

        private void DrawLoop(Vector2f position, Color color)
        {
            const int pointCount = 40;
            var vertices = new Vertex[pointCount];
            
            Vector2f start = new Vector2f(
                position.X + VertexRadius,
                position.Y
            );

            Vector2f end = new Vector2f(
                position.X - VertexRadius,
                position.Y
            );

            Vector2f peak = new Vector2f(
                position.X,
                position.Y - VertexRadius * 3
            );

            Vector2f controlRight = new Vector2f(
                position.X + VertexRadius * 2,
                position.Y - VertexRadius * 2
            );

            Vector2f controlLeft = new Vector2f(
                position.X - VertexRadius * 2,
                position.Y - VertexRadius * 2
            );
            
            for (int i = 0; i < pointCount; i++)
            {
                float t = i / (float)(pointCount - 1);
                Vector2f point;

                if (t < 0.5f)
                {
                    float st = t * 2;
                    point = new Vector2f(
                        BezierPoint(start.X, controlRight.X, peak.X, st),
                        BezierPoint(start.Y, controlRight.Y, peak.Y, st)
                    );
                }
                else
                {
                    float st = (t - 0.5f) * 2;
                    point = new Vector2f(
                        BezierPoint(peak.X, controlLeft.X, end.X, st),
                        BezierPoint(peak.Y, controlLeft.Y, end.Y, st)
                    );
                }

                vertices[i] = new Vertex(point, color);
            }

            window.Draw(vertices, PrimitiveType.LineStrip);
            
            float arrowLength = ArrowLength;
            float arrowAngle = (float)(Math.PI / 6);
            
            // Using a different variable name to avoid conflict with the t in the loop above
            float arrowT = 0.95f;  // Changed from 't' to 'arrowT'
            Vector2f arrowBase = new Vector2f(
                BezierPoint(peak.X, controlLeft.X, end.X, arrowT),
                BezierPoint(peak.Y, controlLeft.Y, end.Y, arrowT)
            );
            
            Vector2f direction = new Vector2f(end.X - arrowBase.X, end.Y - arrowBase.Y);
            float length = (float)Math.Sqrt(direction.X * direction.X + direction.Y * direction.Y);
            direction = new Vector2f(direction.X / length, direction.Y / length);
            
            Vector2f perpendicular = new Vector2f(-direction.Y, direction.X);

            Vector2f arrowPoint1 = new Vector2f(
                arrowBase.X - direction.X * arrowLength + perpendicular.X * arrowLength * 0.5f,
                arrowBase.Y - direction.Y * arrowLength + perpendicular.Y * arrowLength * 0.5f
            );

            Vector2f arrowPoint2 = new Vector2f(
                arrowBase.X - direction.X * arrowLength - perpendicular.X * arrowLength * 0.5f,
                arrowBase.Y - direction.Y * arrowLength - perpendicular.Y * arrowLength * 0.5f
            );
            
            var arrow = new Vertex[]
            {
                new Vertex(arrowBase, color),
                new Vertex(arrowPoint1, color),
                new Vertex(arrowPoint2, color)
            };
            window.Draw(arrow, PrimitiveType.Triangles);
        }

        private float BezierPoint(float start, float control, float end, float t)
        {
            float t1 = (1 - t) * (1 - t);
            float t2 = 2 * (1 - t) * t;
            float t3 = t * t;
            return t1 * start + t2 * control + t3 * end;
        }
    }
}