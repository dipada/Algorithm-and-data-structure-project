package unionfindset;

import java.util.HashMap;

/**
 * It rappresents a union find set data structure, also knows as disjoint sets.
 * @author Daniele Di Palma
 */
public class UnionFindSet<T>{

  /**
   * This inner class rappresents a singleton, implemented like a node
   */
  private class Node<V>{
    private int rank;
    private V elem;
    private Node<V> parent;

    private Node(V elem){
      rank = 0;
      this.elem = elem;
      parent = this;
    }
  }

  // Hashmap rappresents set of disjoints sets (nodes)
  // based on rappresentative key
  private HashMap<T, Node<T>> set;

  public UnionFindSet(){
    this.set = new HashMap<>();
  }

  /**
   * This method create new set (tree with one node) with a single element that is
   * also representative.
   * Since the sets are disjoint, @param x cannot be in other sets.
   * 
   * @param x representative element of singleton
   * @throws UnionFindSetException if parameter is null
   */
  public void makeSet(T x) throws UnionFindSetException {

    if(x == null){
      throw new UnionFindSetException("makeSet: parameter cannot be null");
    }

    if(!set.containsKey(x)){
      set.put(x, new Node<T>(x));
    }
  }

  /**
   * This method performs union between two sets.
   * PRE: sets are disjoint
   * POST: union of two sets
   * 
   * @param x rappresentative of first tree (set)
   * @param y rappresentative of second tree (set)
   * @throws UnionFindSetException if one of the two sets does not exist
   */
  public void union(T x, T y) throws UnionFindSetException {

    if(set.containsKey(x) && set.containsKey(y)){
      link(findSet(x), findSet(y));
    }else{
      throw new UnionFindSetException("union: set doesn't exist");
    }
  }

  /**
   * This method take a rapresentative of a node and goes back up to find the root,
   * then descends by updating the nodes making them point directly to the root.
   * 
   * @param x rapresentative of set
   * @return reference to the parent
   * @throws UnionFindSetException
   */
  public T findSet(T x) throws UnionFindSetException{
    if(!set.containsKey(x)){
      throw new UnionFindSetException("findSet: set doesn't exist");
    }

    Node<T> node = set.get(x);
    if(node != node.parent){
      node.parent = set.get(findSet(node.parent.elem));
    }
    return node.parent.elem;
  }

  /**
   * This method take two rapresentatives of sets (tree in this implementation).
   * If the ranks of two trees aren't same, attach the lower rank tree with the
   * higher one,
   * otherwise it connects one of the two trees to the other, then increases the
   * rank of the resulting tree.
   * 
   * @param xt rapresentative of first set (tree)
   * @param yt rapresentative of second set (tree)
   */
  private void link(T xt, T yt){
    Node<T> x = set.get(xt);
    Node<T> y = set.get(yt);

    if(x.rank > y.rank){
      y.parent = x;
    }else{
      x.parent = y;
      if(x.rank == y.rank){
        y.rank += 1;
      }
    }
  }

  /**
   * This method take rapresentative of set and return rank associate at that node
   * 
   * @param x rapresentative of set
   * @return rank of node
   * @throws UnionFindSetException if set doesn't exist
   */
  protected int getRank(T x) throws UnionFindSetException{
    if(!set.containsKey(x)){
      throw new UnionFindSetException("getRank: set doesn't exist");
    }
    return set.get(x).rank;
  }

  /**
   * Take rapresentative of set and return parent node reference
   * 
   * @param x rapresentative of set
   * @return parent node reference of rapresentative
   * @throws UnionFindSetException if set doesn't exist
   */
  protected Node<T> getParent(T x) throws UnionFindSetException {
    if(!set.containsKey(x)){
      throw new UnionFindSetException("getParent: set doesn't exist");
    }
    return set.get(x).parent;
  }

  /**
   * Take rapresentative of set and return node reference
   * 
   * @param x rapresentative of set
   * @return node referecence of rapresentative
   * @throws UnionFindSetException if set does't exist
   */
  protected Node<T> getElemSet(T x) throws UnionFindSetException{
    if (!set.containsKey(x)){
      throw new UnionFindSetException("getParent: set doesn't exist");
    }
    return set.get(x);
  }

  /**
   * This method return dimesion of set
   * 
   * @return dimension of set
   */
  protected int getSetSize(){
    return set.size();
  }

}
