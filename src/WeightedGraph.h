#ifndef WEIGHTEDGRAPH_H_
#define WEIGHTEDGRAPH_H_

#include <Graph.h>

/**
 * An interface for a graph whose edges have non-uniform weights.
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-03
 */
template <class V, class E>
class WeightedGraph : public Graph<V, E>
{
public:
	/**
	 * The default weight for an edge.
	 */
	static const double DEFAULT_EDGE_WEIGHT = 1.0;

	/**
	 * Assigns a weight to an edge.
	 *
	 * @param e edge on which to set weight
	 * @param weight new weight for edge
	 */
	virtual void setEdgeWeight(E* e, double weight) = 0;
};

#endif /* WEIGHTEDGRAPH_H_ */
