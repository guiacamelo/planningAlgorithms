dijkstra: dijkstra.o heap.o graph.o
	g++ dijkstra.o heap.o graph.o -o dijkstra
dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp
heap.o: heap.cpp heap.h
	g++ -c heap.cpp heap.h
graph.o: graph.cpp graph.h
	g++ -c graph.cpp graph.h
gen: gen.o
	g++ gen.o -o gen
gen.o: gen.cpp 
	g++ -c gen.cpp 
clean:
	rm *o dijkstra gen *gch