#include <stdio.h>
#include <stdlib.h>

#include "deq.h"

static void testInsertHead(){
	Deq q = deq_new();
	char val = 'e';
	char *point = &val;
	Data d = point;
	deq_head_put(q,d);
	if(1 == deq_len(q)){
		printf("Test Head has passed\n");
	}
	else{
		printf("Test Head has failed\n");
	}
	deq_head_get(q);
	deq_del(q,0);
}

static void testInsertTail(){
	Deq q = deq_new();
	char val = 'f';
	char *point = &val;
	Data d = point;
	deq_tail_put(q,d);
	if(1 == deq_len(q)){
		printf("Test Tail has passed\n");
	}
	else{
		printf("Test Tail has failed\n");
	}
	deq_tail_get(q);
	deq_del(q,0);
}
static void testInsertHead2(){
	Deq q = deq_new();
	char val = 'd';
	char val1 = 'p';
	char *point1 = &val;
	char *point2 = &val1;
	Data d1 = point1;
	Data d2 = point2;
	deq_head_put(q,d1);
	deq_head_put(q,d2);
	if(2 == deq_len(q)){
		printf("Test Head 2 has passed\n");
		char *s=deq_str(q,0);
		printf("%s\n", s);
		free(s);
	}
	else{
		printf("Test Head 2 has failed\n");
	}
	deq_head_get(q);
	deq_del(q,0);

}

static void testIth(){
	Deq q = deq_new();
	char val = 's';
	char *point = &val;
	Data d = point;
	deq_head_put(q,d);
	Data goal = deq_head_ith(q,0);
	if ( goal == d){
		printf("Test Ith successful\n");
	}
	else{
		printf("Test Ith Failed\n");
	}
	deq_head_get(q);
	deq_del(q,0);

}

static void testRem() {
    Deq q = deq_new();
    char val = 's';
    char *point = &val;
    Data d = point;
    deq_head_put(q, d);
    Data goal = deq_head_rem(q, d);
    if (goal == d)
        printf("Test rem successful\n");
    else
        printf("Test rem failed\n");
    deq_del(q, 0);
}

int main(){
  Deq q=deq_new();

  char *s=deq_str(q,0);
  printf("%s\n",s);
  free(s);
  deq_del(q,0);

  testInsertHead();
  testInsertTail();
  testInsertHead2();
  testIth();
  testRem();
  return 0;
}