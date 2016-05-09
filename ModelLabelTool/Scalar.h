/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 17
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#ifndef SCALAR_H_
#define SCALAR_H_
#include "stdafx.h"

namespace cv{
	typedef struct _Scalar{
		double val[4];
	} Scalar;
}
#endif