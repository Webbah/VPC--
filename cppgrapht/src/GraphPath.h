#ifndef GRAPHPATH_H_
#define GRAPHPATH_H_

#include <list>
#include <Graph.h>

/**
 * A GraphPath represents a <a href="http://mathworld.wolfram.com/Path.html">
 * path</a> in a {@link Graph}. Note that a path is defined primarily in terms
 * of edges (rather than vertices) so that multiple edges between the same pair
 * of vertices can be discriminated.
 *
 * @author Rolf Brinkmann <rolfb@mail.upb.de>
 * @since 2011-06-16
 */
template <class V, class E>
class GraphPath
{
public:
	// Constructor
	GraphPath(){}
	
	// Destructor
	virtual ~GraphPath(){}
	
    //~ Methods ----------------------------------------------------------------

    /**
     * Returns the graph over which this path is defined. The path may also be
     * valid with respect to other graphs.
     *
     * @return the containing graph
     */
    virtual Graph<V, E>* getGraph() = 0;

    /**
     * Returns the start vertex in the path.
     *
     * @return the start vertex
     */
    virtual V* getStartVertex() = 0;

    /**
     * Returns the end vertex in the path.
     *
     * @return the end vertex
     */
    virtual V* getEndVertex() = 0;

    /**
     * Returns the edges making up the path. The first edge in this path is
     * incident to the start vertex. The last edge is incident to the end
     * vertex. The vertices along the path can be obtained by traversing from
     * the start vertex, finding its opposite across the first edge, and then
     * doing the same successively across subsequent edges; {@link
     * Graphs#getPathVertexList} provides a convenience method for this.
     *
     * <p>Whether or not the returned edge list is modifiable depends on the
     * path implementation.
     *
     * @return list of edges traversed by the path
     */
    virtual list<E*>* getEdgeList() = 0;

    /**
     * Returns the weight assigned to the path. Typically, this will be the sum
     * of the weights of the edge list entries (as defined by the containing
     * graph), but some path implementations may use other definitions.
     *
     * @return the weight of the path
     */
    virtual double getWeight() = 0;
};

#endif /*GRAPHPATH_H_*/
