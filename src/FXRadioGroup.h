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
	FXMenuRadio* current_checked_element;

public:
	FXRadioGroup();

	void setCheck( FXMenuRadio *ele );
	FXMenuRadio *getChecked() const;
	void add( FXMenuRadio *ele ) { elements.push_back( ele ); }

	SavePoint* getSavePoint();
};



#endif /* SRC_FXRADIOGROUP_H_ */
