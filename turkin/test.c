#include <stdio.h>
#include "../array.h"
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main()
{
    int result_of_running = 0;
//Тест #1: создание массива, вставка элементов, их получение, удаление массива
    ARRAY array = create_array();        if (array == NULL)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}   //Создание массива
    int el = 1;                        
    int result = insert(array,0,&el);    if (result != 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}     //Вставка элемента el в array[0]
    int * res_el;
    res_el = get(array,0);               if (res_el == NULL) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}  //"Вытаскивание" элемента 0 из массива. Если элемента нет, это хреново
                                         if (el != *res_el)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}   //"Вытаскивание" чего-то другого - тоже не айс
    result = destroy_array(array);       if (result == -1)   {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = destroy_array(array);       if (result != -1)   {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}    //Должно возвращаться -1. Мы уже почистили этот массив. 
    array = create_array();              if (array == NULL)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}   //Массив должен создаться без проблем
    //Все то же самое, что и выше - должно работать нормально
    el = 10;
    result = insert(array,1,&el);        if (result != 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}     //Вставка элемента el в array[1]
    res_el = get(array,1);               if (res_el == NULL) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}  //"Вытаскивание" элемента 0 из массива. Если элемента нет, это хреново
                                         if (el != *res_el)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}   //"Вытаскивание" чего-то другого - тоже не айс
    result = destroy_array(array);       if (result == -1)   {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = destroy_array(array);       if (result != -1)   {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}    //Должно возвращаться -1. Мы уже почистили этот массив. 
    array = create_array();              if (array == NULL)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;} 
    result = insert(array,-1,&el);       if (result == 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}     //Ожидается ошибка. Нет отрицательных индексов.
    res_el = get(array,-1);              if (res_el != NULL) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}  //То же
    result = destroy_array(array);       if (result == 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}     //Ожидается ошибка. В массив мы ничего не положили.

//Тест #2: сортировка массива. Задача: ввести массив, отсортировать и убедиться, что он отсортирован.
    array = create_array();              if (array == NULL)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;} 
    srand(time(NULL));
    int max_index = -1,i;
    float num[100];
    for (i = 0; i < 100; i++)
    {
        num[i] = rand() % 100;
        result = insert(array,i,&num[i]);if (result != 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
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
            cur = get(array,j);          if (cur == NULL)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
            prev = get(array,j-1);       if (prev == NULL)   {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
            if (* prev > * cur)
            {
               result = insert(array, j - 1, cur);if (result != 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
               insert(array, j, prev);   if (result != 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
            }
        }
    }
    for (i = 1; i < 100; i++)
    {
        prev = get(array,i-1);           if (prev == NULL)   {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
        element = get(array,i);          if (element == NULL) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
                                         if (!(*prev <= *element)) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}   //Если это условие не выполнено, то массив не был нормально отсортирован.
    }
    result = destroy_array(array);       if (result == -1)   {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
//Тест #3. Работа с несколькими массивами.
    ARRAY array1 = create_array();		 if (array == NULL)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    array = create_array();				 if (array == NULL)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    for (i = 0; i < 100; i++)
    {
        num[i] = rand() % 100;
        result = insert(array1,i,&num[i]);if (result != 0)    {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    }
    array = array1; 
    for (i = 0; i < 100; i++)
    {
    	element = get(array,i);
    	prev = get(array1,i);			  if (prev != element) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    }
    result = destroy_array(array1);		  if (result == -1)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = destroy_array(array);		  if (result != -1)  {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
 
//Тест #4. Испытание дерева на прочность. Списки вряд ли пострадают.
    array = create_array();
    num[1] = 1;
    num[2] = 2;
    float number = 3;
    float * result_number;
    result = insert(array,3,&num[1]);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = insert(array,1,&num[2]);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result_number = get(array,3);		if (*result_number != 1) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result_number = get(array,1);	    if (*result_number != 2) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = insert(array,2,&number);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result_number = get(array,2);		if (*result_number != 3) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = insert(array,0,&number);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result_number = get(array,0);		if (*result_number != 3) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = insert(array,4,&number);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = insert(array,4,&num[2]);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result_number = get(array,4);		if (*result_number != 2) {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = insert(array,5,&number);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    result = insert(array,3,&num[2]);	if (result != 0)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}

    result = destroy_array(array);      if (result == -1)     {printf("Error in %s on line %d\n",__FILE__,__LINE__); result_of_running = -1;}
    return result_of_running;
}
