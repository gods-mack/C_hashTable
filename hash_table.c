
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "hash_table.h"

#define PRIME_CONST1 151
#define PRIME_CONST2 163


/*
define and intialize our table items
and saves a copy of the strings k and v in 
the new chunk of memory. The function is marked as 
static because it will only ever be called by code 
internal to the hash table

*/
static struct table_item *new_table_item(const char *_key,const char *_data) {

	struct table_item  *item = malloc(sizeof(struct table_item*));
	item->key  = strdup(_key);
	item->data = strdup(_data);

	return item;
}


// create a new hash_table with size 53 (for now indexes.
static struct h_table* new_h_table(void) {

	struct h_table *table = malloc(sizeof(struct h_table*));
	table->size = 53; // for now
	table->count = 0;
	//                              53 *  sizeof(itembox)
	table->items = calloc((size_t)table->size,sizeof(struct table_item*));

	return table;	

}

// delete or free a perticular table itembox
static void delete_table_item(struct table_item *i){
	free(i->key);
	free(i->data);
	free(i);
}

// delete or free a entire hash_table
static void delete_table(struct h_table *ht) {

	int i;
	for(i = 0; i < ht->size; i++) {
		struct table_item * it = ht->items[i];
		if(it != NULL) {
			delete_table_item(it);
		}
	}

	free(ht->items);
	free(ht);

}


/*
hash_function example

hash("cat", 151, 53)

hash = (151**2 * 99 + 151**1 * 97 + 151**0 * 116) % 53
hash = (2257299 + 14647 + 116) % 53
hash = (2272062) % 53
return hash = 5

*/

// m is total number of buckets or size of table
static int hash_function(const char* s,const int a,const int m) {

	long index = 0; int i ;

	const int len  = strlen(s);
	
	int p = len - 1;
	for(i = 0; i < len; i++) {

		index += (long)pow(a, len - (i+1)) * (int)s[i];
		index = index % m;
	}

	return (int)index;
}

static int double_hashing(const char *s,const int num_buckets,
						 const int attempts) {

	const int hash1 = hash_function(s,PRIME_CONST1,num_buckets);
	const int hash2 = hash_function(s,PRIME_CONST2,num_buckets);

	int index = (hash1 * (attempts * (hash2 + 1))) % num_buckets;

	return index;
}



static void insert_hash(struct h_table *table,const char *key,
	 			  const char *data) {

	struct table_item *it = new_table_item(key,data);
	int attempts = 0;
	const int num_buckets = 53;

	// find empty index
	int index;
	while(1){
	
		index = double_hashing(key,table->size,attempts);

		if(table->items[index] == NULL){ // found empty index
			break;
		}
		attempts++;
	}


	table->items[index] = it;
	table->count++;

}

static char *search_hash(struct h_table *table, const char *key) {

	int index = double_hashing(key,table->size,0);

	struct table_item *it = table->items[index];
	int i = 1;

	while(it != NULL) {

		if(strcmp(it->key, key) == 0) {
			return it->data;
		}
		index = double_hashing(key,table->size,i);
		it = table->items[index];
		i++;
	}

	return NULL;
}


// DELETtion
//do..
// 1.modify insert_hahs
// 2.modiy search_hahs

static table_item HT_DELETED_ITEM = {NULL, NULL};


void delete_hash(h_table* ht, const char* key) {

    int index = double_hahsing(key, ht->size, 0);
    table_item * item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    ht->count--;
}









/*

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

}*/