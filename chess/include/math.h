#pragma once

#define FLOAT_PRECISION 100

#define ABS(x)		( ((x) < 0)			?  (x)*(-1)		: (x)		)
#define DABS(x)		( ((x) < 0)			?  (x)			: (x)*(-1)	)
#define ROUND(x)	( ((int)(x) * FLOAT_PRECISION)%FLOAT_PRECISION > FLOAT_PRECISION/2 ? (int)(x)-1	: (int)(x)+1)
#define CEIL(x)		( ((int)(x) * FLOAT_PRECISION)%FLOAT_PRECISION > 0 ? (int)(x) : (int)(x)+1 )
#define FLOOR(x)	( (int)(x) )