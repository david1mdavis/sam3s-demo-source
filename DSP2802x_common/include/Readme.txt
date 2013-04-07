
August 3rd, 2010

Updated Jan 20, 2011:  Removed a reference to a coef table that caused the lib to not link with codegen 4.x. 

Preliminary IQmath Natural log function.

Two libraries are included:

(a) IQmathLog.lib: This build of the library can be linked with code built for fixed-point.
(b) IQmathLog_f32.lib: This build of the library can be linked with code built with the --float_support=fpu32 switch. 
    This can be useful for mixing IQmath with native floating-point code on devices with the C28x+FPU.

This library includes only the natural log function: 

_iq   _IQlog( _iq A)      ; Q = GLOBAL_Q

_iqN  _IQNlog( _iqN A)    ; Q = 1-29


Cycles: ~148 (includes call & return)
This function does not use a lookup table.


Example:

#include "IQmathLib.h"
#include "IQlog.h"

...

main()
{
    _iq x;
    _iq y;
    
    
....
   y = _IQ(1.5);  
   x = _IQlog(y);  // x =  0.405465108
   
   
}