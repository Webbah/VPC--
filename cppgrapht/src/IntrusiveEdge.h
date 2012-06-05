#ifndef INTRUSIVEEDGE_H_
#define INTRUSIVEEDGE_H_

/**
 * IntrusiveEdge encapsulates the internals for the default edge implementation.
 * It is not intended to be referenced directly (which is why it's not public);
 * use DefaultEdge for that.
 *
 * @author Manuel Webersen <webem@mail.upb.de>
 * @since 2011-06-11
 */
template <class V>
class IntrusiveEdge
{
public:
    V* source;
    V* target;
};

#endif /* INTRUSIVEEDGE_H_ */
