#ifndef DIRECTEDWEIGHTEDMULTIGRAPH_H_
#define DIRECTEDWEIGHTEDMULTIGRAPH_H_

#include <DirectedMultigraph.h>
#include <WeightedGraph.h>

/**
 * A directed weighted multigraph. A directed weighted multigraph is a
 * non-simple directed graph in which loops and multiple edges between any two
 * vertices are permitted, and edges have weights.
 *
 * @author Heinrich Drobin <hedr@mail.upb.de>
 * @since 2011-06-20
 */

template <class V, class E>

class DirectedWeightedMultigraph: public DirectedMultigraph<V, E>, public WeightedGraph<V, E>
{
    //~ Constructors -----------------------------------------------------------

    /**
     * Creates a new directed weighted multigraph with the specified edge
     * factory.
     *
     * @param ef the edge factory of the new graph.
     */

public:
    DirectedWeightedMultigraph(EdgeFactory<V, E>* ef) : DirectedMultigraph<V, E>(ef){}

	//~ Destructors -----------------------------------------------------------

	virtual ~DirectedWeightedMultigraph(){}

};

#endif /* DIRECTEDWEIGHTEDMULTIGRAPH_H_ */
