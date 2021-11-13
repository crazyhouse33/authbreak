#ifndef XXX_DATA_H_GUARD_XXX
#define XXX_DATA_H_GUARD_XXX

// This represent the structured informations recolted by all the attacks. Thoses shared infos are updated until no existing attack use it

typedef struct Shared_data{
	short* subscribers; // describe how many attacks need wich part
}Shared_data;

typedef enum Data_structure {
	RUNSTAT_TREE
} Data_structure;

void put(Shared_data* data, char** points);
void unregister(Shared_data* data, Data_structure* structures);

#endif

