Per facilitare la compilazione e l'esecuzione dei test e dell'applicazione main:

(1) assicurarsi di avere il file italian_dist_graph.csv nella directory Exercise_3_4
(2) Per avviare l'applicazione, dalla directory Exercise_3_4 digitare:
    (2.1) make
    (2.2) make run_graph_usage

(3) Per avviare i test, dalla directory Exercize_3_4 digitare:
    (3.1) make
    (3.2) make run_test_unionFindSet run_test_graph

(4) Se si vuole avviare l'applicazione senza l'ausilio del make, spostarsi in classes/ e digitare:
    (4.1) java graphusage/GraphUsage "../italian_dist_graph.csv"
