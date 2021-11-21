#include "STC89xx.h"     // Official header from STC-ISP for STC89xx / STC90xx

#define led15 P15
#define led17 P17

void main()
{
     int n;
     led15 = 0;  // LED on
     led17 = 1;  // LED off
     for (n = 0; n < 10000; n++); // waste some cycles
     led15 = 1;  // LED off
     led17 = 0;  // LED off
     for (n = 0; n < 10000; n++); // waste some cycles
}