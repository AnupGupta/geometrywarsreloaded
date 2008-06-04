/**********************************************
*  Macros:    BindFunc
*  Desc:      Typedefs a boost::bind so 
*             that it can be used as so:
*             ///////////////////////////
*			  BindFunc(class, func, object)
*			  ///////////////////////////
*  Macros:    Callback
*  Desc:      Typedefs a boost::function so 
*             that it can be used as so:
*             ///////////////////////////
*			  Callback(signature) e.g. Callback(void (void)) func
*			  ///////////////////////////
*  Author:    Vaios Kalpias-Ilias (C) 2008-2009
***********************************************/

#ifndef FUNCTIONBIND_H
#define FUNCTIONBIND_H

#include <boost/bind.hpp>
#include <boost/function.hpp>

#define Callback(signature) boost::function<signature> 
#define BindFunc(className, funcName, object) boost::bind(&className::funcName, object)
#define BindFuncOneArg(className, funcName, object) boost::bind(&className::funcName, object, _1)
#define BindFuncTwoArg(className, funcName, object) boost::bind(&className::funcName, object, _1, _2)


#endif
