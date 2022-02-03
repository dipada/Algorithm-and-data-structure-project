package unionfindset;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertSame;
import org.junit.Before;
import org.junit.Test;

/**
 * It specifies a test suite for the UnionFindSet library
 * To improve readability, Java methods' naming conventions are not fully
 * respected...
 * 
 * @author Daniele Di Palma
 */
public class UnionFindSetTests {
  private UnionFindSet<String> set_string;
  private UnionFindSet<Integer> set_integer;
  String s1, s2, s3;
  int n1, n2, n3, n4;

  @Before
  public void createTree() {
    set_string = new UnionFindSet<String>();
    set_integer = new UnionFindSet<Integer>();
    s1 = "red";
    s2 = "gree";
    s3 = "blue";
    n1 = 42;
    n2 = 1;
    n3 = 3;
    n4 = -12;
  }

  @Test
  public void test_getSetSize_zeroSets() throws UnionFindSetException {
    assertEquals(0, set_string.getSetSize());
  }

  @Test
  public void test_getSetSize_oneSet() throws UnionFindSetException {
    set_string.makeSet(s1);
    assertEquals(1, set_string.getSetSize());
  }

  @Test
  public void test_getSetSize_twoSets() throws UnionFindSetException {
    set_string.makeSet(s1);
    set_string.makeSet(s2);
    assertEquals(2, set_string.getSetSize());
  }

  @Test
  public void test_getSetSize_threeSets() throws UnionFindSetException {
    set_string.makeSet(s1);
    set_string.makeSet(s2);
    set_string.makeSet(s3);
    assertEquals(3, set_string.getSetSize());
  }

  @Test
  public void test_makeSet_two_EqualEl() throws UnionFindSetException {
    set_string.makeSet(s1);
    set_string.makeSet(s1);
    assertEquals(1, set_string.getSetSize());
  }

  @Test
  public void test_makeSet_three_EqualEl() throws UnionFindSetException {
    set_integer.makeSet(n1);
    set_integer.makeSet(n1);
    set_integer.makeSet(n1);
    assertEquals(1, set_integer.getSetSize());
  }

  @Test
  public void test_union_String_reference_threeSets() throws UnionFindSetException {

    set_string.makeSet(s1);
    set_string.makeSet(s2);
    set_string.makeSet(s3);
    set_string.union(s1, s2);
    set_string.union(s2, s3);

    assertSame(set_string.getElemSet(s2), set_string.getParent(s2));
    assertSame(set_string.getElemSet(s2), set_string.getParent(s1));
    assertSame(set_string.getElemSet(s2), set_string.getParent(s2));
    assertSame(set_string.getElemSet(s2), set_string.getParent(s3));
  }

  @Test
  public void test_union_Integer_reference_fourSets() throws UnionFindSetException {

    set_integer.makeSet(n1);
    set_integer.makeSet(n2);
    set_integer.makeSet(n3);
    set_integer.makeSet(n4);

    set_integer.union(n1, n2);
    set_integer.union(n3, n4);
    set_integer.union(n2, n4);

    assertSame(set_integer.getElemSet(n4), set_integer.getParent(n4));
    assertSame(set_integer.getElemSet(n4), set_integer.getParent(n2));
    assertSame(set_integer.getElemSet(n4), set_integer.getParent(n3));
    assertSame(set_integer.getElemSet(n2), set_integer.getParent(n1));
  }

  @Test
  public void test_union_String_Rank_threeSets() throws UnionFindSetException {
    set_string.makeSet(s1);
    set_string.makeSet(s2);
    set_string.makeSet(s3);

    set_string.union(s1, s2);
    set_string.union(s2, s3);

    assertEquals(1, set_string.getRank(s2));
    assertEquals(0, set_string.getRank(s1));
    assertEquals(0, set_string.getRank(s3));
  }

  @Test
  public void test_union_Integer_Rank_fourSets() throws UnionFindSetException {
    set_integer.makeSet(n1);
    set_integer.makeSet(n2);
    set_integer.makeSet(n3);
    set_integer.makeSet(n4);

    set_integer.union(n1, n2);
    set_integer.union(n3, n4);
    set_integer.union(n2, n4);

    assertEquals(2, set_integer.getRank(n4));
    assertEquals(1, set_integer.getRank(n2));
    assertEquals(0, set_integer.getRank(n3));
    assertEquals(0, set_integer.getRank(n1));
  }

  @Test
  public void test_findSet_String_oneSet() throws UnionFindSetException {
    set_string.makeSet(s1);
    assertSame(s1, set_string.findSet(s1));
  }

  @Test
  public void test_findSet_Integer_fourSets() throws UnionFindSetException {

    set_integer.makeSet(n1);
    set_integer.makeSet(n2);
    set_integer.makeSet(n3);
    set_integer.makeSet(n4);

    set_integer.union(n1, n2);
    set_integer.union(n3, n4);
    set_integer.union(n2, n4);

    assertSame(n4, set_integer.findSet(n4));
    assertSame(n4, set_integer.findSet(n3));
    assertSame(n4, set_integer.findSet(n2));
    assertSame(n4, set_integer.findSet(n1));
  }
}