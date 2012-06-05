#ifndef DIRECTEDMULTIGRAPH_H_
#define DIRECTEDMULTIGRAPH_H_

#include <AbstractBaseGraph.h>
#include <DirectedGraph.h>

/**
 * A directed multigraph. A directed multigraph is a non-simple directed graph
 * in which loops and multiple edges between any two vertices are permitted.
 *
 * @author Heinrich Drobin <hedr@mail.upb.de>
 * @since 2011-06-19
 */

template <class V, class E>

class DirectedMultigraph: public AbstractBaseGraph<V, E>, public DirectedGraph<V, E>
{
    //~ Constructors -----------------------------------------------------------

    /**
     * Creates a new directed multigraph with the specified edge factory.
     *
     * @param ef the edge factory of the new graph.
     */

public:
	DirectedMultigraph(EdgeFactory<V, E>* ef) : AbstractBaseGraph<V, E>(ef, true, true){}

	//~ Destructors -----------------------------------------------------------

	virtual ~DirectedMultigraph(){}

};

#endif /* DIRECTEDMULTIGRAPH_H_ */
