#include "shared_data.h"
#include <stdbool.h>

static bool need_update(Shared_data* data, Data_structure structure){
	return data->subscribers[structure] >= 0;
}

static void update_runstat_tree(char** points){};

void put(Shared_data* data, char** points){
	if (need_update(data, RUNSTAT_TREE))
		update_runstat_tree(points);
}

void unregister(Shared_data* data, Data_structure* structures){
	int i=0;
	Data_structure structure;
	while (  structure = structures[i])
		data->subscribers[structure]--;
}





