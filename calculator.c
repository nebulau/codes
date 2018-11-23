#include<stdio.h>
#define M 50
typedef struct node{
    int flag;
    int data;
    struct node *left,*right;
}BTNode,*BTREE;
int full(int top) {
    return top == M - 1;
}
int empty(int top) {
    return top == -1;
}
: 
int push(char stack[], int *top, char i) {
    if (full(*top))    return 0;
    else {
        stack[++(*top)] = i;
        return 1;
    }
}
int PUSH(int stack[], int *top, int i) {
    if (full(*top))    return 0;
    else { 
        stack[++(*top)] = i;
        return 1;
    }
}
int pop(char stack[], int *top, char *i) {
    if (empty(*top))    return 0;
    else {
        *i = stack[(*top)--];
        return 1;
    } 
}
int POP(int stack[], int *top, int *i) {
    if (empty(*top))    return 0;
    else {
        *i = stack[(*top)--];
        return 1;
    }
}
char gettop(char stack[], int t) {
    return stack[t];
}
int judge(char a, char b) {
    if (a == '*' || a == '/') return 1;
    else if (a == '+' || a == '-') { 
        if (b == '*' || b == '/')    return 0;
        else {
            return 1;
        }
    }
    else {
        if (b == '(')    return 1;
        else {
            return 0;
        }
    } 
} 
int main() {
    int top = -1, i = 0, j = 0, s3[50] = { 0 }, x = 0, k, TOP = -1, y, z, STACK[M];
    char s1[50], stack[M], m, s2[50];//s1为表达式，stack为符号栈，s2为后缀表达式符号部分，s3为数字部分
    for (k = 0; k < 50; k++)    s2[k] = 'a';
    while (1) { 
        scanf("%c", &s1[i++]); 
        if (s1[i - 1] == '=')    break;
    }
    s1[i - 1] = '\0';
    for (i = 0; s1[i] != '\0'; i++) {
        if (s1[i] > 47 && s1[i] < 58) { 
            for (k = i; s1[k] > 47 && s1[k] < 58; k++) {
                x = x * 10 + s1[k] - '0';
            }
            s3[j++] = x;
            x = 0; 
            i = k - 1;
        }
        else if (s1[i] != 40 && s1[i] != 41 && s1[i] != ' ') {
            if (empty(top))    push(stack, &top, s1[i]); 
            else {
                if (judge(gettop(stack, top),s1[i])) {
                    while (judge(gettop(stack, top), s1[i])) {
                        pop(stack, &top, &m);
                        s2[j++] = m;
                    }
                    push(stack, &top, s1[i]);
                }
                else {
                    push(stack, &top, s1[i]);
                }
            }
        } 
        if (s1[i] == '(')    push(stack, &top, s1[i]); 
        if (s1[i] == ')') { 
            m = 'a';
            while (m != '(') {
                pop(stack, &top, &m);
                if (m != '(')    s2[j++] = m;
            }
        }
    }
    while (!empty(top)) { 
        pop(stack, &top, &m);
        s2[j++] = m;
    }
    s2[j] = '\0';
    for (k = 0; k < j; k++) {
        if (s3[k] != 0)    PUSH(STACK, &TOP, s3[k]);
        if (s2[k] != 'a') {
            POP(STACK, &TOP, &z);
            POP(STACK, &TOP, &y);
            switch (s2[k]) {
            case '+':x = y + z; break;
            case '-':x = y - z; break; 
            case '*':x = y * z; break;
            case '/':x = y / z; break;
            }
            PUSH(STACK, &TOP, x);
        }
    }
    printf("%d", STACK[0]);
    return 0;
}
