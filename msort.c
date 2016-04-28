#include <stdio.h>
#include "list.h"


void msort(LIST* lst){

 if(lst_length(lst) <= 1)
     return;

 LIST* lst2 = lst_prefix(lst, lst_length(lst)/2);
 msort(lst);
 msort(lst2);

 lst_merge_sorted(lst, lst2);
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
printf("The list before the merge sort: \n");
lst_print(lst);
printf("The list after the merge sort: \n");
msort(lst);
lst_print(lst);
lst_free(lst);


return 0;
}
