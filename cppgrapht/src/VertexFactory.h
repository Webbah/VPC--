#ifndef VERTEXFACTORY_H_
#define VERTEXFACTORY_H_

/**
 * A vertex factory used by graph algorithms for creating new vertices.
 * Normally, vertices are constructed by user code and added to a graph
 * explicitly, but algorithms which generate new vertices require a factory.
 *
 * @author Galina Engelmann <galinae@mail.upb.de>
 * @since 2011-06-06
 */
template<class V>
class VertexFactory
{
public:
    /**
     * Creates a new vertex.
     *
     * @return the new vertex
     */
	virtual V* createVertex() = 0;
};
#endif /* VERTEXFACTORY_H_ */
