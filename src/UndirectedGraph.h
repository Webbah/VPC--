#ifndef UNDIRECTEDGRAPH_H_
#define UNDIRECTEDGRAPH_H_

#include <Graph.h>

/**
 * A graph whose all edges are undirected. This is the root interface of all
 * undirected graphs.
 *
 * <p>See <a href="http://mathworld.wolfram.com/Graph.html">
 * http://mathworld.wolfram.com/Graph.html</a> for more on undirected and on
 * directed graphs.</p>
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-03
 */
template <class V, class E>
class UndirectedGraph : public Graph<V, E>
{
public:
	/**
	 * Returns the degree of the specified vertex. A degree of a vertex in an
	 * undirected graph is the number of edges touching that vertex.
	 *
	 * @param vertex vertex whose degree is to be calculated.
	 *
	 * @return the degree of the specified vertex.
	 */
	virtual int degreeOf(V* vertex) = 0;
};

#endif /* UNDIRECTEDGRAPH_H_ */
