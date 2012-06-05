#ifndef CLASSBASEDEDGEFACTORY_H_
#define CLASSBASEDEDGEFACTORY_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include <EdgeFactory.h>

/**
 * An {@link EdgeFactory} for producing edges by using a class as a factory.
 *
 * @author Heinrich Drobin <hedr@mail.upb.de>
 * @since 2011-06-13
 */
using namespace std;

template <class V, class E>
class ClassBasedEdgeFactory: public EdgeFactory<V, E>
{
public:
    //~ Methods ----------------------------------------------------------------

    /**
     * @see EdgeFactory#createEdge(Object, Object)
     */
    E* createEdge(V* source, V* target)
    {
        //try {
            E* newEdge = new E();
            newEdge->source = source;
            newEdge->target = target;
            return newEdge;
        /*}
        catch (exception& e){
            throw new logic_error("Edge factory failed: " += e.what());
        }*/
    }
};

#endif /* CLASSBASEDEDGEFACTORY_H_ */
