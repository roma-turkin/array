#include <stdio.h>
#include "../array.h"
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define ERROR {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;};
int main()
{
    int result_of_running = 0;
//Тест #1: создание массива, вставка элементов, их получение, удаление массива
    ARRAY array = create_array();        if (array == NULL)  ERROR     //Создание массива
    int el = 1;                        
    int * res_el;
    res_el = get(array,10);				 if (res_el != NULL) ERROR
    int result = insert(array,0,&el);    if (result != 0)    ERROR     //Вставка элемента el в array[0]
    res_el = get(array,0);               if (res_el == NULL) ERROR     //"Вытаскивание" элемента 0 из массива. Если элемента нет, это хреново
                                         if (el != *res_el)  ERROR     //"Вытаскивание" чего-то другого - тоже не айс
    result = destroy_array(array);       if (result == -1)   ERROR
//    result = destroy_array(array);       if (result != -1)   ERROR     //Должно возвращаться -1. Мы уже почистили этот массив. 
    array = create_array();              if (array == NULL)  ERROR     //Массив должен создаться без проблем
    //Все то же самое, что и выше - должно работать нормально
    el = 10;
    result = insert(array,1,&el);        if (result != 0)    ERROR     //Вставка элемента el в array[1]
    res_el = get(array,1);               if (res_el == NULL) ERROR     //"Вытаскивание" элемента 0 из массива. Если элемента нет, это хреново
                                         if (el != *res_el)  ERROR     //"Вытаскивание" чего-то другого - тоже не айс
    result = destroy_array(array);       if (result == -1)   ERROR
 //  result = destroy_array(array);       if (result != -1)   ERROR     //Должно возвращаться -1. Мы уже почистили этот массив. 
    array = create_array();              if (array == NULL)  ERROR 
    result = insert(array,-1,&el);       if (result == 0)    ERROR     //Ожидается ошибка. Нет отрицательных индексов.
    res_el = get(array,-1);              if (res_el != NULL) ERROR     //То же
    result = destroy_array(array);       if (result == 0)    ERROR     //Ожидается ошибка. В массив мы ничего не положили.
//    result = destroy_array(NULL);		 if (result == 0) 	 ERROR 	   //А что, надо же бранч проверить

//Тест #2: сортировка массива. Задача: ввести массив, отсортировать и убедиться, что он отсортирован.
    array = create_array();              if (array == NULL)  ERROR 
    srand(time(NULL));
    int max_index = -1,i;
    float num[100];
    for (i = 0; i < 100; i++)
    {
        num[i] = rand() % 100;
        result = insert(array,i,&num[i]);if (result != 0)    ERROR
        if (max_index < i) max_index = i;
    }
    float * element;
    // Cортировка. Без извращений. Просто пузырьком.
    float * prev, * cur, * tmp;
    int j;
    for (i = 0; i < 100; i++)
    {
        for (j = 1; j < 100; j++)
        {
            cur = get(array,j);          if (cur == NULL)    ERROR
            prev = get(array,j-1);       if (prev == NULL)   ERROR
            if (* prev > * cur)
            {
               result = insert(array, j - 1, cur);if (result != 0)    ERROR
               insert(array, j, prev);   if (result != 0)    ERROR
            }
        }
    }
    for (i = 1; i < 100; i++)
    {
        prev = get(array,i-1);           if (prev == NULL)   ERROR
        element = get(array,i);          if (element == NULL) ERROR
                                         if (!(*prev <= *element)) ERROR   //Массив не отсортирован нормально .
    }
    result = destroy_array(array);       if (result == -1)   ERROR
//Тест #3. Работа с несколькими массивами.
    ARRAY array1 = create_array();		 if (array == NULL)  ERROR
    array = create_array();				 if (array == NULL)  ERROR
    for (i = 0; i < 100; i++)
    {
        num[i] = rand() % 100;
        result = insert(array1,i,&num[i]); if (result != 0)  ERROR
    }
    array = array1; 
    for (i = 0; i < 100; i++)
    {
    	element = get(array,i);
    	prev = get(array1,i);			  if (prev != element) ERROR
    }
    result = destroy_array(array1);		  if (result == -1)  ERROR
 //   result = destroy_array(array);		  if (result != -1)  ERROR
 
//Тест #4. Испытание дерева на прочность. Списки вряд ли пострадают.
    //Тут вставляются элементы слева и справа, по-разному 
    array = create_array();
    num[1] = 1;
    num[2] = 2;
    float number = 3;
    float * result_number;
    result = insert(array,3,&num[1]);	if (result != 0)    	 ERROR
    result = insert(array,1,&num[2]);	if (result != 0)     	 ERROR
    result_number = get(array,3);		if (*result_number != 1) ERROR
    result_number = get(array,1);	    if (*result_number != 2) ERROR
    result = insert(array,2,&number);	if (result != 0)     	 ERROR
    result_number = get(array,2);		if (*result_number != 3) ERROR
    result = insert(array,0,&number);	if (result != 0)     	 ERROR
    result_number = get(array,0);		if (*result_number != 3) ERROR
    result = insert(array,4,&number);	if (result != 0)     	 ERROR
    result = insert(array,4,&num[2]);	if (result != 0)     	 ERROR
    result_number = get(array,4);		if (*result_number != 2) ERROR
    result = insert(array,5,&number);	if (result != 0)     	 ERROR
    result = insert(array,3,&num[2]);	if (result != 0)     	 ERROR

    result = destroy_array(array);      if (result == -1)     	 ERROR
//Тест #5. Внесем немного случайности
    array = create_array();
    float double_array[100];
    for (i = 0; i < 100; i++)
    {
    	double_array[i] = (float)(rand() % 10000)/100;
    }
    for (i = 0; i < 90; i++)
    {
    	int index = rand() % 100;
    	int value = rand() % 100; //Индекс некоего элемента из double_array
    	result = insert(array,index,&double_array[value]); if (result != 0) ERROR
    	element = get(array,index);						   
    	if (element != &double_array[value]) ERROR //Оно конечно наивно полагать, что за 2 операции что-то изменится, но вдруг...
    }
	for (i = 0; i < 110; i++)
	{
		element = get(array,i);
	}
	for (i = 0; i < 10; i++)
	{
		result = insert(array,i,NULL);		if (result == -1) ERROR
	}
	result = destroy_array(array);		if (result == -1) ERROR
    return result_of_running;

}
