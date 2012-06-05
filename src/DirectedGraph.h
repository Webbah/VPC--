#ifndef DIRECTEDGRAPH_H_
#define DIRECTEDGRAPH_H_

#include <set>
#include <Graph.h>

/**
 * A graph whose all edges are directed. This is the root interface of all
 * directed graphs.
 *
 * <p>See <a href="http://mathworld.wolfram.com/DirectedGraph.html">
 * http://mathworld.wolfram.com/DirectedGraph.html</a> for more on directed
 * graphs.</p>
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-03
 */
template <class V, class E>
class DirectedGraph// : public Graph<V, E>
{
public:
	/**
	 * Returns the "in degree" of the specified vertex. An in degree of a vertex
	 * in a directed graph is the number of inward directed edges from that
	 * vertex. See <a href="http://mathworld.wolfram.com/Indegree.html">
	 * http://mathworld.wolfram.com/Indegree.html</a>.
	 *
	 * @param vertex vertex whose degree is to be calculated.
	 *
	 * @return the degree of the specified vertex.
	 */
	virtual int inDegreeOf(V* vertex) = 0;

	/**
	 * Returns a set of all edges incoming into the specified vertex.
	 *
	 * @param vertex the vertex for which the list of incoming edges to be
	 * returned.
	 *
	 * @return a set of all edges incoming into the specified vertex.
	 */
	virtual set<E*>* incomingEdgesOf(V* vertex) = 0;

	/**
	 * Returns the "out degree" of the specified vertex. An out degree of a
	 * vertex in a directed graph is the number of outward directed edges from
	 * that vertex. See <a href="http://mathworld.wolfram.com/Outdegree.html">
	 * http://mathworld.wolfram.com/Outdegree.html</a>.
	 *
	 * @param vertex vertex whose degree is to be calculated.
	 *
	 * @return the degree of the specified vertex.
	 */
	virtual int outDegreeOf(V* vertex) = 0;

	/**
	 * Returns a set of all edges outgoing from the specified vertex.
	 *
	 * @param vertex the vertex for which the list of outgoing edges to be
	 * returned.
	 *
	 * @return a set of all edges outgoing from the specified vertex.
	 */
	virtual set<E*>* outgoingEdgesOf(V* vertex) = 0;
};

#endif /* DIRECTEDGRAPH_H_ */
