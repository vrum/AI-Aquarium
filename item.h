#ifndef ITEM_H
#define ITEM_H

#include <libtcod.h>

struct entity;
struct map;
struct item;

typedef void (*item_func)(struct item* item, TCOD_list_t params);
typedef struct item* (*item_constructor)(int x, int y);

typedef enum item_type
{
	// Make an enum entry for each item type.
#define DEFINE_ITEM(name,char,colour,recipe...) ITEM_##name,
#include "items.def"
#undef DEFINE_ITEM
	NUM_ITEM_TYPES
} item_type;

typedef struct item
{
	int x; // Position in the map
	int y;
	struct map* host_map;
	struct entity* owner;

	item_type type;
	item_func use_effect;
	
	TCOD_color_t color; // Colour to draw with
	char c; // The character to represent the item
} item;

#define MAX_RECIPE_COMPONENTS 8
extern item_type recipes[][MAX_RECIPE_COMPONENTS];
extern item_constructor item_constructors[NUM_ITEM_TYPES];
extern const char* item_names[NUM_ITEM_TYPES];

item* item_new(const char* name, int x, int y, char c, TCOD_color_t color, item_type type, item_func effect);
void item_delete(item* i);

void item_set_map(item* i, struct map* m);
void item_set_owner(item* i, struct entity* e);

// Define a "new" function for each item type.
#define DEFINE_ITEM(name,char,colour,recipe...) item* item_new_##name(int x, int y);
#include "items.def"
#undef DEFINE_ITEM

#endif
