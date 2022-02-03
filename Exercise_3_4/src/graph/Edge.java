package graph;

/**
 * Class representing an edge of the graph.
 * 
 * @author Daniele Di Palma
 */
public final class Edge<V,E>{
  private E label;
  private V start;
  private V dest;

  public Edge(V start, V dest, E label){
    this.start = start;
    this.dest = dest;
    this.label = label;
  }

  public Edge(V start, V dest){
    this(start, dest, null);
  }

  public V getStartVertex(){
    return start;
  }

  public V getDestVertex(){
    return dest;
  }

  public E getLabel(){
    return label;
  }
}
