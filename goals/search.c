#include <libtcod.h>
#include <stdlib.h>
#include <stdio.h>
#include "goals/search.h"
#include "goals/pickup_item.h"
#include "goals/move.h"
#include "entity.h"
#include "item.h"
#include "util.h"

static bool search_goal(goal* g, entity* e, TCOD_list_t params)
{
	item_type type = (item_type)TCOD_list_get(params,0);
	int how_many = (long)TCOD_list_get(params,1);
	int count = entity_has_item_type(e,type);
	if(count >= how_many) return true;
	
	foreach(item,e->seen_items)
	{
		item* i = *itr;
		if(i->type == type)
		{
			entity_add_goal(e,goal_new_pickup_item(e,i));
			return false;
		}
	}

	entity_add_goal(e,goal_new_move(e,e->x+5*(-1+rand()%3),e->y+5*(-1+rand()%3)));
	return false;
}

goal* goal_new_search(struct entity* owner, item_type type, int how_many)
{
	goal* g = goal_new(owner,&search_goal,NULL,NULL,type,how_many,NULL);
	sprintf(g->name,"search: %s x%d",item_names[type],how_many);
	return g;
}
