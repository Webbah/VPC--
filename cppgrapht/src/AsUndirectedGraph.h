#ifndef ASUNDIRECTEDGRAPH_H_
#define ASUNDIRECTEDGRAPH_H_

#include <string>
#include <set>
#include <stdexcept>
#include <GraphDelegator.h>
#include <UndirectedGraph.h>

#define DEFAULT_RETURN_VALUE (0)
#define NO_EDGE_ADD ("this graph does not support edge addition")
#define UNDIRECTED ("this graph only supports undirected operations")

/**
 * An undirected view of the backing directed graph specified in the
 * constructor. This graph allows modules to apply algorithms designed for
 * undirected graphs to a directed graph by simply ignoring edge direction. If
 * the backing directed graph is an <a
 * href="http://mathworld.wolfram.com/OrientedGraph.html">oriented graph</a>,
 * then the view will be a simple graph; otherwise, it will be a multigraph.
 * Query operations on this graph "read through" to the backing graph. Attempts
 * to add edges will result in an <code>UnsupportedOperationException</code>,
 * but vertex addition/removal and edge removal are all supported (and
 * immediately reflected in the backing graph).
 *
 * <p>Note that edges returned by this graph's accessors are really just the
 * edges of the underlying directed graph. Since there is no interface
 * distinction between directed and undirected edges, this detail should be
 * irrelevant to algorithms.</p>
 *
 * <p>This graph does <i>not</i> pass the hashCode and equals operations through
 * to the backing graph, but relies on <tt>Object</tt>'s <tt>equals</tt> and
 * <tt>hashCode</tt> methods. This graph will be serializable if the backing
 * graph is serializable.</p>
 *
 * @author Rolf Brinkmann <rolfb@mail.upb.de>
 * @since 2011-06-09
 */
template <class V, class E>
class AsUndirectedGraph :
	public GraphDelegator<V, E>,
	public UndirectedGraph<V, E>
{
private:
    //~ Static fields/initializers ---------------------------------------------

public:
    //~ Constructors -----------------------------------------------------------

    /**
     * Constructor for AsUndirectedGraph.
     *
     * @param g the backing directed graph over which an undirected view is to
     * be created.
     */
	AsUndirectedGraph(DirectedGraph<V, E> g) : GraphDelegator<V, E>(g){}
	virtual ~AsUndirectedGraph(){}
	
    //~ Methods ----------------------------------------------------------------

    /**
     * @see Graph#getAllEdges(Object, Object)
     */
    set<E*>* getAllEdges(V* sourceVertex, V* targetVertex)
    {
        set<E*>* forwardList = GraphDelegator<V,E>::getAllEdges(sourceVertex, targetVertex);

        if (sourceVertex.equals(targetVertex)) {
            // avoid duplicating loops
            return forwardList;
        }

        set<E*>* reverseList = GraphDelegator<V,E>::getAllEdges(targetVertex, sourceVertex);
        set<E*>* list;
        typename set<E*>::iterator it;
        for (it = forwardList.begin(); it != forwardList.end(); it++){
        	list.insert(forwardList(it));
        }
        for (it = reverseList.begin(); it != reverseList.end(); it++){
        	list.insert(reverseList(it));
        }

        return list;
    }

    /**
     * @see Graph#getEdge(Object, Object)
     */
    E* getEdge(V* sourceVertex, V* targetVertex)
    {
        E* edge = GraphDelegator<V,E>::getEdge(sourceVertex, targetVertex);

        if (edge != NULL) {
            return edge;
        }

        // try the other direction
        return GraphDelegator<V,E>::getEdge(targetVertex, sourceVertex);
    }

    /**
     * @see Graph#addEdge(Object, Object)
     */
    E* addEdge(V* sourceVertex, V* targetVertex)
    {
        throw new domain_error(NO_EDGE_ADD);
    }

    /**
     * @see Graph#addEdge(Object, Object, Object)
     */
    bool addEdge(V* sourceVertex, V* targetVertex, E* e)
    {
        throw new domain_error(NO_EDGE_ADD);
    }

    /**
     * @see UndirectedGraph#degreeOf(Object)
     */
    int degreeOf(V* vertex)
    {
        // this counts loops twice, which is consistent with AbstractBaseGraph
        return GraphDelegator<V,E>::inDegreeOf(vertex) + GraphDelegator<V,E>::outDegreeOf(vertex);
    }

    /**
     * @see DirectedGraph#inDegreeOf(Object)
     */
    int inDegreeOf(V* vertex)
    {
        throw new domain_error(UNDIRECTED);
    }

    /**
     * @see DirectedGraph#incomingEdgesOf(Object)
     */
    set<E*>* incomingEdgesOf(V* vertex)
    {
        throw new domain_error(UNDIRECTED);
    }

    /**
     * @see DirectedGraph#outDegreeOf(Object)
     */
    int outDegreeOf(V* vertex)
    {
        throw new domain_error(UNDIRECTED);
    }

    /**
     * @see DirectedGraph#outgoingEdgesOf(Object)
     */
    set<E*>* outgoingEdgesOf(V* vertex)
    {
        throw new domain_error(UNDIRECTED);
    }

    /**
     * @see AbstractBaseGraph#toString()
     */
    /*string toString()
    {
        return GraphDelegator<V*,E*>::toStringFromSets(vertexSet(), edgeSet(), false);
    }*/
};

#endif /*ASUNDIRECTEDGRAPH_H_*/
