/**
 * An edge factory used by graphs for creating new edges.
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-03
 */

#ifndef EDGEFACTORY_H_
#define EDGEFACTORY_H_

template <class V, class E>
class EdgeFactory
{
public:
	/**
	 * Creates a new edge whose endpoints are the specified source and target
	 * vertices.
	 *
	 * @param sourceVertex the source vertex.
	 * @param targetVertex the target vertex.
	 *
	 * @return a new edge whose endpoints are the specified source and target
	 * vertices.
	 */
	virtual E* createEdge(V* sourceVertex, V* targetVertex) = 0;
};

#endif /* EDGEFACTORY_H_ */
