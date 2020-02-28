#include "common.h"

void p(char *fmt, ... ){
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  Serial.println(buf);
}

int mod (int a, int b)
{
   if(a >= 0 && a < b) return a;

   if(b < 0) return -mod(-a, -b);   
   
   int ret = a % b;
   if(ret < 0) ret+=b;
   
   return ret;
}
