#ifndef _BOXTYPE_H_
#define _BOXTYPE_H_

#define _YX 0
#define _ZA 1
#define _TL 2
#define _XZ 3
#define _MB 4
#define _KUN 5
#define _QIU 6

#define _XY(x,y,w)  ((x)+(y)*(w))
#define _XY_X(i,w)  ((i)%(w))
#define _XY_Y(i,w)  ((i)/(w))
   
#endif