#ifndef VERTEX_H
#define VERTEX_H

using namespace std;
class Vertex {
private:
	int id;
	int distance;

public:
	Vertex(int ids, int distances){
		id=ids;
		distance=distances;
	}

	int getId() {
		return id;
	}
	int getDistance() {
		return distance;
	}
};
#endif
