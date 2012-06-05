#ifndef GRAPHDELEGATOR_H_
#define GRAPHDELEGATOR_H_

#include <string>
#include <set>
#include <stdexcept>
#include <Graph.h>
#include <AbstractGraph.h>
#include <UndirectedGraph.h>

/**
 * A graph backed by the the graph specified at the constructor, which delegates
 * all its methods to the backing graph. Operations on this graph "pass through"
 * to the to the backing graph. Any modification made to this graph or the
 * backing graph is reflected by the other.
 *
 * <p>This graph does <i>not</i> pass the hashCode and equals operations through
 * to the backing graph, but relies on <tt>Object</tt>'s <tt>equals</tt> and
 * <tt>hashCode</tt> methods.</p>
 *
 * <p>This class is mostly used as a base for extending subclasses.</p>
 *
 * @author Rolf Brinkmann <rolfb@mail.upb.de>
 * @since 2011-06-09
 */
template <class V, class E>
class GraphDelegator :
	public AbstractGraph<V, E>,
	public Graph<V, E>
{
private:
	//~ Static fields/initializers ---------------------------------------------

	//~ Instance fields --------------------------------------------------------

	/**
	* The graph to which operations are delegated.
	*/
	Graph<V, E>* delegate;
	
public:
	//~ Constructors -----------------------------------------------------------
	/**
	 * Constructor for GraphDelegator.
	 *
	 * @param g the backing graph (the delegate).
	 *
	 * @throws invalid_argument exception iff <code>g==NULL</code>
	 */
	GraphDelegator(Graph<V, E>* g) : AbstractGraph<V,E>()
	{
		if (g == NULL) {
			throw new invalid_argument("g must not be NULL.");
		}
		
		delegate = g;	 
	}
	 
	virtual ~GraphDelegator(){}
	
    //~ Methods ----------------------------------------------------------------

    /**
     * @see Graph#getAllEdges(Object, Object)
     */
    set<E*>* getAllEdges(V* sourceVertex, V* targetVertex)
    {
        return delegate.getAllEdges(sourceVertex, targetVertex);
    }

    /**
     * @see Graph#getEdge(Object, Object)
     */
    E* getEdge(V* sourceVertex, V* targetVertex)
    {
        return delegate.getEdge(sourceVertex, targetVertex);
    }

    /**
     * @see Graph#getEdgeFactory()
     */
    EdgeFactory<V, E>* getEdgeFactory()
    {
        return delegate.getEdgeFactory();
    }

    /**
     * @see Graph#addEdge(Object, Object)
     */
    E* addEdge(V* sourceVertex, V* targetVertex)
    {
        return delegate.addEdge(sourceVertex, targetVertex);
    }

    /**
     * @see Graph#addEdge(Object, Object, Object)
     */
    bool addEdge(V* sourceVertex, V* targetVertex, E* e)
    {
        return delegate.addEdge(sourceVertex, targetVertex, e);
    }

    /**
     * @see Graph#addVertex(Object)
     */
    bool addVertex(V* v)
    {
        return delegate.addVertex(v);
    }

    /**
     * @see Graph#containsEdge(Object)
     */
    bool containsEdge(E* e)
    {
        return delegate.containsEdge(e);
    }

    /**
     * @see Graph#containsVertex(Object)
     */
    bool containsVertex(V* v)
    {
        return delegate.containsVertex(v);
    }

    /**
     * @see UndirectedGraph#degreeOf(Object)
     */
    int degreeOf(V* vertex)
    {
    	return ((UndirectedGraph<V, E>*) delegate).degreeOf(vertex);
    }

    /**
     * @see Graph#edgeSet()
     */
    set<E*>* edgeSet()
    {
        return delegate.edgeSet();
    }

    /**
     * @see Graph#edgesOf(Object)
     */
    set<E*>* edgesOf(V* vertex)
    {
        return delegate.edgesOf(vertex);
    }

    /**
     * "<V*, ? extends E*>" replaced with <V*,E*>
     * 
     * @see DirectedGraph#inDegreeOf(Object)
     */
    int inDegreeOf(V* vertex)
    {
    	return ((DirectedGraph<V, E>*) delegate).inDegreeOf(vertex);
    }

    /**
     * @see DirectedGraph#incomingEdgesOf(Object)
     */
    set<E*>* incomingEdgesOf(V* vertex)
    {
    	return ((DirectedGraph<V, E>*) delegate).incomingEdgesOf(vertex);
    }

    /**
     * "<V*, ? extends E*>" replaced with <V*,E*>
     * 
     * @see DirectedGraph#outDegreeOf(Object)
     */
    int outDegreeOf(V* vertex)
    {
    	return ((DirectedGraph<V, E>*) delegate).outDegreeOf(vertex);
    }

    /** 
     * @see DirectedGraph#outgoingEdgesOf(Object)
     */
    set<E*>* outgoingEdgesOf(V* vertex)
    {
    	return ((DirectedGraph<V, E>*) delegate).outgoingEdgesOf(vertex);
    }

    /**
     * @see Graph#removeEdge(Object)
     */
    bool removeEdge(E* e)
    {
        return delegate.removeEdge(e);
    }

    /**
     * @see Graph#removeEdge(Object, Object)
     */
    E* removeEdge(V* sourceVertex, V* targetVertex)
    {
        return delegate.removeEdge(sourceVertex, targetVertex);
    }

    /**
     * @see Graph#removeVertex(Object)
     */
    bool removeVertex(V* v)
    {
        return delegate.removeVertex(v);
    }

    /**
     * @see java.lang.Object#toString()
     */
    string toString()
    {
        return delegate.toString();
    }

    /**
     * @see Graph#vertexSet()
     */
    set<V*>* vertexSet()
    {
        return delegate.vertexSet();
    }

    /**
     * @see Graph#getEdgeSource(Object)
     */
    V* getEdgeSource(E* e)
    {
        return delegate.getEdgeSource(e);
    }

    /**
     * @see Graph#getEdgeTarget(Object)
     */
    V* getEdgeTarget(E* e)
    {
        return delegate.getEdgeTarget(e);
    }

    /**
     * @see Graph#getEdgeWeight(Object)
     */
    double getEdgeWeight(E* e)
    {
        return delegate.getEdgeWeight(e);
    }

    /**
     * @see WeightedGraph#setEdgeWeight(Object, double)
     */
    void setEdgeWeight(E* e, double weight)
    {
    	((WeightedGraph<V, E>*) delegate).setEdgeWeight(e, weight);
    }
};

#endif /*GRAPHDELEGATOR_H_*/
