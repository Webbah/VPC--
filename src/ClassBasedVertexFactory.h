#ifndef CLASSBASEDVERTEXFACTORY_H_
#define CLASSBASEDVERTEXFACTORY_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include <VertexFactory.h>


/**
 * An {@link EdgeFactory} for producing edges by using a class as a factory.
 *
 * @author Heinrich Drobin <hedr@mail.upb.de>
 * @since 2011-06-13
 */
using namespace std;

template <class V>
class ClassBasedVertexFactory: public VertexFactory<V>
{
public:
    //~ Methods ----------------------------------------------------------------

    /**
     * @see VertexFactory#createVertex()
     */
    V* createVertex()
    {
        try {
            return new V();
        }
        catch (exception& e){
            throw new logic_error("Vertex factory failed: " += e.what());
        }
    }
};
#endif /* CLASSBASEDVERTEXFACTORY_H_ */
