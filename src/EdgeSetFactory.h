#ifndef EDGESETFACTORY_H_
#define EDGESETFACTORY_H_

#include <set>

using namespace std;

/**
 * A factory for edge sets. This interface allows the creator of a graph to
 * choose the {@link java.util.Set} implementation used internally by the graph
 * to maintain sets of edges. This provides control over performance tradeoffs
 * between memory and CPU usage.
 *
 * @author Galina Engelmann <galinae@mail.upb.de>
 * @since 2011-06-06
 */
template <class V, class E>
class EdgeSetFactory
{
public:
    /**
     * Create a new edge set for a particular vertex.
     *
     * @param vertex the vertex for which the edge set is being created;
     * sophisticated factories may be able to use this information to choose an
     * optimal set representation (e.g. ArrayUnenforcedSet for a vertex expected
     * to have low degree, and LinkedHashSet for a vertex expected to have high
     * degree)
     *
     * @return new set
     */
	virtual set<E*>* createEdgeSet(V* vertex) = 0;
};
#endif /* EDGESETFACTORY_H_ */
