#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <EdgeFactory.h>

using namespace std;

/**
 * The root interface in the graph hierarchy. A mathematical graph-theory graph
 * object <tt>G(V*,E*)</tt> contains a set <tt>V*</tt> of vertices and a set <tt>
 * E*</tt> of edges. Each edge e=(v1,v2) in E* connects vertex v1 to vertex v2.
 * for more information about graphs and their related definitions see <a
 * href="http://mathworld.wolfram.com/Graph.html">
 * http://mathworld.wolfram.com/Graph.html</a>.
 *
 * <p>This library generally follows the terminology found at: <a
 * href="http://mathworld.wolfram.com/topics/GraphTheory.html">
 * http://mathworld.wolfram.com/topics/GraphTheory.html</a>. Implementation of
 * this interface can provide simple-graphs, multigraphs, pseudographs etc. The
 * package <code>org.jgrapht.graph</code> provides a gallery of abstract and
 * concrete graph implementations.</p>
 *
 * <p>This library works best when vertices represent arbitrary objects and
 * edges represent the relationships between them. Vertex and edge instances may
 * be shared by more than one graph.</p>
 *
 * <p>Through templates, a graph can be typed to specific classes for vertices
 * <code>V*</code> and edges <code>E*&lt;T&gt;</code>. Such a graph can contain
 * vertices of type <code>V*</code> and all sub-types and Edges of type <code>
 * E*</code> and all sub-types.</p>
 *
 * <p>For guidelines on vertex and edge classes, see <a
 * href="http://pub.eigenbase.org/wiki/JGraphT:EqualsAndHashCode">this wiki
 * page</a>.
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-03
 */
template <class V, class E>
class Graph
{
public:
	/**
	 * Returns a set of all edges connecting source vertex to target vertex if
	 * such vertices exist in this graph. If any of the vertices does not exist
	 * or is <code>null</code>, returns <code>null</code>. If both vertices
	 * exist but no edges found, returns an empty set.
	 *
	 * <p>In undirected graphs, some of the returned edges may have their source
	 * and target vertices in the opposite order. In simple graphs the returned
	 * set is either singleton set or empty set.</p>
	 *
	 * @param sourceVertex source vertex of the edge.
	 * @param targetVertex target vertex of the edge.
	 *
	 * @return a set of all edges connecting source vertex to target vertex.
	 */
	virtual set<E*>* getAllEdges(V* sourceVertex, V* targetVertex) = 0;

	/**
	 * Returns an edge connecting source vertex to target vertex if such
	 * vertices and such edge exist in this graph. Otherwise returns <code>
	 * null</code>. If any of the specified vertices is <code>null</code>
	 * returns <code>null</code>
	 *
	 * <p>In undirected graphs, the returned edge may have its source and target
	 * vertices in the opposite order.</p>
	 *
	 * @param sourceVertex source vertex of the edge.
	 * @param targetVertex target vertex of the edge.
	 *
	 * @return an edge connecting source vertex to target vertex.
	 */
	virtual E* getEdge(V* sourceVertex, V* targetVertex) = 0;

	/**
	 * Returns the edge factory using which this graph creates new edges. The
	 * edge factory is defined when the graph is constructed and must not be
	 * modified.
	 *
	 * @return the edge factory using which this graph creates new edges.
	 */
	virtual EdgeFactory<V, E>* getEdgeFactory() = 0;

	/**
	 * Creates a new edge in this graph, going from the source vertex to the
	 * target vertex, and returns the created edge. Some graphs do not allow
	 * edge-multiplicity. In such cases, if the graph already contains an edge
	 * from the specified source to the specified target, than this method does
	 * not change the graph and returns <code>null</code>.
	 *
	 * <p>The source and target vertices must already be contained in this
	 * graph. If they are not found in graph invalid_argument is
	 * thrown.</p>
	 *
	 * <p>This method creates the new edge <code>e</code> using this graph's
	 * <code>EdgeFactory</code>. For the new edge to be added <code>e</code>
	 * must <i>not</i> be equal to any other edge the graph (even if the graph
	 * allows edge-multiplicity). More formally, the graph must not contain any
	 * edge <code>e2</code> such that <code>e2.equals(e)</code>. If such <code>
	 * e2</code> is found then the newly created edge <code>e</code> is
	 * abandoned, the method leaves this graph unchanged returns <code>
	 * null</code>.</p>
	 *
	 * @param sourceVertex source vertex of the edge.
	 * @param targetVertex target vertex of the edge.
	 *
	 * @return The newly created edge if added to the graph, otherwise <code>
	 * null</code>.
	 *
	 * @throws invalid_argument if source or target vertices are not
	 * found in the graph.
	 * @throws invalid_argument if any of the specified vertices is <code>
	 * null</code>.
	 *
	 * @see #getEdgeFactory()
	 */
	virtual E* addEdge(V* sourceVertex, V* targetVertex) = 0;

	/**
	 * Adds the specified edge to this graph, going from the source vertex to
	 * the target vertex. More formally, adds the specified edge, <code>
	 * e</code>, to this graph if this graph contains no edge <code>e2</code>
	 * such that <code>e2.equals(e)</code>. If this graph already contains such
	 * an edge, the call leaves this graph unchanged and returns <tt>false</tt>.
	 * Some graphs do not allow edge-multiplicity. In such cases, if the graph
	 * already contains an edge from the specified source to the specified
	 * target, than this method does not change the graph and returns <code>
	 * false</code>. If the edge was added to the graph, returns <code>
	 * true</code>.
	 *
	 * <p>The source and target vertices must already be contained in this
	 * graph. If they are not found in graph invalid_argument is
	 * thrown.</p>
	 *
	 * @param sourceVertex source vertex of the edge.
	 * @param targetVertex target vertex of the edge.
	 * @param e edge to be added to this graph.
	 *
	 * @return <tt>true</tt> if this graph did not already contain the specified
	 * edge.
	 *
	 * @throws invalid_argument if source or target vertices are not
	 * found in the graph.
	 * @throws invalid_argument if the specified edge is not assignment
	 * compatible with the class of edges produced by the edge factory of this
	 * graph.
	 * @throws invalid_argument if any of the specified vertices is <code>
	 * null</code>.
	 *
	 * @see #addEdge(Object, Object)
	 * @see #getEdgeFactory()
	 */
	virtual bool addEdge(V* sourceVertex, V* targetVertex, E* e) = 0;

	/**
	 * Adds the specified vertex to this graph if not already present. More
	 * formally, adds the specified vertex, <code>v</code>, to this graph if
	 * this graph contains no vertex <code>u</code> such that <code>
	 * u.equals(v)</code>. If this graph already contains such vertex, the call
	 * leaves this graph unchanged and returns <tt>false</tt>. In combination
	 * with the restriction on constructors, this ensures that graphs never
	 * contain duplicate vertices.
	 *
	 * @param v vertex to be added to this graph.
	 *
	 * @return <tt>true</tt> if this graph did not already contain the specified
	 * vertex.
	 *
	 * @throws invalid_argument if the specified vertex is <code>
	 * null</code>.
	 */
	virtual bool addVertex(V* v) = 0;

	/**
	 * Returns <tt>true</tt> if and only if this graph contains an edge going
	 * from the source vertex to the target vertex. In undirected graphs the
	 * same result is obtained when source and target are inverted. If any of
	 * the specified vertices does not exist in the graph, or if is <code>
	 * null</code>, returns <code>false</code>.
	 *
	 * @param sourceVertex source vertex of the edge.
	 * @param targetVertex target vertex of the edge.
	 *
	 * @return <tt>true</tt> if this graph contains the specified edge.
	 */
	virtual bool containsEdgeV(V* sourceVertex, V* targetVertex) = 0;

	/**
	 * Returns <tt>true</tt> if this graph contains the specified edge. More
	 * formally, returns <tt>true</tt> if and only if this graph contains an
	 * edge <code>e2</code> such that <code>e.equals(e2)</code>. If the
	 * specified edge is <code>null</code> returns <code>false</code>.
	 *
	 * @param e edge whose presence in this graph is to be tested.
	 *
	 * @return <tt>true</tt> if this graph contains the specified edge.
	 */
	virtual bool containsEdge(E* e) = 0;

	/**
	 * Returns <tt>true</tt> if this graph contains the specified vertex. More
	 * formally, returns <tt>true</tt> if and only if this graph contains a
	 * vertex <code>u</code> such that <code>u.equals(v)</code>. If the
	 * specified vertex is <code>null</code> returns <code>false</code>.
	 *
	 * @param v vertex whose presence in this graph is to be tested.
	 *
	 * @return <tt>true</tt> if this graph contains the specified vertex.
	 */
	virtual bool containsVertex(V* v) = 0;

	/**
	 * Returns a set of the edges contained in this graph. The set is backed by
	 * the graph, so changes to the graph are reflected in the set. If the graph
	 * is modified while an iteration over the set is in progress, the results
	 * of the iteration are undefined.
	 *
	 * <p>The graph implementation may maintain a particular set ordering (e.g.
	 * via {@link java.util.LinkedHashSet}) for deterministic iteration, but
	 * this is not required. It is the responsibility of callers who rely on
	 * this behavior to only use graph implementations which support it.</p>
	 *
	 * @return a set of the edges contained in this graph.
	 */
	virtual const set<E*>* edgeSet() = 0;

	/**
	 * Returns a set of all edges touching the specified vertex. If no edges are
	 * touching the specified vertex returns an empty set.
	 *
	 * @param vertex the vertex for which a set of touching edges is to be
	 * returned.
	 *
	 * @return a set of all edges touching the specified vertex.
	 *
	 * @throws invalid_argument if vertex is not found in the graph.
	 * @throws invalid_argument if vertex is <code>null</code>.
	 */
	virtual const set<E*>* edgesOf(V* vertex) = 0;

	/**
	 * Removes all the edges in this graph that are also contained in the
	 * specified edge set. After this call returns, this graph will
	 * contain no edges in common with the specified edges. This method will
	 * invoke the {@link #removeEdge(Object)} method.
	 *
	 * @param edges edges to be removed from this graph.
	 *
	 * @return <tt>true</tt> if this graph changed as a result of the call
	 *
	 * @throws invalid_argument if the specified edge collection is <tt>
	 * null</tt>.
	 *
	 * @see #removeEdge(Object)
	 * @see #containsEdge(Object)
	 */
	// Note:	Uses set instead of collection, as no common base-class exists
	// 			for set and list in C++. If support for list is needed, create
	//			an overloaded method
	virtual bool removeAllEdges(set<E*>* edges) = 0;

	/**
	 * Removes all the edges going from the specified source vertex to the
	 * specified target vertex, and returns a set of all removed edges. Returns
	 * <code>null</code> if any of the specified vertices does not exist in the
	 * graph. If both vertices exist but no edge is found, returns an empty set.
	 * This method will either invoke the {@link #removeEdge(Object)} method, or
	 * the {@link #removeEdge(Object, Object)} method.
	 *
	 * @param sourceVertex source vertex of the edge.
	 * @param targetVertex target vertex of the edge.
	 *
	 * @return the removed edges, or <code>null</code> if no either vertex not
	 * part of graph
	 */
	virtual set<E*>* removeAllEdges(V* sourceVertex, V* targetVertex) = 0;

	/**
	 * Removes all the vertices in this graph that are also contained in the
	 * specified vertex set. After this call returns, this graph will
	 * contain no vertices in common with the specified vertices. This method
	 * will invoke the {@link #removeVertex(Object)} method.
	 *
	 * @param vertices vertices to be removed from this graph.
	 *
	 * @return <tt>true</tt> if this graph changed as a result of the call
	 *
	 * @throws invalid_argument if the specified vertex collection is <tt>
	 * null</tt>.
	 *
	 * @see #removeVertex(Object)
	 * @see #containsVertex(Object)
	 */
	// Note:	Uses set instead of collection, as no common base-class exists
	// 			for set and list in C++. If support for list is needed, create
	//			an overloaded method
	virtual bool removeAllVertices(set<V*>* vertices) = 0;

	/**
	 * Removes an edge going from source vertex to target vertex, if such
	 * vertices and such edge exist in this graph. Returns the edge if removed
	 * or <code>null</code> otherwise.
	 *
	 * @param sourceVertex source vertex of the edge.
	 * @param targetVertex target vertex of the edge.
	 *
	 * @return The removed edge, or <code>null</code> if no edge removed.
	 */
	virtual E* removeEdge(V* sourceVertex, V* targetVertex) = 0;

	/**
	 * Removes the specified edge from the graph. Removes the specified edge
	 * from this graph if it is present. More formally, removes an edge <code>
	 * e2</code> such that <code>e2.equals(e)</code>, if the graph contains such
	 * edge. Returns <tt>true</tt> if the graph contained the specified edge.
	 * (The graph will not contain the specified edge once the call returns).
	 *
	 * <p>If the specified edge is <code>null</code> returns <code>
	 * false</code>.</p>
	 *
	 * @param e edge to be removed from this graph, if present.
	 *
	 * @return <code>true</code> if and only if the graph contained the
	 * specified edge.
	 */
	virtual bool removeEdge(E* e) = 0;

	/**
	 * Removes the specified vertex from this graph including all its touching
	 * edges if present. More formally, if the graph contains a vertex <code>
	 * u</code> such that <code>u.equals(v)</code>, the call removes all edges
	 * that touch <code>u</code> and then removes <code>u</code> itself. If no
	 * such <code>u</code> is found, the call leaves the graph unchanged.
	 * Returns <tt>true</tt> if the graph contained the specified vertex. (The
	 * graph will not contain the specified vertex once the call returns).
	 *
	 * <p>If the specified vertex is <code>null</code> returns <code>
	 * false</code>.</p>
	 *
	 * @param v vertex to be removed from this graph, if present.
	 *
	 * @return <code>true</code> if the graph contained the specified vertex;
	 * <code>false</code> otherwise.
	 */
	virtual bool removeVertex(V* v) = 0;

	/**
	 * Returns a set of the vertices contained in this graph. The set is backed
	 * by the graph, so changes to the graph are reflected in the set. If the
	 * graph is modified while an iteration over the set is in progress, the
	 * results of the iteration are undefined.
	 *
	 * <p>The graph implementation may maintain a particular set ordering (e.g.
	 * via {@link java.util.LinkedHashSet}) for deterministic iteration, but
	 * this is not required. It is the responsibility of callers who rely on
	 * this behavior to only use graph implementations which support it.</p>
	 *
	 * @return a set view of the vertices contained in this graph.
	 */
	virtual const set<V*>* vertexSet() = 0;

	/**
	 * Returns the source vertex of an edge. For an undirected graph, source and
	 * target are distinguishable designations (but without any mathematical
	 * meaning).
	 *
	 * @param e edge of interest
	 *
	 * @return source vertex
	 */
	virtual V* getEdgeSource(E* e) = 0;

	/**
	 * Returns the target vertex of an edge. For an undirected graph, source and
	 * target are distinguishable designations (but without any mathematical
	 * meaning).
	 *
	 * @param e edge of interest
	 *
	 * @return target vertex
	 */
	virtual V* getEdgeTarget(E* e) = 0;

	/**
	 * Returns the weight assigned to a given edge. Unweighted graphs return 1.0
	 * (as defined by {@link WeightedGraph#DEFAULT_EDGE_WEIGHT}), allowing
	 * weighted-graph algorithms to apply to them where meaningful.
	 *
	 * @param e edge of interest
	 *
	 * @return edge weight
	 *
	 * @see WeightedGraph
	 */
	virtual double getEdgeWeight(E* e) = 0;
};

#endif /* GRAPH_H_ */
