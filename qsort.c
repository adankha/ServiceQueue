#include <stdio.h>
#include "list.h"

void qsort1(LIST* lst){

  if(lst_length(lst) <= 1)
     return;

  ElemType pivot = lst_pop_front(lst);
  LIST* pivotList = lst_create();
  lst_push_front(pivotList, pivot);

  LIST* lst2 = lst_filter_leq(lst, pivot);

  qsort1(lst);
  qsort1(lst2);

  lst_concat(lst2, pivotList);
  lst_concat(lst2, lst);
  lst_concat(lst, lst2);

}

int main(){

ElemType userVal;

printf("Please enter a set of integers.\n");
int checker;

LIST* lst = lst_create();

while (1){

   checker = scanf("%i", &userVal);
   if (checker == EOF || checker == 0)
    break;
   lst_push_back(lst, userVal);
}
printf("The list before the quick sort: \n");
lst_print(lst);
printf("The list after the quick sort: \n");
qsort1(lst);
lst_print(lst);
lst_free(lst);

return 0;
}

