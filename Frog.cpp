
#include <iostream>
#include <queue>
#include <string.h>
#define Maxlength 100
#define Maxlength_frog 7
#define Max_frog 3
#define frog_green 1
#define frog_red 2
using namespace std;

int goal[] = {2, 2, 2, 0, 1, 1, 1};
const char *action[] = {
    "First state",
    "Frog jump to right 1 step",
    "Frog jump to left 1 step",
    "Frog jump to right 2 step",
    "Frog jump to left 2 step"};
typedef struct
{
    int frogs[7];
    int stone;
} State;
void makeNullState(State *state)
{
    for (int i = 0; i < 7; i++)
    {
        state->frogs[i] = 0;
    }
    state->stone = 0;
}
int isJump(State state, char der[])
{
    int position_stone = state.stone;
    if (strcmp(der, "left") == 0)
        if (state.frogs[position_stone - 1] != state.frogs[position_stone - 2])
            return 1;
    if (strcmp(der, "right") == 0)
        if (state.frogs[position_stone + 1] != state.frogs[position_stone + 2])
            return 1;
    return 0;
}
void copyArray(int array1[], int array2[])
{
    for (int i = 0; i < Maxlength_frog; i++)
    {
        array2[i] = array1[i];
    }
}

int jumpLeft_1(State cur_state, State *result)
{
    if (cur_state.stone > 0)
    {
        copyArray(cur_state.frogs, result->frogs);
        result->stone = cur_state.stone;
        int position_stone = result->stone;
        swap(result->frogs[position_stone], result->frogs[position_stone - 1]);
        result->stone--;
        return 1;
    }
    return 0;
}
int jumpRight_1(State cur_state, State *result)
{
    if (cur_state.stone < Maxlength_frog - 1)
    {
        copyArray(cur_state.frogs, result->frogs);
        result->stone = cur_state.stone;
        int position_stone = result->stone;
        swap(result->frogs[position_stone], result->frogs[position_stone + 1]);
        result->stone++;
        return 1;
    }
    return 0;
}
int jumpLeft_2(State cur_state, State *result)
{
    if (cur_state.stone > 1 && isJump(cur_state, (char *)"left"))
    {
        copyArray(cur_state.frogs, result->frogs);
        result->stone = cur_state.stone;
        int position_stone = result->stone;
        swap(result->frogs[position_stone], result->frogs[position_stone - 2]);
        result->stone -= 2;
        return 1;
    }
    return 0;
}
int jumpRight_2(State cur_state, State *result)
{
    if (cur_state.stone < Maxlength_frog - 2 && isJump(cur_state, (char *)"right"))
    {
        copyArray(cur_state.frogs, result->frogs);
        result->stone = cur_state.stone;
        int position_stone = result->stone;
        swap(result->frogs[position_stone], result->frogs[position_stone + 2]);
        result->stone += 2;
        return 1;
    }
    return 0;
}
int checkGoal(State state)
{
    for (int i = 1; i < Maxlength_frog; i++)
    {
        if (state.frogs[i] != goal[i])
        {
            return 0;
        }
    }
    return 1;
}
void printState(State state)
{
    cout << "\t";
    for (int e : state.frogs)
    {
        cout << e << " ";
    }
}
int call_operator(State cur_state, State *result, int opt)
{
    switch (opt)
    {
    case 1:
        return jumpLeft_1(cur_state, result);
    case 2:
        return jumpRight_1(cur_state, result);
    case 3:
        return jumpLeft_2(cur_state, result);
    case 4:
        return jumpRight_2(cur_state, result);
    default:
        cout << "Error call operator";
        return 0;
    }
}
typedef struct Node
{
    State state;
    struct Node *Parent;
    int no_function;
} Node;
int compareState(State state1, State state2)
{
    for (int i = 0; i < Maxlength_frog; i++)
    {
        if (state1.frogs[i] != state2.frogs[i])
            return 0;
    }
    return 1;
}
int findState(State state, queue<Node *> queue)
{
    while (!queue.empty())
    {
        if (compareState(queue.front()->state, state))
            return 1;
        queue.pop();
    }
    return 0;
}
Node *BFS_Algorithm(State state)
{
    queue<Node *> Open, Close;
    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    Open.push(root);
    while (!Open.empty())
    {
        Node *node = Open.front();
        Open.pop();
        Close.push(node);
        if (checkGoal(node->state))
            return node;
        int opt;
        for (opt = 1; opt <= 4; opt++)
        {
            State newState;
            makeNullState(&newState);
            if (call_operator(node->state, &newState, opt))
            {
                if (findState(newState, Open) || findState(newState, Close))
                    continue;
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->Parent = node;
                newNode->no_function = opt;
                Open.push(newNode);
            }
        }
    }
    return NULL;
}
void print_WaysToGetGoal(Node *node)
{
    Node a[100];
    int i = 0;
    while (node->Parent != NULL)
    {
        a[i++] = *node;
        node = node->Parent;
    }
    a[i] = *node;
    int no_action = 0;
    while (i >= 0)
    {
        printf("\nAction %d: %s \n", no_action++, action[a[i].no_function]);
        printState(a[i].state);
        i--;
    }
}
int main()
{
    State state = {1, 1, 1, 0, 2, 2, 2};
    state.stone = 3;
    Node *node = BFS_Algorithm(state);
    print_WaysToGetGoal(node);
    return 0;
}