#include <stdio.h>
#include "../array.h"
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main()
{
//Тест #1: создание массива, вставка элементов, их получение, удаление массива
    ARRAY array = create_array();                       assert(array != NULL);   //Создание массива
    int el = 1;                        
    int result = insert(array,0,&el);                   assert(result == 0);     //Вставка элемента el в array[0]
    int * res_el;
    res_el = get(array,0);                              assert(res_el != NULL);  //"Вытаскивание" элемента 0 из массива. Если элемента нет, это хреново
                                                        assert(el == *res_el);   //"Вытаскивание" чего-то другого - тоже не айс
    result = destroy_array(array);                      assert(result != -1);
    result = destroy_array(array);                      assert(result == -1);    //Должно возвращаться -1. Мы уже почистили этот массив. 
    array = create_array();                             assert(array != NULL);   //Массив должен создаться без проблем
    //Все то же самое, что и выше - должно работать нормально
    el = 10;
    result = insert(array,1,&el);                       assert(result == 0);     //Вставка элемента el в array[1]
    res_el = get(array,1);                              assert(res_el != NULL);  //"Вытаскивание" элемента 0 из массива. Если элемента нет, это хреново
                                                        assert(el == *res_el);   //"Вытаскивание" чего-то другого - тоже не айс
    result = destroy_array(array);                      assert(result != -1);
    result = destroy_array(array);                      assert(result == -1);    //Должно возвращаться -1. Мы уже почистили этот массив. 
    array = create_array();                             assert(array != NULL); 
    result = insert(array,-1,&el);                      assert(result != 0);     //Ожидается ошибка. Нет отрицательных индексов.
    res_el = get(array,-1);                             assert(res_el == NULL);  //То же
    result = destroy_array(array);                      assert(result != 0);     //Ожидается ошибка. В массив мы ничего не положили.
//Тест #2: сортировка массива. Задача: ввести массив, отсортировать и убедиться, что он отсортирован.
    array = create_array();                             assert(array != NULL); 
    srand(time(NULL));
    int max_index = -1,i;
    float num[100];
    for (i = 0; i < 100; i++)
    {
        num[i] = rand() % 100;
        result = insert(array,i,&num[i]);               assert(result == 0);
        if (max_index < i) max_index = i;
    }
    float * element;
    //Теперь сортировка. Без извращений. Просто пузырьком.
    float * prev, * cur, * tmp;
    int j;
    for (i = 0; i < 100; i++)
    {
        for (j = 1; j < 100; j++)
        {
            cur = get(array,j);                         assert(cur != NULL);
            prev = get(array,j-1);                      assert(prev != NULL);
            if (* prev > * cur)
            {
               result = insert(array, j - 1, cur);      assert(result == 0);
               insert(array, j, prev);                  assert(result == 0);
            }
        }
    }
    for (i = 1; i < 100; i++)
    {
        prev = get(array,i-1);                          assert(prev != NULL);
        element = get(array,i);                         assert(element != NULL);
                                                        assert(*prev <= *element);   //Если это условие не выполнено, то массив не был нормально отсортирован.
    }
    result = destroy_array(array);                      assert(result != -1);
//Тест #3. Работа с несколькими массивами.
    ARRAY array1 = create_array();						assert(array != NULL);
    array = create_array();								assert(array != NULL);
    for (i = 0; i < 100; i++)
    {
        num[i] = rand() % 100;
        result = insert(array1,i,&num[i]);               assert(result == 0);
    }
    array = array1; //Ох-хо-хо, а я извращенец
    for (i = 0; i < 100; i++)
    {
    	element = get(array,i);
    	prev = get(array1,i);							 assert(prev == element);
    }
    result = destroy_array(array1);						 assert(result != -1);
    result = destroy_array(array);						 assert(result == -1);
//Тест #4. Большие числа. Очень большие.
    array = create_array();
    long long index,k;
    /*
    float big_num = 1239.761210;
    for (k = 0; k < 100001; k++)
    {
    	result = insert(array,k,&big_num);				assert(result == 0);
    	//printf("%lld\n",k);
    }
    int time1 = time();
    element = get(array,100000);						
    int time2 = time();
    printf("%d\n",time2-time1);
    */

    result = destroy_array(array);

}
