#ifndef ABSTRACTBASEGRAPH_H_
#define ABSTRACTBASEGRAPH_H_

#include <map>
#include <set>
#include <stdexcept>
#include <typeinfo>
#include <AbstractGraph.h>
#include <EdgeFactory.h>
#include <EdgeSetFactory.h>
#include <Graphs.h>
#include <IntrusiveEdge.h>
#include <UndirectedGraph.h>
#include <WeightedGraph.h>

/**
 * The most general implementation of the {@link Graph} interface.
 * Its subclasses add various restrictions to get more specific graphs. The
 * decision whether it is directed or undirected is decided at construction time
 * and cannot be later modified (see constructor for details).
 *
 * <p>This graph implementation guarantees deterministic vertex and edge set
 * ordering (via {@link map}).</p>
 *
 * @author ManueL Webersen <webem@mail.upb.de>
 * @since 2011-06-11
 */
template <class V, class E>
class AbstractBaseGraph : public AbstractGraph<V, E>
{
public:
	EdgeFactory<V, E>* edgeFactory;
	EdgeSetFactory<V, E>* edgeSetFactory;
	map<E*, IntrusiveEdge<V>* >* edgeMap;
	set<E*>* unmodifiableEdgeSet;
	set<V*>* unmodifiableVertexSet;
	bool allowingMultipleEdges;

	/**
     * .
     */
	class Specifics
    {
	public:
		AbstractBaseGraph<V, E>* abg;

		Specifics(AbstractBaseGraph<V, E>* abgPointer)
		{
			abg = abgPointer;
		}

        virtual void addVertex(V* vertex) = 0;
        virtual set<V*>* getVertexSet() = 0;

        /**
         * .
         *
         * @param sourceVertex
         * @param targetVertex
         *
         * @return
         */
        virtual set<E*>* getAllEdges(V* sourceVertex, V* targetVertex) = 0;

        /**
         * .
         *
         * @param sourceVertex
         * @param targetVertex
         *
         * @return
         */
        virtual E* getEdge(V* sourceVertex, V* targetVertex) = 0;

        /**
         * Adds the specified edge to the edge containers of its source and
         * target vertices.
         *
         * @param e
         */
        virtual void addEdgeToTouchingVertices(E* e) = 0;

        /**
         * .
         *
         * @param vertex
         *
         * @return
         */
        virtual int degreeOf(V* vertex) = 0;

        /**
         * .
         *
         * @param vertex
         *
         * @return
         */
        virtual set<E*>* edgesOf(V* vertex) = 0;

        /**
         * .
         *
         * @param vertex
         *
         * @return
         */
        virtual int inDegreeOf(V* vertex) = 0;

        /**
         * .
         *
         * @param vertex
         *
         * @return
         */
        virtual set<E*>* incomingEdgesOf(V* vertex) = 0;

        /**
         * .
         *
         * @param vertex
         *
         * @return
         */
        virtual int outDegreeOf(V* vertex) = 0;

        /**
         * .
         *
         * @param vertex
         *
         * @return
         */
        virtual set<E*>* outgoingEdgesOf(V* vertex) = 0;

        /**
         * Removes the specified edge from the edge containers of its source and
         * target vertices.
         *
         * @param e
         */
        virtual void removeEdgeFromTouchingVertices(E* e) = 0;
	};

	Specifics* specifics;

	template <class VV, class EE>
	class ArrayListFactory : public EdgeSetFactory<VV, EE>
	{
	public:
        /**
         * @see EdgeSetFactory.createEdgeSet
         */
        set<EE*>* createEdgeSet(VV* vertex)
        {
            return new set<EE*>();
        }
    };

	/**
	 * A container for vertex edges.
	 */
	template <class VV, class EE>
	class DirectedEdgeContainer
	{
	public:
		set<EE*>* incoming;
		set<EE*>* outgoing;
		const set<EE*>* unmodifiableIncoming;
		const set<EE*>* unmodifiableOutgoing;

		DirectedEdgeContainer(EdgeSetFactory<VV, EE>* edgeSetFactory,
			VV* vertex)
		{
			incoming = edgeSetFactory->createEdgeSet(vertex);
			outgoing = edgeSetFactory->createEdgeSet(vertex);
			unmodifiableIncoming = NULL;
			unmodifiableOutgoing = NULL;
		}

		/**
		 * A lazy build of unmodifiable incoming edge set.
		 *
		 * @return
		 */
		const set<EE*>* getUnmodifiableIncomingEdges()
		{
			if (unmodifiableIncoming == NULL) {
				unmodifiableIncoming = (const set<EE*>*)incoming;
			}

			return unmodifiableIncoming;
		}

		/**
		 * A lazy build of unmodifiable outgoing edge set.
		 *
		 * @return
		 */
		const set<EE*>* getUnmodifiableOutgoingEdges()
		{
			if (unmodifiableOutgoing == NULL) {
				unmodifiableOutgoing = (const set<EE*>*)outgoing;
			}

			return unmodifiableOutgoing;
		}

		/**
		 * .
		 *
		 * @param e
		 */
		void addIncomingEdge(EE* e)
		{
			incoming->insert(e);
		}

		/**
		 * .
		 *
		 * @param e
		 */
		void addOutgoingEdge(EE* e)
		{
			outgoing->insert(e);
		}

		/**
		 * .
		 *
		 * @param e
		 */
		void removeIncomingEdge(EE* e)
		{
			incoming->erase(e);
		}

		/**
		 * .
		 *
		 * @param e
		 */
		void removeOutgoingEdge(EE* e)
		{
			outgoing->erase(e);
		}
	};

	/**
	 * .
	 */
	class DirectedSpecifics : public Specifics
	{
	public:
		map<V*, DirectedEdgeContainer<V, E>* >* vertexMapDirected;

		DirectedSpecifics(AbstractBaseGraph<V, E>* abgPointer) : Specifics(abgPointer)
		{
			vertexMapDirected = new map<V*, DirectedEdgeContainer<V, E>* >();
		}

		void addVertex(V* v)
		{
			// add with a lazy edge container entry
			vertexMapDirected->insert(pair<V*, DirectedEdgeContainer<V, E>* >(v, NULL));
		}

		set<V*>* getVertexSet()
		{
			set<V*>* vset = new set<V*>();

			typename map<V*, DirectedEdgeContainer<V, E>* >::iterator iter;
			for (iter = vertexMapDirected->begin(); iter != vertexMapDirected->end(); ++iter) {
				vset->insert(iter->first);
			}

			return vset;
		}

		/**
		 * @see Graph#getAllEdges(Object, Object)
		 */
		set<E*>* getAllEdges(V* sourceVertex, V* targetVertex)
		{
			set<E*>* edges = NULL;

			if (this->abg->containsVertex(sourceVertex)
				&& this->abg->containsVertex(targetVertex))
			{
				edges = new set<E*>();

				DirectedEdgeContainer<V, E>* ec = getEdgeContainer(sourceVertex);

				typename set<E*>::iterator iter;

				for (iter = ec->outgoing->begin(); iter != ec->outgoing->end(); ++iter) {
					if (this->abg->getEdgeTarget(*iter) == targetVertex) {
						edges->insert(*iter);
					}
				}
			}

			return edges;
		}

		/**
		 * @see Graph#getEdge(Object, Object)
		 */
		E* getEdge(V* sourceVertex, V* targetVertex)
		{
			if (this->abg->containsVertex(sourceVertex)
				&& this->abg->containsVertex(targetVertex))
			{
				DirectedEdgeContainer<V, E>* ec = getEdgeContainer(sourceVertex);

				typename set<E*>::iterator iter;

				for (iter = ec->outgoing->begin(); iter!=ec->outgoing->end(); ++iter) {
					if (this->abg->getEdgeTarget((E*)*iter) == targetVertex) {
						return *iter;
					}
				}
			}

			return NULL;
		}

		/**
		 * @see AbstractBaseGraph#addEdgeToTouchingVertices(Edge)
		 */
		void addEdgeToTouchingVertices(E* e)
		{
			V* source = this->abg->getEdgeSource(e);
			V* target = this->abg->getEdgeTarget(e);

			getEdgeContainer(source)->addOutgoingEdge(e);
			getEdgeContainer(target)->addIncomingEdge(e);
		}

		/**
		 * @see UndirectedGraph#degreeOf(Object)
		 */
		int degreeOf(V* vertex)
		{
			throw new logic_error("No such operation in a directed graph");
		}

		/**
		 * @see Graph#edgesOf(Object)
		 */
		set<E*>* edgesOf(V* vertex)
		{
			set<E*>* inAndOut = getEdgeContainer(vertex)->incoming;

			typename set<E*>::iterator iter;
			for (iter = getEdgeContainer(vertex)->outgoing->begin(); iter != getEdgeContainer(vertex)->outgoing->end(); ++iter) {
				inAndOut->insert(*iter);
			}

			// we have two copies for each self-loop - remove one of them.
			if (this->abg->allowingLoops) {
				set<E*>* loops = getAllEdges(vertex, vertex);

				typename set<E*>::iterator iter2;
				for (iter2 = inAndOut->begin(); iter2 != inAndOut->end(); iter2++) {
				//for (unsigned int i = 0; i < inAndOut->size();) {
					//E* e = inAndOut->find(i);
					E* e = *iter2;

					if (loops->count(e) > 0) {
						inAndOut->erase(iter2);
						loops->erase(e); // so we remove it only once
					}
				}
			}

			return inAndOut;
		}

		/**
		 * @see DirectedGraph#inDegree(Object)
		 */
		int inDegreeOf(V* vertex)
		{
			return getEdgeContainer(vertex)->incoming->size();
		}

		/**
		 * @see DirectedGraph#incomingEdges(Object)
		 */
		set<E*>* incomingEdgesOf(V* vertex)
		{
			return (set<E*>*)getEdgeContainer(vertex)->getUnmodifiableIncomingEdges();
		}

		/**
		 * @see DirectedGraph#outDegree(Object)
		 */
		int outDegreeOf(V* vertex)
		{
			return getEdgeContainer(vertex)->outgoing->size();
		}

		/**
		 * @see DirectedGraph#outgoingEdges(Object)
		 */
		set<E*>* outgoingEdgesOf(V* vertex)
		{
			return (set<E*>*)getEdgeContainer(vertex)->getUnmodifiableOutgoingEdges();
		}

		/**
		 * @see AbstractBaseGraph#removeEdgeFromTouchingVertices(Edge)
		 */
		void removeEdgeFromTouchingVertices(E* e)
		{
			V* source = this->abg->getEdgeSource(e);
			V* target = this->abg->getEdgeTarget(e);

			getEdgeContainer(source)->removeOutgoingEdge(e);
			getEdgeContainer(target)->removeIncomingEdge(e);
		}

		/**
		 * A lazy build of edge container for specified vertex.
		 *
		 * @param vertex a vertex in this graph.
		 *
		 * @return EdgeContainer
		 */
		DirectedEdgeContainer<V, E>* getEdgeContainer(V* vertex)
		{
			this->abg->assertVertexExist(vertex);

			DirectedEdgeContainer<V, E>* ec = vertexMapDirected->find(vertex)->second;

			if (ec == NULL) {
				ec = new DirectedEdgeContainer<V, E>(
					this->abg->edgeSetFactory,
					vertex);
				vertexMapDirected->insert(pair<V*, DirectedEdgeContainer<V, E>* >(vertex, ec));
			}

			return ec;
		}
	};

	/**
	 * A container of for vertex edges.
	 */
	template <class VV, class EE>
	class UndirectedEdgeContainer
	{
	public:
		set<EE*>* vertexEdges;
		const set<EE*>* unmodifiableVertexEdges;

		UndirectedEdgeContainer(
			EdgeSetFactory<VV, EE>* edgeSetFactory,
			VV* vertex)
		{
			vertexEdges = edgeSetFactory->createEdgeSet(vertex);
			unmodifiableVertexEdges = NULL;
		}

		/**
		 * A lazy build of unmodifiable list of vertex edges
		 *
		 * @return
		 */
		const set<EE*>* getUnmodifiableVertexEdges()
		{
			if (unmodifiableVertexEdges == NULL) {
				unmodifiableVertexEdges = (const set<EE*>*)vertexEdges;
			}

			return unmodifiableVertexEdges;
		}

		/**
		 * .
		 *
		 * @param e
		 */
		void addEdge(EE* e)
		{
			vertexEdges->insert(e);
		}

		/**
		 * .
		 *
		 * @return
		 */
		int edgeCount()
		{
			return vertexEdges->size();
		}

		/**
		 * .
		 *
		 * @param e
		 */
		void removeEdge(EE* e)
		{
			vertexEdges->erase(e);
		}
	};

	/**
	 * .
	 */
	class UndirectedSpecifics : public Specifics
	{
	public:
		map<V*, UndirectedEdgeContainer<V, E>* >* vertexMapUndirected;

		UndirectedSpecifics(AbstractBaseGraph<V, E>* abgPointer) : Specifics(abgPointer)
		{
			vertexMapUndirected = new map<V*, UndirectedEdgeContainer<V, E>* >();
		}

		void addVertex(V* v)
		{
			// add with a lazy edge container entry
			vertexMapUndirected->insert(pair<V*, UndirectedEdgeContainer<V, E>* >(v, NULL));
		}

		set<V*>* getVertexSet()
		{
			set<V*>* vset = new set<V*>();

			typename map<V*, UndirectedEdgeContainer<V, E>* >::iterator iter;
			for (iter = vertexMapUndirected->begin(); iter != vertexMapUndirected->end(); ++iter) {
				vset->insert(iter->first);
			}

			return vset;
		}

		/**
		 * @see Graph#getAllEdges(Object, Object)
		 */
		set<E*>* getAllEdges(V* sourceVertex, V* targetVertex)
		{
			set<E*>* edges = NULL;

			if (this->abg->containsVertex(sourceVertex)
				&& this->abg->containsVertex(targetVertex))
			{
				edges = new set<E*>();

				typename set<E*>::iterator iter;

				for (iter = getEdgeContainer(sourceVertex)->vertexEdges->begin(); iter != getEdgeContainer(sourceVertex)->vertexEdges->end(); ++iter) {
					bool equalStraight =
						sourceVertex == this->abg->getEdgeSource((E*)*iter)
						&& targetVertex == this->abg->getEdgeTarget((E*)*iter);

					bool equalInverted =
						sourceVertex == this->abg->getEdgeTarget((E*)*iter)
						&& targetVertex == this->abg->getEdgeSource((E*)*iter);

					if (equalStraight || equalInverted) {
						edges->insert(*iter);
					}
				}
			}

			return edges;
		}

		/**
		 * @see Graph#getEdge(Object, Object)
		 */
		E* getEdge(V* sourceVertex, V* targetVertex)
		{
			if (this->abg->containsVertex(sourceVertex)
				&& this->abg->containsVertex(targetVertex))
			{
				typename set<E*>::iterator iter;

				for (iter = getEdgeContainer(sourceVertex)->vertexEdges->begin(); iter != getEdgeContainer(sourceVertex)->vertexEdges->end(); ++iter) {
					bool equalStraight =
						sourceVertex == this->abg->getEdgeSource(*iter)
						&& targetVertex == this->abg->getEdgeTarget(*iter);

					bool equalInverted =
						sourceVertex == this->abg->getEdgeTarget(*iter)
						&& targetVertex == this->abg->getEdgeSource(*iter);

					if (equalStraight || equalInverted) {
						return *iter;
					}
				}
			}

			return NULL;
		}

		/**
		 * @see AbstractBaseGraph#addEdgeToTouchingVertices(Edge)
		 */
		void addEdgeToTouchingVertices(E* e)
		{
			V* source = this->abg->getEdgeSource(e);
			V* target = this->abg->getEdgeTarget(e);

			getEdgeContainer(source)->addEdge(e);

			if (source != target) {
				getEdgeContainer(target)->addEdge(e);
			}
		}

		/**
		 * @see UndirectedGraph#degreeOf(V*)
		 */
		int degreeOf(V* vertex)
		{
			if (this->abg->allowingLoops) { // then we must count, and add loops twice

				int degree = 0;
				set<E*>* edges = getEdgeContainer(vertex)->vertexEdges;

				typename set<E*>::iterator iter;

				for (iter = edges->begin(); iter != edges->end(); ++iter) {
					if (this->abg->getEdgeSource((E*)*iter) == this->abg->getEdgeTarget((E*)*iter)) {
						degree += 2;
					} else {
						degree += 1;
					}
				}

				return degree;
			} else {
				return getEdgeContainer(vertex)->edgeCount();
			}
		}

		/**
		 * @see Graph#edgesOf(V*)
		 */
		set<E*>* edgesOf(V* vertex)
		{
			return (set<E*>*)getEdgeContainer(vertex)->getUnmodifiableVertexEdges();
		}

		/**
		 * @see DirectedGraph#inDegreeOf(Object)
		 */
		int inDegreeOf(V* vertex)
		{
			throw new logic_error("No such operation in an undirected graph");
		}

		/**
		 * @see DirectedGraph#incomingEdgesOf(Object)
		 */
		set<E*>* incomingEdgesOf(V* vertex)
		{
			throw new logic_error("No such operation in an undirected graph");
		}

		/**
		 * @see DirectedGraph#outDegreeOf(Object)
		 */
		int outDegreeOf(V* vertex)
		{
			throw new logic_error("No such operation in an undirected graph");
		}

		/**
		 * @see DirectedGraph#outgoingEdgesOf(Object)
		 */
		set<E*>* outgoingEdgesOf(V* vertex)
		{
			throw new logic_error("No such operation in an undirected graph");
		}

		/**
		 * @see AbstractBaseGraph#removeEdgeFromTouchingVertices(Edge)
		 */
		void removeEdgeFromTouchingVertices(E* e)
		{
			V* source = this->abg->getEdgeSource(e);
			V* target = this->abg->getEdgeTarget(e);

			getEdgeContainer(source)->removeEdge(e);

			if (source != target) {
				getEdgeContainer(target)->removeEdge(e);
			}
		}

		/**
		 * A lazy build of edge container for specified vertex.
		 *
		 * @param vertex a vertex in this graph.
		 *
		 * @return EdgeContainer
		 */
		UndirectedEdgeContainer<V, E>* getEdgeContainer(V* vertex)
		{
			this->abg->assertVertexExist(vertex);

			UndirectedEdgeContainer<V, E>* ec = vertexMapUndirected->find(vertex)->second;

			if (ec == NULL) {
				ec = new UndirectedEdgeContainer<V, E>(
					this->abg->edgeSetFactory,
					vertex);
				vertexMapUndirected->insert(pair<V*, UndirectedEdgeContainer<V, E>* >(vertex, ec));
			}

			return ec;
		}
	};

public:
	bool allowingLoops;

	/**
	 * Construct a new pseudograph. The pseudograph can either be directed or
	 * undirected, depending on the specified edge factory.
	 *
	 * @param ef the edge factory of the new graph.
	 * @param allowMultipleEdges whether to allow multiple edges or not.
	 * @param allowLoops whether to allow edges that are self-loops or not.
	 *
	 * @throws invalid_argument if the specified edge factory is <code>
	 * NULL</code>.
	 */
	AbstractBaseGraph(
		EdgeFactory<V, E>* ef,
		bool allowMultipleEdges,
		bool allowLoops,
		bool directed)
	{
		if (ef == NULL) {
			throw new invalid_argument("Invalid argument given for EdgeFactory: NULL");
		}

		edgeMap = new map<E*, IntrusiveEdge<V>* >();

		edgeFactory = ef;

		allowingLoops = allowLoops;
		allowingMultipleEdges = allowMultipleEdges;

		unmodifiableEdgeSet = NULL;
		unmodifiableVertexSet = NULL;

		//specifics = createSpecifics();
		if (directed) {
			specifics = new DirectedSpecifics(this);
		} else {
			specifics = new UndirectedSpecifics(this);
		}

		this->edgeSetFactory = new ArrayListFactory<V, E>();
	}

	/**
	 * @see Graph#getAllEdges(Object, Object)
	 */
	set<E*>* getAllEdges(V* sourceVertex, V* targetVertex)
	{
		return specifics->getAllEdges(sourceVertex, targetVertex);
	}

	/**
	 * Returns <code>true</code> if and only if self-loops are allowed in this
	 * graph. A self loop is an edge that its source and target vertices are the
	 * same.
	 *
	 * @return <code>true</code> if and only if graph loops are allowed.
	 */
	bool isAllowingLoops()
	{
		return allowingLoops;
	}

	/**
	 * Returns <code>true</code> if and only if multiple edges are allowed in
	 * this graph. The meaning of multiple edges is that there can be many edges
	 * going from vertex v1 to vertex v2.
	 *
	 * @return <code>true</code> if and only if multiple edges are allowed.
	 */
	bool isAllowingMultipleEdges()
	{
		return allowingMultipleEdges;
	}

	/**
	 * @see Graph#getEdge(Object, Object)
	 */
	E* getEdge(V* sourceVertex, V* targetVertex)
	{
		return specifics->getEdge(sourceVertex, targetVertex);
	}

	/**
	 * @see Graph#getEdgeFactory()
	 */
	EdgeFactory<V, E>* getEdgeFactory()
	{
		return edgeFactory;
	}

	/**
	 * Set the {@link EdgeSetFactory} to use for this graph. Initially, a graph
	 * is created with a default implementation which always supplies a {@link
	 * set}.
	 *
	 * @param edgeSetFactory factory to use for subsequently created edge sets
	 * (this call has no effect on existing edge sets)
	 */
	void setEdgeSetFactory(EdgeSetFactory<V, E>* edgeSetFactory)
	{
		this->edgeSetFactory = edgeSetFactory;
	}

	/**
	 * @see Graph#addEdge(Object, Object)
	 */
	E* addEdge(V* sourceVertex, V* targetVertex)
	{
		assertVertexExist(sourceVertex);
		assertVertexExist(targetVertex);

		if (!allowingMultipleEdges
			&& containsEdgeV(sourceVertex, targetVertex))
		{
			return NULL;
		}

		if (!allowingLoops && sourceVertex == targetVertex) {
			throw new invalid_argument("Loops not allowed");
		}

		E* e = edgeFactory->createEdge(sourceVertex, targetVertex);

		if (containsEdge(e)) { // this restriction should stay!
			return NULL;
		} else {
			IntrusiveEdge<V>* intrusiveEdge =
				createIntrusiveEdge(e, sourceVertex, targetVertex);

			edgeMap->insert(pair<E*, IntrusiveEdge<V>* >(e, intrusiveEdge));
			specifics->addEdgeToTouchingVertices(e);

			return e;
		}
	}

	/**
	 * @see Graph#addEdge(Object, Object, Object)
	 */
	bool addEdge(V* sourceVertex, V* targetVertex, E* e)
	{
		if (e == NULL) {
			throw new invalid_argument("NULL-pointer given for e");
		} else if (containsEdge(e)) {
			return false;
		}

		assertVertexExist(sourceVertex);
		assertVertexExist(targetVertex);

		if (!allowingMultipleEdges
			&& containsEdgeV(sourceVertex, targetVertex))
		{
			return false;
		}

		if (!allowingLoops && sourceVertex == targetVertex) {
			throw new invalid_argument("Loops not allowed");
		}

		IntrusiveEdge<V>* intrusiveEdge =
			createIntrusiveEdge(e, sourceVertex, targetVertex);

		edgeMap->insert(pair<E*, IntrusiveEdge<V>* >(e, intrusiveEdge));
		specifics->addEdgeToTouchingVertices(e);

		return true;
	}

	IntrusiveEdge<V>* createIntrusiveEdge(
		E* e,
		V* sourceVertex,
		V* targetVertex)
	{
		IntrusiveEdge<V>* intrusiveEdge;
		if (typeid(e) == typeid(IntrusiveEdge<V>*)) {
			intrusiveEdge = (IntrusiveEdge<V>*) e;
		} else {
			intrusiveEdge = new IntrusiveEdge<V>();
		}
		intrusiveEdge->source = sourceVertex;
		intrusiveEdge->target = targetVertex;
		return intrusiveEdge;
	}

	/**
	 * @see Graph#addVertex(Object)
	 */
	bool addVertex(V* v)
	{
		if (v == NULL) {
			throw new invalid_argument("NULL-pointer given for v");
		} else  if (containsVertex(v)) {
			return false;
		} else {
			specifics->addVertex(v);

			return true;
}
	}

	/**
	 * @see Graph#getEdgeSource(Object)
	 */
	V* getEdgeSource(E* e)
	{
		return (V*)getIntrusiveEdge(e)->source;
	}

	/**
	 * @see Graph#getEdgeTarget(Object)
	 */
	V* getEdgeTarget(E* e)
	{
		return (V*)getIntrusiveEdge(e)->target;
	}

	IntrusiveEdge<V>* getIntrusiveEdge(E* e)
	{
		if (typeid(e) == typeid(IntrusiveEdge<V>*)) {
			return (IntrusiveEdge<V>*) e;
		}

		return edgeMap->find(e)->second;
	}

	/**
	 * Returns a shallow copy of this graph instance. Neither edges nor vertices
	 * are cloned.
	 *
	 * @return a shallow copy of this set.
	 */
	AbstractBaseGraph(const AbstractBaseGraph& source)
	{
		//AbstractBaseGraph<V*, E*>* newGraph = new AbstractBaseGraph<V*, E*>(*this);

		this->edgeMap = new map<E*, IntrusiveEdge<V>* >();

		this->edgeFactory = source->edgeFactory;
		this->unmodifiableEdgeSet = NULL;
		this->unmodifiableVertexSet = NULL;

		// NOTE:  it's important for this to happen in an object
		// method so that the new inner class instance gets associated with
		// the right outer class instance
		this->specifics = this->createSpecifics();

		Graphs::addGraph<V, E>(this, source);

		//return (void*)newGraph;
	}

	/**
	 * @see Graph#containsEdge(Object)
	 */
	bool containsEdge(E* e)
	{
		return edgeMap->count(e) == 1;
	}

	/**
	 * @see Graph#containsVertex(Object)
	 */
	bool containsVertex(V* v)
	{
		return specifics->getVertexSet()->count(v) == 1;
	}

	/**
	 * @see UndirectedGraph#degreeOf(Object)
	 */
	int degreeOf(V* vertex)
	{
		return specifics->degreeOf(vertex);
	}

	/**
	 * @see Graph#edgeSet()
	 */
	const set<E*>* edgeSet()
	{
		if (unmodifiableEdgeSet == NULL) {
			set<E*>* eset = new set<E*>();

			typename map<E*, IntrusiveEdge<V>* >::iterator iter;
			for (iter = edgeMap->begin(); iter != edgeMap->end(); ++iter) {
				eset->insert((E*)iter->second);
			}

			return eset;

			unmodifiableEdgeSet = eset;
		}

		return (const set<E*>*)unmodifiableEdgeSet;
	}

	/**
	 * @see Graph#edgesOf(Object)
	 */
	set<E*>* edgesOf(V* vertex)
	{
		return specifics->edgesOf(vertex);
	}

	/**
	 * @see DirectedGraph#inDegreeOf(Object)
	 */
	int inDegreeOf(V* vertex)
	{
		return specifics->inDegreeOf(vertex);
	}

	/**
	 * @see DirectedGraph#incomingEdgesOf(Object)
	 */
	set<E*>* incomingEdgesOf(V* vertex)
	{
		return specifics->incomingEdgesOf(vertex);
	}

	/**
	 * @see DirectedGraph#outDegreeOf(Object)
	 */
	int outDegreeOf(V* vertex)
	{
		return specifics->outDegreeOf(vertex);
	}

	/**
	 * @see DirectedGraph#outgoingEdgesOf(Object)
	 */
	set<E*>* outgoingEdgesOf(V* vertex)
	{
		return specifics->outgoingEdgesOf(vertex);
	}

	/**
	 * @see Graph#removeEdge(Object, Object)
	 */
	E* removeEdge(V* sourceVertex, V* targetVertex)
	{
		E* e = getEdge(sourceVertex, targetVertex);

		if (e != NULL) {
			specifics->removeEdgeFromTouchingVertices(e);
			edgeMap->erase(e);
		}

		return e;
	}

	/**
	 * @see Graph#removeEdge(Object)
	 */
	bool removeEdge(E* e)
	{
		if (containsEdge(e)) {
			specifics->removeEdgeFromTouchingVertices(e);
			edgeMap->erase(e);

			return true;
		} else {
			return false;
		}
	}

	/**
	 * @see Graph#removeVertex(Object)
	 */
	bool removeVertex(V* v)
	{
		if (containsVertex(v)) {
			set<E*>* touchingEdgesList = edgesOf(v);
			removeAllEdges(touchingEdgesList);

			specifics->getVertexSet()->erase(v); // remove the vertex itself

			return true;
		} else {
			return false;
		}
	}

	/**
	 * @see Graph#vertexSet()
	 */
	const set<V*>* vertexSet()
	{
		if (unmodifiableVertexSet == NULL) {
			unmodifiableVertexSet = (specifics->getVertexSet());
		}

		return (const set<V*>*)unmodifiableVertexSet;
	}

	/**
	 * @see Graph#getEdgeWeight(Object)
	 */
	double getEdgeWeight(E* e)
	{
		if (typeid(e) == typeid(DefaultWeightedEdge<V>*)) {
			return ((DefaultWeightedEdge<V>*) e)->getWeight();
		} else {
			return WeightedGraph<V, E>::DEFAULT_EDGE_WEIGHT;
		}
	}

	/**
	 * @see WeightedGraph#setEdgeWeight(Object, double)
	 */
	void setEdgeWeight(E* e, double weight)
	{
		if (typeid(e) != typeid(DefaultWeightedEdge<V>)) {
			throw new invalid_argument("Given edge is not a valid DefaultWeightedEdge");
		}
		((DefaultWeightedEdge<V>) e)->weight = weight;
	}

//	Specifics* createSpecifics()
//	{
//		if (typeid(this) == typeid(DirectedGraph<V, E>*)) {
//			return new DirectedSpecifics(this);
//		} else if (typeid(this) == typeid(UndirectedGraph<V, E>*)) {
//			return new UndirectedSpecifics(this);
//		} else {
//			//throw new invalid_argument("Must be instance of either DirectedGraph or UndirectedGraph");
//			cout << typeid(this).name();
//			return NULL;
//		}
//	}

	virtual void dummy() {}
};

#endif /* ABSTRACTBASEGRAPH_H_ */
