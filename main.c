
#include<stdio.h>
#include<string.h>

#include "hash_table.h"

int main() {

	struct h_table *my_table = new_h_table();

	printf("enter five enteries\n");
	for(int i=0; i < 5; i++) {
		char key[100];
		char data[100];
		scanf("%s ",key);
		scanf("%s ",data);
		insert_hash(my_table,key,data);

	}

	char *find = "manish";
	char *data = search_hash(my_table,find);
	printf("data %s\n",data );

}