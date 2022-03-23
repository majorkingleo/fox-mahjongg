/*
 * FXRadioGroup.cc
 *
 *  Created on: 23.03.2022
 *      Author: martin
 */
#include "FXRadioGroup.h"
#include <iostream>

FXRadioGroup::SavePoint::SavePoint( SavePoint * other )
: current_checked_element( other->current_checked_element ),
  parent( other->parent )
{
	other->current_checked_element = 0;
	delete other;
}


FXRadioGroup::SavePoint & FXRadioGroup::SavePoint::operator=( SavePoint & other )
{
	current_checked_element = other.current_checked_element;
	parent                  = other.parent;

	other.current_checked_element = 0;

	return *this;
}

void FXRadioGroup::SavePoint::rollback()
{
	if( !current_checked_element ) {
		return;
	}

	parent->setCheck( current_checked_element );
}

void FXRadioGroup::SavePoint::commit()
{
	current_checked_element  =0;
}

FXRadioGroup::FXRadioGroup()
: elements(),
  current_checked_element(0)
{

}


void FXRadioGroup::setCheck( FXMenuRadio *ele )
{
	for( FXMenuRadio *other : elements ) {
		if( other != ele ) {
			other->setCheck( false );
		}
	}

	std::cout << "checking: " << ele->getText().text() << std::endl;

	current_checked_element = ele;
	ele->setCheck( true );
}

FXRadioGroup::SavePoint* FXRadioGroup::getSavePoint()
{
	return new SavePoint( this );
}

FXMenuRadio* FXRadioGroup::getChecked() const
{
	return current_checked_element;
}
