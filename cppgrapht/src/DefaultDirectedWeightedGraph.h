
#ifndef DEFAULTDIRECTEDWEIGHTEDGRAPH_H_
#define DEFAULTDIRECTEDWEIGHTEDGRAPH_H_


#include <DefaultDirectedGraph.h>
#include <WeightedGraph.h>
//#include <ClassBasedEdgeFactory.h>

/**
 * A directed weighted graph. A directed weighted graph is a non-simple directed
 * graph in which multiple edges between any two vertices are <i>not</i>
 * permitted, but loops are. The graph has weights on its edges.
 *
 * @see DefaultDirectedGraph
 * @author Galina Engelmann <galinae@mail.upb.de>
 * @since 2011-06-22
 */

template< class V, class E>
 class DefaultDirectedWeightedGraph: public DefaultDirectedGraph<V, E>,
                                     public WeightedGraph<V, E>

{

    //~ Static fields/initializers ---------------------------------------------



    //~ Constructors -----------------------------------------------------------

    /**
     * Creates a new directed weighted graph.
     *
     * @param edgeClass class on which to base factory for edges
     */
public:
        DefaultDirectedWeightedGraph(E* edgeClass)
    {
      //request heap-memory and call the constructor for initialisation
       ClassBasedEdgeFactory<V, E>* ef = new ClassBasedEdgeFactory<V, E>(edgeClass);

           this->DefaultDirectedWeightedGraph(ef);
    }

    /**
     * Creates a new directed weighted graph with the specified edge factory.
     *
     * @param ef the edge factory of the new graph.
     */
        //Standard-konstructor of the Upperclass is called
 DefaultDirectedWeightedGraph(EdgeFactory<V, E>* ef) : DefaultDirectedGraph<V, E>(ef){}
       // Destructer
       virtual ~DefaultDirectedWeightedGraph(){}
};



#endif /* DEFAULTDIRECTEDWEIGHTEDGRAPH_H_ */
