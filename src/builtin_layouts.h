/*
 * builtin_layouts.h
 *
 *  Created on: 27.03.2022
 *      Author: martin
 */

#ifndef SRC_BUILTIN_LAYOUTS_H_
#define SRC_BUILTIN_LAYOUTS_H_

#include <fx.h>
#include <map>

struct BuiltInLayoutData
{
	std::string  name;	// name of the map
	std::string  data;	// file contente
	int			 id;		// user defined data
	FXMenuRadio *mc;

	BuiltInLayoutData()
	: name(),
	  data(),
	  id(0),
	  mc(0)
	{}

	BuiltInLayoutData( const std::string & name,
					   const std::string & data )
	: name( name ),
	  data( data ),
	  id( 0 ),
	  mc( 0 )
	{}
};


std::map<std::string,BuiltInLayoutData> getBuildInLayoutData();


#endif /* SRC_BUILTIN_LAYOUTS_H_ */
