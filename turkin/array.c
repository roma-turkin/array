/*
25.02.14
Планируется реализовать массив как двоичное дерево поиска (пока необязательно сбалансированное).
Структура узла - индекс элемента массива, указатель на содержимое элемента массива и два указателя на следующие узлы дерева
right соответствует большему индексу, left - меньшему.
*/

#include "../array.h"
#include <stdlib.h>

struct node{
    INDEX index;
    DATA data;
    struct node * right;
    struct node * left;
};
/*
    В функции create_array мы выделяем память под один узел - root. В root->index лежит -1 - так мы отличаем корень дерева от всех остальных
узлов. (полагается, что это нормальный Си-шный массив с индексами от 0 и до скольки угодно.
ARRAY определен в array.h, ARRAY == void *
*/
ARRAY create_array(){
    struct node * root;
    root = malloc(sizeof(struct node));
    root->index = -1;
    root->data = 0;
    root->right = 0;
    root->left = 0;
    return root;
}
/*
    Данная функция получает в качестве аргументов массив, в который надо вставить элемент, индекс элемента и указатель на место памяти, 
где хранится информация. Логика работы такова - заполняем некоторый лист дерева "leaf" значениями из аргументов. Затем последовательно начиная
с корня спускаемся по узлам дерева до нижнего уровня, в который мы вставляем элемент. Если элементов еще нет, вставляем лист в левую ветку.
*/
int insert(ARRAY array,INDEX input_index,DATA input_data){
	struct node * root;
	root = (struct node *)array;
    struct node * leaf;
    leaf = malloc(sizeof(struct node));
    if (leaf==NULL){
        goto insert_error; 
    }
    leaf->index = input_index;
    leaf->data = input_data;
    leaf->right = 0;
    leaf->left = 0;
    if (!root->left){
        root->left = leaf;
        return 0;
    }
    struct node * current; //Current node 
    current = root->left;
    int leaf_inserted = 0; //Флаг, который подымется, когда лист будет вставлен на место.
    while (!leaf_inserted){ 
    	if (current->index == leaf->index){//Новый элемент массива попадает на место рута
    		leaf->left = current->left;
    		leaf->right = current->right;
    		root->left = leaf;
    		free(current);
    		leaf_inserted = 1;
    		continue;
    	}
    	//Во всех остальных ответвлениях программы текущий индекс не может равняться тому, который мы вставляем.
    	if (current->index > leaf->index){ //Вставляем слева
    		if (!current->left){//Слева нет элемента, сюда и надо вставить лист
    			current->left = leaf;
    			leaf_inserted = 1;
    			continue;
    		}
    		if (current->left->index == leaf->index){//Индекс левого элемента совпадает с индексом листа
    			leaf->left = current->left->left;
    			leaf->right = current->left->right;
    			free(current->left);
    			current->left = leaf;
    			leaf_inserted = 1;
    			continue;
    		}
    		current = current->left; //Слева от текущего элемента лежит элемент с индексом, не равным индексу вставляемого листа.
    		continue;
    	}
    	if (current->index < leaf->index){ //Вставляем справа
    		if (!current->right){//Справа пусто, можно вставлять
    			current->right = leaf;
    			leaf_inserted = 1;
    			continue;
    		}
    		if (current->right->index == leaf->index){
    			leaf->right = current->right->right;
    			leaf->left = current->right->left;
    			free(current->right);
    			current->right = leaf;
    			leaf_inserted = 1;
    			continue;
    		}
    		current = current->right;
    	}
    }
    return 0;
	insert_error:
    return -1;
}
