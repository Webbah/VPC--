#include <iostream>
#include <exception>
#include "AbstractBaseGraph.h"
#include "AbstractGraph.h"
#include "AsUndirectedGraph.h"
#include "ClassBasedEdgeFactory.h"
#include "ClassBasedVertexFactory.h"
#include "DefaultEdge.h"
#include "DefaultWeightedEdge.h"
#include "DefaultDirectedGraph.h"
#include "DefaultDirectedWeightedGraph.h"
#include "DirectedGraph.h"
#include "DirectedMultigraph.h"
#include "EdgeFactory.h"
#include "EdgeSetFactory.h"
#include "Graph.h"
#include "GraphDelegator.h"
#include "GraphPath.h"
#include "Graphs.h"
#include "IntrusiveEdge.h"
#include "UndirectedGraph.h"
#include "VertexFactory.h"
#include "WeightedGraph.h"


using namespace std;

int main()
{
	cout << "Start\n";
	try {
		ClassBasedEdgeFactory<int, DefaultEdge<int> >* ef = new ClassBasedEdgeFactory<int, DefaultEdge<int> >();
		DefaultDirectedGraph<int, DefaultEdge<int> >* g = new DefaultDirectedGraph<int, DefaultEdge<int> >(ef);

		int v1 = 1;
		int v2 = 2;
		int v3 = 3;
		g->addVertex(&v1);
		g->addVertex(&v2);
		g->addVertex(&v3);

		const set<int* >* vs = g->vertexSet();

		g->addEdge(&v1, &v2);
		g->addEdge(&v1, &v3);

		const set<DefaultEdge<int>* >* es = g->edgeSet();
		cout << "Num Vertices: " << vs->size() << "\n";
		cout << "Num Edges: " << es->size() << "\n";
	} catch (invalid_argument &e) {
		cout << e.what();
	}

	cout << "End";
	return 0;
}
