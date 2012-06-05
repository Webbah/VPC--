#ifndef ABSTRACTGRAPH_H_
#define ABSTRACTGRAPH_H_

#include <typeinfo>
#include <set>
#include <list>
#include <stdexcept>
#include <Graph.h>
#include <DirectedGraph.h>
#include <DefaultEdge.h>
#include <DefaultWeightedEdge.h>

/**
 * A skeletal implementation of the <tt>Graph</tt> interface, to minimize the
 * effort required to implement graph interfaces. This implementation is
 * applicable to both: directed graphs and undirected graphs.
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-05
 * @see Graph
 * @see DirectedGraph
 * @see UndirectedGraph
 */
template <class V, class E>
class AbstractGraph : public Graph<V, E>
{
public:
	/**
	 * Construct a new empty graph object.
	 */
	AbstractGraph()
	{
		// empty
	}

	/**
	 * @see Graph#containsEdge(Object, Object)
	 */
	bool containsEdgeV(V* sourceVertex, V* targetVertex)
	{
		return getEdge(sourceVertex, targetVertex) != NULL;
	}

	/**
	 * @see Graph#removeAllEdges(Collection)
	 */
	bool removeAllEdges(set<E*>* edges)
	{
		bool modified = false;

		typename set<E*>::iterator it;
		for (it = edges->begin(); it != edges->end(); it++) {
			modified |= removeEdge(*it);
		}

		return modified;
	}

	/**
	 * @see Graph#removeAllEdges(Object, Object)
	 */
	set<E*>* removeAllEdges(V* sourceVertex, V* targetVertex)
	{
		set<E*>* removed = getAllEdges(sourceVertex, targetVertex);
		removeAllEdges(removed);

		return removed;
	}

	/**
	 * @see Graph#removeAllVertices(Collection)
	 */
	bool removeAllVertices(set<V*>* vertices)
	{
		bool modified = false;

		typename set<V*>::iterator it;
		for (it = vertices->begin(); it != vertices->end(); it++) {
			modified |= removeVertex(*it);
		}

		return modified;
	}

	/**
	 * Returns a string of the parenthesized pair (V*, E*) representing this
	 * G=(V*,E*) graph. 'V*' is the string representation of the vertex set, and
	 * 'E*' is the string representation of the edge set.
	 *
	 * @return a string representation of this graph.
	 */
	/*string toString()
	{
		return toStringFromSets(
			this->vertexSet(),
			this->edgeSet(),
			typeid(this) == typeid(DirectedGraph<V, E>)
		);
	}*/

protected:
	/**
	 * Ensures that the specified vertex exists in this graph, or else throws
	 * exception.
	 *
	 * @param v vertex
	 *
	 * @return <code>true</code> if this assertion holds.
	 *
	 * @throws NullPointerException if specified vertex is <code>null</code>.
	 * @throws IllegalArgumentException if specified vertex does not exist in
	 * this graph.
	 */
	bool assertVertexExist(V* v)
	{
		if (containsVertex(v)) {
			return true;
		} else if (v == NULL) {
			throw new invalid_argument("Null pointer given");
		} else {
			throw new invalid_argument("No such vertex in graph");
		}
	}

	/**
	 * Helper for subclass implementations of toString( ).
	 *
	 * @param vertexSet the vertex set V* to be printed
	 * @param edgeSet the edge set E* to be printed
	 * @param directed true to use parens for each edge (representing directed);
	 * false to use curly braces (representing undirected)
	 *
	 * @return a string representation of (V*,E*)
	 */
	/*string toStringFromSets(
		set<V*>* vertexSet,
		set<E*>* edgeSet,
		bool directed)
	{
		string renderedEdges = "";

		string sb = ""; // TODO replace by ostream
		typename set<E*>::iterator it;
		for (it = edgeSet->begin(); it != edgeSet->end(); it++) {
			if ((typeid(*it) != typeid(DefaultEdge<V>*))
				&& (typeid(*it) != typeid(DefaultWeightedEdge<V>*)))
			{
				sb.append((*it)->toString());
				sb.append("=");
			}
			if (directed) {
				sb.append("(");
			} else {
				sb.append("{");
			}
			sb.append(this->getEdgeSource(*it));
			sb.append(",");
			sb.append(this->getEdgeTarget(*it));
			if (directed) {
				sb.append(")");
			} else {
				sb.append("}");
			}

			renderedEdges.append(sb);
			sb = "";
		}

		return "(" + vertexSet + ", " + renderedEdges + ")";
	}*/
};

#endif /* ABSTRACTGRAPH_H_ */
