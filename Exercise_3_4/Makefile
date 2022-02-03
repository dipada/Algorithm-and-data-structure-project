JC = javac
JFLAG = -d $(CLASS_DIR)
CLASS_DIR = ../classes/

MV_SRC_DIR = cd src/;

UNION_FIND_SRC_DIR = unionfindset/
UNION_FIND_SRC_CLASS = UnionFindSet.java UnionFindSetException.java
UNION_FIND_SRC_TEST_CLASS = UnionFindSetTests.java UnionFindSetTestsRunner.java $(UNION_FIND_SRC_CLASS)

GRAPH_SRC_DIR = graph/
GRAPH_SRC_CLASS = Graph.java Edge.java GraphException.java
GRAPH_SRC_TEST_CLASS = GraphTestsRunner.java GraphTests.java $(GRAPH_SRC_CLASS)

KRUSKAL_SRC_DIR = kruskal/
KRUSKAL_SRC_CLASS = Kruskal.java KruskalException.java EdgeComparatorLabel.java

GRAPH_USAGE_SRC_DIR = graphusage/
GRAPH_USAGE_SRC_CLASS = GraphUsage.java Record.java

ifeq ($(OS), Windows_NT)
	CLASS_PATH = '.;../lib/hamcrest-core-1.3.jar;../lib/junit-4.12.jar'
else
	CLASS_PATH = '.:../lib/hamcrest-core-1.3.jar:../lib/junit-4.12.jar'
endif

all: unionFindSet unionFindSetTest graph graphTest kruskal graphusage

unionFindSetTest: unionFindSet
	$(MV_SRC_DIR) $(JC) $(JFLAG) -cp $(CLASS_PATH) $(addprefix $(UNION_FIND_SRC_DIR),$(UNION_FIND_SRC_TEST_CLASS))

unionFindSet:
	$(MV_SRC_DIR) $(JC) $(JFLAG) $(addprefix $(UNION_FIND_SRC_DIR),$(UNION_FIND_SRC_CLASS))

graph:
	$(MV_SRC_DIR) $(JC) $(JFLAG) $(addprefix $(GRAPH_SRC_DIR),$(GRAPH_SRC_CLASS))

graphTest: graph
	$(MV_SRC_DIR) $(JC) $(JFLAG) -cp $(CLASS_PATH) $(addprefix $(GRAPH_SRC_DIR),$(GRAPH_SRC_TEST_CLASS))

kruskal: unionFindSet
	$(MV_SRC_DIR) $(JC) $(JFLAG) $(addprefix $(KRUSKAL_SRC_DIR),$(KRUSKAL_SRC_CLASS))

graphusage: kruskal graph
	$(MV_SRC_DIR) $(JC) $(JFLAG) $(addprefix $(GRAPH_USAGE_SRC_DIR),$(GRAPH_USAGE_SRC_CLASS))

run_test_unionFindSet:
	cd classes/; java -cp $(CLASS_PATH) unionfindset/UnionFindSetTestsRunner

run_test_graph:
	cd classes/; java -cp $(CLASS_PATH) graph/GraphTestsRunner

run_graph_usage:
	@cd classes/; java graphusage/GraphUsage "../italian_dist_graph.csv"

.PHONY:
clean:
	@rm -r classes/*

# Exec tests UnionFindSet by command line
# Move in classes dir 
# java -cp '.:../lib/hamcrest-core-1.3.jar:../lib/junit-4.12.jar:'  unionfindset.UnionFindSetTestsRunner