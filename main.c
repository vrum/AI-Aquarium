#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libtcod.h>
#include "map.h"
#include "entity.h"
#include "util.h"
#include "goal.h"
#include "goals/nothing.h"
#include "goals/move.h"
#include "goals/explore.h"

int main (int argc, char* argv[])
{
	TCOD_console_init_root(80,60,"Test!",0,TCOD_RENDERER_GLSL);
	TCOD_sys_set_fps(30);

	map* m = map_new(80,60,'.');
	map_randomize(m,6);

	int num_entities = 5;
	for(int i = 0; i < num_entities; ++i)
	{
		int x, y;
		map_random_free_spot(m,&x,&y);
		entity* e = entity_new(x,y,'@',TCOD_color_RGB(rand()%255,rand()%255,rand()%255));
		map_add_entity(m,e);		
		
		goal* g = goal_new_move(e,3,3);
		goal_add_subgoal(g,goal_new_move(e,78,58));
		entity_add_goal(e,g);
	}

	int lookat = 0;
	entity* e = TCOD_list_get(m->entities,lookat);
	while(1)
	{		
		map_draw(e->known_map,NULL);
		foreach(entity,e->seen)
		{
			entity_draw(*itr,NULL);
		}
		foreach(entity,m->entities)
		{
			entity* e = *itr;
			entity_look(e);
			entity_do_goal(e);
		}
		TCOD_console_flush();
		TCOD_key_t key = TCOD_console_check_for_keypress(TCOD_KEY_PRESSED);
		if(key.c == 'q') { break; }
		if(key.c == 'n') { lookat = (lookat+1)%TCOD_list_size(m->entities);
			               e = TCOD_list_get(m->entities,lookat); }
	}
	map_delete(m);
}
