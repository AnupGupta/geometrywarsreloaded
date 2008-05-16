/**********************************************
*  Macros:    SmartPointer
*  Desc:      Typedefs a boost::shared_ptr so 
*             that it can be used as so:
*             ///////////////////////////
*			  class A{}; SmartPointer(A);
*             APtr pA = ...
*			  ///////////////////////////
*			  Now pA is a smart pointer to an object A
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <boost/shared_ptr.hpp>

#define NAME2_HIDDEN(a,b) a ## b
#define NAME2(a,b) NAME2_HIDDEN(a,b)
#define SmartPointer(classname) typedef boost::shared_ptr<classname> NAME2(classname,Ptr);

#endif