/*
 * builtin_layouts.cc
 *
 *  Created on: 27.03.2022
 *      Author: martin
 */
#include "builtin_layouts.h"
#include "data_builtin_layouts.h"

std::map<std::string,BuiltInLayoutData> getBuildInLayoutData()
{
	std::map<std::string,BuiltInLayoutData> res;

	res["Arena"] 		= BuiltInLayoutData( "Arena", 		builtin_layout_arena );
	res["Arrow"] 		= BuiltInLayoutData( "Arrow", 		builtin_layout_arrow );
	res["Boar"] 		= BuiltInLayoutData( "Boar", 		builtin_layout_boar );
	res["Bridge"]		= BuiltInLayoutData( "Bridge", 		builtin_layout_bridge );
	res["Ceremonial"] 	= BuiltInLayoutData( "Ceremonial", 	builtin_layout_ceremonial );
	res["Deepwell"] 	= BuiltInLayoutData( "Deepwell", 	builtin_layout_deepwell );
	res["Default"] 		= BuiltInLayoutData( "Default", 	builtin_layout_default );
	res["Dog"] 			= BuiltInLayoutData( "Dog", 		builtin_layout_dog );
	res["Dragon"] 		= BuiltInLayoutData( "Dragon", 		builtin_layout_dragon );
	res["Farandole"] 	= BuiltInLayoutData( "Farandole", 	builtin_layout_farandole );
	res["Hare"] 		= BuiltInLayoutData( "Hare", 		builtin_layout_hare );
	res["Horse"] 		= BuiltInLayoutData( "Horse", 		builtin_layout_horse );
	res["Hourglass"] 	= BuiltInLayoutData( "Hourglass", 	builtin_layout_hourglass );
	res["Monkey"] 		= BuiltInLayoutData( "Monkey", 		builtin_layout_monkey );
	res["Ox"] 			= BuiltInLayoutData( "Ox", 			builtin_layout_ox );
	res["Papillon"] 	= BuiltInLayoutData( "Papillon", 	builtin_layout_papillon );
	res["Ram"] 			= BuiltInLayoutData( "Ram", 		builtin_layout_ram );
	res["Rat"] 			= BuiltInLayoutData( "Rat", 		builtin_layout_rat );
	res["Rooster"] 		= BuiltInLayoutData( "Rooster", 	builtin_layout_rooster );
	res["Schoon"] 		= BuiltInLayoutData( "Schoon", 		builtin_layout_schoon );
	res["Snake"] 		= BuiltInLayoutData( "Snake", 		builtin_layout_snake );
	res["Theater"] 		= BuiltInLayoutData( "Theater", 	builtin_layout_theater );
	res["Tiger"] 		= BuiltInLayoutData( "Tiger", 		builtin_layout_tiger );
	res["Wedges"] 		= BuiltInLayoutData( "Wedges", 		builtin_layout_wedges );



	return res;
}
