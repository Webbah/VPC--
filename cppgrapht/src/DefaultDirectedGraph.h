

#ifndef DEFAULTDIRECTEDGRAPH_H_
#define DEFAULTDIRECTEDGRAPH_H_
#include <AbstractBaseGraph.h>
#include <DirectedGraph.h>
#include <ClassBasedEdgeFactory.h>

/**
 * A directed graph. A default directed graph is a non-simple directed graph in
 * which multiple edges between any two vertices are <i>not</i> permitted, but
 * loops are.
 *
 * <p>prefixed 'Default' to avoid name collision with the DirectedGraph
 * interface.</p>
 * @author Galina Engelmann <galinae@mail.upb.de>
 * @since 2011-06-22
 */
template<class V,class E>
class DefaultDirectedGraph : public AbstractBaseGraph<V, E>, public DirectedGraph<V, E>
{
    //~ Static fields/initializers ---------------------------------------------



    //~ Constructors -----------------------------------------------------------

    /**
     * Creates a new directed graph.
     *
     * @param edgeClass class on which to base factory for edges
     */
public: DefaultDirectedGraph(E* edgeClass)
    {
	//request heap-memory and call the constructor for initialisation


   ClassBasedEdgeFactory<V, E>* ef = new ClassBasedEdgeFactory<V, E>(edgeClass);
    //Reference to the new object
    this->DefaultDirectedGraph(ef);



    }

    /**
     * Creates a new directed graph with the specified edge factory.
     *
     * @param ef the edge factory of the new graph.
     */

//Standard-konstructor of the Upperclass is called
	DefaultDirectedGraph(EdgeFactory<V, E>* ef) : AbstractBaseGraph<V, E>(ef, false, true, true){}


	/**
	 * @see DirectedGraph#inDegreeOf(Object)
	 */
	int inDegreeOf(V* vertex)
	{
		return this->specifics->inDegreeOf(vertex);
	}

	/**
	 * @see DirectedGraph#incomingEdgesOf(Object)
	 */
	set<E*>* incomingEdgesOf(V* vertex)
	{
		return this->specifics->incomingEdgesOf(vertex);
	}

	/**
	 * @see DirectedGraph#outDegreeOf(Object)
	 */
	int outDegreeOf(V* vertex)
	{
		return this->specifics->outDegreeOf(vertex);
	}

	/**
	 * @see DirectedGraph#outgoingEdgesOf(Object)
	 */
	set<E*>* outgoingEdgesOf(V* vertex)
	{
		return this->specifics->outgoingEdgesOf(vertex);
	}
};


#endif /* DEFAULTDIRECTEDGRAPH_H_ */
