/*
 * FXRadioGroup.h
 *
 *  Created on: 23.03.2022
 *      Author: martin
 */

#ifndef SRC_FXRADIOGROUP_H_
#define SRC_FXRADIOGROUP_H_

#include "fx.h"
#include <vector>
#include <map>

class FXRadioGroup
{
public:
	/** this acts like a smart pointer, to check and uncheck
	 * the correct radio label
	 */
	class SavePoint
	{
		FXMenuRadio* current_checked_element;
		FXRadioGroup* parent;

	public:
		SavePoint( FXRadioGroup* parent )
		: current_checked_element( parent->getChecked() ),
		  parent( parent )
		{}

		SavePoint( SavePoint *other );
		SavePoint( const SavePoint & other ) = delete;
		SavePoint & operator=( SavePoint & other );

		~SavePoint() {
			rollback();
		}

		void commit();
		void rollback();
	};

private:
	std::vector<FXMenuRadio*> elements;
	std::map<int,FXMenuRadio*> element_by_idx;
	FXMenuRadio* current_checked_element;

public:
	FXRadioGroup();

	void setCheck( FXMenuRadio *ele );

	void setCheck( int idx ) {
		FXMenuRadio* mc = get( idx );
		if( mc ) {
			setCheck( mc );
		}
	}

	FXMenuRadio *getChecked() const;

	void add( FXMenuRadio *ele, int idx = -1 ) {
		elements.push_back( ele );

		if( idx >= 0 ) {
			element_by_idx[idx] = ele;
		}
	}

	FXMenuRadio* get( int idx ) {
		return element_by_idx[idx];
	}

	SavePoint* getSavePoint();
};



#endif /* SRC_FXRADIOGROUP_H_ */
