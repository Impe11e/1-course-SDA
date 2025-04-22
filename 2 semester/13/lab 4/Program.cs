using SFML.Graphics;
using SFML.Window;
using SFML.System;

namespace GraphVisualization
{
    class Program
    {
        static void Main(string[] args)
        {
            var graph = new Graph();
            
            try
            {
                Console.WriteLine("Lab 4 - Graph Characteristics and Connectivity");
                Console.WriteLine("Variant: 4313");
                Console.WriteLine("Controls:");
                Console.WriteLine("- LEFT/RIGHT or SPACE: Switch between views");
                Console.WriteLine("- S: Save screenshot");
                Console.WriteLine("- ESC: Exit");
                
                graph.Run();
            }
            catch (Exception e)
            {
                Console.WriteLine($"An error occurred: {e.Message}");
                Console.WriteLine("Press any key to exit...");
                Console.ReadKey();
            }
        }
    }
}