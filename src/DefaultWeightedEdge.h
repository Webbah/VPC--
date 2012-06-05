#ifndef DEFAULTWEIGHTEDEDGE_H_
#define DEFAULTWEIGHTEDEDGE_H_

#include <WeightedGraph.h>
#include <DefaultEdge.h>

/**
 * A default implementation for edges in a {@link WeightedGraph}. All access to
 * the weight of an edge must go through the graph interface, which is why this
 * class doesn't expose any public methods.
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-15
 */
template <class V>
class DefaultWeightedEdge : public DefaultEdge<V>
{
public:
    double weight;

    DefaultWeightedEdge()
    {
    	weight = WeightedGraph<V*, DefaultWeightedEdge>::DEFAULT_EDGE_WEIGHT;
    }

    /**
     * Retrieves the weight of this edge. This is protected, for use by
     * subclasses only (e.g. for implementing toString).
     *
     * @return weight of this edge
     */
    double getWeight()
    {
        return weight;
    }
};

#endif /* DEFAULTWEIGHTEDEDGE_H_ */
