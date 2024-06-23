#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void delay(int ms) {
    for (int t = 0; t < ms; t++) {
        for (int i = 0; i < 123000; i++);
    }
}

// Item definition
typedef struct item {
    char maNV[50];
    int namsinh;
    float hesoluong;
    float phucapCV;
    double tongluong;
} item;

// Linked list node structure
typedef struct Node {
    item Data;
    struct Node *next;
} Node;

typedef Node *LinkedList;

// List by array
typedef struct list {
    item Data[N];
    int size;
} list;

// Stack by array
typedef struct stack {
    item Data[N];
    int Top;
} stack;

// Stack by pointer
struct NodeS {
    item Data;
    struct NodeS *Next;
};

typedef struct Stack {
    struct NodeS *Top;
} Stack;

// Queue by array
typedef struct queue {
    item Data[N];
    int size;
    int front, rear;
} queue;

// Queue by pointer
typedef struct NodeQ {
    item Data;
    struct NodeQ *Next;
} NodeQ;

typedef struct Queue {
    NodeQ *Front, *Rear;
    int count;
} Queue;

//------------------------------------------------------//
// INITIALIZATION

// List
void InitList(list *l, LinkedList *L) {
    l->size = 0;
    *L = NULL;
}

// Stack
void InitStack(stack *s, Stack *S) {
    s->Top = 0;
    S->Top = NULL;
}

// Queue
void InitQueue(queue *q, Queue *Q) {
    q->size = 0;
    q->front = 0;
    q->rear = N - 1;
    Q->count = 0;
    Q->Front = NULL;
    Q->Rear = NULL;
}

//------------------------------------------------------//
// EMPTY CHECKS

// List
void EmptyList(list l, LinkedList L) {
    if (l.size == 0 && L == NULL) {
        printf("Danh sach rong\n");
    } else {
        printf("Danh sach co phan tu\n");
    }
}

// Stack
void EmptyStack(stack s, Stack S) {
    if (s.Top == 0 && S.Top == NULL)
        printf("Ngan xep rong\n");
    else
        printf("Ngan xep co phan tu\n");
}

// Queue
void EmptyQueue(queue q, Queue Q) {
    if (q.size == 0 && Q.count == 0)
        printf("Hang doi rong\n");
    else
        printf("Hang doi co phan tu\n");
}

//------------------------------------------------------//
// FULL CHECKS

// List
void FullList(list l) {
    if (l.size == N)
        printf("Danh sach da day\n");
    else
        printf("Danh sach con trong\n");
}

// Stack
void FullStack(stack s) {
    if (s.Top == N)
        printf("Ngan xep da day\n");
    else
        printf("Ngan xep con trong\n");
}

// Queue
void FullQueue(queue q) {
    if (q.size == N)
        printf("Hang doi da day\n");
    else
        printf("Hang doi con trong\n");
}

//------------------------------------------------------//

// Input for linked list (pointer)
Node *makeNodeL(item x) {
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    strcpy(p->Data.maNV, x.maNV);
    p->Data.hesoluong = x.hesoluong;
    p->Data.namsinh = x.namsinh;
    p->Data.phucapCV = x.phucapCV;
    p->Data.tongluong = x.tongluong;
    p->next = NULL;
    return p;
}

int len(LinkedList L) {
    Node *p = L;
    int d = 0;
    while (p != NULL) {
        d++;
        p = p->next;
    }
    return d;
}

void insert(LinkedList *L, item x, int k) {
    Node *p = makeNodeL(x);
    int i = 1;

    if (k < 1 || k > len(*L) + 1) {
        printf("Invalid position %d.\n", k);
        return;
    }

    if (k == 1) { // Insert at the beginning
        p->next = *L;
        *L = p;
    } else { // Insert elsewhere
        Node *q = *L;
        while (q != NULL && i != k - 1) { // Move to position k-1
            i++;
            q = q->next;
        }
        if (q == NULL) {
            printf("Position %d is out of range.\n", k);
            return;
        }
        p->next = q->next; // Connect new node
        q->next = p;
    }
}

void inputData(LinkedList *L) { // Nh?p danh sách liên k?t vào d?u ds
    item x;
    int n; // Bi?n n dùng d? ch?a s? ph?n t? c?a ds
    // Nh?p s? ph?n t? trong ds
    printf("\nNhap so phan tu cua ds:");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        fflush(stdin);
        printf("\nnhap ma nhan vien: ");
        scanf("%s", &x.maNV);
        fflush(stdin);
        printf("\nnhap nam sinh: ");
        scanf("%d", &x.namsinh);
        fflush(stdin);
        printf("\nnhap he so luong: ");
        scanf("%f", &x.hesoluong);
        fflush(stdin);
        printf("\nnhap phu cap chuc vu: ");
        scanf("%f", &x.phucapCV);
        x.tongluong=x.hesoluong*x.phucapCV;
		int k;
        printf("Nhap k= ");
        scanf("%d", &k);
        fflush(stdin);
        insert(L, x, k);
    }
}

void deleteNodeAtPositionL(LinkedList *L, int k) {
    if (*L == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node *current = *L;
    Node *prev = NULL;
    int count = 1;
    // Traverse to the desired position
    while (current != NULL && count < k) {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("Position %d is out of range.\n", k);
        return;
    }

    // Update the pointers to skip the node at the specified position
    if (prev == NULL) {
        // Deleting the first node
        *L = current->next;
    } else {
        prev->next = current->next;
    }

    // Free memory
    free(current);
    printf("Node at position %d deleted successfully.\n", k);
}

//------------------------------------------------------//

struct NodeS *makeNodeS(item x) {
    struct NodeS *p = (struct NodeS *)malloc(sizeof(struct NodeS));
    if (p) {
        strcpy(p->Data.maNV, x.maNV);
        p->Data.phucapCV = x.phucapCV;
        p->Data.namsinh = x.namsinh;
        p->Data.hesoluong = x.hesoluong;
        p->Data.tongluong = x.tongluong;
        p->Next = NULL;
    }
    return p;
}

void push(Stack *S, item x) {
    struct NodeS *newNode = makeNodeS(x);
    if (newNode) {
        newNode->Next = S->Top;
        S->Top = newNode;
    } else {
        printf("Memory allocation failed. Unable to push.\n");
    }
}

void pop(Stack *S) {
    if (S->Top) {
        struct NodeS *temp = S->Top;
        S->Top = S->Top->Next;
        free(temp); // Free memory for the popped node
    } else {
        printf("Stack is empty. Cannot pop.\n");
    }
}

void popAll(Stack *S) {
    while (S->Top) {
        struct NodeS *temp = S->Top;
        S->Top = S->Top->Next;
        free(temp);
    }
}

void inputDataS(Stack *S) {
    int numx;
    printf("Enter the number of NV: ");
    scanf("%d", &numx);
    for (int i = 0; i < numx; ++i) {
        item x;
        printf("\nnhap ma nhan vien: ");
        scanf("%s", &x.maNV);
        printf("nhap nam sinh: ");
        scanf("%d", &x.namsinh);
        printf("nhap he so luong: ");
        scanf("%f", &x.hesoluong);
        printf("nhap phu cap chuc vu: ");
        scanf("%f", &x.phucapCV);
        x.tongluong=x.hesoluong*x.phucapCV;
        push(S, x);
    }
}

//------------------------------------------------------//

void Enqueue(Queue *Q, item x) {
    NodeQ *newNode = (NodeQ *)malloc(sizeof(NodeQ));
    if (newNode) {
        newNode->Data = x;
        newNode->Next = NULL;

        if (Q->Rear == NULL) { // If queue is empty
            Q->Front = newNode;
            Q->Rear = newNode;
        } else {
            Q->Rear->Next = newNode;
            Q->Rear = newNode;
        }
        Q->count++;
        printf("Inserted successfully into queue.\n");
    } else {
        printf("Memory allocation failed. Unable to insert.\n");
    }
}

void Dequeue(Queue *Q) {
    if (Q->Front == NULL) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }

    NodeQ *temp = Q->Front;
    Q->Front = Q->Front->Next;
    free(temp);

    if (Q->Front == NULL) { // If queue becomes empty
        Q->Rear = NULL;
    }

    Q->count--;
    printf("Dequeued successfully.\n");
}

void DeleteAllQueue(Queue *Q) {
    while (Q->Front) {
        NodeQ *temp = Q->Front;
        Q->Front = Q->Front->Next;
        free(temp);
    }
    Q->Rear = NULL;
    Q->count = 0;
    printf("Queue cleared successfully.\n");
}

//------------------------------------------------------//

// Display all elements in the linked list
void ShowList(LinkedList L) {
    Node *p = L;
    printf("Danh sach lien ket:\n");
    while (p != NULL) {
        printf("\n\nMa NV: %s\n Nam sinh: %d\n He so luong: %.2f\n Phu cap CV: %.2f\n Tong luong: %.2lf\n",
               p->Data.maNV, p->Data.namsinh, p->Data.hesoluong, p->Data.phucapCV, p->Data.tongluong);
        p = p->next;
    }
}

// Display all elements in the stack
void ShowStack(Stack S) {
    struct NodeS *p = S.Top;
    printf("Ngan xep:\n");
    while (p != NULL) {
        printf("\n\nMa NV: %s\n Nam sinh: %d\n He so luong: %.2f\n Phu cap CV: %.2f\n Tong luong: %.2lf\n",
               p->Data.maNV, p->Data.namsinh, p->Data.hesoluong, p->Data.phucapCV, p->Data.tongluong);
        p = p->Next;
    }
}

// Display all elements in the queue
void ShowQueue(Queue Q) {
    NodeQ *p = Q.Front;
    printf("Hang doi:\n");
    while (p != NULL) {
        printf("\n\nMa NV: %s\n Nam sinh: %d\n He so luong: %.2f\n Phu cap CV: %.2f\n Tong luong: %.2lf\n",
               p->Data.maNV, p->Data.namsinh, p->Data.hesoluong, p->Data.phucapCV, p->Data.tongluong);
        p = p->Next;
    }
}

//------------------------------------------------------//

int main() {
    list l;
    LinkedList L = NULL;
    stack s;
    Stack S;
    queue q;
    Queue Q;
    InitList(&l, &L);
    InitStack(&s, &S);
    InitQueue(&q, &Q);

    int choice = 1;
    while (choice != 0) {
        printf("\n1. Kiem tra danh sach rong \n");
        printf("2. Kiem tra ngan xep rong \n");
        printf("3. Kiem tra hang doi rong \n");
        printf("4. Nhap du lieu danh sach (poiter)\n");
        printf("5. Xoa du lieu danh sach (poiter)\n");
        printf("6. Kiem tra danh sach day (mang) \n");
        printf("7. Kiem tra ngan xep day (mang) \n");
        printf("8. Kiem tra hang doi day (mang) \n");
        printf("9. Nhap du lieu ngan xep (poiter) \n");
        printf("10. Xoa du lieu ngan xep (poiter) \n");
        printf("11. Xoa toan bo du lieu ngan xep (poiter) \n");
        printf("12. Enqueue into queue (pointer) \n");
        printf("13. Dequeue from queue (pointer) \n");
        printf("14. Xoa toan bo du lieu hang doi (poiter) \n");
        printf("15. Hien thi danh sach lien ket \n");
        printf("16. Hien thi ngan xep \n");
        printf("17. Hien thi hang doi \n");
        printf("0. Ket thuc chuong trinh\n");
        printf("Lua chon yeu cau: \n");
        scanf("%d", &choice);
        fflush(stdin);
        system("cls");

        switch (choice) {
            case 1: {
                EmptyList(l, L);
                break;
            }

            case 2: {
                EmptyStack(s, S);
                break;
            }

            case 3: {
                EmptyQueue(q, Q);
                break;
            }

            case 4: {
                inputData(&L);
                break;
            }

            case 5: {
                int k;
                printf("Enter position to delete: ");
                scanf("%d", &k);
                deleteNodeAtPositionL(&L, k);
                break;
            }

            case 6: {
                FullList(l);
                break;
            }

            case 7: {
                FullStack(s);
                break;
            }

            case 8: {
                FullQueue(q);
                break;
            }

            case 9: {
                inputDataS(&S);
                break;
            }

            case 10: {
                pop(&S);
                printf("Removed top item from stack.\n");
                break;
            }

            case 11: {
                popAll(&S);
                printf("Removed all items from stack.\n");
                break;
            }

            case 12: {
                int numEnqueue;
                printf("Enter the number of items to enqueue: ");
                scanf("%d", &numEnqueue);
                for (int i = 0; i < numEnqueue; ++i) {
                    item x;
                    printf("\nnhap ma nhan vien: ");
                    scanf("%s", &x.maNV);
                    printf("nhap nam sinh: ");
                    scanf("%d", &x.namsinh);
                    printf("nhap he so luong: ");
                    scanf("%f", &x.hesoluong);
                    printf("nhap phu cap chuc vu: ");
                    scanf("%f", &x.phucapCV);
                    x.tongluong=x.hesoluong*x.phucapCV;
                    Enqueue(&Q, x);
                }
                break;
            }

            case 13: {
                Dequeue(&Q);
                break;
            }

            case 14: {
                DeleteAllQueue(&Q);
                break;
            }

            case 15: {
                ShowList(L);
                break;
            }

            case 16: {
                ShowStack(S);
                break;
            }

            case 17: {
                ShowQueue(Q);
                break;
            }

            case 0: {
                printf("Chuong trinh duoc ket thuc\n");
                break;
            }

            default: {
                printf("Lua chon khong hop le.\n");
                break;
            }
        }
        delay(5000);
    }

    return 0;
}

