#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList*)calloc(1,sizeof(ForwardList));
    l->size = 0;
    l->head = NULL;
    return l;
}
int forward_list_size(ForwardList *l){
    return l->size;
}
void forward_list_push_front(ForwardList *l, data_type data){
    l->size = l->size + 1;
    l->head = node_construct(data,l->head);
}
void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    Node *n = l->head;
    printf("[");
    for(int i = 0;i<l->size;i++){
        print_fn(n->value);
        n = n->next;
        if(i != (l->size-1)){
            printf(", ");
        }
    }
    printf("]");
}

void forward_list_destroy(ForwardList *l){
    Node *n = l->head,*next;
    for(int i = 0; i<forward_list_size(l);i++){
        next = n->next;
        node_destroy(n);
        n = next;
    }
    free(l);
}

data_type forward_list_get(ForwardList *l, int i){
    if((i>=l->size)&&(i>-1)){
        exit(1);
    }
    Node *n = l->head;
    for(int j = 1; j<=i; j++){
        n = n->next;
    }
    return n->value;
}

data_type forward_list_pop_front(ForwardList *l){
    Node *apagado = l->head;
    data_type valor = apagado->value;
    l->head = apagado->next;
    node_destroy(apagado);
    l->size--;
    return valor;
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList *reverse = forward_list_construct();
    for(int i = 0; i<l->size; i++){
        forward_list_push_front(reverse,forward_list_get(l,i));
    }
    return reverse;
}

void forward_list_remove(ForwardList *l, data_type val){
    int apagados = 0;
    Node *apagar = NULL,*atual = NULL,*anterior = NULL;
    for(int i = 0; i < l->size;i++){
        if((i-apagados)== 0){
            atual = l->head;
        }else{
            anterior = atual;
            atual = atual->next;
        }
        if(forward_list_get(l,(i-apagados))==val){
            if((i-apagados) == 0){
                apagar = l->head;
                l->head = l->head->next;
            }else{
                apagar = atual;
                anterior->next = atual->next;
                atual = anterior;
            }
            node_destroy(apagar);
            apagados++;
        }
    }
    l->size = l->size - apagados;
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    data_type valor;
    for(int i = m->size-1; i>=0; i--){
        valor = forward_list_get(m,i);
        forward_list_push_front(l,valor);
    }
}