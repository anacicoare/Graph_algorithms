#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct SNode {
    int data;
    struct SNode* next;
} SNode_t;

typedef struct stack {
    SNode_t* top;
    SNode_t* len;
} stack_t;

//element to be queued for task 3
typedef struct element
{
    int index;
    int* visited;
} element_t;

typedef struct queue_node {

    element_t data;
    struct queue_node* next;
    struct queue_node* prev;

} queue_node;
typedef struct queue_struct {

    int len;
    struct queue_node* head;
    struct queue_node* tail;

} queue_struct;

int power(int n, int p)
{
    int i, ret = 1;
    for (i = 0; i < p; i++)
        ret = ret * n;
    return ret;
}

queue_node* init_queue_node(element_t node)
{

    queue_node* new_node = malloc(sizeof(queue_node));
    if (new_node == NULL)
        return NULL;

    new_node->data = node;
    new_node->prev = new_node->next = NULL;

    return new_node;
}

queue_struct* init_queue()
{

    queue_struct* new_queue = malloc(sizeof(queue_struct));

    if (new_queue == NULL)
        return NULL;

    new_queue->head = NULL;
    new_queue->tail = NULL;
    new_queue->len = 0;

    return new_queue;
}

void enqueue(queue_struct* queue, element_t data)
{

    queue_node* new = init_queue_node(data);

    if (queue->len == 0)
    {
        queue->head = new;
        queue->tail = new;
    }
    else
    {
        new->next = queue->head;
        queue->head->prev = new;
        queue->head = new;
    }
    (queue->len)++;
}

element_t dequeue(queue_struct* queue)
{
    element_t ret;

    queue_node* aux = queue->tail;

    if (queue->len == 1)
    {
        queue->tail = NULL;
        queue->head = NULL;
    }
    else
    {
        queue->tail = aux->prev;
        queue->tail->next = NULL;
    }
    (queue->len)--;

    ret = aux->data;

    free(aux);

    return ret;
}


SNode_t* initStackNode(int value) {
    SNode_t* newNode = malloc(sizeof(SNode_t));
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

stack_t* initStack() {
    stack_t* newStack = malloc(sizeof(stack_t));
    newStack->top = NULL;
    newStack->len = 0;

    return newStack;
}

void push(stack_t* stack, int data) {

    SNode_t* new_node = initStackNode(data);

    new_node->next = stack->top;
    stack->top = new_node;
    ++stack->len;
}

int pop(stack_t* stack) {
    SNode_t* aux = stack->top;
    int ret;

    if (stack->len == 0) {
        // Stiva e goala
        return -1;
    }

    // Salvez valoarea nodului
    ret = aux->data;

    // Elimin nodul din stiva
    stack->top = aux->next;
    --stack->len;

    free(aux);

    return ret;
}

int top(stack_t* stack) {
    if (stack->len == 0) {
        return -1;
    }
    return stack->top->data;
}

//computes minimum distance between a visited and unvisited node and returns the
//unvisited node's index
int minDistance(float* dist, int* sptSet, int nr_nodes)
{
    // Initialize min value
    float min = 1000000;
    int min_index = 0;

    for (int v = 0; v < nr_nodes; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

void dijkstra(float** map, int nr_nodes, int src, int dest, float* dist, int* sptSet, int** parents, int* index)
{
    int i;

    // init all distances as maximum and shortest path tree (visited nodes array)
    // as unvisited
    for (i = 0; i < nr_nodes; i++)
    {
        dist[i] = 1000000;
        sptSet[i] = 0;
    }

    //dist from source is always 0
    dist[src] = 0;

    for (int count = 0; count < nr_nodes - 1; count++)
    {
        //min distance unvisited node
        int u = minDistance(dist, sptSet, nr_nodes);

        //make node visited
        sptSet[u] = 1;

        for (int v = 0; v < nr_nodes; v++)
            if (!sptSet[v] && map[u][v] && map[u][v] != 1000000 && (dist[u] != 1000000) && (dist[u] + map[u][v] < dist[v]))
            {
                //update dist
                dist[v] = dist[u] + map[u][v];

                //one more element to the route
                (index[v]) = index[u] + 1;

                //remember route
                for (i = 0; i < index[u]; i++)
                    parents[v][i] = parents[u][i];

                parents[v][index[v] - 1] = u;

            }
    }

    // now we return to print the constructed distance route
}

void swap(int* a, int* b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

//used to create the deposits array
void break_line_in_deposits(int* deposits, int* nr_deposits)
{
    char whitespace, deposit;
    *nr_deposits = 0;

    scanf("%c", &whitespace); // '\n'
    whitespace = '1';
    while (whitespace != '\n')
    {
        scanf("%c", &deposit);
        scanf("%c", &whitespace);
        deposits[*nr_deposits] = deposit - '0';
        (*nr_deposits)++;
    }

}

void copy_arrays(int* arr1, int* arr2, int nr_nodes)
{
    int i;
    for (i = 0; i < nr_nodes; i++)
        arr1[i] = arr2[i];
}

int not_deposit(int node, int* deposits, int nr_deposits)
{
    int i;
    for (i = 0; i < nr_deposits; i++)
        if (node == deposits[i])
            return 0;
    return 1;
}

//init function used for tarjan
void reset_nodes(int* deg, int* low_link, int* index, int* in_stack, int nr_nodes)
{
    int i;
    for (i = 0; i < nr_nodes; i++)
    {
        index[i] = -1;
        deg[i] = 0;
        low_link[i] = -1;
        in_stack[i] = 0;
    }
}
int current_index = 0;
void tarjan(int src, int nr_nodes, int* index, int* low_link, int* in_stack, int* deg, float** adj, stack_t* stack, int start_deposit, int** tarjan_array, int* nr_lines, int* deposits, int nr_deposits)
{
    int i;

    index[src] = current_index;
    low_link[src] = current_index;
    current_index++;

    push(stack, src);
    in_stack[src] = 1;

    for (i = 0; i < nr_nodes; i++)
        if (adj[src][i] > 0 && i != start_deposit)
        {
            if (index[i] == -1) //if undefined then we recurse on it and define it
            {
                tarjan(i, nr_nodes, index, low_link, in_stack, deg, adj, stack, start_deposit, tarjan_array, nr_lines, deposits, nr_deposits);
                low_link[src] = min(low_link[src], low_link[i]);
            }
            else
            if (in_stack[i])
                low_link[src] = min(low_link[src], index[i]);
        }

    if (index[src] == low_link[src]) //if end of cycle
    {
        int n;
        int nr_elements = 0;

        int line_has_deposit = 0;
        n = pop(stack); //add stack to tarjan array
        while (n != -1)
        {
            if (1 - not_deposit(n, deposits, nr_deposits))
            {
                line_has_deposit = 1;
                break;
            }
            tarjan_array[*nr_lines][nr_elements] = n;
            nr_elements++;
            in_stack[n] = 0;

            if (n == src)
            {
                break;
            }
            n = pop(stack);
        }
        if (line_has_deposit == 0)
            (*nr_lines)++;
    }

}

void sort_array(int* arr, int nr_elements)
{
    int i, j;
    for (i = 0; i < nr_elements; i++)
        for (j = i + 1; j < nr_elements; j++)
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
}

void swap_lines(int** matrix, int nr_elements, int first_line, int second_line, int* elements_on_line)
{
    int i;
    for (i = 0; i < nr_elements; i++)
        swap(&matrix[first_line][i], &matrix[second_line][i]);
    swap(&elements_on_line[first_line], &elements_on_line[second_line]);
}

void sort_matrix_lines(int** matrix, int nr_nodes, int nr_lines, int* elements_on_line)
{
    int i, j;

    for (i = 0; i < nr_lines; i++)
        sort_array(matrix[i], elements_on_line[i]);

    for (i = 0; i < nr_lines; i++)
        for (j = i + 1; j < nr_lines; j++)
            if (matrix[i][0] > matrix[j][0])
                swap_lines(matrix, nr_nodes, i, j, elements_on_line);
}

int all_are_visited(int* visited, int start, int end)
{
    int i;
    for (i = start; i < end; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

int is_on_line(int* arr, int nr_nodes, int value)
{
    int i;
    for (i = 0; i < nr_nodes; i++)
        if (arr[i] == value)
            return 1;

    return 0;
}

int check_arrays_are_the_same(int* arr1, int* arr2, int len)
{
    int i;

    for (i = 0; i < len; i++)
        if (arr1[i] != arr2[i])
            return 0;

    return 1;
}

int check_element_extracted_before(element_t* elements, int nr_elements, element_t element, int nr_nodes)
{
    int i;
    for (i = 0; i < nr_elements; i++)
        if (elements[i].index == element.index && check_arrays_are_the_same(elements[i].visited, element.visited, nr_nodes) == 1)
            return 1;
    return 0;
}
int main()
{
    int nr_nodes, nr_links, nr_deposits, i, j, x, y;
    float** map;
    float cost;

    scanf("%d%d%d", &nr_nodes, &nr_links, &nr_deposits);

    map = (float**)calloc(nr_nodes, sizeof(float**));
    if (map == NULL)
        return -1;
    for (i = 0; i < nr_nodes; i++)
    {
        map[i] = (float*)calloc(nr_nodes, sizeof(float*));
        if (map[i] == NULL)
            return -1;
    }

    for (i = 0; i < nr_links; i++)
    {
        scanf("%d%d%f", &x, &y, &cost);
        map[x][y] = cost;
    }



    int* dest = calloc(nr_nodes, sizeof(int));

    float* dist = calloc(nr_nodes, sizeof(float));

    int* sptSet = calloc(nr_nodes, sizeof(int));

    int** parents = (int**)calloc(nr_nodes, sizeof(int*));
    for (i = 0; i < nr_nodes; i++)
        parents[i] = (int*)calloc(nr_nodes, sizeof(int));

    int* index = (int*)calloc(nr_nodes, sizeof(int));
    int src, nr_tasks, task_number;
    int nr_shops = 1, k;


    int* deposits = calloc(nr_nodes, sizeof(int));
    //read deposits array

    nr_deposits = 0;
    break_line_in_deposits(deposits, &nr_deposits);

    src = 0;
    scanf("%d", &nr_tasks);

    for (task_number = 0; task_number < nr_tasks; task_number++)
    {
        char task_name[5];
        scanf("%s", task_name);
        if (strcmp(task_name, "e1") == 0)
        {
            float total_cost = 0;
            scanf("%d", &src);
            scanf("%d", &nr_shops);
            for (i = 0; i < nr_shops; i++)
            {
                float sum_road;
                scanf("%d", &dest[i]);

                printf("%d\n", dest[i]);

                //first part of the road
                sum_road = 0;
                dijkstra(map, nr_nodes, src, dest[i], dist, sptSet, parents, index);
                parents[dest[i]][index[dest[i]]] = dest[i];
                for (j = 1; j <= index[dest[i]]; j++)
                    sum_road += map[parents[dest[i]][j - 1]][parents[dest[i]][j]];
                printf("%.1f ", sum_road);
                total_cost += sum_road;

                for (k = 0; k < nr_nodes; k++)
                    sptSet[k] = 0;
                for (k = 0; k < nr_nodes; k++)
                    index[k] = 0;
                swap(&src, &dest[i]);

                //second part of the road
                sum_road = 0;
                dijkstra(map, nr_nodes, src, dest[i], dist, sptSet, parents, index);
                parents[dest[i]][index[dest[i]]] = dest[i];
                for (j = 1; j <= index[dest[i]]; j++)
                    sum_road += map[parents[dest[i]][j - 1]][parents[dest[i]][j]];
                printf("%.1f", sum_road);
                total_cost += sum_road;
                printf("\n");


                //start printing road
                for (k = 0; k < nr_nodes; k++)
                    sptSet[k] = 0;
                for (k = 0; k < nr_nodes; k++)
                    index[k] = 0;
                swap(&src, &dest[i]);
                dijkstra(map, nr_nodes, src, dest[i], dist, sptSet, parents, index);

                printf("%d ", src);
                for (j = 1; j <= index[dest[i]]; j++)
                    printf("%d ", parents[dest[i]][j]);

                for (k = 0; k < nr_nodes; k++)
                    sptSet[k] = 0;
                for (k = 0; k < nr_nodes; k++)
                    index[k] = 0;
                swap(&src, &dest[i]);
                dijkstra(map, nr_nodes, src, dest[i], dist, sptSet, parents, index);

                for (j = 1; j < index[dest[i]]; j++)
                    printf("%d ", parents[dest[i]][j]);
                printf("%d", dest[i]);

                if (i != (nr_shops - 1))
                    printf("\n");

                for (k = 0; k < nr_nodes; k++)
                    sptSet[k] = 0;
                for (k = 0; k < nr_nodes; k++)
                    index[k] = 0;
                swap(&src, &dest[i]);
            }
            printf("\n");
            printf("%.1f", total_cost);

            for (k = 0; k < nr_nodes; k++)
                sptSet[k] = 0;
            for (k = 0; k < nr_nodes; k++)
                index[k] = 0;
            for (k = 0; k < nr_nodes; k++)
                for (j = 0; j < nr_nodes; j++)
                    parents[k][j] = 0;

            if (task_number != nr_tasks - 1)
                printf("\n");
        }

        if (strcmp(task_name, "e2") == 0)
        {
            int i, j;

            //new map containing all nodes that are not a deposit
            float** new_map = (float**)calloc(nr_nodes, sizeof(float*));
            if (new_map == NULL)
                return -1;
            for (i = 0; i < nr_nodes; i++)
            {
                new_map[i] = (float*)calloc(nr_nodes, sizeof(float));
                if (new_map[i] == NULL)
                    return -1;
            }

            int* index = (int*)malloc(nr_nodes * sizeof(int));
            current_index = 0;
            int* deg = (int*)malloc(nr_nodes * sizeof(int));
            int* low_link = (int*)malloc(nr_nodes * sizeof(int));
            int* in_stack = (int*)malloc(nr_nodes * sizeof(int));

            int** tarjan_array = (int**)calloc(nr_nodes, sizeof(int*));
            if (tarjan_array == NULL)
                return -1;
            for (i = 0; i < nr_nodes; i++)
            {
                tarjan_array[i] = (int*)calloc(nr_nodes, sizeof(int));
                if (tarjan_array[i] == NULL)
                    return -1;
            }

            for (i = 0; i < nr_nodes; i++)
                for (j = 0; j < nr_nodes; j++)
                    if (not_deposit(i, deposits, nr_deposits))
                        new_map[i][j] = map[i][j];

            for (i = 0; i < nr_nodes; i++)
                for (j = 0; j < nr_nodes; j++)
                    tarjan_array[i][j] = -1;

            reset_nodes(deg, low_link, index, in_stack, nr_nodes);

            stack_t* stack = initStack();
            int nr_lines = 0;
            for (i = 0; i < nr_nodes; i++)
                if (index[i] == -1 && not_deposit(i, deposits, nr_deposits))
                    tarjan(i, nr_nodes, index, low_link, in_stack, deg, new_map, stack, deposits[0], tarjan_array, &nr_lines, deposits, nr_deposits);

            int* elements_on_line = (int*)calloc(nr_nodes, sizeof(int));

            for (i = 0; i < nr_lines; i++)
                for (j = 0; j < nr_nodes; j++)
                    if (tarjan_array[i][j] != -1)
                        elements_on_line[i]++;

            //sort elements for print
            sort_matrix_lines(tarjan_array, nr_nodes, nr_lines, elements_on_line);

            //print tarjan_array
            printf("%d\n", nr_lines);
            for (i = 0; i < nr_lines; i++)
            {
                int print = 1;
                if (elements_on_line[i] == 1)
                {
                    int iteration = 0;
                    for (iteration = 0; iteration < nr_nodes; iteration++)
                        if (new_map[tarjan_array[i][elements_on_line[i] - 1]][iteration] != 0 && not_deposit(iteration, deposits, nr_deposits) == 1)
                            print = 0;
                }
                if (print == 1)
                {
                    for (j = 0; j < elements_on_line[i] - 1; j++)
                        printf("%d ", tarjan_array[i][j]);
                    printf("%d", tarjan_array[i][elements_on_line[i] - 1]);
                    if (i != nr_lines - 1)
                        printf("\n");
                }

            }

            while (stack->len != 0)
                pop(stack);

            free(elements_on_line);
            free(stack);
            free(low_link);
            free(index);
            free(in_stack);
            free(deg);

            for (i = 0; i < nr_nodes; i++)
                free(new_map[i]);
            free(new_map);

            for (i = 0; i < nr_nodes; i++)
                free(tarjan_array[i]);
            free(tarjan_array);
        }

        if (strcmp(task_name, "e3") == 0)
        {

            int deposits_number;


            int nr_lines, line;
            scanf("%d", &nr_lines);
            int** matrix = (int**)calloc(nr_nodes, sizeof(int*));
            for (i = 0; i < nr_nodes; i++)
                matrix[i] = (int*)calloc(nr_nodes, sizeof(int));

            for (line = 0; line < nr_lines; line++)
            {
                //the printed number
                float print_min = 100000.0;

                float min_dist_to = 10000000, min_dist_from = 10000000;
                int start_point, end_point;
                int elements_on_line;
                float cost = 0;

                scanf("%d", &elements_on_line);
                int a;
                for (i = 0; i < elements_on_line; i++)
                {
                    scanf("%d", &a);
                    matrix[line][i] = a;
                }

                for (deposits_number = 0; deposits_number < nr_deposits; deposits_number++)
                {
                    min_dist_to = 10000000;
                    min_dist_from = 100000000;

                    //now construct new graph that has only linkings to the elements on line
                    cost = 0;

                    float** new_graph = (float**)calloc(nr_nodes, sizeof(float*));
                    for (i = 0; i < nr_nodes; i++)
                        new_graph[i] = (float*)calloc(nr_nodes, sizeof(float));
                    for (i = 0; i < nr_nodes; i++)
                        for (j = 0; j < nr_nodes; j++)
                        {
                            int z;
                            int has_i = 0, has_j = 0;
                            for (z = 0; z < elements_on_line; z++)
                            {
                                if (matrix[line][z] == i)
                                    has_i = 1;
                                if (matrix[line][z] == j)
                                    has_j = 1;
                            }
                            if (has_i == 1 && has_j == 1)
                                new_graph[i][j] = map[i][j];
                        }

                    //get entry point and exit point of the cycle

                    for (i = 0; i < elements_on_line; i++)
                    {
                        for (k = 0; k < nr_nodes; k++)
                            sptSet[k] = 0;
                        for (k = 0; k < nr_nodes; k++)
                            index[k] = 0;

                        dijkstra(map, nr_nodes, deposits[deposits_number], matrix[line][i], dist, sptSet, parents, index);

                        if (min_dist_to > dist[matrix[line][i]])
                        {
                            min_dist_to = dist[matrix[line][i]];
                            start_point = matrix[line][i];
                        }
                    }
                    cost += min_dist_to;

                    for (i = 0; i < elements_on_line; i++)
                    {
                        for (k = 0; k < nr_nodes; k++)
                            sptSet[k] = 0;
                        for (k = 0; k < nr_nodes; k++)
                            index[k] = 0;
                        dijkstra(map, nr_nodes, matrix[line][i], deposits[deposits_number], dist, sptSet, parents, index);

                        if (min_dist_from > dist[deposits[deposits_number]])
                        {
                            min_dist_from = dist[deposits[deposits_number]];
                            end_point = matrix[line][i];
                        }
                    }
                    cost += min_dist_from;

                    //keep count of elements extracted from queue
                    element_t* extracted_elements = calloc(nr_nodes * nr_nodes, sizeof(element_t));


                    queue_struct* visit_queue = init_queue();

                    //shortest road from start_point to end_point visiting all other points on matrix[line]
                    element_t last_visit;
                    element_t current_visit;
                    element_t next_visit;
                    element_t queue_item;
                    last_visit.index = start_point;

                    last_visit.visited = (int*)malloc(nr_nodes * nr_nodes * sizeof(int));
                    current_visit.visited = (int*)malloc(nr_nodes * nr_nodes * sizeof(int));
                    next_visit.visited = (int*)malloc(nr_nodes * nr_nodes * sizeof(int));
                    queue_item.visited = (int*)malloc(nr_nodes * nr_nodes * sizeof(int));

                    for (i = 0; i < nr_nodes * nr_nodes; i++)
                    {
                        last_visit.visited[i] = 0;
                        current_visit.visited[i] = 0;
                        next_visit.visited[i] = 0;
                        queue_item.visited[i] = 0;
                    }

                    //start queue and dijkstra modified as in hint
                    queue_item.index = start_point;
                    enqueue(visit_queue, queue_item);

                    //copy last visited
                    last_visit.index = queue_item.index;
                    for (i = 0; i < nr_nodes * nr_nodes; i++)
                        last_visit.visited[i] = queue_item.visited[i];
                    //endcopy


                    int visited_elements = 1;

                    float road_cost = 0;

                    while (visit_queue->len != 0)
                    {
                        //obtain queued visit and note it
                        queue_item = dequeue(visit_queue);
                        queue_item.visited[queue_item.index] = 1;

                        road_cost += new_graph[last_visit.index][queue_item.index];

                        if (new_graph[last_visit.index][queue_item.index] == 0)
                            visited_elements--;

                        extracted_elements[visited_elements] = queue_item;
                        visited_elements++;

                        ////add elements that were not visited before to the queue
                        for (i = 0; i < nr_nodes; i++)
                            if (new_graph[queue_item.index][i] != 0)
                            {
                                int prev_index = queue_item.index;

                                queue_item.index = i;

                                enqueue(visit_queue, queue_item);

                                queue_item.index = prev_index;

                            }

                        int all_elements_are_visited = 1;
                        for (i = 0; i < elements_on_line; i++)
                            if (queue_item.visited[matrix[line][i]] == 0)
                                all_elements_are_visited = 0;

                        if (queue_item.index == end_point && all_elements_are_visited == 1)
                        {

                            road_cost = 0;
                            for (i = 0; i < visited_elements - 1; i++)
                                road_cost += map[extracted_elements[i].index][extracted_elements[i + 1].index];

                            break;
                            road_cost = 0;
                        }

                        //last_visit = current_visit;
                        last_visit.index = queue_item.index;
                        for (i = 0; i < nr_nodes * nr_nodes; i++)
                            last_visit.visited[i] = queue_item.visited[i];
                    }

                    cost += road_cost;

                    if (print_min > cost)
                        print_min = cost;

                    while (visit_queue->len > 0)
                        dequeue(visit_queue);

                    free(queue_item.visited);
                    free(last_visit.visited);
                    free(current_visit.visited);
                    free(next_visit.visited);
                    for (i = 0; i < nr_nodes; i++)
                        free(new_graph[i]);
                    free(new_graph);

                    free(visit_queue);

                    free(extracted_elements);
                }

                printf("%.1f", print_min);
                if (line != nr_lines - 1)
                    printf("\n");
            }

            for (i = 0; i < nr_nodes; i++)
                free(matrix[i]);
            free(matrix);
        }
    }

    free(deposits);
    free(index);
    for (i = 0; i < nr_nodes; i++)
        free(parents[i]);
    free(parents);
    free(dist);
    free(dest);
    free(sptSet);
    for (i = 0; i < nr_nodes; i++)
        free(map[i]);
    free(map);

    return 0;
}


