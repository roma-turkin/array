/*
25.02.14
Планируется реализовать массив как двоичное дерево поиска (пока необязательно сбалансированное).
Структура узла - индекс элемента массива, указатель на содержимое элемента массива и два указателя на следующие узлы дерева
right соответствует большему индексу, left - меньшему.
*/

#include "../array.h"
#include <stdlib.h>
#include <stdio.h>

struct node{
    INDEX index;
    DATA data;
    struct node * right;
    struct node * left;
};
/*
    В функции create_array мы выделяем память под один узел - root. В root->index лежит -1 - так мы отличаем корень дерева от всех остальных
узлов. (полагается, что это нормальный Си-шный массив с индексами от 0 и до скольки угодно).
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
	struct node * root;				//Забираем array в свою переменную root, которую не жалко если что попортить
	root = (struct node *)array;	
    struct node * leaf;				//Данная переменная и будет новым элементом массива
    leaf = malloc(sizeof(struct node));
    if (leaf==NULL){				//Ошибка выделения памяти
        goto insert_error; 
    }
    if (input_index < 0){
    	goto insert_error;			//Нельзя вставлять элементы с отрицательными индексами! Не положено!
    }
    leaf->index = input_index;
    leaf->data = input_data;
    leaf->right = NULL;
    leaf->left = NULL;
    if (!root->left){				//root - просто корень, он не является элементом массива. Первый элемент массива лежит слева от root.
        root->left = leaf;			//Дальше начиная с первого элемента дерево и начинает рост
        return 0;
    }
    struct node * current;  //Current node, узел, в который мы спустились в результате последней итерации
    current = root->left;	//Начальное состояние - первый элемент. Наличие этого элемента гарантировано операциями сверху.
    int leaf_inserted = 0;  //Флаг, который подымется, когда лист будет вставлен на место.
    while (!leaf_inserted){ 
    	if (current->index == leaf->index){ //Новый элемент массива попадает на место первого. Вообще в алгоритме полагается, что ситуация
    		leaf->left = current->left;		//равных индексов у текущего элемента и вставляемого возможна только для первого элемента.
    		leaf->right = current->right;	//В этом случае получается вставить элемент, не прибегая к дополнительным переменным.
    		root->left = leaf;				//На данном шаге первый лист просто подменяется вставляемым, а после память освобождается.
    		free(current);
    		leaf_inserted = 1;
    		continue;
    	}
    	//Во всех остальных ответвлениях программы текущий индекс не может равняться тому, который мы вставляем.
    	if (current->index > leaf->index){ 	//Индекс нового элемента меньше, чем индекс текущего. Смотрим в левую ветку дерева.
    		if (!current->left){			//Слева нет элемента, сюда и надо вставить лист
    			current->left = leaf;
    			leaf_inserted = 1;
    			continue;
    		}
    		if (current->left->index == leaf->index){//Левый элемент есть, и его индекс совпадает с индексом листа
    			leaf->left = current->left->left;
    			leaf->right = current->left->right;
    			free(current->left);
    			current->left = leaf;
    			leaf_inserted = 1;
    			continue;
    		}
    		current = current->left; //Слева от текущего элемента лежит элемент с индексом, не равным индексу нового элемента.
    	}
    	if (current->index < leaf->index){ //Вставляем справа. Все то же самое, что и для левой ветки, только справа
    		if (!current->right){
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

DATA get(ARRAY array, INDEX index){
	if (index < 0){
		return NULL;    				//Нет у нас элементов с отрицательными индексами, нет, не было и не будет
	}
	struct node * current;
	current = (struct node *) array;	//Начинаем обход с корня.
	if (!current->left){ 				//Массив пуст, т.е. левая ветка root никуда не ведет
		return NULL; 
	} else{
		current = current->left;		//Первый элемент есть. Начинаем обход.
	}
	//int completed = 0;
	while (1){ //Цикл бесконечный, так как в результате обхода дерева должно вернуться какое-то значение, и функция завершит работу.
		if (current->index == index){ //Нашли искомый элемент. Возвращаем его же.
			return current->data;
		}
		if (current->index > index && current->left){//Искомый индекс меньше, чем текущий. Отправляемся в левую ветку.
			current = current->left;
			continue;
		}
		if (current->index > index && !current->left){
			return NULL; 							//Искомый индекс меньше, чем текущий, и слева пусто. Нет такого элемента.
		}
		if (current->index < index && current->right){//Та же история с правой веткой.
			current = current->right;
			continue;
		}
		if (current->index < index && !current->right){
			return NULL;
		}
	}
}
/*
С помощью функции destroy_array мы рекурсивно проходим по всем узлам дерева и освобождаем занятую узлами память. 
*/

int destroy_array(ARRAY array){
	if (!array){
		return -1; 				//Нам скормили NULL
	}
	struct node * left, *right, *root;
	root = (struct node *) array;
	if (!root->left)
	{
		return -1;
	}
	left = root->left;
	right = root->right;
	if (left)
	{					//Спускаемся только в те ветки, где что-то есть. Там имеет смысл освобождать что-либо
		destroy_array(left);	//Ну а здесь зарыта вся рекурсия.
		free(left);				//После того, как все элементы слева от текущего элемента освобождены, можно освобождать и текущий.
	}
	if (right)
	{
		destroy_array(right);
		free(right);
	}
	root->left = NULL;
	root->right = NULL;
	//free(root);
	return 0;
}

void balance_tree(struct node * element)
{
	
}