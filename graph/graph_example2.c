// Function to create an adjacency list from specified edges
struct Graph* createGraph(struct Edge edges[], int n)
{
	unsigned i;

	// allocate memory for graph data structure
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

	// initialize head pointer for all vertices
	for (i = 0; i < N; i++)
		graph->head[i] = NULL;

	// add edges to the directed graph one by one
	for (i = 0; i < n; i++)
	{
		// get source and destination vertex
		int src = edges[i].src;
		int dest = edges[i].dest;

		// 1. allocate new node of Adjacency List from src to dest

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;

		// point new node to current head
		newNode->next = graph->head[src];

		// point head pointer to new node
		graph->head[src] = newNode;

		// 2. allocate new node of Adjacency List from dest to src

		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = src;

		// point new node to current head
		newNode->next = graph->head[dest];
	
		// change head pointer to point to the new node
		graph->head[dest] = newNode;
		
	}

	return graph;
}
