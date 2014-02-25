/*
Members of the group:
Афанасьев Филипп
Лысенко Павел
Свихнушина Екатерина
Степанов Игорь
Туркин Роман
*/

#define ARRAY void *
#define DATA void *
#define INDEX long


ARRAY create_array();
//NULL in case of allocating problems

int insert(ARRAY, INDEX, DATA);
//if DATA = NULL it equals to deleting element, 0 in case of success

DATA get(ARRAY, INDEX);
//returns NULL in case of failure

int destroy_array(ARRAY);
//-1 if there is no such array
