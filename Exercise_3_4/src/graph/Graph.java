package graph;

import java.util.ArrayList;
import java.util.HashMap;


/**
 * It represents a graph data structure and implement operations of this ADT.
 * 
 * @author Daniele Di Palma
 * @param <V>: type of the vertex
 * @param <E>: type of label
 */
public class Graph<V,E>{
  private boolean oriented;

  // Internal structure to represent graph 
  private HashMap<V,ArrayList<Edge<V,E>>> graph;

  public Graph(boolean oriented){
    this.oriented = oriented;
    this.graph = new HashMap<>();
  }

  /**
   * It add a vertex to the graph
   * 
   * @param vertex the vertex to be add
   * @throws GraphException if parameter is null
   */
  public void addVertex(V vertex) throws GraphException{
    if(vertex == null){
      throw new GraphException("addVertex: vertex cannot be null");
    }
    graph.put(vertex, new ArrayList<>());    
  }

  /**
   * It add edge to the graph. 
   * It will create passed vertex if doesn't exist.
   * 
   * @param start start vertex of edge
   * @param dest  dest vertex of edge
   * @param label label associated to the edge
   * @throws GraphException
   */
  public void addEdge(V start, V dest, E label) throws GraphException{
    if(start == null || dest == null){
      throw new GraphException("addEdge: can't add Edge, one or both parameters are null");
    }

    if(!graph.containsKey(start)){
      this.addVertex(start);
    }

    if(!graph.containsKey(dest)){
      this.addVertex(dest);
    }

    if(!this.hasEdge(start,dest)){
      Edge<V,E> edge = new Edge<>(start, dest, label);
      graph.get(start).add(edge);

      if(!oriented){
        edge = new Edge<>(dest, start, label);
        graph.get(dest).add(edge);
      }
    }
  }

  /**
   * Check if graph is oriented (direct).
   * 
   * @return true if graph oriented, false otherwise.
   */
  public boolean isOriented(){
    return oriented;
  }

  /**
   * Check if graph contains a vertex.
   * 
   * @param vertex checked vertex
   * @return true if vertex is present, false otherwise
   * @throws GraphException if passed paramater is null
   */
  public boolean hasVertex(V vertex) throws GraphException{
    if(vertex == null){
      throw new GraphException("hasVertex: parameter cannot be null");
    }
    return graph.containsKey(vertex);
  }

  /**
   * Check if graph contains a edge.
   * 
   * @param start vertex where edge start
   * @param dest  vertex where edge end
   * @return  true if edge is presente in the graph, false otherwise.
   * @throws GraphException if on of two vertex passed is null
   */
  public boolean hasEdge(V start, V dest) throws GraphException{
    if(start == null || dest == null){
      throw new GraphException("hasEdge: parameter cannot be null");
    }

    boolean found = false;
    Edge<V,E> edge;

    if(graph.containsKey(start)){
      for(int i = 0; i < graph.get(start).size() && !found; i++){
        edge = graph.get(start).get(i);
        if(edge.getDestVertex().equals(dest)){
          found = true;
        }
      }
    }
    return found;
  }
  
  /**
   * It remove given vertex by graph.
   * 
   * @param vertex vertex to remove
   * @throws GraphException if passed vertex is null
   */
  public void removeVertex(V vertex) throws GraphException{
    if(vertex == null){
      throw new GraphException("removeVertex: parameter cannot be null");
    }

    if(graph.containsKey(vertex)){

      if(oriented){
        for(int i = 0; i < graph.get(vertex).size(); i++){
          graph.get(vertex).remove(i);
        }
        graph.remove(vertex);
      }else{
        ArrayList<V> verIncomingEdge = new ArrayList<>();

        for(int i = 0; i < graph.get(vertex).size(); i++){
          verIncomingEdge.add(graph.get(vertex).get(i).getDestVertex());
          graph.get(vertex).remove(i);
        }
        graph.remove(vertex);

        for(V v : verIncomingEdge){
          for(int i = 0; i < graph.get(v).size(); i++){
            if(graph.get(v).get(i).getDestVertex().equals(vertex)){
              graph.get(v).remove(i);
            }
          }
          graph.remove(v);
        }
      }
    }
  }

  /**
   * It remove edge by the graph.
   * 
   * @param start vertex where edge start
   * @param dest  vertex where edge end
   * @throws GraphException if one of passed vertex is null
   */
  public void removeEdge(V start, V dest) throws GraphException{
    if(start == null || dest == null){
      throw new GraphException("removeEdge: parameter cannot be null");
    }

    boolean found = false;
    Edge<V,E> edge;

    for(int i = 0; i < graph.get(start).size(); i++){
      edge = graph.get(start).get(i);
      if(edge.getDestVertex().equals(dest)){
        graph.get(start).remove(i);
        found = true;
      }
    }

    if(!oriented && found){
      found = false;
      for(int i = 0; i < graph.get(dest).size(); i++){
        edge = graph.get(dest).get(i);
        if(edge.getDestVertex().equals(start)){
          graph.get(dest).remove(i);
          found = true;
        }
      }
    }
  }

  /**
   * It determines the number of vertex of the graph
   * 
   * @return number of vertex
   */
  public int numberVertex(){
    return graph.size();
  }

  /**
   * It determines the number of edge of the graph
   * 
   * @return number of edge
   */
  public int numberEdge(){
    int count = 0;

    for(V vertex : graph.keySet()){
      count += graph.get(vertex).size();
    }

    return (oriented) ? count : count/2;
  }

  /**
   * It retrive all vertex of graph in a set
   * 
   * @return arraylist of vertex
   */
  public ArrayList<V> getVertexSet(){
    ArrayList<V> vertex = new ArrayList<>();

    for(V key : graph.keySet()){
      vertex.add(key);
    }

    return vertex;
  }

  /**
   * It retrive all edge of graph in a set
   * 
   * @return arraylist of edge
   */
  public ArrayList<Edge<V, E>> getEdgeSet(){
    ArrayList<Edge<V, E>> edges = new ArrayList<>();

    for(V vertex : graph.keySet()){
      edges.addAll(graph.get(vertex));
    }

    return edges;
  }

  /**
   * It retrive adjacents vertex of specified vertex.
   * 
   * @param vertex vertex of which to take the adjacents
   * @return arraylist of adjacents vertex
   * @throws GraphException if passed vertex is null
   */
  public ArrayList<V> getAdjacentVer(V vertex) throws GraphException{
    if(vertex == null){
      throw new GraphException("getAdjacentVer: parameter cannot be null");
    }

    ArrayList<V> adjacentVertex = new ArrayList<>();
    for(int i = 0; i < graph.get(vertex).size(); i++){
      adjacentVertex.add(graph.get(vertex).get(i).getDestVertex());
    }

    return adjacentVertex;
  }

  /**
   * It retrive label associate with a couple of vertex
   * 
   * @param start start vertex
   * @param dest  dest vertex
   * @return a value if label is present, null otherwise
   * @throws GraphException if one of passed vertex is null
   */
  public E getLabel(V start, V dest) throws GraphException{
    if(start == null || dest == null){
      throw new GraphException("getLabel: parameter cannot be null");
    }

    E label = null;
    if(hasEdge(start, dest)){
      boolean found = false;
      for(int i = 0; i < graph.get(start).size() && !found; i++){
        if(graph.get(start).get(i).getDestVertex().equals(dest)){
          label = graph.get(start).get(i).getLabel();
          found = true;
        }
      }
    }
    return label;
  }
}
