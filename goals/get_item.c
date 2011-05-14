#include <stdio.h>
#include "goals/get_item.h"
#include "goals/move.h"
#include "entity.h"
#include "item.h"

/* static bool pre_get_item_goal(entity* e, TCOD_list_t params) */
/* { */
/* 	return true; */
/* } */

static bool get_item_goal(entity* e, TCOD_list_t params)
{
	item* i = TCOD_list_get(params,0);
	if(i->host_map == e->host_map && (e->x == i->x && e->y == i->y))
	{
		entity_get_item(e,i);
	}
	// I feel like there should be a way to convey complete failure of this goal.
	return true;
}

/* static bool post_get_item_goal(entity* e, TCOD_list_t params) */
/* { */
/* 	return true; */
/* } */

goal* goal_new_get_item(entity* owner, item* item)
{
	goal* g = goal_new(owner,NULL,&get_item_goal,NULL,item,NULL);
	goal_add_subgoal(g,goal_new_move(owner,item->x,item->y));
	return g;
}
