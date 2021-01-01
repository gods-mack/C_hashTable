
#include<stdio.h>


struct table_item{
	char *key;
	char *data;
	
};

struct h_table{
	int size;
	int count;
	struct table_item **items;
};



static struct table_item* new_table_item(const char *k,const char *d);
static struct h_table* new_h_table(void);

static void delete_table_item(struct table_item *it);
static void delete_table(struct h_table *tb);

static int hash_fucntion(const char*,const int a,const int m);
static int double_hashing(const char*,const int m,const int i);

static void insert_hash(struct h_table *table,const char *key, const char *data);
static char *search_hash(struct h_table *tb,const char *k);



