#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 10

// 그래프의 인접 리스트 구조체 정의
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

void initializeGraph(Graph* graph);      // 그래프 초기화 함수
Node* createNode(int v);                 // 새로운 노드 생성 함수
void insertVertex(Graph* graph);         // 정점 추가 함수
void insertEdge(Graph* graph, int src, int dest); // 간선 추가 함수
void DFS(Graph* graph, int vertex);      // DFS 구현 함수
void BFS(Graph* graph, int startVertex); // BFS 구현 함수
void printGraph(Graph* graph);           // 그래프 출력 함수
void freeGraph(Graph* graph);            // 그래프 메모리 해제 함수

int main() {
    char command;
    int src, dest;
    Graph graph;

    initializeGraph(&graph);

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Graph Searches                               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize  Graph    = z                                       \n");
        printf(" Insert Vertex        = v       Insert Edge            = e      \n");
        printf(" Depth First Search   = d       Breath First Search    = b      \n");
        printf(" Print Graph          = p       Quit                   = q      \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
            case 'z': case 'Z':
                initializeGraph(&graph);
                break;
            case 'q': case 'Q':
                freeGraph(&graph);
                break;
            case 'v': case 'V':
                insertVertex(&graph);
                break;
            case 'e': case 'E':
                printf("Enter source and destination vertex: ");
                scanf("%d %d", &src, &dest);
                insertEdge(&graph, src, dest);
                break;
            case 'd': case 'D':
                for(int i = 0; i < MAX_VERTICES; i++)
                    graph.visited[i] = 0;
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &src);
                DFS(&graph, src);
                break;
            case 'b': case 'B':
                for(int i = 0; i < MAX_VERTICES; i++)
                    graph.visited[i] = 0;
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &src);
                BFS(&graph, src);
                break;
            case 'p': case 'P':
                printGraph(&graph);
                break;
            default:
                printf("\n       >>>>>   Invalid Command!   <<<<<     \n");
                break;
        }
    } while(command != 'q' && command != 'Q');

    return 0;
}

// 그래프 초기화 함수
void initializeGraph(Graph* graph) {
    graph->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
}

// 새로운 노드 생성 함수
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 정점 추가 함수
void insertVertex(Graph* graph) {
    if (graph->numVertices >= MAX_VERTICES) {
        printf("Graph: Cannot insert more than %d vertices.\n", MAX_VERTICES);
        return;
    }
    graph->numVertices++;
}

// 간선 추가 함수
void insertEdge(Graph* graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Graph: Vertex number out of bounds.\n");
        return;
    }
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// DFS 구현 함수
void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// BFS 구현 함수
void BFS(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear] = startVertex;
    rear++;

    while (front < rear) {
        int currentVertex = queue[front];
        printf("Visited %d\n", currentVertex);
        front++;

        temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                queue[rear] = adjVertex;
                rear++;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// 그래프 출력 함수
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("\n Vertex %d\n: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// 그래프 메모리 해제 함수
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
}
