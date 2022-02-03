package graph;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import org.junit.Before;
import org.junit.Test;

/**
 * It specifies a test suite for the Graph library
 * To improve readability, Java methods' naming conventions are not fully
 * respected...
 * 
 * @author Daniele Di Palma
 */
public class GraphTests{

  private Graph<Integer, Float> direct_graph;
  private Graph<String, Integer> indirect_graph;

  int n1, n2, n3;
  String s1, s2, s3;
  float l1, l2;

  @Before
  public void initTests(){
    direct_graph = new Graph<>(true);
    indirect_graph = new Graph<>(false);
    n1 = 15;
    n2 = -4;
    n3 = 8;
    s1 = "red";
    s2 = "blue";
    s3 = "green";
    l1 = 1.31f;
    l2 = 0.41f;
  }

  @Test
  public void test_direct_add_one_vertex() throws GraphException{
    direct_graph.addVertex(n1);
    assertEquals(1, direct_graph.numberVertex());
  }

  @Test
  public void test_indirect_add_one_vertex() throws GraphException{
    indirect_graph.addVertex(s1);
    assertEquals(1, indirect_graph.numberVertex());
  }

  @Test
  public void test_direct_add_one_edge() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    assertEquals(1, direct_graph.numberEdge());
  }

  @Test
  public void test_indirect_add_one_edge() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    assertEquals(1, indirect_graph.numberEdge());
  }

  @Test
  public void test_direct_isOriented(){
    assertTrue(direct_graph.isOriented());
  }

  @Test
  public void test_indirect_isOriented(){
    assertFalse(indirect_graph.isOriented());
  }

  @Test
  public void test_direct_hasVertex_exist() throws GraphException{
    direct_graph.addVertex(n1);
    assertTrue(direct_graph.hasVertex(n1));
  }

  @Test
  public void test_indirect_hasVertex_exist() throws GraphException{
    indirect_graph.addVertex(s1);
    assertTrue(indirect_graph.hasVertex(s1));
  }

  @Test
  public void test_direct_hasVertex_notExist() throws GraphException{
    assertFalse(direct_graph.hasVertex(n1));
  }  

  @Test
  public void test_indirect_hasVertex_notExist() throws GraphException{
    assertFalse(indirect_graph.hasVertex(s1));
  }

  @Test
  public void test_direct_hasEdge_exist() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    assertTrue(direct_graph.hasEdge(n1, n2));
    assertFalse(direct_graph.hasEdge(n2, n1));
  }

  @Test
  public void test_indirect_hasEdge_exist() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    assertTrue(indirect_graph.hasEdge(s1, s2));
    assertTrue(indirect_graph.hasEdge(s2, s1));
  }

  @Test
  public void test_direct_hasEdge_notExist() throws GraphException{
    assertFalse(direct_graph.hasEdge(n1, n2));
  }

  @Test
  public void test_indirect_hasEdge_notExist() throws GraphException{
    assertFalse(indirect_graph.hasEdge(s1, s2));
  }

  @Test
  public void test_direct_removeVertex_one() throws GraphException{
    direct_graph.addVertex(n1);
    direct_graph.addVertex(n2);

    direct_graph.removeVertex(n1);
    assertEquals(1, direct_graph.numberVertex());
  }

  @Test
  public void test_indirect_removeVertex_one() throws GraphException{
    indirect_graph.addVertex(s1);
    indirect_graph.addVertex(s2);

    indirect_graph.removeVertex(s1);
    assertEquals(1, indirect_graph.numberVertex());
  }

  @Test
  public void test_direct_removeVertex_two() throws GraphException{
    direct_graph.addVertex(n1);
    direct_graph.addVertex(n2);

    direct_graph.removeVertex(n1);
    direct_graph.removeVertex(n2);
    assertEquals(0, direct_graph.numberVertex());
  }

  @Test
  public void test_indirect_removeVertex_two() throws GraphException{
    indirect_graph.addVertex(s1);
    indirect_graph.addVertex(s2);

    indirect_graph.removeVertex(s2);
    indirect_graph.removeVertex(s1);
    assertEquals(0, indirect_graph.numberVertex());
  }

  @Test
  public void test_direct_removeVertex_onEdge() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    direct_graph.removeVertex(n1);

    assertFalse(direct_graph.hasEdge(n1, n2));
  }

  @Test
  public void test_indirect_removeVertex_onEdge() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    indirect_graph.removeVertex(s1);

    assertFalse(indirect_graph.hasEdge(s1, s2) || indirect_graph.hasEdge(s2, s1));
  }

  @Test
  public void test_direct_removeEdge_one() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    direct_graph.addEdge(n2, n1, l2);

    direct_graph.removeEdge(n1, n2);
    assertEquals(1, direct_graph.numberEdge());
  }

  @Test
  public void test_indirect_removeEdge_one() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    indirect_graph.addEdge(s3, s2, n2);
    
    indirect_graph.removeEdge(s3, s2);
    assertEquals(1, indirect_graph.numberEdge());
  }

  @Test
  public void test_direct_removeEdge_two() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    direct_graph.addEdge(n2, n1, l2);

    direct_graph.removeEdge(n1, n2);
    direct_graph.removeEdge(n2, n1);
    assertEquals(0, direct_graph.numberEdge());
  }

  @Test
  public void test_indirect_removeEdge_two() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    indirect_graph.addEdge(s3, s2, n2);
    

    indirect_graph.removeEdge(s1, s2);
    indirect_graph.removeEdge(s3, s2);
    assertEquals(0, indirect_graph.numberEdge());
  }

  @Test
  public void test_direct_numberVertex_zero() throws GraphException{
    assertEquals(0, direct_graph.numberVertex());
  }

  @Test
  public void test_indirect_numberVertex_zero(){
    assertEquals(0, indirect_graph.numberVertex());
  }

  @Test
  public void test_direct_numberVertex_three() throws GraphException{
    direct_graph.addVertex(n1);
    direct_graph.addVertex(n2);
    direct_graph.addVertex(n3);
    assertEquals(3, direct_graph.numberVertex());
  }

  @Test
  public void test_indirect_numberVertex_three() throws GraphException{
    indirect_graph.addVertex(s1);
    indirect_graph.addVertex(s2);
    indirect_graph.addVertex(s3);
    assertEquals(3, indirect_graph.numberVertex());
  }

  @Test
  public void test_direct_numberEdge_zero(){
    assertEquals(0, direct_graph.numberEdge());
  }

  @Test
  public void test_indirect_numberEdge_zero(){
    assertEquals(0, indirect_graph.numberEdge());
  }

  @Test
  public void test_direct_numberEdge_four() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    direct_graph.addEdge(n2, n1, l2);
    direct_graph.addEdge(n1, n3, l1);
    direct_graph.addEdge(n3, n1, l1);
    assertEquals(4, direct_graph.numberEdge());
  }

  @Test
  public void test_indirect_numberEdge_four() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    indirect_graph.addEdge(s2, s1, n2);
    indirect_graph.addEdge(s1, s3, n1);
    indirect_graph.addEdge(s3, s1, n1);
    assertEquals(2, indirect_graph.numberEdge());
  }

  @Test
  public void test_direct_getVertex_zero() throws GraphException{
    assertEquals(0, direct_graph.getVertexSet().size());
  }

  @Test
  public void test_indirect_getVertex_zero() throws GraphException{
    assertEquals(0, indirect_graph.getVertexSet().size());
  }

  @Test
  public void test_direct_getVertexSet_three() throws GraphException{
    direct_graph.addVertex(n1);
    direct_graph.addVertex(n2);
    direct_graph.addVertex(n3);
    assertEquals(3, direct_graph.getVertexSet().size());
  }

  @Test
  public void test_indirect_getVertexSet_three() throws GraphException{
    indirect_graph.addVertex(s1);
    indirect_graph.addVertex(s2);
    indirect_graph.addVertex(s3);
    assertEquals(3, indirect_graph.getVertexSet().size());
  }

  @Test
  public void test_direct_getEdgeSet_zeroEdge(){
    assertEquals(0, direct_graph.getVertexSet().size());
  }

  @Test
  public void test_indirect_getEdgeSet_zeroEdge(){
    assertEquals(0, indirect_graph.getEdgeSet().size());
  }

  @Test
  public void test_direct_getEdgeSet_threeEdge() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    direct_graph.addEdge(n2, n1, l2);
    direct_graph.addEdge(n1, n3, l2);
    assertEquals(3, direct_graph.getVertexSet().size());
  }

  @Test
  public void test_indirect_getEdgeSet_threeEdge() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    indirect_graph.addEdge(s2, s1, n2);
    indirect_graph.addEdge(s1, s3, n2);
    assertEquals(3, indirect_graph.getVertexSet().size());
  }
  
  @Test
  public void test_direct_getLabel_notExist() throws GraphException{
    assertNull(direct_graph.getLabel(n1, n2));
  }

  @Test
  public void test_indirect_getLabel_notExist() throws GraphException{
    assertNull(indirect_graph.getLabel(s1, s2));
  }

  @Test
  public void test_direct_getLabel() throws GraphException{
    direct_graph.addEdge(n1, n2, l1);
    float label = direct_graph.getLabel(n1, n2);
    assertTrue(l1 == label);
  }

  @Test
  public void test_indirect_getLabel() throws GraphException{
    indirect_graph.addEdge(s1, s2, n1);
    float label = indirect_graph.getLabel(s1, s2);
    assertTrue(n1 == label);
  }

  @Test
  public void test_direct_getLabel_three() throws GraphException{
    direct_graph.addEdge(n1, n2, l2);
    direct_graph.addEdge(n1, n3, l1);
    direct_graph.addEdge(n3, n1, l2);
    float label = direct_graph.getLabel(n1, n3);
    assertTrue(l1 == label);
  }

  @Test
  public void test_indirect_getLabel_three() throws GraphException{
    indirect_graph.addEdge(s1, s2, n2);
    indirect_graph.addEdge(s1, s3, n1);
    indirect_graph.addEdge(s2, s3, n2);
    int label = indirect_graph.getLabel(s1, s3);
    assertTrue(n1 == label);
  }

}
