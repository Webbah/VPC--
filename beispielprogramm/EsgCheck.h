/**************************************************
	INCOMPLETE!
**************************************************/

#ifndef ESGCHECK_H_
#define ESGCHECK_H_

#include <set>
#include <DirectedGraph.h>

/**
 * @author: Manuel Webersen
 * @since: 2011-07-14
 */
template <class V, class E, class G>
class EsgCheck {
public:
	static const int RESULT_ERROR = -1;
	static const int RESULT_VALID = 0;
	static const int RESULT_MULTIPLE_STARTNODES = 1;
	static const int RESULT_MULTIPLE_ENDNODES = 2;
	static const int RESULT_NO_STARTNODE = 3;
	static const int RESULT_NO_ENDNODE = 4;
	static const int RESULT_UNREACHABLE_NODES = 5;

	set<V*>* visited;
	G* graph;

	EsgCheck(G* graphP) {
		graph = graphP;
		visited = new set<V*>();
	}

	int isESG()
	{
		int result = RESULT_ERROR;
		V* startNode = NULL;
		V* endNode = NULL;
		const set<V*>* vs = graph->vertexSet();

		visited->clear();

		// find start- and end-nodes
		typename set<V*>::iterator it;
		for (it = vs->begin(); it != vs->end(); ++it) {
			V* node = *it;

			if (graph->inDegreeOf(node) == 0) {
				// start node candidate
				if (startNode == NULL) {
					startNode = node;
				} else {
					result = RESULT_MULTIPLE_STARTNODES;
					break;
				}
			}
			if (graph->outDegreeOf(node) == 0) {
				// end node candidate
				if (endNode == NULL) {
					endNode = node;
				} else {
					result = RESULT_MULTIPLE_ENDNODES;
					break;
				}
			}
		}

		if (startNode == NULL) {
			result = RESULT_NO_STARTNODE;
		} else if (endNode == NULL) {
			result = RESULT_NO_ENDNODE;
		} else {

			// visit every node
			checkNode(startNode);
		}

		if (visited->size() != vs->size()) {
			result = RESULT_UNREACHABLE_NODES;
		} else {
			result = RESULT_VALID;
		}

		return result;
	}

	void checkNode(V* node)
	{
		set<E*>* edges = graph->outgoingEdgesOf(node);
		typename set<E*>::iterator it;

		visited->insert(node);
		cout << " #" << edges->size() << "# ";
		for (it = edges->begin(); it != edges->end(); ++it) {
			E* edge = *it;
			V* subNode = edge->target;
			checkNode(subNode);
		}
	}
};

#endif /* ESGCHECK_H_ */
