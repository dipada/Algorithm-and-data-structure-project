package kruskal;

import java.util.Comparator;
import graph.Edge;

/**
 * Comparator for the weighted kruskal edge
 * 
 * @author Daniele Di Palma
 * @param <V> type of vertex
 * @param <E> type of label (it is a weight in kruskal algorithm)
 */
public class EdgeComparatorLabel<V, E extends Number> implements Comparator<Edge<V,E>> {
  @Override
  public int compare(Edge<V, E> e1, Edge<V, E> e2){
    return Double.compare(e1.getLabel().doubleValue(), e2.getLabel().doubleValue());
  }
}