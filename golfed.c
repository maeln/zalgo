#include <stdio.h>
#include <stdint.h>
typedef uint32_t t;
t x=1;
t r(){return(x=((x*0x21a7)%0x7fffffff));}
p(t c){char u[]={0xc0|((c>>6)&0x1f),0x80|(c&0x3f),0};fputs(u,stdout);}
main(c){while(~(c=getchar())){putc(c,stdout);t n=r()%6;while(n--){p(0x300+(r()%112));}}}
