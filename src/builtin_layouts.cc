/*
 * builtin_layouts.cc
 *
 *  Created on: 27.03.2022
 *      Author: martin
 */
#include "builtin_layouts.h"
#include "data_builtin_layouts.h"

#ifdef ENABLE_NLS
#	include <libintl.h>
#	include <locale.h>
#endif

#ifdef ENABLE_NLS
#	define _(STRING) gettext(STRING)
#else
#	define _(STRING) (STRING)
#endif

std::map<std::string,BuiltInLayoutData> getBuildInLayoutData()
{
	std::map<std::string,BuiltInLayoutData> res;

	res["Arena"] 		= BuiltInLayoutData( _("Arena"), 		builtin_layout_arena );
	res["Arrow"] 		= BuiltInLayoutData( _("Arrow"), 		builtin_layout_arrow );
	res["Boar"] 		= BuiltInLayoutData( _("Boar"), 		builtin_layout_boar );
	res["Bridge"]		= BuiltInLayoutData( _("Bridge"), 		builtin_layout_bridge );
	res["Ceremonial"] 	= BuiltInLayoutData( _("Ceremonial"), 	builtin_layout_ceremonial );
	res["Deepwell"] 	= BuiltInLayoutData( _("Deepwell"), 	builtin_layout_deepwell );
	res["Default"] 		= BuiltInLayoutData( _("Default"), 		builtin_layout_default );
	res["Dog"] 			= BuiltInLayoutData( _("Dog"), 			builtin_layout_dog );
	res["Dragon"] 		= BuiltInLayoutData( _("Dragon"), 		builtin_layout_dragon );
	res["Farandole"] 	= BuiltInLayoutData( _("Farandole"), 	builtin_layout_farandole );
	res["Hare"] 		= BuiltInLayoutData( _("Hare"), 		builtin_layout_hare );
	res["Horse"] 		= BuiltInLayoutData( _("Horse"), 		builtin_layout_horse );
	res["Hourglass"] 	= BuiltInLayoutData( _("Hourglass"), 	builtin_layout_hourglass );
	res["Monkey"] 		= BuiltInLayoutData( _("Monkey"), 		builtin_layout_monkey );
	res["Ox"] 			= BuiltInLayoutData( _("Ox"), 			builtin_layout_ox );
	res["Papillon"] 	= BuiltInLayoutData( _("Papillon"), 	builtin_layout_papillon );
	res["Ram"] 			= BuiltInLayoutData( _("Ram"), 			builtin_layout_ram );
	res["Rat"] 			= BuiltInLayoutData( _("Rat"), 			builtin_layout_rat );
	res["Rooster"] 		= BuiltInLayoutData( _("Rooster"), 		builtin_layout_rooster );
	res["Schoon"] 		= BuiltInLayoutData( _("Schoon"), 		builtin_layout_schoon );
	res["Snake"] 		= BuiltInLayoutData( _("Snake"), 		builtin_layout_snake );
	res["Theater"] 		= BuiltInLayoutData( _("Theater"), 		builtin_layout_theater );
	res["Tiger"] 		= BuiltInLayoutData( _("Tiger"), 		builtin_layout_tiger );
	res["Wedges"] 		= BuiltInLayoutData( _("Wedges"), 		builtin_layout_wedges );



	return res;
}
