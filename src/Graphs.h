#ifndef GRAPHS_H_
#define GRAPHS_H_

#include <string>
#include <set>
#include <list>
#include <stdexcept>
#include <assert.h>
#include <Graph.h>
#include <DirectedGraph.h>
#include <WeightedGraph.h>
#include <AsUndirectedGraph.h>
#include <GraphPath.h>

/**
 * A collection of utilities to assist with graph manipulation.
 *
 * @author Rolf Brinkmann <rolfb@mail.upb.de>
 * @since 2011-06-09
 */
class Graphs
{
public:
	Graphs(){}
	virtual ~Graphs(){}
	
    //~ Methods ----------------------------------------------------------------

    /**
     * Creates a new edge and adds it to the specified graph similarly to the
     * {@link Graph#addEdge(Object, Object)} method.
     *
     * @param g the graph for which the edge to be added.
     * @param sourceVertex source vertex of the edge.
     * @param targetVertex target vertex of the edge.
     * @param weight weight of the edge.
     *
     * @return The newly created edge if added to the graph, otherwise <code>
     * NULL</code>.
     *
     * @see Graph#addEdge(Object, Object)
     */
	template <class V, class E>
    static E* addEdge(
    	Graph<V, E>* g,
    	V* sourceVertex,
    	V* targetVertex,
    	double weight)
    {
        EdgeFactory<V, E>* ef = g->getEdgeFactory();
        E* e = ef->createEdge(sourceVertex, targetVertex);

        // we first create the edge and set the weight to make sure that
        // listeners will see the correct weight upon addEdge.
        
        assert(typeid(g) == typeid(WeightedGraph<V,E>*));
        WeightedGraph<V, E>* gAsWeightedGraph = (WeightedGraph<V, E>*) g;
        gAsWeightedGraph->setEdgeWeight(e, weight);

        return g->addEdge(sourceVertex, targetVertex, e) ? e : NULL;
    }

    /**
     * Adds the specified source and target vertices to the graph, if not
     * already included, and creates a new edge and adds it to the specified
     * graph similarly to the {@link Graph#addEdge(Object, Object)} method.
     *
     * @param g the graph for which the specified edge to be added.
     * @param sourceVertex source vertex of the edge.
     * @param targetVertex target vertex of the edge.
     *
     * @return The newly created edge if added to the graph, otherwise <code>
     * NULL</code>.
     */
	template <class V, class E>
    static E* addEdgeWithVertices(
        Graph<V, E>* g,
        V* sourceVertex,
        V* targetVertex)
    {
        g->addVertex(sourceVertex);
        g->addVertex(targetVertex);

        return g->addEdge(sourceVertex, targetVertex);
    }

    /**
     * Adds the specified edge to the graph, including its vertices if not
     * already included.
     *
     * @param targetGraph the graph for which the specified edge to be added.
     * @param sourceGraph the graph in which the specified edge is already
     * present
     * @param edge edge to add
     *
     * @return <tt>true</tt> if the target graph did not already contain the
     * specified edge.
     */
	template <class V, class E>
    static bool addEdgeWithVertices(
        Graph<V, E>* targetGraph,
        Graph<V, E>* sourceGraph,
        E* edge)
    {
        V* sourceVertex = sourceGraph->getEdgeSource(edge);
        V* targetVertex = sourceGraph->getEdgeTarget(edge);

        targetGraph->addVertex(sourceVertex);
        targetGraph->addVertex(targetVertex);

        return targetGraph->addEdge(sourceVertex, targetVertex, edge);
    }

    /**
     * Adds the specified source and target vertices to the graph, if not
     * already included, and creates a new weighted edge and adds it to the
     * specified graph similarly to the {@link Graph#addEdge(Object, Object)}
     * method.
     *
     * @param g the graph for which the specified edge to be added.
     * @param sourceVertex source vertex of the edge.
     * @param targetVertex target vertex of the edge.
     * @param weight weight of the edge.
     *
     * @return The newly created edge if added to the graph, otherwise <code>
     * NULL</code>.
     */
	template <class V, class E>
    static E* addEdgeWithVertices(
        Graph<V, E>* g,
        V* sourceVertex,
        V* targetVertex,
        double weight)
    {
        g->addVertex(sourceVertex);
        g->addVertex(targetVertex);

        return addEdge(g, sourceVertex, targetVertex, weight);
    }

    /**
     * Adds all the vertices and all the edges of the specified source graph to
     * the specified destination graph. First all vertices of the source graph
     * are added to the destination graph. Then every edge of the source graph
     * is added to the destination graph. This method returns <code>true</code>
     * if the destination graph has been modified as a result of this operation,
     * otherwise it returns <code>false</code>.
     *
     * <p>The behavior of this operation is undefined if any of the specified
     * graphs is modified while operation is in progress.</p>
     *
     * @param destination the graph to which vertices and edges are added.
     * @param source the graph used as source for vertices and edges to add.
     *
     * @return <code>true</code> if and only if the destination graph has been
     * changed as a result of this operation.
     */
	template <class V, class E>
    static bool addGraph(
        Graph<V, E>* destination,
        Graph<V, E>* source)
    {
        bool modified = addAllVertices<V,E>(destination, source->vertexSet());
        modified |= addAllEdges<V,E>(destination, source, source->edgeSet());

        return modified;
    }

    /**
     * Adds all the vertices and all the edges of the specified source digraph
     * to the specified destination digraph, reversing all of the edges. If you
     * want to do this as a linked view of the source graph (rather than by
     * copying to a destination graph), use {@link EdgeReversedGraph} instead.
     *
     * <p>The behavior of this operation is undefined if any of the specified
     * graphs is modified while operation is in progress.</p>
     *
     * @param destination the graph to which vertices and edges are added.
     * @param source the graph used as source for vertices and edges to add.
     *
     * @see EdgeReversedGraph
     */
	template <class V, class E>
    static void addGraphReversed(
        DirectedGraph<V, E>* destination,
        DirectedGraph<V, E>* source)
    {	
        addAllVertices<V, E>(destination, source->vertexSet());

        set<E*>* edgeSet = source->edgeSet;
        typename set<E*>::iterator it;
        for (it = edgeSet->begin(); it != edgeSet->end(); it++) {
            destination->addEdge(
                source->getEdgeTarget(edgeSet(it)),
                source->getEdgeSource(edgeSet(it)));
        }
    }

    /**
     * Adds a subset of the edges of the specified source graph to the specified
     * destination graph. The behavior of this operation is undefined if either
     * of the graphs is modified while the operation is in progress. {@link
     * #addEdgeWithVertices} is used for the transfer, so source vertexes will
     * be added automatically to the target graph.
     *
     * @param destination the graph to which edges are to be added
     * @param source the graph used as a source for edges to add
     * @param edges the edges to be added
     *
     * @return <tt>true</tt> if this graph changed as a result of the call
     */
	template <class V, class E>
    static bool addAllEdges(
        Graph<V, E>* destination,
        Graph<V, E>* source,
        set<E*>* edges)
    {
		V* s;
		V* t;
        bool modified = false;
        typename set<E*>::iterator it;
        
        for (it = edges->begin(); it != edges->end(); it++){
            s = source->getEdgeSource(edges(it));
            t = source->getEdgeTarget(edges(it));
            destination->addVertex(s);
            destination->addVertex(t);
            modified |= destination->addEdge(s, t, edges(it));
        }

        return modified;
    }

    /**
     * Adds all of the specified vertices to the destination graph. The behavior
     * of this operation is undefined if the specified vertex collection is
     * modified while the operation is in progress. This method will invoke the
     * {@link Graph#addVertex(Object)} method.
     *
     * @param destination the graph to which edges are to be added
     * @param vertices the vertices to be added to the graph.
     *
     * @return <tt>true</tt> if graph changed as a result of the call
     *
     * @throws NullPointerException if the specified vertices contains one or
     * more NULL vertices, or if the specified vertex collection is <tt>
     * NULL</tt>.
     *
     * @see Graph#addVertex(Object)
     */
	template <class V, class E>
    static bool addAllVertices(
        Graph<V, E>* destination,
        set<V*>* vertices)
    {
        bool modified = false;
        typename set<V*>::iterator it;
        
        for (it = vertices->begin(); it != vertices->end(); it++){
            modified |= destination->addVertex(vertices(it));
        }

        return modified;
    }

    /**
     * Returns a list of vertices that are the neighbors of a specified vertex.
     * If the graph is a multigraph vertices may appear more than once in the
     * returned list.
     *
     * @param g the graph to look for neighbors in.
     * @param vertex the vertex to get the neighbors of.
     *
     * @return a list of the vertices that are the neighbors of the specified
     * vertex.
     */
	template <class V, class E>
    static list<V*> neighborListOf(
    	Graph<V, E>* g,
        V* vertex)
    {
        list<V*>* neighbors;
        set<E*>* edges = g->edgesOf(vertex);
        typename set<E*>::iterator it;

        for (it = edges->begin(); it != edges->end(); it++){
            neighbors->insert(getOppositeVertex(g, edges(it), vertex));
        }

        return neighbors;
    }

    /**
     * Returns a list of vertices that are the direct predecessors of a
     * specified vertex. If the graph is a multigraph, vertices may appear more
     * than once in the returned list.
     *
     * @param g the graph to look for predecessors in.
     * @param vertex the vertex to get the predecessors of.
     *
     * @return a list of the vertices that are the direct predecessors of the
     * specified vertex.
     */
	template <class V, class E>
    static list<V*>* predecessorListOf(
        DirectedGraph<V, E>* g,
        V* vertex)
    {
        list<V*>* predecessors;
        set<E*>* edges = g->incomingEdgesOf(vertex);
        typename set<E*>::iterator it;

        for (it = edges->begin(); it != edges->end(); it++){
            predecessors->insert(getOppositeVertex(g, edges(it), vertex));
        }

        return predecessors;
    }

    /**
     * Returns a list of vertices that are the direct successors of a specified
     * vertex. If the graph is a multigraph vertices may appear more than once
     * in the returned list.
     *
     * @param g the graph to look for successors in.
     * @param vertex the vertex to get the successors of.
     *
     * @return a list of the vertices that are the direct successors of the
     * specified vertex.
     */
	template <class V, class E>
    static list<V*> successorListOf(
        DirectedGraph<V, E>* g,
        V* vertex)
    {
        list<V*>* successors;
        set<E*>* edges = g->outgoingEdgesOf(vertex);
        typename set<E*>::iterator it;

        for (it = edges->begin(); it != edges->end(); it++){
            successors->insert(getOppositeVertex(g, edges(it), vertex));
        }

        return successors;
    }

    /**
     * Returns an undirected view of the specified graph. If the specified graph
     * is directed, returns an undirected view of it. If the specified graph is
     * already undirected, just returns it.
     *
     * @param g the graph for which an undirected view is to be returned.
     *
     * @return an undirected view of the specified graph, if it is directed, or
     * or the specified graph itself if it is already undirected.
     *
     * @throws invalid_argument if the graph is neither DirectedGraph
     * nor UndirectedGraph.
     *
     * @see AsUndirectedGraph
     */
	template <class V, class E>
    static UndirectedGraph<V, E>* undirectedGraph(Graph<V, E>* g)
    {
        if (typeid(g) == typeid(DirectedGraph<V*,E*>*)){
            return new AsUndirectedGraph<V*, E*>*((DirectedGraph<V*, E*>*) g);
        } else if (typeid(g) == typeid(DirectedGraph<V*,E*>*)){
            return (UndirectedGraph<V*, E*>*) g;
        } else {
            throw invalid_argument(
                "Graph must be either DirectedGraph or UndirectedGraph");
        }
    }

    /**
     * Tests whether an edge is incident to a vertex.
     *
     * @param g graph containing e and v
     * @param e edge in g
     * @param v vertex in g
     *
     * @return true iff e is incident on v
     */
	template <class V, class E>
    static bool testIncidence(Graph<V, E>* g, E* e, V* v)
    {
        return (g->getEdgeSource(e) == v)
            || (g->getEdgeTarget(e) == v);
    }

    /**
     * Gets the vertex opposite another vertex across an edge.
     *
     * @param g graph containing e and v
     * @param e edge in g
     * @param v vertex in g
     *
     * @return vertex opposite to v across e
     */
	template <class V, class E>
    static V* getOppositeVertex(Graph<V, E>* g, E* e, V* v)
    {
        V* source = g->getEdgeSource(e);
        V* target = g->getEdgeTarget(e);
        if (v == source) {
            return target;
        } else if (v == target) {
            return source;
        } else {
            throw invalid_argument("no such vertex");
        }
    }

    /**
     * Gets the list of vertices visited by a path.
     *
     * @param path path of interest
     *
     * @return corresponding vertex list
     */
	template <class V, class E>
    static list<V*>* getPathVertexList(GraphPath<V, E>* path)
    {
        Graph<V, E>* g = path->getGraph();
        list<V*>* list;
        set<E*>* edges = path->getEdgeList();
        typename set<E*>::iterator it;
        
        V* v = path->getStartVertex();
        list->insert(v);
        for (it = edges->begin(); it != edges->end(); it++){
            v = getOppositeVertex(g, edges(it), v);
            list->insert(v);
        }
        return list;
    }
};

#endif /*GRAPHS_H_*/
