#include <stdio.h>
#include "../array.h"
#include <assert.h>
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

}
