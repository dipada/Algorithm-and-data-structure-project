package graphusage;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

import graph.Edge;
import graph.Graph;
import graph.GraphException;
import kruskal.Kruskal;


/**
 * Java application that loads a file of records in a graph data structure.
 * After that determines mst of that graph using kruskal algorithm and printq results.
 * 
 * @author Daniele Di Palma
 */
public class GraphUsage{
  private static final Charset ENCODING = StandardCharsets.UTF_8;

  private static void loadFile(String filePath, Graph<String,Double> graph) throws IOException, GraphException{
    System.out.println("\nLoading data from file... ");
    Path inputFilePath = Paths.get(filePath);
    try(BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING)){
      String line = null;
      while((line = fileInputReader.readLine()) != null){
        String[] lineElements = line.split(",");
        graph.addEdge(lineElements[0], lineElements[1], Double.parseDouble(lineElements[2]));
      }
    }
    System.out.println("Data loaded\n");
  }

  private static double computeWeight(Graph<String,Double> graph){
    ArrayList<Edge<String,Double>> edge = graph.getEdgeSet();
    double totalWeight = 0;
    for(int i = 0; i < edge.size(); i++){
      totalWeight += edge.get(i).getLabel();
    }
    return totalWeight/2;
  }
  /**
   * 
   * @param args the command line arguments. It should contain only one argument
   *             specifying the filepath of the data file.
   * @throws Exception if no line argument is passed.
   */
  public static void main(String[] args) throws Exception{

    if(args.length < 1){
      throw new Exception("Usage: GraphUsage <file_name>");
    }
    
    Graph<String,Double> graph = new Graph<>(false);
    Kruskal<String,Double> mst = new Kruskal<>();
    long timer = System.nanoTime();

    loadFile(args[0], graph);
    
    graph = mst.kruscal(graph);
    
    System.out.println("Vertex:\t" + graph.numberVertex() + "\nEdge:\t" + graph.numberEdge());
    System.out.printf("Weight:\t%.3f Km\n", computeWeight(graph)/1e3);
    timer = System.nanoTime() - timer;
		System.out.printf("\nExecution time: %.2f ms (%.2f sec)\n", (timer/1e6), (timer/1e9));
  }
}