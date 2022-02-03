package kruskal;

import java.util.ArrayList;

import graph.Edge;
import graph.Graph;
import graph.GraphException;
import unionfindset.UnionFindSet;
import unionfindset.UnionFindSetException;

/**
 * It represent Kruskal algorithm implementation
 * using UnionFindSet data structure.
 * It will determines the minimum spanning tree
 * of a given graph
 * 
 * @author Daniele Di Palma
 * @param <V> type of vertex
 * @param <E> type of label (it is a weight in kruskal algorithm)
 * 
 */
public class Kruskal<V, E extends Number>{
  
  private Graph<V,E> mst;
  
  public Kruskal(){
    this.mst = new Graph<>(false);
  }

  public Graph<V,E> kruscal(Graph<V,E> graph) throws KruskalException, UnionFindSetException, GraphException{
    if(graph == null){
      throw new KruskalException("kruskal: passed graph cannot be null");
    }
    
    ArrayList<V> vertexArray = graph.getVertexSet();
    UnionFindSet<V> set = new UnionFindSet<>();

    for(V vertex : vertexArray){
      set.makeSet(vertex);
    }

    ArrayList<Edge<V,E>> edgeArray = graph.getEdgeSet();

    edgeArray.sort(new EdgeComparatorLabel<>());

    for(Edge<V,E> edge : edgeArray) {
      if(set.findSet(edge.getStartVertex()) != set.findSet(edge.getDestVertex())){

        mst.addEdge(edge.getStartVertex(), edge.getDestVertex(), edge.getLabel());        
        
        set.union(edge.getStartVertex(), edge.getDestVertex());
      }
    }
    return mst;    
  }
}