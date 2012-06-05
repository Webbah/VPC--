#ifndef DEFAULTEDGE_H_
#define DEFAULTEDGE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

#include <IntrusiveEdge.h>

using namespace std;

/**
 * A default implementation for edges in a {@link Graph}.
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-11
 */
template <class V>
class DefaultEdge : public IntrusiveEdge<V>
{
protected:
	/**
     * Retrieves the source of this edge. This is protected, for use by
     * subclasses only (e.g. for implementing toString).
     *
     * @return source of this edge
     */
    V* getSource()
    {
        return this->source;
    }

    /**
     * Retrieves the target of this edge. This is protected, for use by
     * subclasses only (e.g. for implementing toString).
     *
     * @return target of this edge
     */
    V* getTarget()
    {
        return this->target;
    }

public:
    string toString()
    {
    	stringstream sb;
   		sb << "(" << this->source << " : " << this->target << ")";
   		return sb.str();
    }
};

#endif /* DEFAULTEDGE_H_ */
