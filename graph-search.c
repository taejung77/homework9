#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 10 // 최대 정점 개수

// 그래프의 인접 리스트 노드 구조체 정의
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 그래프 구조체 정의
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

    // 그래프 초기화
    initializeGraph(&graph);

    do {
        // 메뉴 출력
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Graph Searches                               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize  Graph    = z                                       \n");
        printf(" Insert Vertex        = v       Insert Edge            = e      \n");
        printf(" Depth First Search   = d       Breath First Search    = b      \n");
        printf(" Print Graph          = p       Quit                   = q      \n");
        printf("----------------------------------------------------------------\n");

        // 명령어 입력
        printf("Command = ");
        scanf(" %c", &command);

        // 명령어에 따라 함수 호출
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
                if(scanf("%d %d", &src, &dest) != 2) {
                    printf("Invalid input.\n");
                    break;
                }
                insertEdge(&graph, src, dest);
                break;
            case 'd': case 'D':
                for(int i = 0; i < MAX_VERTICES; i++)
                    graph.visited[i] = 0;
                printf("Enter starting vertex for DFS: ");
                if(scanf("%d", &src) != 1 || src >= graph.numVertices) {
                    printf("Invalid vertex number.\n");
                    break;
                }
                DFS(&graph, src);
                break;
            case 'b': case 'B':
                for(int i = 0; i < MAX_VERTICES; i++)
                    graph.visited[i] = 0;
                printf("Enter starting vertex for BFS: ");
                if(scanf("%d", &src) != 1 || src >= graph.numVertices) {
                    printf("Invalid vertex number.\n");
                    break;
                }
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

void initializeGraph(Graph* graph) {
    graph->numVertices = 0;  // 초기 정점 개수는 0
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;  // 인접 리스트 초기화
        graph->visited[i] = 0;      // 방문 배열 초기화
    }
}

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node)); // 노드 메모리 할당
    if (newNode == NULL) {
        printf("Memory allocation error.\n");
        exit(1); // 메모리 할당 실패 시 프로그램 종료
    }
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void insertVertex(Graph* graph) {
    if (graph->numVertices >= MAX_VERTICES) {
        printf("Graph: Cannot insert more than %d vertices.\n", MAX_VERTICES);
        return;
    }
    graph->numVertices++;  // 정점 개수 증가
}

void insertEdge(Graph* graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Graph: Vertex number out of bounds.\n");
        return;
    }
    // src -> dest 간선 추가
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // dest -> src 간선 추가 (무향 그래프)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1; // 현재 정점 방문 표시
    printf("Visited %d \n", vertex);

    // 인접 정점 방문
    while (temp != NULL) {
        int connectedVertex = temp->vertex; 

        if (graph->visited[connectedVertex] == 0) { // 방문하지 않은 정점이면 DFS 호출
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    graph->visited[startVertex] = 1; // 시작 정점 방문 표시
    queue[rear] = startVertex;       // 큐에 시작 정점 추가
    rear++;

    while (front < rear) { // 큐가 비어있지 않은 동안 반복
        int currentVertex = queue[front]; 
        printf("Visited %d\n", currentVertex);
        front++;

        temp = graph->adjLists[currentVertex]; // 현재 정점의 인접 정점 탐색

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) { // 방문하지 않은 정점이면 큐에 추가
                queue[rear] = adjVertex;
                rear++;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("\n Vertex %d\n: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");  // 인접 리스트의 끝을 표시
    }
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
        graph->adjLists[i] = NULL; // 인접 리스트를 NULL로 설정
    }
    printf("Graph memory freed.\n");
}
