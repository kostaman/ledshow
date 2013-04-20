#line 1 "..\\sdio\\src\\s3cmci.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"
 
 
 





 






 









#line 34 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"


  
  typedef unsigned int size_t;    








 
 

 
  typedef struct __va_list __va_list;





   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 125 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 944 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"



 
#line 2 "..\\sdio\\src\\s3cmci.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"
 
 
 




 
 



 












  


 








#line 45 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


  
  typedef unsigned int size_t;










    



    typedef unsigned short wchar_t;  
#line 74 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { __int64 quot, rem; } lldiv_t;
    


#line 95 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"
   



 

   




 
#line 114 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) __int64 atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) __int64 strtoll(const char * __restrict  ,
                               char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned __int64 strtoull(const char * __restrict  ,
                                         char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 414 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 502 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 531 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"

extern __declspec(__nothrow) __pure int abs(int  );
   



 

extern __declspec(__nothrow) __pure div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __pure long int labs(long int  );
   



 




extern __declspec(__nothrow) __pure ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __pure __int64 llabs(__int64  );
   



 




extern __declspec(__nothrow) __pure lldiv_t lldiv(__int64  , __int64  );
   











 
#line 612 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"



 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __pure __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 



 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 866 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


 
#line 3 "..\\sdio\\src\\s3cmci.c"
#line 1 "..\\sdio\\inc\\reg_sdio.h"










 




#line 31 "..\\sdio\\inc\\reg_sdio.h"







#line 45 "..\\sdio\\inc\\reg_sdio.h"

#line 53 "..\\sdio\\inc\\reg_sdio.h"

#line 60 "..\\sdio\\inc\\reg_sdio.h"

#line 75 "..\\sdio\\inc\\reg_sdio.h"

 








#line 96 "..\\sdio\\inc\\reg_sdio.h"

#line 107 "..\\sdio\\inc\\reg_sdio.h"

#line 126 "..\\sdio\\inc\\reg_sdio.h"



#line 4 "..\\sdio\\src\\s3cmci.c"
#line 1 "..\\sdio\\inc\\type.h"





typedef char  S8;
typedef short	S16;
typedef int     S32;
typedef long long  S64;

typedef char   __s8;
typedef short  __s16;
typedef int   	  __s32;
typedef long long    __s64;


typedef unsigned char  U8;
typedef unsigned short	U16;
typedef unsigned int     U32;
typedef unsigned long  long   U64;




 
typedef unsigned long long   u64; 

typedef unsigned char   __u8;
typedef unsigned short  __u16;
typedef unsigned int   	 __u32;
typedef unsigned long long    __u64; 

typedef unsigned char 		uint8_t;
typedef unsigned short 		uint16_t;
typedef unsigned int     	uint32_t; 

typedef unsigned char 		int8_t;
typedef unsigned short 		int16_t;
typedef unsigned int     	int32_t;

typedef unsigned short 		__le16;
typedef unsigned int 		__le32;
typedef unsigned long long	__le64;

typedef unsigned short 		__be16;
typedef unsigned int		__be32;








#line 61 "..\\sdio\\inc\\type.h"











 

#line 108 "..\\sdio\\inc\\type.h"





#line 202 "..\\sdio\\inc\\type.h"


#line 212 "..\\sdio\\inc\\type.h"

#line 220 "..\\sdio\\inc\\type.h"

 



#line 233 "..\\sdio\\inc\\type.h"

#line 5 "..\\sdio\\src\\s3cmci.c"
#line 1 "..\\sdio\\inc\\common.h"
#line 1 "..\\main\\xxxconfig.h"














#line 4 "..\\sdio\\inc\\common.h"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdarg.h"
 
 
 





 









#line 26 "C:\\Keil\\ARM\\RV31\\INC\\stdarg.h"








 

 
 
  typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 






#line 118 "C:\\Keil\\ARM\\RV31\\INC\\stdarg.h"











 
#line 5 "..\\sdio\\inc\\common.h"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
 
 
 
 




 








 











#line 37 "C:\\Keil\\ARM\\RV31\\INC\\string.h"


  
  typedef unsigned int size_t;








extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 184 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 200 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 223 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 238 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 261 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 493 "C:\\Keil\\ARM\\RV31\\INC\\string.h"



 
#line 6 "..\\sdio\\inc\\common.h"
#line 7 "..\\sdio\\inc\\common.h"
#line 8 "..\\sdio\\inc\\common.h"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"
 
 
 
 





 






 







#line 32 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"






#line 46 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"

 
#line 56 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"

 
 









 
#line 78 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"





#line 130 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"

extern __declspec(__nothrow) __pure unsigned char **__rt_ctype_table(void);







    extern int (isalnum)(int  );

     





    extern int (isalpha)(int  );

     





    extern int (iscntrl)(int  );

     
     

 




    extern int (isdigit)(int  );

     

    extern int (isblank)(int  );
     
     
     





    extern int (isgraph)(int  );

     





    extern int (islower)(int  );

     





    extern int (isprint)(int  );

     
     





    extern int (ispunct)(int  );

     





    extern int (isspace)(int  );

     





    extern int (isupper)(int  );

     

 
 

__inline int __isxdigit_helper(int __t) { return (__t ^ (__t << 2)); }




    extern int (isxdigit)(int  );

     



extern int tolower(int  );
     
     

extern int toupper(int  );
     
     







#line 269 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"



 
#line 9 "..\\sdio\\inc\\common.h"
#line 10 "..\\sdio\\inc\\common.h"
#line 1 "..\\target\\system.h"



#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"














 

 



 
#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"














 

 







 
#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_conf.h"













 

 



 
#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_type.h"














 

 



 
 
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;   
typedef signed short const sc16;   
typedef signed char  const sc8;    

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed long  const vsc32;   
typedef volatile signed short const vsc16;   
typedef volatile signed char  const vsc8;    

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;   
typedef unsigned short const uc16;   
typedef unsigned char  const uc8;    

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;   
typedef volatile unsigned short const vuc16;   
typedef volatile unsigned char  const vuc8;    

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#line 73 "..\\STM32F10x_lib\\inc\\stm32f10x_type.h"

 
 
 



 
#line 22 "..\\STM32F10x_lib\\inc\\stm32f10x_conf.h"

 
 


 
 

 
 





 


 


 


 


 


 
#line 66 "..\\STM32F10x_lib\\inc\\stm32f10x_conf.h"

 


 



 


 


 
#line 90 "..\\STM32F10x_lib\\inc\\stm32f10x_conf.h"

 




 


 


 


 


 


 


 





 


 
#line 133 "..\\STM32F10x_lib\\inc\\stm32f10x_conf.h"

 
#line 141 "..\\STM32F10x_lib\\inc\\stm32f10x_conf.h"

 



 


 
#line 167 "..\\STM32F10x_lib\\inc\\stm32f10x_conf.h"



 
#line 27 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"
#line 28 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"
#line 1 "..\\STM32F10x_lib\\inc\\cortexm3_macro.h"













 

 



 
#line 22 "..\\STM32F10x_lib\\inc\\cortexm3_macro.h"

 
 
 
 
void __WFI(void);
void __WFE(void);
void __SEV(void);
void __ISB(void);
void __DSB(void);
void __DMB(void);
void __SVC(void);
u32 __MRS_CONTROL(void);
void __MSR_CONTROL(u32 Control);
u32 __MRS_PSP(void);
void __MSR_PSP(u32 TopOfProcessStack);
u32 __MRS_MSP(void);
void __MSR_MSP(u32 TopOfMainStack);
void __RESETPRIMASK(void);
void __SETPRIMASK(void);
u32 __READ_PRIMASK(void);
void __RESETFAULTMASK(void);
void __SETFAULTMASK(void);
u32 __READ_FAULTMASK(void);
void __BASEPRICONFIG(u32 NewPriority);
u32 __GetBASEPRI(void);
u16 __REV_HalfWord(u16 Data);
u32 __REV_Word(u32 Data);



 
#line 29 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"

 
 
 
 

 
typedef struct
{
  vu32 SR;
  vu32 CR1;
  vu32 CR2;
  vu32 SMPR1;
  vu32 SMPR2;
  vu32 JOFR1;
  vu32 JOFR2;
  vu32 JOFR3;
  vu32 JOFR4;
  vu32 HTR;
  vu32 LTR;
  vu32 SQR1;
  vu32 SQR2;
  vu32 SQR3;
  vu32 JSQR;
  vu32 JDR1;
  vu32 JDR2;
  vu32 JDR3;
  vu32 JDR4;
  vu32 DR;
} ADC_TypeDef;

 
typedef struct
{
  u32  RESERVED0;
  vu16 DR1;
  u16  RESERVED1;
  vu16 DR2;
  u16  RESERVED2;
  vu16 DR3;
  u16  RESERVED3;
  vu16 DR4;
  u16  RESERVED4;
  vu16 DR5;
  u16  RESERVED5;
  vu16 DR6;
  u16  RESERVED6;
  vu16 DR7;
  u16  RESERVED7;
  vu16 DR8;
  u16  RESERVED8;
  vu16 DR9;
  u16  RESERVED9;
  vu16 DR10;
  u16  RESERVED10; 
  vu16 RTCCR;
  u16  RESERVED11;
  vu16 CR;
  u16  RESERVED12;
  vu16 CSR;
  u16  RESERVED13[5];
  vu16 DR11;
  u16  RESERVED14;
  vu16 DR12;
  u16  RESERVED15;
  vu16 DR13;
  u16  RESERVED16;
  vu16 DR14;
  u16  RESERVED17;
  vu16 DR15;
  u16  RESERVED18;
  vu16 DR16;
  u16  RESERVED19;
  vu16 DR17;
  u16  RESERVED20;
  vu16 DR18;
  u16  RESERVED21;
  vu16 DR19;
  u16  RESERVED22;
  vu16 DR20;
  u16  RESERVED23;
  vu16 DR21;
  u16  RESERVED24;
  vu16 DR22;
  u16  RESERVED25;
  vu16 DR23;
  u16  RESERVED26;
  vu16 DR24;
  u16  RESERVED27;
  vu16 DR25;
  u16  RESERVED28;
  vu16 DR26;
  u16  RESERVED29;
  vu16 DR27;
  u16  RESERVED30;
  vu16 DR28;
  u16  RESERVED31;
  vu16 DR29;
  u16  RESERVED32;
  vu16 DR30;
  u16  RESERVED33; 
  vu16 DR31;
  u16  RESERVED34;
  vu16 DR32;
  u16  RESERVED35;
  vu16 DR33;
  u16  RESERVED36;
  vu16 DR34;
  u16  RESERVED37;
  vu16 DR35;
  u16  RESERVED38;
  vu16 DR36;
  u16  RESERVED39;
  vu16 DR37;
  u16  RESERVED40;
  vu16 DR38;
  u16  RESERVED41;
  vu16 DR39;
  u16  RESERVED42;
  vu16 DR40;
  u16  RESERVED43;
  vu16 DR41;
  u16  RESERVED44;
  vu16 DR42;
  u16  RESERVED45;    
} BKP_TypeDef;

 
typedef struct
{
  vu32 TIR;
  vu32 TDTR;
  vu32 TDLR;
  vu32 TDHR;
} CAN_TxMailBox_TypeDef;

typedef struct
{
  vu32 RIR;
  vu32 RDTR;
  vu32 RDLR;
  vu32 RDHR;
} CAN_FIFOMailBox_TypeDef;

typedef struct
{
  vu32 FR1;
  vu32 FR2;
} CAN_FilterRegister_TypeDef;

typedef struct
{
  vu32 MCR;
  vu32 MSR;
  vu32 TSR;
  vu32 RF0R;
  vu32 RF1R;
  vu32 IER;
  vu32 ESR;
  vu32 BTR;
  u32  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  u32  RESERVED1[12];
  vu32 FMR;
  vu32 FM1R;
  u32  RESERVED2;
  vu32 FS1R;
  u32  RESERVED3;
  vu32 FFA1R;
  u32  RESERVED4;
  vu32 FA1R;
  u32  RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[14];
} CAN_TypeDef;

 
typedef struct
{
  vu32 DR;
  vu8  IDR;
  u8   RESERVED0;
  u16  RESERVED1;
  vu32 CR;
} CRC_TypeDef;


 
typedef struct
{
  vu32 CR;
  vu32 SWTRIGR;
  vu32 DHR12R1;
  vu32 DHR12L1;
  vu32 DHR8R1;
  vu32 DHR12R2;
  vu32 DHR12L2;
  vu32 DHR8R2;
  vu32 DHR12RD;
  vu32 DHR12LD;
  vu32 DHR8RD;
  vu32 DOR1;
  vu32 DOR2;
} DAC_TypeDef;

 
typedef struct
{
  vu32 IDCODE;
  vu32 CR;	
}DBGMCU_TypeDef;

 
typedef struct
{
  vu32 CCR;
  vu32 CNDTR;
  vu32 CPAR;
  vu32 CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  vu32 ISR;
  vu32 IFCR;
} DMA_TypeDef;

 
typedef struct
{
  vu32 IMR;
  vu32 EMR;
  vu32 RTSR;
  vu32 FTSR;
  vu32 SWIER;
  vu32 PR;
} EXTI_TypeDef;

 
typedef struct
{
  vu32 ACR;
  vu32 KEYR;
  vu32 OPTKEYR;
  vu32 SR;
  vu32 CR;
  vu32 AR;
  vu32 RESERVED;
  vu32 OBR;
  vu32 WRPR;
} FLASH_TypeDef;

typedef struct
{
  vu16 RDP;
  vu16 USER;
  vu16 Data0;
  vu16 Data1;
  vu16 WRP0;
  vu16 WRP1;
  vu16 WRP2;
  vu16 WRP3;
} OB_TypeDef;

 
typedef struct
{
  vu32 BTCR[8];   
} FSMC_Bank1_TypeDef; 

typedef struct
{
  vu32 BWTR[7];
} FSMC_Bank1E_TypeDef;

typedef struct
{
  vu32 PCR2;
  vu32 SR2;
  vu32 PMEM2;
  vu32 PATT2;
  u32  RESERVED0;   
  vu32 ECCR2; 
} FSMC_Bank2_TypeDef;  

typedef struct
{
  vu32 PCR3;
  vu32 SR3;
  vu32 PMEM3;
  vu32 PATT3;
  u32  RESERVED0;   
  vu32 ECCR3; 
} FSMC_Bank3_TypeDef; 

typedef struct
{
  vu32 PCR4;
  vu32 SR4;
  vu32 PMEM4;
  vu32 PATT4;
  vu32 PIO4; 
} FSMC_Bank4_TypeDef; 

 
typedef struct
{
  vu32 CRL;
  vu32 CRH;
  vu32 IDR;
  vu32 ODR;
  vu32 BSRR;
  vu32 BRR;
  vu32 LCKR;
} GPIO_TypeDef;

typedef struct
{
  vu32 EVCR;
  vu32 MAPR;
  vu32 EXTICR[4];
} AFIO_TypeDef;

 
typedef struct
{
  vu16 CR1;
  u16  RESERVED0;
  vu16 CR2;
  u16  RESERVED1;
  vu16 OAR1;
  u16  RESERVED2;
  vu16 OAR2;
  u16  RESERVED3;
  vu16 DR;
  u16  RESERVED4;
  vu16 SR1;
  u16  RESERVED5;
  vu16 SR2;
  u16  RESERVED6;
  vu16 CCR;
  u16  RESERVED7;
  vu16 TRISE;
  u16  RESERVED8;
} I2C_TypeDef;

 
typedef struct
{
  vu32 KR;
  vu32 PR;
  vu32 RLR;
  vu32 SR;
} IWDG_TypeDef;

 
typedef struct
{
  vu32 ISER[2];
  u32  RESERVED0[30];
  vu32 ICER[2];
  u32  RSERVED1[30];
  vu32 ISPR[2];
  u32  RESERVED2[30];
  vu32 ICPR[2];
  u32  RESERVED3[30];
  vu32 IABR[2];
  u32  RESERVED4[62];
  vu32 IPR[15];
} NVIC_TypeDef;

typedef struct
{
  vuc32 CPUID;
  vu32 ICSR;
  vu32 VTOR;
  vu32 AIRCR;
  vu32 SCR;
  vu32 CCR;
  vu32 SHPR[3];
  vu32 SHCSR;
  vu32 CFSR;
  vu32 HFSR;
  vu32 DFSR;
  vu32 MMFAR;
  vu32 BFAR;
  vu32 AFSR;
} SCB_TypeDef;

 
typedef struct
{
  vu32 CR;
  vu32 CSR;
} PWR_TypeDef;

 
typedef struct
{
  vu32 CR;
  vu32 CFGR;
  vu32 CIR;
  vu32 APB2RSTR;
  vu32 APB1RSTR;
  vu32 AHBENR;
  vu32 APB2ENR;
  vu32 APB1ENR;
  vu32 BDCR;
  vu32 CSR;
} RCC_TypeDef;

 
typedef struct
{
  vu16 CRH;
  u16  RESERVED0;
  vu16 CRL;
  u16  RESERVED1;
  vu16 PRLH;
  u16  RESERVED2;
  vu16 PRLL;
  u16  RESERVED3;
  vu16 DIVH;
  u16  RESERVED4;
  vu16 DIVL;
  u16  RESERVED5;
  vu16 CNTH;
  u16  RESERVED6;
  vu16 CNTL;
  u16  RESERVED7;
  vu16 ALRH;
  u16  RESERVED8;
  vu16 ALRL;
  u16  RESERVED9;
} RTC_TypeDef;

 
typedef struct
{
  vu32 POWER;
  vu32 CLKCR;
  vu32 ARG;
  vu32 CMD;
  vuc32 RESPCMD;
  vuc32 RESP1;
  vuc32 RESP2;
  vuc32 RESP3;
  vuc32 RESP4;
  vu32 DTIMER;
  vu32 DLEN;
  vu32 DCTRL;
  vuc32 DCOUNT;
  vuc32 STA;
  vu32 ICR;
  vu32 MASK;
  u32  RESERVED0[2];
  vuc32 FIFOCNT;
  u32  RESERVED1[13];
  vu32 FIFO;
} SDIO_TypeDef;

 
typedef struct
{
  vu16 CR1;
  u16  RESERVED0;
  vu16 CR2;
  u16  RESERVED1;
  vu16 SR;
  u16  RESERVED2;
  vu16 DR;
  u16  RESERVED3;
  vu16 CRCPR;
  u16  RESERVED4;
  vu16 RXCRCR;
  u16  RESERVED5;
  vu16 TXCRCR;
  u16  RESERVED6;
  vu16 I2SCFGR;
  u16  RESERVED7;
  vu16 I2SPR;
  u16  RESERVED8;  
} SPI_TypeDef;

 
typedef struct
{
  vu32 CTRL;
  vu32 LOAD;
  vu32 VAL;
  vuc32 CALIB;
} SysTick_TypeDef;

 
typedef struct
{
  vu16 CR1;
  u16  RESERVED0;
  vu16 CR2;
  u16  RESERVED1;
  vu16 SMCR;
  u16  RESERVED2;
  vu16 DIER;
  u16  RESERVED3;
  vu16 SR;
  u16  RESERVED4;
  vu16 EGR;
  u16  RESERVED5;
  vu16 CCMR1;
  u16  RESERVED6;
  vu16 CCMR2;
  u16  RESERVED7;
  vu16 CCER;
  u16  RESERVED8;
  vu16 CNT;
  u16  RESERVED9;
  vu16 PSC;
  u16  RESERVED10;
  vu16 ARR;
  u16  RESERVED11;
  vu16 RCR;
  u16  RESERVED12;
  vu16 CCR1;
  u16  RESERVED13;
  vu16 CCR2;
  u16  RESERVED14;
  vu16 CCR3;
  u16  RESERVED15;
  vu16 CCR4;
  u16  RESERVED16;
  vu16 BDTR;
  u16  RESERVED17;
  vu16 DCR;
  u16  RESERVED18;
  vu16 DMAR;
  u16  RESERVED19;
} TIM_TypeDef;

 
typedef struct
{
  vu16 SR;
  u16  RESERVED0;
  vu16 DR;
  u16  RESERVED1;
  vu16 BRR;
  u16  RESERVED2;
  vu16 CR1;
  u16  RESERVED3;
  vu16 CR2;
  u16  RESERVED4;
  vu16 CR3;
  u16  RESERVED5;
  vu16 GTPR;
  u16  RESERVED6;
} USART_TypeDef;

 
typedef struct
{
  vu32 CR;
  vu32 CFR;
  vu32 SR;
} WWDG_TypeDef;

 
 
 
 



 



 


 




#line 634 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"

#line 651 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"



#line 670 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"

 

 


 






 


 






 
 
 

 



























































































































































































































#line 924 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"














 
#line 1180 "..\\STM32F10x_lib\\inc\\stm32f10x_map.h"

 
 
 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"

#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

 
 
typedef struct
{
  u32 ADC_Mode;
  FunctionalState ADC_ScanConvMode; 
  FunctionalState ADC_ContinuousConvMode;
  u32 ADC_ExternalTrigConv;
  u32 ADC_DataAlign;
  u8 ADC_NbrOfChannel;
}ADC_InitTypeDef;

 



                                 



 
#line 55 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

#line 66 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

 
 
#line 75 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"
 


 
#line 85 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

#line 100 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

 






 
#line 127 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

#line 137 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

 
#line 147 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

#line 156 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

 
 





 



 






#line 188 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

 










 
#line 208 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

#line 216 "..\\STM32F10x_lib\\inc\\stm32f10x_adc.h"

 








 











 


 


 


 


 


 


 


 
 
void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ITConfig(ADC_TypeDef* ADCx, u16 ADC_IT, FunctionalState NewState);
void ADC_ResetCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_StartCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, u8 Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime);
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
u16 ADC_GetConversionValue(ADC_TypeDef* ADCx);
u32 ADC_GetDualModeConversionValue(void);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, u32 ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx);
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, u8 Length);
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, u8 ADC_InjectedChannel, u16 Offset);
u16 ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, u8 ADC_InjectedChannel);
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, u32 ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, u16 HighThreshold, u16 LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel);
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, u8 ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, u8 ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, u16 ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, u16 ADC_IT);



 
#line 26 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_bkp.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_bkp.h"

 
 
 






 










 
#line 87 "..\\STM32F10x_lib\\inc\\stm32f10x_bkp.h"

#line 102 "..\\STM32F10x_lib\\inc\\stm32f10x_bkp.h"



 
 
void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(u16 BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(u16 BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(u8 CalibrationValue);
void BKP_WriteBackupRegister(u16 BKP_DR, u16 Data);
u16 BKP_ReadBackupRegister(u16 BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);



 
#line 30 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_can.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_can.h"

 
 
typedef struct
{
  FunctionalState CAN_TTCM;
  FunctionalState CAN_ABOM;
  FunctionalState CAN_AWUM;
  FunctionalState CAN_NART;
  FunctionalState CAN_RFLM;
  FunctionalState CAN_TXFP;
  u8 CAN_Mode;
  u8 CAN_SJW;
  u8 CAN_BS1;
  u8 CAN_BS2;
  u16 CAN_Prescaler;
} CAN_InitTypeDef;

 
typedef struct
{
  u8 CAN_FilterNumber;
  u8 CAN_FilterMode;
  u8 CAN_FilterScale;
  u16 CAN_FilterIdHigh;
  u16 CAN_FilterIdLow;
  u16 CAN_FilterMaskIdHigh;
  u16 CAN_FilterMaskIdLow;
  u16 CAN_FilterFIFOAssignment;
  FunctionalState CAN_FilterActivation;
} CAN_FilterInitTypeDef;

 
typedef struct
{
  u32 StdId;
  u32 ExtId;
  u8 IDE;
  u8 RTR;
  u8 DLC;
  u8 Data[8];
} CanTxMsg;

 
typedef struct
{
  u32 StdId;
  u32 ExtId;
  u8 IDE;
  u8 RTR;
  u8 DLC;
  u8 Data[8];
  u8 FMI;
} CanRxMsg;

 

 



 








 








 
#line 119 "..\\STM32F10x_lib\\inc\\stm32f10x_can.h"



 
#line 131 "..\\STM32F10x_lib\\inc\\stm32f10x_can.h"



 


 


 






 






 






 





 





 





 





 





 



 



 







 
#line 225 "..\\STM32F10x_lib\\inc\\stm32f10x_can.h"

#line 233 "..\\STM32F10x_lib\\inc\\stm32f10x_can.h"

#line 240 "..\\STM32F10x_lib\\inc\\stm32f10x_can.h"

 
 
void CAN_DeInit(void);
u8 CAN_Init(CAN_InitTypeDef* CAN_InitStruct);
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);
void CAN_ITConfig(u32 CAN_IT, FunctionalState NewState);
u8 CAN_Transmit(CanTxMsg* TxMessage);
u8 CAN_TransmitStatus(u8 TransmitMailbox);
void CAN_CancelTransmit(u8 Mailbox);
void CAN_FIFORelease(u8 FIFONumber);
u8 CAN_MessagePending(u8 FIFONumber);
void CAN_Receive(u8 FIFONumber, CanRxMsg* RxMessage);
u8 CAN_Sleep(void);
u8 CAN_WakeUp(void);
FlagStatus CAN_GetFlagStatus(u32 CAN_FLAG);
void CAN_ClearFlag(u32 CAN_FLAG);
ITStatus CAN_GetITStatus(u32 CAN_IT);
void CAN_ClearITPendingBit(u32 CAN_IT);



 
#line 34 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_crc.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_crc.h"

 
 
 
 
void CRC_ResetDR(void);
u32 CRC_CalcCRC(u32 Data);
u32 CRC_CalcBlockCRC(u32 pBuffer[], u32 BufferLength);
u32 CRC_GetCRC(void);
void CRC_SetIDRegister(u8 IDValue);
u8 CRC_GetIDRegister(void);



 
#line 38 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_dac.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_dac.h"

 
 
typedef struct
{
  u32 DAC_Trigger;
  u32 DAC_WaveGeneration;
  u32 DAC_LFSRUnmask_TriangleAmplitude;
  u32 DAC_OutputBuffer; 
}DAC_InitTypeDef;

 
 
#line 45 "..\\STM32F10x_lib\\inc\\stm32f10x_dac.h"

#line 55 "..\\STM32F10x_lib\\inc\\stm32f10x_dac.h"

 








 
#line 78 "..\\STM32F10x_lib\\inc\\stm32f10x_dac.h"

#line 91 "..\\STM32F10x_lib\\inc\\stm32f10x_dac.h"

#line 116 "..\\STM32F10x_lib\\inc\\stm32f10x_dac.h"

 






 






 








 






 


 
 
void DAC_DeInit(void);
void DAC_Init(u32 DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(u32 DAC_Channel, FunctionalState NewState);
void DAC_DMACmd(u32 DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(u32 DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(u32 DAC_Channel, u32 DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(u32 DAC_Align, u16 Data);
void DAC_SetChannel2Data(u32 DAC_Align, u16 Data);
void DAC_SetDualChannelData(u32 DAC_Align, u16 Data2, u16 Data1);
u16 DAC_GetDataOutputValue(u32 DAC_Channel);



 
#line 42 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_dbgmcu.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_dbgmcu.h"

 
 
#line 42 "..\\STM32F10x_lib\\inc\\stm32f10x_dbgmcu.h"
                                           


 
 
u32 DBGMCU_GetREVID(void);
u32 DBGMCU_GetDEVID(void);
void DBGMCU_Config(u32 DBGMCU_Periph, FunctionalState NewState);



 


#line 46 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"

 
 
typedef struct
{
  u32 DMA_PeripheralBaseAddr;
  u32 DMA_MemoryBaseAddr;
  u32 DMA_DIR;
  u32 DMA_BufferSize;
  u32 DMA_PeripheralInc;
  u32 DMA_MemoryInc;
  u32 DMA_PeripheralDataSize;
  u32 DMA_MemoryDataSize;
  u32 DMA_Mode;
  u32 DMA_Priority;
  u32 DMA_M2M;
}DMA_InitTypeDef;

 
#line 54 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"

 






 






 






 








 








 





 










 





 






 
#line 153 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"
 
#line 174 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"

#line 200 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"

 
 
#line 231 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"
 
#line 252 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"

#line 278 "..\\STM32F10x_lib\\inc\\stm32f10x_dma.h"

 


 
 
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, u32 DMA_IT, FunctionalState NewState);
u16 DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);
FlagStatus DMA_GetFlagStatus(u32 DMA_FLAG);
void DMA_ClearFlag(u32 DMA_FLAG);
ITStatus DMA_GetITStatus(u32 DMA_IT);
void DMA_ClearITPendingBit(u32 DMA_IT);



 
#line 50 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_exti.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_exti.h"

 
 
typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;


                            
 
typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;





 
typedef struct
{
  u32 EXTI_Line;
  EXTIMode_TypeDef EXTI_Mode;
  EXTITrigger_TypeDef EXTI_Trigger;
  FunctionalState EXTI_LineCmd;
}EXTI_InitTypeDef;

 
 
#line 80 "..\\STM32F10x_lib\\inc\\stm32f10x_exti.h"



#line 93 "..\\STM32F10x_lib\\inc\\stm32f10x_exti.h"
                                 
 
 
void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(u32 EXTI_Line);
FlagStatus EXTI_GetFlagStatus(u32 EXTI_Line);
void EXTI_ClearFlag(u32 EXTI_Line);
ITStatus EXTI_GetITStatus(u32 EXTI_Line);
void EXTI_ClearITPendingBit(u32 EXTI_Line);



 
#line 54 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_flash.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_flash.h"

 

 
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;


 








 







 







 

 
#line 97 "..\\STM32F10x_lib\\inc\\stm32f10x_flash.h"

 
#line 132 "..\\STM32F10x_lib\\inc\\stm32f10x_flash.h"






 





 





 





 





 





 






								 
 
 
 
void FLASH_SetLatency(u32 FLASH_Latency);
void FLASH_HalfCycleAccessCmd(u32 FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(u32 FLASH_PrefetchBuffer);


void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(u32 Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramWord(u32 Address, u32 Data);
FLASH_Status FLASH_ProgramHalfWord(u32 Address, u16 Data);
FLASH_Status FLASH_ProgramOptionByteData(u32 Address, u8 Data);
FLASH_Status FLASH_EnableWriteProtection(u32 FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(u16 OB_IWDG, u16 OB_STOP, u16 OB_STDBY);
u32 FLASH_GetUserOptionByte(void);
u32 FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_ITConfig(u16 FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(u16 FLASH_FLAG);
void FLASH_ClearFlag(u16 FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(u32 Timeout);




 
#line 58 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_fsmc.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_fsmc.h"

 
 
typedef struct
{
  u32 FSMC_AddressSetupTime;
  u32 FSMC_AddressHoldTime;
  u32 FSMC_DataSetupTime;
  u32 FSMC_BusTurnAroundDuration;
  u32 FSMC_CLKDivision;
  u32 FSMC_DataLatency;
  u32 FSMC_AccessMode;
}FSMC_NORSRAMTimingInitTypeDef;

 
typedef struct
{
  u32 FSMC_Bank;
  u32 FSMC_DataAddressMux;
  u32 FSMC_MemoryType;
  u32 FSMC_MemoryDataWidth;
  u32 FSMC_BurstAccessMode;
  u32 FSMC_WaitSignalPolarity;
  u32 FSMC_WrapMode;
  u32 FSMC_WaitSignalActive;
  u32 FSMC_WriteOperation;
  u32 FSMC_WaitSignal;
  u32 FSMC_ExtendedMode;
  u32 FSMC_AsyncWait;
  u32 FSMC_WriteBurst;
   
  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;
   
  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;
}FSMC_NORSRAMInitTypeDef;

 
typedef struct
{
  u32 FSMC_SetupTime;
  u32 FSMC_WaitSetupTime;
  u32 FSMC_HoldSetupTime;
  u32 FSMC_HiZSetupTime;
}FSMC_NAND_PCCARDTimingInitTypeDef;

 
typedef struct
{
  u32 FSMC_Bank;
  u32 FSMC_Waitfeature;
  u32 FSMC_MemoryDataWidth;
  u32 FSMC_ECC;
  u32 FSMC_ECCPageSize;
  u32 FSMC_AddressLowMapping;
  u32 FSMC_TCLRSetupTime;
  u32 FSMC_TARSetupTime;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;
}FSMC_NANDInitTypeDef;

 
typedef struct
{
  u32 FSMC_Waitfeature;
  u32 FSMC_AddressLowMapping;
  u32 FSMC_TCLRSetupTime;
  u32 FSMC_TARSetupTime;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct;
}FSMC_PCCARDInitTypeDef;

 
 
#line 109 "..\\STM32F10x_lib\\inc\\stm32f10x_fsmc.h"













                                    





 
 






 









                                     
 





                                      
                               
 






                                   





                                        
  





                                 
                                  





                                    
 





                              
 






 





                               
 





                                  
                                   






 


 


 


 


 


 


 









                                  
 
 





                                    
 





                                    
 





                                            
 
#line 276 "..\\STM32F10x_lib\\inc\\stm32f10x_fsmc.h"

#line 283 "..\\STM32F10x_lib\\inc\\stm32f10x_fsmc.h"
                                                              
 





 


 


 


 


 


 


 










 











 
 
void FSMC_NORSRAMDeInit(u32 FSMC_Bank);
void FSMC_NANDDeInit(u32 FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMCmd(u32 FSMC_Bank, FunctionalState NewState);
void FSMC_NANDCmd(u32 FSMC_Bank, FunctionalState NewState);
void FSMC_PCCARDCmd(FunctionalState NewState);
void FSMC_NANDECCCmd(u32 FSMC_Bank, FunctionalState NewState);
u32 FSMC_GetECC(u32 FSMC_Bank);
void FSMC_ITConfig(u32 FSMC_Bank, u32 FSMC_IT, FunctionalState NewState);
FlagStatus FSMC_GetFlagStatus(u32 FSMC_Bank, u32 FSMC_FLAG);
void FSMC_ClearFlag(u32 FSMC_Bank, u32 FSMC_FLAG);
ITStatus FSMC_GetITStatus(u32 FSMC_Bank, u32 FSMC_IT);
void FSMC_ClearITPendingBit(u32 FSMC_Bank, u32 FSMC_IT);



 
#line 62 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"

 
#line 32 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"
                                     
 
typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;



                                         
 
typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;





                              
 
typedef struct
{
  u16 GPIO_Pin;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOMode_TypeDef GPIO_Mode;
}GPIO_InitTypeDef;

 
typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;


 
 
#line 95 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"



#line 114 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"
                            
 
#line 141 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"


#line 156 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"
                              
 
#line 165 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"






                                         
#line 179 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"
                                       
 
#line 197 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"

#line 214 "..\\STM32F10x_lib\\inc\\stm32f10x_gpio.h"
                          
 
 
void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
u8 GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
u16 GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
u8 GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
u16 GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, u16 PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_EventOutputConfig(u8 GPIO_PortSource, u8 GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(u32 GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(u8 GPIO_PortSource, u8 GPIO_PinSource);



 
#line 66 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

 
 
typedef struct
{
  u16 I2C_Mode;
  u16 I2C_DutyCycle;
  u16 I2C_OwnAddress1;
  u16 I2C_Ack;
  u16 I2C_AcknowledgedAddress;
  u32 I2C_ClockSpeed;
}I2C_InitTypeDef;

 



 







 






 






 






 






 
#line 86 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

#line 96 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

 






 






 






 
#line 133 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

#line 140 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

#line 148 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

 
#line 171 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

#line 178 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

#line 190 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

 
 






 

     
 


 


 


 



 


 

      
 

                                          
 


#line 246 "..\\STM32F10x_lib\\inc\\stm32f10x_i2c.h"

 

 


 
 
void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, u8 Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef* I2Cx, u16 I2C_IT, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, u8 Data);
u8 I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, u8 Address, u8 I2C_Direction);
u16 I2C_ReadRegister(I2C_TypeDef* I2Cx, u8 I2C_Register);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, u16 I2C_SMBusAlert);
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, u16 I2C_PECPosition);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
u8 I2C_GetPEC(I2C_TypeDef* I2Cx);
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, u16 I2C_DutyCycle);
u32 I2C_GetLastEvent(I2C_TypeDef* I2Cx);
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, u32 I2C_EVENT);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, u32 I2C_FLAG);
void I2C_ClearFlag(I2C_TypeDef* I2Cx, u32 I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, u32 I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, u32 I2C_IT);



 
#line 70 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_iwdg.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_iwdg.h"

 
 
 






 
#line 41 "..\\STM32F10x_lib\\inc\\stm32f10x_iwdg.h"

#line 49 "..\\STM32F10x_lib\\inc\\stm32f10x_iwdg.h"

 







 
 
void IWDG_WriteAccessCmd(u16 IWDG_WriteAccess);
void IWDG_SetPrescaler(u8 IWDG_Prescaler);
void IWDG_SetReload(u16 Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(u16 IWDG_FLAG);



 
#line 74 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"

 
 
typedef struct
{
  u8 NVIC_IRQChannel;
  u8 NVIC_IRQChannelPreemptionPriority;
  u8 NVIC_IRQChannelSubPriority;
  FunctionalState NVIC_IRQChannelCmd;
} NVIC_InitTypeDef;

 
 
#line 96 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"


#line 158 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"


 
#line 170 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"





#line 182 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"












#line 201 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"











 






 








 
#line 239 "..\\STM32F10x_lib\\inc\\stm32f10x_nvic.h"












 
 
void NVIC_DeInit(void);
void NVIC_SCBDeInit(void);
void NVIC_PriorityGroupConfig(u32 NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_StructInit(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SETPRIMASK(void);
void NVIC_RESETPRIMASK(void);
void NVIC_SETFAULTMASK(void);
void NVIC_RESETFAULTMASK(void);
void NVIC_BASEPRICONFIG(u32 NewPriority);
u32 NVIC_GetBASEPRI(void);
u16 NVIC_GetCurrentPendingIRQChannel(void);
ITStatus NVIC_GetIRQChannelPendingBitStatus(u8 NVIC_IRQChannel);
void NVIC_SetIRQChannelPendingBit(u8 NVIC_IRQChannel);
void NVIC_ClearIRQChannelPendingBit(u8 NVIC_IRQChannel);
u16 NVIC_GetCurrentActiveHandler(void);
ITStatus NVIC_GetIRQChannelActiveBitStatus(u8 NVIC_IRQChannel);
u32 NVIC_GetCPUID(void);
void NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);
void NVIC_GenerateSystemReset(void);
void NVIC_GenerateCoreReset(void);
void NVIC_SystemLPConfig(u8 LowPowerMode, FunctionalState NewState);
void NVIC_SystemHandlerConfig(u32 SystemHandler, FunctionalState NewState);
void NVIC_SystemHandlerPriorityConfig(u32 SystemHandler, u8 SystemHandlerPreemptionPriority,
                                      u8 SystemHandlerSubPriority);
ITStatus NVIC_GetSystemHandlerPendingBitStatus(u32 SystemHandler);
void NVIC_SetSystemHandlerPendingBit(u32 SystemHandler);
void NVIC_ClearSystemHandlerPendingBit(u32 SystemHandler);
ITStatus NVIC_GetSystemHandlerActiveBitStatus(u32 SystemHandler);
u32 NVIC_GetFaultHandlerSources(u32 SystemHandler);
u32 NVIC_GetFaultAddress(u32 SystemHandler);



 
#line 78 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_pwr.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_pwr.h"

 
 
 
#line 35 "..\\STM32F10x_lib\\inc\\stm32f10x_pwr.h"






 






 




 
 








 
 
void PWR_DeInit(void);
void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_PVDCmd(FunctionalState NewState);
void PWR_PVDLevelConfig(u32 PWR_PVDLevel);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_EnterSTOPMode(u32 PWR_Regulator, u8 PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(u32 PWR_FLAG);
void PWR_ClearFlag(u32 PWR_FLAG);



 
#line 82 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"

 
typedef struct
{
  u32 SYSCLK_Frequency;
  u32 HCLK_Frequency;
  u32 PCLK1_Frequency;
  u32 PCLK2_Frequency;
  u32 ADCCLK_Frequency;
}RCC_ClocksTypeDef;

 
 







 








 
#line 68 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"

#line 77 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"

 








 
#line 97 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"







 










 
#line 122 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"







 






 








 







 








 
#line 170 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"



 
#line 190 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"



 
#line 215 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"



 










 
#line 241 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"

#line 248 "..\\STM32F10x_lib\\inc\\stm32f10x_rcc.h"



 
 
void RCC_DeInit(void);
void RCC_HSEConfig(u32 RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(u8 HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(u32 RCC_PLLSource, u32 RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_SYSCLKConfig(u32 RCC_SYSCLKSource);
u8 RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(u32 RCC_SYSCLK);
void RCC_PCLK1Config(u32 RCC_HCLK);
void RCC_PCLK2Config(u32 RCC_HCLK);
void RCC_ITConfig(u8 RCC_IT, FunctionalState NewState);
void RCC_USBCLKConfig(u32 RCC_USBCLKSource);
void RCC_ADCCLKConfig(u32 RCC_PCLK2);
void RCC_LSEConfig(u8 RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(u32 RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(u32 RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(u32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(u32 RCC_APB1Periph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(u32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(u32 RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(u8 RCC_MCO);
FlagStatus RCC_GetFlagStatus(u8 RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(u8 RCC_IT);
void RCC_ClearITPendingBit(u8 RCC_IT);



 
#line 86 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_rtc.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_rtc.h"

 
 
 








                                                                     
 













                           
 
 
void RTC_ITConfig(u16 RTC_IT, FunctionalState NewState);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
u32  RTC_GetCounter(void);
void RTC_SetCounter(u32 CounterValue);
void RTC_SetPrescaler(u32 PrescalerValue);
void RTC_SetAlarm(u32 AlarmValue);
u32  RTC_GetDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
FlagStatus RTC_GetFlagStatus(u16 RTC_FLAG);
void RTC_ClearFlag(u16 RTC_FLAG);
ITStatus RTC_GetITStatus(u16 RTC_IT);
void RTC_ClearITPendingBit(u16 RTC_IT);



 
#line 90 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"

 
typedef struct
{
  u8 SDIO_ClockDiv;
  u32 SDIO_ClockEdge;
  u32 SDIO_ClockBypass;
  u32 SDIO_ClockPowerSave;
  u32 SDIO_BusWide;
  u32 SDIO_HardwareFlowControl;
} SDIO_InitTypeDef;

typedef struct
{
  u32 SDIO_Argument;
  u32 SDIO_CmdIndex;
  u32 SDIO_Response;
  u32 SDIO_Wait;
  u32 SDIO_CPSM;
} SDIO_CmdInitTypeDef;

typedef struct
{
  u32 SDIO_DataTimeOut;
  u32 SDIO_DataLength;
  u32 SDIO_DataBlockSize;
  u32 SDIO_TransferDir;
  u32 SDIO_TransferMode;
  u32 SDIO_DPSM;
} SDIO_DataInitTypeDef;

 
 





                                   






  






 






                                
  





                                  
 





 
#line 121 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"



 


 








 







 





 








 


 
#line 178 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"

#line 194 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"

 






 






 





 
#line 240 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"

#line 265 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"



#line 292 "..\\STM32F10x_lib\\inc\\stm32f10x_sdio.h"


                                                        
 






 
 
void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(u32 SDIO_PowerState);
u32 SDIO_GetPowerState(void);
void SDIO_ITConfig(u32 SDIO_IT, FunctionalState NewState);
void SDIO_DMACmd(FunctionalState NewState);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
u8 SDIO_GetCommandResponse(void);
u32 SDIO_GetResponse(u32 SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
u32 SDIO_GetDataCounter(void);
u32 SDIO_ReadData(void);
void SDIO_WriteData(u32 Data);
u32 SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(FunctionalState NewState);
void SDIO_StopSDIOReadWait(FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(u32 SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
void SDIO_SendCEATACmd(FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(u32 SDIO_FLAG);
void SDIO_ClearFlag(u32 SDIO_FLAG);
ITStatus SDIO_GetITStatus(u32 SDIO_IT);
void SDIO_ClearITPendingBit(u32 SDIO_IT);



 
#line 94 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"

 
 
typedef struct
{
  u16 SPI_Direction;
  u16 SPI_Mode;
  u16 SPI_DataSize;
  u16 SPI_CPOL;
  u16 SPI_CPHA;
  u16 SPI_NSS;
  u16 SPI_BaudRatePrescaler;
  u16 SPI_FirstBit;
  u16 SPI_CRCPolynomial;
}SPI_InitTypeDef;

 
typedef struct
{
  u16 I2S_Mode;
  u16 I2S_Standard;
  u16 I2S_DataFormat;
  u16 I2S_MCLKOutput;
  u16 I2S_AudioFreq;
  u16 I2S_CPOL;
}I2S_InitTypeDef;

 








 










 






 






 






 






 






 
#line 114 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"

#line 123 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"

 






 










 












 










  






 
#line 180 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"

#line 187 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"

 






 





 






 





 






 






















 
#line 253 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"

#line 260 "..\\STM32F10x_lib\\inc\\stm32f10x_spi.h"

 


 
 
void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, u8 SPI_I2S_IT, FunctionalState NewState);
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, u16 SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2S_SendData(SPI_TypeDef* SPIx, u16 Data);
u16 SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, u16 SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, u16 SPI_DataSize);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
u16 SPI_GetCRC(SPI_TypeDef* SPIx, u8 SPI_CRC);
u16 SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, u16 SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, u8 SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, u8 SPI_I2S_IT);



 
#line 98 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_systick.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_systick.h"

 
 
 






 








 










 
 
void SysTick_CLKSourceConfig(u32 SysTick_CLKSource);
void SysTick_SetReload(u32 Reload);
void SysTick_CounterCmd(u32 SysTick_Counter);
void SysTick_ITConfig(FunctionalState NewState);
u32 SysTick_GetCounter(void);
FlagStatus SysTick_GetFlagStatus(u8 SysTick_FLAG);



 
#line 102 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 

 
typedef struct
{
  u16 TIM_Prescaler;
  u16 TIM_CounterMode;
  u16 TIM_Period;
  u16 TIM_ClockDivision;
  u8 TIM_RepetitionCounter;
} TIM_TimeBaseInitTypeDef;

 
typedef struct
{
  u16 TIM_OCMode;
  u16 TIM_OutputState;
  u16 TIM_OutputNState;
  u16 TIM_Pulse;
  u16 TIM_OCPolarity;
  u16 TIM_OCNPolarity;
  u16 TIM_OCIdleState;
  u16 TIM_OCNIdleState;
} TIM_OCInitTypeDef;

 
typedef struct
{
  u16 TIM_Channel;
  u16 TIM_ICPolarity;
  u16 TIM_ICSelection;
  u16 TIM_ICPrescaler;
  u16 TIM_ICFilter;
} TIM_ICInitTypeDef;

 
typedef struct
{
  u16 TIM_OSSRState;
  u16 TIM_OSSIState;
  u16 TIM_LOCKLevel; 
  u16 TIM_DeadTime;
  u16 TIM_Break;
  u16 TIM_BreakPolarity;
  u16 TIM_AutomaticOutput;
} TIM_BDTRInitTypeDef;

                              

#line 81 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"




#line 91 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 
#line 99 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 106 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 115 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"
 






 
















 








 












 






 






 






 






 






 






 






 






 





 










 






 






 






 






 






 








 










 
#line 298 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"



#line 308 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 317 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 
#line 338 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 358 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 
#line 378 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 397 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 
#line 406 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"



#line 416 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 










 
#line 437 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 446 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"






 








 






 






 






  








 
#line 500 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"



#line 510 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 






 






 





                                     
 






  
#line 548 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 557 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 593 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

 










 






 
#line 625 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 638 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 646 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"

#line 665 "..\\STM32F10x_lib\\inc\\stm32f10x_tim.h"
                                                                                            
 


 


 
 

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, u16 TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, u16 TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, u16 TIM_DMABase, u16 TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, u16 TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_TIxExternalCLKSource,
                                u16 TIM_ICPolarity, u16 ICFilter);                                
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                             u16 ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, 
                             u16 TIM_ExtTRGPolarity, u16 ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                   u16 ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, u16 Prescaler, u16 TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, u16 TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, u16 TIM_EncoderMode,
                                u16 TIM_IC1Polarity, u16 TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, u16 TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, u16 TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, u16 TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, u16 TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, u16 TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, u16 Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, u16 Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, u16 Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, u16 Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, u16 Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, u16 Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, u16 TIM_CKD);
u16 TIM_GetCapture1(TIM_TypeDef* TIMx);
u16 TIM_GetCapture2(TIM_TypeDef* TIMx);
u16 TIM_GetCapture3(TIM_TypeDef* TIMx);
u16 TIM_GetCapture4(TIM_TypeDef* TIMx);
u16 TIM_GetCounter(TIM_TypeDef* TIMx);
u16 TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, u16 TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, u16 TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, u16 TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, u16 TIM_IT);
                                                                                                             


 








#line 106 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_usart.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_usart.h"

 
 
typedef struct
{
  u32 USART_BaudRate;
  u16 USART_WordLength;
  u16 USART_StopBits;
  u16 USART_Parity;
  u16 USART_Mode;
  u16 USART_HardwareFlowControl;  
} USART_InitTypeDef;

 
typedef struct
{
  u16 USART_Clock;
  u16 USART_CPOL;
  u16 USART_CPHA;
  u16 USART_LastBit;
} USART_ClockInitTypeDef;

 















 


                                    



 









 








 





 















 






 




                               
 




 






 
#line 146 "..\\STM32F10x_lib\\inc\\stm32f10x_usart.h"






















 





 






 







 






 
#line 207 "..\\STM32F10x_lib\\inc\\stm32f10x_usart.h"






                              










 
 
void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ITConfig(USART_TypeDef* USARTx, u16 USART_IT, FunctionalState NewState);
void USART_DMACmd(USART_TypeDef* USARTx, u16 USART_DMAReq, FunctionalState NewState);
void USART_SetAddress(USART_TypeDef* USARTx, u8 USART_Address);
void USART_WakeUpConfig(USART_TypeDef* USARTx, u16 USART_WakeUp);
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, u16 USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendData(USART_TypeDef* USARTx, u16 Data);
u16 USART_ReceiveData(USART_TypeDef* USARTx);
void USART_SendBreak(USART_TypeDef* USARTx);
void USART_SetGuardTime(USART_TypeDef* USARTx, u8 USART_GuardTime);
void USART_SetPrescaler(USART_TypeDef* USARTx, u8 USART_Prescaler);
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_IrDAConfig(USART_TypeDef* USARTx, u16 USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, u16 USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, u16 USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, u16 USART_IT);



 
#line 110 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


#line 1 "..\\STM32F10x_lib\\inc\\stm32f10x_wwdg.h"














 

 



 
#line 23 "..\\STM32F10x_lib\\inc\\stm32f10x_wwdg.h"

 
 
 














 
 
void WWDG_DeInit(void);
void WWDG_SetPrescaler(u32 WWDG_Prescaler);
void WWDG_SetWindowValue(u8 WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(u8 Counter);
void WWDG_Enable(u8 Counter);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);



 
#line 114 "..\\STM32F10x_lib\\inc\\stm32f10x_lib.h"


 
 
 
 
void debug(void);



 
#line 5 "..\\target\\system.h"
#line 6 "..\\target\\system.h"











void dbg_void(void);
void print_void(void *fmt,...);
 







void enable_timer(void);
void disable_timer(void);
void Delay(u32 nTime);
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(USART_TypeDef *USARTx);
void timerbase_config(void);
void SPI1_Config(void);
void EXTI_Configuration(void);
void debug_data_stream(char *info,char *pdata,u16 len);
char Uart_GetKey(void);
void Uart_SendByte(u8 ch);
void Uart_GetString(char *string);
int Uart_GetIntNum(void);
int Uart_GetIntNum_GJ(void);
int write_flash(u32 StartAddr,u16 *buf,u16 len);
int read_flash(u32 StartAddr,u16 *buf,u16 len);


void RCC_Configuration(void);
void watch_dog_config(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void assert_failed(u8* file, u32 line);


#line 11 "..\\sdio\\inc\\common.h"
#line 1 "..\\sdio\\inc\\s3cmci.h"








 



#line 14 "..\\sdio\\inc\\s3cmci.h"



 








enum s3cmci_waitfor {
	COMPLETION_NONE,
	COMPLETION_FINALIZE,
	COMPLETION_CMDSENT,
	COMPLETION_RSPFIN,
	COMPLETION_XFERFINISH,
	COMPLETION_XFERFINISH_RSPFIN,
};
	

struct stm32_host {
	
	
	struct mmc_host		*mmc;
	
	
	unsigned long 		base;
	int			irq;
	int			irq_cd;
	int			dma;

	unsigned long		clk_rate;
	unsigned long		clk_div;
	unsigned long		real_rate;
	u8			prescaler;

	int			is2440;
	unsigned		sdiimsk;
	unsigned		sdidata;
	int			dodma;
	int			dmatogo;

	bool			irq_disabled;
	bool			irq_enabled;
	bool			irq_state;
	int			sdio_irqen;

	struct mmc_request	*mrq;
	int			cmd_is_stop;

	
	enum s3cmci_waitfor	complete_what;

	int			dma_complete;

	u32			pio_sgptr;
	u32			pio_bytes;
	u32			pio_count;
	u32			*pio_ptr;

	u32			pio_active;

	int			bus_width;

	
	
	char			*status;

	unsigned int		ccnt, dcnt;










 
};
struct mmc_host * stm32_probe(void);
void  stm32_irq(void);
#line 12 "..\\sdio\\inc\\common.h"




enum { MSG_MSGDUMP, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR };




















 
#line 47 "..\\sdio\\inc\\common.h"



#line 58 "..\\sdio\\inc\\common.h"




 



















#line 88 "..\\sdio\\inc\\common.h"


#line 99 "..\\sdio\\inc\\common.h"

#line 110 "..\\sdio\\inc\\common.h"


#line 130 "..\\sdio\\inc\\common.h"





 







static void xdbug_buf(const char * name , const unsigned char * buf , const int len)
{
	int i = 0;
	printf("dbug buf [%s]\n",name);
	for(;i<len;i++)
	{
		printf("0x%02x,",buf[i]);
	}
	printf("\n");
}
#line 164 "..\\sdio\\inc\\common.h"























#line 195 "..\\sdio\\inc\\common.h"








void mmc_delay(unsigned int time);
void ms_delay(void);
void  mdelay(unsigned long time);

bool time_after(char res, unsigned long *time_out);
const char *print_ssid(char *buf, const char *ssid, u8 ssid_len);
u8 convert_from_bytes_to_power_of_two(u16 NumberOfBytes);
void  *ERR_PTR(long error);
long  PTR_ERR(const void *ptr);
long  IS_ERR(const void *ptr);
void  lbs_hex(unsigned int grp, const char *prompt, u8 *buf, int len);
#line 223 "..\\sdio\\inc\\common.h"

#line 6 "..\\sdio\\src\\s3cmci.c"
#line 7 "..\\sdio\\src\\s3cmci.c"
#line 1 "..\\sdio\\inc\\mmc.h"





















 




#line 28 "..\\sdio\\inc\\mmc.h"

 
    
#line 48 "..\\sdio\\inc\\mmc.h"

   




   


   






   




   




   



   


   












 














 

#line 135 "..\\sdio\\inc\\mmc.h"




 
#line 147 "..\\sdio\\inc\\mmc.h"
 
#line 158 "..\\sdio\\inc\\mmc.h"

 

struct _mmc_csd {
	u8  csd_structure;
	u8  spec_vers;
	u8  taac;
	u8  nsac;
	u8  tran_speed;
	u16 ccc;
	u8  read_bl_len;
	u8  read_bl_partial;
	u8  write_blk_misalign;
	u8  read_blk_misalign;
	u8  dsr_imp;
	u16 c_size;
	u8  vdd_r_curr_min;
	u8  vdd_r_curr_max;
	u8  vdd_w_curr_min;
	u8  vdd_w_curr_max;
	u8  c_size_mult;
	union {
		struct {  
			u8  erase_grp_size;
			u8  erase_grp_mult;
		} v31;
		struct {  
			u8  sector_size;
			u8  erase_grp_size;
		} v22;
	} erase;
	u8  wp_grp_size;
	u8  wp_grp_enable;
	u8  default_ecc;
	u8  r2w_factor;
	u8  write_bl_len;
	u8  write_bl_partial;
	u8  file_format_grp;
	u8  copy;
	u8  perm_write_protect;
	u8  tmp_write_protect;
	u8  file_format;
	u8  ecc;
};



 




 

					 
					 

					 

					 

					 

					 

					 

					 

					 

					 

					 

					 
					 
					 



 














 

#line 262 "..\\sdio\\inc\\mmc.h"



 














 









#line 8 "..\\sdio\\src\\s3cmci.c"
#line 1 "..\\sdio\\inc\\core.h"






 



#line 12 "..\\sdio\\inc\\core.h"
#line 13 "..\\sdio\\inc\\core.h"
#line 14 "..\\sdio\\inc\\core.h"
#line 15 "..\\sdio\\inc\\core.h"
#line 1 "..\\sdio\\inc\\host.h"



#line 5 "..\\sdio\\inc\\host.h"
#line 6 "..\\sdio\\inc\\host.h"
#line 7 "..\\sdio\\inc\\host.h"
#line 1 "..\\sdio\\inc\\core.h"






 
#line 8 "..\\sdio\\inc\\host.h"
#line 1 "..\\sdio\\inc\\card.h"



#line 5 "..\\sdio\\inc\\card.h"
#line 6 "..\\sdio\\inc\\card.h"
#line 7 "..\\sdio\\inc\\card.h"
#line 8 "..\\sdio\\inc\\card.h"
#line 1 "..\\sdio\\inc\\host.h"
#line 9 "..\\sdio\\inc\\card.h"
#line 1 "..\\sdio\\inc\\sd.h"









 





#line 10 "..\\sdio\\inc\\card.h"
#line 1 "..\\sdio\\inc\\sdio.h"









 




#line 16 "..\\sdio\\inc\\sdio.h"
#line 17 "..\\sdio\\inc\\sdio.h"
#line 18 "..\\sdio\\inc\\sdio.h"
#line 19 "..\\sdio\\inc\\sdio.h"
#line 20 "..\\sdio\\inc\\sdio.h"
#line 1 "..\\sdio\\inc\\card.h"
#line 21 "..\\sdio\\inc\\sdio.h"
#line 1 "..\\sdio\\inc\\sdio_func.h"









 




#line 16 "..\\sdio\\inc\\sdio_func.h"
#line 17 "..\\sdio\\inc\\sdio_func.h"
#line 18 "..\\sdio\\inc\\sdio_func.h"
#line 19 "..\\sdio\\inc\\sdio_func.h"
#line 20 "..\\sdio\\inc\\sdio_func.h"
#line 1 "..\\sdio\\inc\\sdio.h"









 

#line 276 "..\\sdio\\inc\\sdio.h"


#line 21 "..\\sdio\\inc\\sdio_func.h"
#line 1 "..\\marvel\\driver\\inc\\if_sdio.h"









 

#line 15 "..\\marvel\\driver\\inc\\if_sdio.h"
#line 16 "..\\marvel\\driver\\inc\\if_sdio.h"
#line 1 "..\\sdio\\inc\\sdio_func.h"









 

#line 17 "..\\marvel\\driver\\inc\\if_sdio.h"
#line 1 "..\\marvel\\driver\\inc\\sdio_ids.h"


 






 

#line 21 "..\\marvel\\driver\\inc\\sdio_ids.h"



 
#line 31 "..\\marvel\\driver\\inc\\sdio_ids.h"






#line 44 "..\\marvel\\driver\\inc\\sdio_ids.h"



#line 18 "..\\marvel\\driver\\inc\\if_sdio.h"
#line 1 "..\\marvel\\driver\\inc\\dev.h"




 




#line 11 "..\\marvel\\driver\\inc\\dev.h"
#line 12 "..\\marvel\\driver\\inc\\dev.h"
#line 1 "..\\marvel\\driver\\inc\\hostcmd.h"



 



#line 9 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 10 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 1 "..\\marvel\\driver\\inc\\mdef.h"



 








#line 17 "..\\marvel\\driver\\inc\\mdef.h"
#line 18 "..\\marvel\\driver\\inc\\mdef.h"

#line 44 "..\\marvel\\driver\\inc\\mdef.h"




































 



 











 

#line 104 "..\\marvel\\driver\\inc\\mdef.h"




 





 
#line 126 "..\\marvel\\driver\\inc\\mdef.h"

 
 






















 
#line 158 "..\\marvel\\driver\\inc\\mdef.h"

 






 
#line 173 "..\\marvel\\driver\\inc\\mdef.h"

 



 




 


 



 

 

 


 

 

 

 


 



 
 


 



 



 



 





 







#line 246 "..\\marvel\\driver\\inc\\mdef.h"














 




#line 272 "..\\marvel\\driver\\inc\\mdef.h"





 
extern const char lbs_driver_version[];
extern u16 lbs_region_code_to_index[6];

extern u8 lbs_bg_rates[14];

 
 
enum SNRNF_TYPE {
	TYPE_BEACON = 0,
	TYPE_RXPD,
	MAX_TYPE_B
};

 
enum SNRNF_DATA {
	TYPE_NOAVG = 0,
	TYPE_AVG,
	MAX_TYPE_AVG
};

 
enum LBS_802_11_POWER_MODE {
	LBS802_11POWERMODECAM,
	LBS802_11POWERMODEMAX_PSP,
	LBS802_11POWERMODEFAST_PSP,
	 
	LBS802_11POWEMODEMAX
};

 
enum PS_STATE {
	PS_STATE_FULL_POWER,
	PS_STATE_AWAKE,
	PS_STATE_PRE_SLEEP,
	PS_STATE_SLEEP
};

 
enum DNLD_STATE {
	DNLD_RES_RECEIVED,
	DNLD_DATA_SENT,
	DNLD_CMD_SENT,
	DNLD_BOOTCMD_SENT,
};

 
enum LBS_MEDIA_STATE {
	LBS_CONNECTED,
	LBS_DISCONNECTED
};

 
enum LBS_802_11_PRIVACY_FILTER {
	LBS802_11PRIVFILTERACCEPTALL,
	LBS802_11PRIVFILTER8021XWEP
};

 
enum mv_ms_type {
	MVMS_DAT = 0,
	MVMS_CMD = 1,
	MVMS_TXDONE = 2,
	MVMS_EVENT
};

 
enum KEY_TYPE_ID {
	KEY_TYPE_ID_WEP = 0,
	KEY_TYPE_ID_TKIP,
	KEY_TYPE_ID_AES
};

 
enum KEY_INFO_WPA {
	KEY_INFO_WPA_MCAST = 0x01,
	KEY_INFO_WPA_UNICAST = 0x02,
	KEY_INFO_WPA_ENABLED = 0x04
};

 
enum _mesh_fw_ver {
	MESH_NONE = 0,  
	MESH_FW_OLD,    
	MESH_FW_NEW,    
};

 


 
#line 376 "..\\marvel\\driver\\inc\\mdef.h"





#line 11 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 1 "..\\marvel\\driver\\inc\\wireless.h"







 




#line 14 "..\\marvel\\driver\\inc\\wireless.h"
#line 15 "..\\marvel\\driver\\inc\\wireless.h"
#line 1 "..\\marvel\\driver\\inc\\if.h"

















 



#line 23 "..\\marvel\\driver\\inc\\if.h"
#line 24 "..\\marvel\\driver\\inc\\if.h"
#line 1 "..\\marvel\\driver\\inc\\wireless.h"







 

#line 1097 "..\\marvel\\driver\\inc\\wireless.h"

#line 25 "..\\marvel\\driver\\inc\\if.h"





 
#line 41 "..\\marvel\\driver\\inc\\if.h"


















 
#line 73 "..\\marvel\\driver\\inc\\if.h"




 
#line 85 "..\\marvel\\driver\\inc\\if.h"

 
#line 100 "..\\marvel\\driver\\inc\\if.h"

 
enum {
	IF_OPER_UNKNOWN,
	IF_OPER_NOTPRESENT,
	IF_OPER_DOWN,
	IF_OPER_LOWERLAYERDOWN,
	IF_OPER_TESTING,
	IF_OPER_DORMANT,
	IF_OPER_UP,
};

 
enum {
	IF_LINK_MODE_DEFAULT,
	IF_LINK_MODE_DORMANT,	 
};









 

struct ifmap 
{
	unsigned long mem_start;
	unsigned long mem_end;
	unsigned short base_addr; 
	unsigned char irq;
	unsigned char dma;
	unsigned char port;
	 
};





#line 16 "..\\marvel\\driver\\inc\\wireless.h"













































































































































 

 

 

 




 

 
#line 179 "..\\marvel\\driver\\inc\\wireless.h"

 
#line 187 "..\\marvel\\driver\\inc\\wireless.h"

 

 





 






 






 

 
#line 223 "..\\marvel\\driver\\inc\\wireless.h"

 


 









 



 


 



 



 


 







 











 

 

 




 



 
 
 

#line 325 "..\\marvel\\driver\\inc\\wireless.h"




 




 

#line 343 "..\\marvel\\driver\\inc\\wireless.h"








 

 

 



 

 


 


 

 



 


 


 
#line 388 "..\\marvel\\driver\\inc\\wireless.h"

 
#line 400 "..\\marvel\\driver\\inc\\wireless.h"

 




 


 


 
#line 422 "..\\marvel\\driver\\inc\\wireless.h"

 
#line 438 "..\\marvel\\driver\\inc\\wireless.h"

 






 
#line 457 "..\\marvel\\driver\\inc\\wireless.h"

 
#line 468 "..\\marvel\\driver\\inc\\wireless.h"
 


 


 
#line 483 "..\\marvel\\driver\\inc\\wireless.h"

 


 


 





 





 
#line 516 "..\\marvel\\driver\\inc\\wireless.h"

 





 
#line 530 "..\\marvel\\driver\\inc\\wireless.h"

 



 




 




 




 

 
#line 559 "..\\marvel\\driver\\inc\\wireless.h"
 





 
#line 572 "..\\marvel\\driver\\inc\\wireless.h"

 








 






 




 




 

 


 
struct	iw_param
{
  __s32		value;		 
  __u8		fixed;		 
  __u8		disabled;	 
  __u16		flags;		 
};




 
struct	iw_point
{
  void  	*pointer;	 
  __u16		length;		 
  __u16		flags;		 
};

#line 636 "..\\marvel\\driver\\inc\\wireless.h"








 
struct	iw_freq
{
	__s32		m;		 
	__s16		e;		 
	__u8		i;		 
	__u8		flags;		 
};



 
struct	iw_quality
{
	__u8		qual;		
 
	__u8		level;		 
	__u8		noise;		 
	__u8		updated;	 
};







 
struct	iw_discarded
{
	__u32		nwid;		 
	__u32		code;		 
	__u32		fragment;	 
	__u32		retries;	 
	__u32		misc;		 
};




 
struct	iw_missed
{
	__u32		beacon;		 
};



 
struct	iw_thrspy
{
	
	struct iw_quality	qual;		 
	struct iw_quality	low;		 
	struct iw_quality	high;		 
};











 
struct	iw_scan_req
{
	__u8		scan_type;  
	__u8		essid_len;
	__u8		num_channels; 
 
	__u8		flags; 

 
	
	

	




 
	__u8		essid[32];

	








 
	__u32		min_channel_time;  
	__u32		max_channel_time;  

	struct iw_freq	channel_list[32];
};

 
























 

struct	iw_encode_ext
{
	__u32		ext_flags;  
	__u8		tx_seq[8];  
	__u8		rx_seq[8];  
	
	

 
	__u16		alg;  
	__u16		key_len;
	__u8		key[64];
};

 
struct	iw_mlme
{
	__u16		cmd;  
	__u16		reason_code;
	
};

 






struct	iw_pmksa
{
	__u32		cmd;  
	
	__u8		pmkid[16];
};

 
struct	iw_michaelmicfailure
{
	__u32		flags;
	
	__u8		tsc[8];  
};

 

struct	iw_pmkid_cand
{
	__u32		flags;  
	__u32		index; 
 
	
};

 


 
struct	iw_statistics
{
	__u16		status;		
 

	struct iw_quality	qual;		
 
	struct iw_discarded	discard;	 
	struct iw_missed	miss;		 
};

 









 
union	iwreq_data
{
	 
	
	
 

	struct iw_point	essid;		 
	struct iw_param	nwid;		 
	struct iw_freq	freq;		

 

	struct iw_param	sens;		 
	struct iw_param	bitrate;	 
	struct iw_param	txpower;	 
	struct iw_param	rts;		 
	struct iw_param	frag;		 
	__u32		mode;		 
	struct iw_param	retry;		 

	struct iw_point	encoding;	 
	struct iw_param	power;		 
	struct iw_quality qual;		 

	
	

	struct iw_param	param;		 
	struct iw_point	data;		 
};






 
struct	iwreq 
{
	union
	{
		char	ifrn_name[16];	 
	} ifr_ifrn;

	 
	union	iwreq_data	u;
};

 



 



 

struct	iw_range
{
	 
	__u32		throughput;	 
	




 

	 
	__u32		min_nwid;	 
	__u32		max_nwid;	 

	 
	__u16		old_num_channels;
	__u8		old_num_frequency;

	 
	__u8		scan_capa; 	 

	 
	__u32		event_capa[6];

	 
	__s32		sensitivity;

	 
	


 
	struct iw_quality	max_qual;	 
	







 
	struct iw_quality	avg_qual;	 

	 
	__u8		num_bitrates;	 
	__s32		bitrate[32];	 

	 
	__s32		min_rts;	 
	__s32		max_rts;	 

	 
	__s32		min_frag;	 
	__s32		max_frag;	 

	 
	__s32		min_pmp;	 
	__s32		max_pmp;	 
	__s32		min_pmt;	 
	__s32		max_pmt;	 
	__u16		pmp_flags;	 
	__u16		pmt_flags;	 
	__u16		pm_capa;	 

	 
	__u16	encoding_size[8];	 
	__u8	num_encoding_sizes;	 
	__u8	max_encoding_tokens;	 
	 
	__u8	encoding_login_index;	 

	 
	__u16		txpower_capa;	 
	__u8		num_txpower;	 
	__s32		txpower[8];	 

	 
	__u8		we_version_compiled;	 
	__u8		we_version_source;	 

	 
	__u16		retry_capa;	 
	__u16		retry_flags;	 
	__u16		r_time_flags;	 
	__s32		min_retry;	 
	__s32		max_retry;	 
	__s32		min_r_time;	 
	__s32		max_r_time;	 

	 
	__u16		num_channels;	 
	__u8		num_frequency;	 
	struct iw_freq	freq[32];	 
	
 

	__u32		enc_capa;	 
};



 
 
struct	iw_priv_args
{
	__u32		cmd;		 
	__u16		set_args;	 
	__u16		get_args;	 
	char		name[16];	 
};

 




 



 
struct iw_event
{
	__u16		len;			 
	__u16		cmd;			 
	union iwreq_data	u;		 
};

 

 
#line 1053 "..\\marvel\\driver\\inc\\wireless.h"



 





#line 1084 "..\\marvel\\driver\\inc\\wireless.h"

 

 
#line 1095 "..\\marvel\\driver\\inc\\wireless.h"



#line 12 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 1 "..\\marvel\\driver\\inc\\mac80211.h"



#line 5 "..\\marvel\\driver\\inc\\mac80211.h"
#line 6 "..\\marvel\\driver\\inc\\mac80211.h"
#line 7 "..\\marvel\\driver\\inc\\mac80211.h"

#line 14 "..\\marvel\\driver\\inc\\mac80211.h"

 






 






#line 41 "..\\marvel\\driver\\inc\\mac80211.h"

 
enum ieee80211_eid {
	WLAN_EID_SSID = 0,
	WLAN_EID_SUPP_RATES = 1,
	WLAN_EID_FH_PARAMS = 2,
	WLAN_EID_DS_PARAMS = 3,
	WLAN_EID_CF_PARAMS = 4,
	WLAN_EID_TIM = 5,
	WLAN_EID_IBSS_PARAMS = 6,
	WLAN_EID_CHALLENGE = 16,
	 
	WLAN_EID_COUNTRY = 7,
	WLAN_EID_HP_PARAMS = 8,
	WLAN_EID_HP_TABLE = 9,
	WLAN_EID_REQUEST = 10,
	 
	WLAN_EID_QBSS_LOAD = 11,
	WLAN_EID_EDCA_PARAM_SET = 12,
	WLAN_EID_TSPEC = 13,
	WLAN_EID_TCLAS = 14,
	WLAN_EID_SCHEDULE = 15,
	WLAN_EID_TS_DELAY = 43,
	WLAN_EID_TCLAS_PROCESSING = 44,
	WLAN_EID_QOS_CAPA = 46,
	





 
	WLAN_EID_MESH_CONFIG = 51,
	WLAN_EID_MESH_ID = 52,
	WLAN_EID_PEER_LINK = 55,
	WLAN_EID_PREQ = 68,
	WLAN_EID_PREP = 69,
	WLAN_EID_PERR = 70,
	 
	WLAN_EID_PWR_CONSTRAINT = 32,
	WLAN_EID_PWR_CAPABILITY = 33,
	WLAN_EID_TPC_REQUEST = 34,
	WLAN_EID_TPC_REPORT = 35,
	WLAN_EID_SUPPORTED_CHANNELS = 36,
	WLAN_EID_CHANNEL_SWITCH = 37,
	WLAN_EID_MEASURE_REQUEST = 38,
	WLAN_EID_MEASURE_REPORT = 39,
	WLAN_EID_QUIET = 40,
	WLAN_EID_IBSS_DFS = 41,
	 
	WLAN_EID_ERP_INFO = 42,
	WLAN_EID_EXT_SUPP_RATES = 50,
	 
	WLAN_EID_HT_CAPABILITY = 45,
	WLAN_EID_HT_INFORMATION = 61,
	 
	WLAN_EID_RSN = 48,
	WLAN_EID_TIMEOUT_INTERVAL = 56,
	WLAN_EID_MMIE = 76  ,
	WLAN_EID_WPA = 221,
	WLAN_EID_GENERIC = 221,
	WLAN_EID_VENDOR_SPECIFIC = 221,
	WLAN_EID_QOS_PARAMETER = 222
};

 
enum ieee80211_category {
	WLAN_CATEGORY_SPECTRUM_MGMT = 0,
	WLAN_CATEGORY_QOS = 1,
	WLAN_CATEGORY_DLS = 2,
	WLAN_CATEGORY_BACK = 3,
	WLAN_CATEGORY_PUBLIC = 4,
	WLAN_CATEGORY_HT = 7,
	WLAN_CATEGORY_SA_QUERY = 8,
	WLAN_CATEGORY_PROTECTED_DUAL_OF_ACTION = 9,
	WLAN_CATEGORY_WMM = 17,
	WLAN_CATEGORY_VENDOR_SPECIFIC_PROTECTED = 126,
	WLAN_CATEGORY_VENDOR_SPECIFIC = 127,
};

 
enum ieee80211_spectrum_mgmt_actioncode {
	WLAN_ACTION_SPCT_MSR_REQ = 0,
	WLAN_ACTION_SPCT_MSR_RPRT = 1,
	WLAN_ACTION_SPCT_TPC_REQ = 2,
	WLAN_ACTION_SPCT_TPC_RPRT = 3,
	WLAN_ACTION_SPCT_CHL_SWITCH = 4,
};

 
enum ieee80211_key_len {
	WLAN_KEY_LEN_WEP40 = 5,
	WLAN_KEY_LEN_WEP104 = 13,
	WLAN_KEY_LEN_CCMP = 16,
	WLAN_KEY_LEN_TKIP = 32,
	WLAN_KEY_LEN_AES_CMAC = 16,
};




 






#line 161 "..\\marvel\\driver\\inc\\mac80211.h"

 




 
enum ieee80211_statuscode {
        WLAN_STATUS_SUCCESS = 0,
        WLAN_STATUS_UNSPECIFIED_FAILURE = 1,
        WLAN_STATUS_CAPS_UNSUPPORTED = 10,
        WLAN_STATUS_REASSOC_NO_ASSOC = 11,
        WLAN_STATUS_ASSOC_DENIED_UNSPEC = 12,
        WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG = 13,
        WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION = 14,
        WLAN_STATUS_CHALLENGE_FAIL = 15,
        WLAN_STATUS_AUTH_TIMEOUT = 16,
        WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA = 17,
        WLAN_STATUS_ASSOC_DENIED_RATES = 18,
         
        WLAN_STATUS_ASSOC_DENIED_NOSHORTPREAMBLE = 19,
        WLAN_STATUS_ASSOC_DENIED_NOPBCC = 20,
        WLAN_STATUS_ASSOC_DENIED_NOAGILITY = 21,
         
        WLAN_STATUS_ASSOC_DENIED_NOSPECTRUM = 22,
        WLAN_STATUS_ASSOC_REJECTED_BAD_POWER = 23,
        WLAN_STATUS_ASSOC_REJECTED_BAD_SUPP_CHAN = 24,
         
        WLAN_STATUS_ASSOC_DENIED_NOSHORTTIME = 25,
        WLAN_STATUS_ASSOC_DENIED_NODSSSOFDM = 26,
         
        WLAN_STATUS_INVALID_IE = 40,
        WLAN_STATUS_INVALID_GROUP_CIPHER = 41,
        WLAN_STATUS_INVALID_PAIRWISE_CIPHER = 42,
        WLAN_STATUS_INVALID_AKMP = 43,
        WLAN_STATUS_UNSUPP_RSN_VERSION = 44,
        WLAN_STATUS_INVALID_RSN_IE_CAP = 45,
        WLAN_STATUS_CIPHER_SUITE_REJECTED = 46,
};

 
enum ieee80211_reasoncode {
        WLAN_REASON_UNSPECIFIED = 1,
        WLAN_REASON_PREV_AUTH_NOT_VALID = 2,
        WLAN_REASON_DEAUTH_LEAVING = 3,
        WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY = 4,
        WLAN_REASON_DISASSOC_AP_BUSY = 5,
        WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA = 6,
        WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA = 7,
        WLAN_REASON_DISASSOC_STA_HAS_LEFT = 8,
        WLAN_REASON_STA_REQ_ASSOC_WITHOUT_AUTH = 9,
         
        WLAN_REASON_DISASSOC_BAD_POWER = 10,
        WLAN_REASON_DISASSOC_BAD_SUPP_CHAN = 11,
         
        WLAN_REASON_INVALID_IE = 13,
        WLAN_REASON_MIC_FAILURE = 14,
        WLAN_REASON_4WAY_HANDSHAKE_TIMEOUT = 15,
        WLAN_REASON_GROUP_KEY_HANDSHAKE_TIMEOUT = 16,
        WLAN_REASON_IE_DIFFERENT = 17,
        WLAN_REASON_INVALID_GROUP_CIPHER = 18,
        WLAN_REASON_INVALID_PAIRWISE_CIPHER = 19,
        WLAN_REASON_INVALID_AKMP = 20,
        WLAN_REASON_UNSUPP_RSN_VERSION = 21,
        WLAN_REASON_INVALID_RSN_IE_CAP = 22,
        WLAN_REASON_IEEE8021X_FAILED = 23,
        WLAN_REASON_CIPHER_SUITE_REJECTED = 24,
};













#line 257 "..\\marvel\\driver\\inc\\mac80211.h"

#line 270 "..\\marvel\\driver\\inc\\mac80211.h"

#line 277 "..\\marvel\\driver\\inc\\mac80211.h"








 









#line 303 "..\\marvel\\driver\\inc\\mac80211.h"

























#line 13 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 1 "..\\marvel\\driver\\inc\\hostcmd.h"



 
#line 789 "..\\marvel\\driver\\inc\\hostcmd.h"

#line 14 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 1 "..\\marvel\\driver\\inc\\types.h"


 



#line 8 "..\\marvel\\driver\\inc\\types.h"
#line 9 "..\\marvel\\driver\\inc\\types.h"
#line 10 "..\\marvel\\driver\\inc\\types.h"




struct ieee_ie_header {
	u8 id;
	u8 len;
} __attribute__ ((packed));

struct ieee_ie_cf_param_set {
	struct ieee_ie_header header;

	u8 cfpcnt;
	u8 cfpperiod;
	__le16 cfpmaxduration;
	__le16 cfpdurationremaining;
} __attribute__((packed));


struct ieee_ie_ibss_param_set {
	struct ieee_ie_header header;

	__le16 atimwindow;
} __attribute__((packed));

union ieee_ss_param_set {
	struct ieee_ie_cf_param_set cf;
	struct ieee_ie_ibss_param_set ibss;
} __attribute__((packed));

struct ieee_ie_fh_param_set {
	struct ieee_ie_header header;

	__le16 dwelltime;
	u8 hopset;
	u8 hoppattern;
	u8 hopindex;
} __attribute__((packed));

struct ieee_ie_ds_param_set {
	struct ieee_ie_header header;

	u8 channel;
} __attribute__((packed));

union ieee_phy_param_set {
	struct ieee_ie_fh_param_set fh;
	struct ieee_ie_ds_param_set ds;
} __attribute__((packed));

 


 


#line 72 "..\\marvel\\driver\\inc\\types.h"





#line 101 "..\\marvel\\driver\\inc\\types.h"

 
struct mrvl_ie_header {
	__le16 type;
	__le16 len;
} __attribute__((packed));

struct mrvl_ie_data {
	struct mrvl_ie_header header;
	u8 Data[1];
} __attribute__((packed));

struct mrvl_ie_rates_param_set {
	struct mrvl_ie_header header;
	u8 rates[1];
} __attribute__((packed));

struct mrvl_ie_ssid_param_set {
	struct mrvl_ie_header header;
	u8 ssid[1];
} __attribute__((packed));

struct mrvl_ie_wildcard_ssid_param_set {
	struct mrvl_ie_header header;
	u8 MaxSsidlength;
	u8 ssid[1];
} __attribute__((packed));

struct chanscanmode {





	u8 passivescan:1;
	u8 disablechanfilt:1;
	u8 reserved_2_7:6;

} __attribute__((packed));

struct chanscanparamset {
	u8 radiotype;
	u8 channumber;
	struct chanscanmode chanscanmode;
	__le16 minscantime;
	__le16 maxscantime;
} __attribute__((packed));

struct mrvl_ie_chanlist_param_set {
	struct mrvl_ie_header header;
	struct chanscanparamset chanscanparam[1];
} __attribute__((packed));

struct mrvl_ie_cf_param_set {
	struct mrvl_ie_header header;
	u8 cfpcnt;
	u8 cfpperiod;
	__le16 cfpmaxduration;
	__le16 cfpdurationremaining;
} __attribute__((packed));

struct mrvl_ie_ds_param_set {
	struct mrvl_ie_header header;
	u8 channel;
} __attribute__((packed));

struct mrvl_ie_rsn_param_set {
	struct mrvl_ie_header header;
	u8 rsnie[1];
} __attribute__((packed));

struct mrvl_ie_tsf_timestamp {
	struct mrvl_ie_header header;
	__le64 tsftable[1];
} __attribute__((packed));

 
struct mrvl_ie_auth_type {
	struct mrvl_ie_header header;
	__le16 auth;
} __attribute__((packed));

 
struct mrvl_ie_power_capability {
	struct mrvl_ie_header header;
	s8 minpower;
	s8 maxpower;
} __attribute__((packed));

 
struct mrvl_ie_thresholds {
	struct mrvl_ie_header header;
	u8 value;
	u8 freq;
} __attribute__((packed));

struct mrvl_ie_beacons_missed {
	struct mrvl_ie_header header;
	u8 beaconmissed;
	u8 reserved;
} __attribute__((packed));

struct mrvl_ie_num_probes {
	struct mrvl_ie_header header;
	__le16 numprobes;
} __attribute__((packed));

struct mrvl_ie_bcast_probe {
	struct mrvl_ie_header header;
	__le16 bcastprobe;
} __attribute__((packed));

struct mrvl_ie_num_ssid_probe {
	struct mrvl_ie_header header;
	__le16 numssidprobe;
} __attribute__((packed));

struct led_pin {
	u8 led;
	u8 pin;
} __attribute__((packed));

struct mrvl_ie_ledgpio {
	struct mrvl_ie_header header;
	struct led_pin ledpin[1];
} __attribute__((packed));

struct led_bhv {
	uint8_t	firmwarestate;
	uint8_t	led;
	uint8_t	ledstate;
	uint8_t	ledarg;
} __attribute__((packed));


struct mrvl_ie_ledbhv {
	struct mrvl_ie_header header;
	struct led_bhv ledbhv[1];
} __attribute__((packed));



 
struct mrvl_meshie_val {
	uint8_t oui[3];
	uint8_t type;
	uint8_t subtype;
	uint8_t version;
	uint8_t active_protocol_id;
	uint8_t active_metric_id;
	uint8_t mesh_capability;
	uint8_t mesh_id_len;
	uint8_t mesh_id[32];
} __attribute__((packed));

struct mrvl_meshie {
	u8 id, len;
	struct mrvl_meshie_val val;
} __attribute__((packed));

struct mrvl_mesh_defaults {
	__le32 bootflag;
	uint8_t boottime;
	uint8_t reserved;
	__le16 channel;
	struct mrvl_meshie meshie;
} __attribute__((packed));






#line 15 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 1 "..\\marvel\\driver\\inc\\list.h"
#line 4 "..\\marvel\\driver\\inc\\list.h"








 

#line 22 "..\\marvel\\driver\\inc\\list.h"



struct list_head {
	struct list_head *next, *prev;
};






static __inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}






 

static __inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}













 
static __inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}









 
static __inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}







 
static __inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}






 

static __inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = entry;
	entry->prev = entry;
}










 
static __inline void list_replace(struct list_head *old,
				struct list_head *new)
{
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;
}

static __inline void list_replace_init(struct list_head *old,
					struct list_head *new)
{
	list_replace(old, new);
	INIT_LIST_HEAD(old);
}




 
static __inline void list_del_init(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}





 
static __inline void list_move(struct list_head *list, struct list_head *head)
{
	__list_del(list->prev, list->next);
	list_add(list, head);
}





 
static __inline void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
}





 
static __inline int list_is_last(const struct list_head *list,
				const struct list_head *head)
{
	return list->next == head;
}




 
static __inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}













 
static __inline int list_empty_careful(const struct list_head *head)
{
	struct list_head *next = head->next;
	return (next == head) && (next == head->prev);
}




 
static __inline int list_is_singular(const struct list_head *head)
{
	return !list_empty(head) && (head->next == head->prev);
}

static __inline void __list_cut_position(struct list_head *list,
		struct list_head *head, struct list_head *entry)
{
	struct list_head *new_first = entry->next;
	list->next = head->next;
	list->next->prev = list;
	list->prev = entry;
	entry->next = list;
	head->next = new_first;
	new_first->prev = head;
}














 
static __inline void list_cut_position(struct list_head *list,
		struct list_head *head, struct list_head *entry)
{
	if (list_empty(head))
		return;
	if (list_is_singular(head) &&
		(head->next != entry && head != entry))
		return;
	if (entry == head)
		INIT_LIST_HEAD(list);
	else
		__list_cut_position(list, head, entry);
}

static __inline void __list_splice(const struct list_head *list,
				 struct list_head *prev,
				 struct list_head *next)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}





 
static __inline void list_splice(const struct list_head *list,
				struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head, head->next);
}





 
static __inline void list_splice_tail(struct list_head *list,
				struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head->prev, head);
}







 
static __inline void list_splice_init(struct list_head *list,
				    struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head, head->next);
		INIT_LIST_HEAD(list);
	}
}








 
static __inline void list_splice_tail_init(struct list_head *list,
					 struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head->prev, head);
		INIT_LIST_HEAD(list);
	}
}






 










 







 













 







 









 









 










 







 












 











 













 












 










 















 















 














 











 

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};




static __inline void INIT_HLIST_NODE(struct hlist_node *h)
{
	h->next = 0;
	h->pprev = 0;
}

static __inline int hlist_unhashed(const struct hlist_node *h)
{
	return !h->pprev;
}

static __inline int hlist_empty(const struct hlist_head *h)
{
	return !h->first;
}

static __inline void __hlist_del(struct hlist_node *n)
{
	struct hlist_node *next = n->next;
	struct hlist_node **pprev = n->pprev;
	*pprev = next;
	if (next)
		next->pprev = pprev;
}
























 				  

 
static __inline void hlist_add_before(struct hlist_node *n,
					struct hlist_node *next)
{
	n->pprev = next->pprev;
	n->next = next;
	next->pprev = &n->next;
	*(n->pprev) = n;
}

static __inline void hlist_add_after(struct hlist_node *n,
					struct hlist_node *next)
{
	next->next = n->next;
	n->next = next;
	next->pprev = &n->next;

	if(next->next)
		next->next->pprev  = &next->next;
}




 
static __inline void hlist_move_list(struct hlist_head *old,
				   struct hlist_head *new)
{
	new->first = old->first;
	if (new->first)
		new->first->pprev = &new->first;
	old->first = 0;
}	 

















 











 











 












 








#line 16 "..\\marvel\\driver\\inc\\hostcmd.h"
#line 1 "..\\marvel\\driver\\inc\\11d.h"



#line 5 "..\\marvel\\driver\\inc\\11d.h"
#line 6 "..\\marvel\\driver\\inc\\11d.h"
#line 1 "..\\marvel\\driver\\inc\\dev.h"




 
#line 7 "..\\marvel\\driver\\inc\\11d.h"
#line 8 "..\\marvel\\driver\\inc\\11d.h"
#line 9 "..\\marvel\\driver\\inc\\11d.h"






 





struct cmd_ds_command;


#pragma pack(1)
 
struct ieee_subbandset {
	u8 firstchan;
	u8 nrchan;
	u8 maxtxpwr;
} __attribute__((packed));
#pragma pack()


struct ieee_ie_country_info_set {
 	struct ieee_ie_header header;
	u8 countrycode[3];
	struct ieee_subbandset subband[1];
};
#pragma pack(1)
struct mrvl_ie_domain_param_set {
	struct mrvl_ie_header header;
	u8 countrycode[3];
	struct ieee_subbandset subband[1];
} __attribute__((packed));

struct cmd_ds_802_11d_domain_info {
	__le16 action;
	struct mrvl_ie_domain_param_set domain;
} __attribute__((packed));

#pragma pack()


 
struct lbs_802_11d_domain_reg {
	 
	u8 countrycode[3];
	 
	u8 nr_subband;
	struct ieee_subbandset subband[83];
};


#pragma pack(1)
struct chan_power_11d {
	u8 chan;
	u8 pwr;
} __attribute__((packed));

struct parsed_region_chan_11d {
	u8 band;
	u8 region;
	s8 countrycode[3];
	struct chan_power_11d chanpwr[40];
	u8 nr_chan;
} __attribute__((packed));

#pragma pack()

struct region_code_mapping {
	u8 region[3];
	u8 code;
};


#pragma pack(1)
struct ieee_ie_country_info_full_set {
	 struct ieee_ie_header header;
	 u8 countrycode[3];
	 struct ieee_subbandset subband[83];
} __attribute__((packed));
#pragma pack()

struct lbs_private;
struct bss_descriptor;
int lbs_set_universaltable(struct lbs_private *priv, u8 band);
void lbs_init_11d(struct lbs_private *priv);
int lbs_cmd_802_11d_domain_info(struct lbs_private *priv,
				 struct cmd_ds_command *cmd, u16 cmdno,
				 u16 cmdOption);
int lbs_ret_802_11d_domain_info(struct cmd_ds_command *resp);
int lbs_parse_dnld_countryinfo_11d(struct lbs_private *priv,
                                        struct bss_descriptor * bss);
int lbs_create_dnld_countryinfo_11d(struct lbs_private *priv);
int lbs_parse_dnld_countryinfo_11d(struct lbs_private *priv,struct bss_descriptor * bss);




#line 17 "..\\marvel\\driver\\inc\\hostcmd.h"

#pragma pack(1)
 
 
struct txpd {
	 
	union {
		 
		__le32 tx_status;
		struct {
			 
			u8 bss_type;
			 
			u8 bss_num;
			 
			__le16 reserved;
		} __attribute__((packed)) bss;

	} __attribute__((packed)) u ;

	 
	__le32 tx_control;
	__le32 tx_packet_location;
	 
	__le16 tx_packet_length;
	 
	u8 tx_dest_addr_high[2];
	 
	u8 tx_dest_addr_low[4];
	 
	u8 priority;
	 
	u8 powermgmt;
	 
	u8 pktdelay_2ms;
	 
	u8 reserved1;
} __attribute__((packed));

 
struct rxpd {
	 
	union {
		 
		__le16 status;
		struct {
			 
			u8 bss_type;
			 
			u8 bss_num;
		} __attribute__((packed)) bss;
	} __attribute__((packed)) u;

	 
	u8 snr;
	 
	u8 rx_control;
	 
	__le16 pkt_len;
	 
	u8 nf;
	 
	u8 rx_rate;
	 
	__le32 pkt_ptr;
	 
	__le32 next_rxpd_ptr;
	 
	u8 priority;
	u8 reserved[3];
} __attribute__((packed));

struct cmd_header {
	__le16 command;
	__le16 size;
	__le16 seqnum;
	__le16 result;
} __attribute__((packed));
#pragma pack()

struct lbs_private;
struct cmd_ctrl_node {
	struct list_head list;
	int result;
	 
	int (*callback)(struct lbs_private *, unsigned long, struct cmd_header *);
	unsigned long callback_arg;
	 
	struct cmd_header *cmdbuf;
	 
	u16 cmdwaitqwoken;
};

 
struct enc_key {
	u16 len;
	u16 flags;   
	u16 type;  
	u8 key[32];
};


#pragma pack(1)
 
 
struct cmd_ds_gen {
	__le16 command;
	__le16 size;
	__le16 seqnum;
	__le16 result;
	void *cmdresp[1];
} __attribute__((packed));







 
struct cmd_ds_get_hw_spec {
	struct cmd_header hdr;

	 
	__le16 hwifversion;
	 
	__le16 version;
	 
	__le16 nr_txpd;
	 
	__le16 nr_mcast_adr;
	 
	u8 permanentaddr[6];

	 
	__le16 regioncode;

	 
	__le16 nr_antenna;

	 
	__le32 fwrelease;

	 
	__le32 wcb_base;
	 
	__le32 rxpd_rdptr;

	 
	__le32 rxpd_wrptr;

	 
	__le32 fwcapinfo;
} __attribute__((packed));

struct cmd_ds_802_11_subscribe_event {
	struct cmd_header hdr;

	__le16 action;
	__le16 events;

	



 
	uint8_t tlv[128];
} __attribute__((packed));




 
struct cmd_ds_802_11_scan {
	struct cmd_header hdr;

	uint8_t bsstype;
	uint8_t bssid[6];
	uint8_t tlvbuffer[1];
} __attribute__((packed));

struct cmd_ds_802_11_scan_rsp {
	struct cmd_header hdr;

	__le16 bssdescriptsize;
	uint8_t nr_sets;
	uint8_t bssdesc_and_tlvbuffer[1];
} __attribute__((packed));

struct cmd_ds_802_11_get_log {
	struct cmd_header hdr;

	__le32 mcasttxframe;
	__le32 failed;
	__le32 retry;
	__le32 multiretry;
	__le32 framedup;
	__le32 rtssuccess;
	__le32 rtsfailure;
	__le32 ackfailure;
	__le32 rxfrag;
	__le32 mcastrxframe;
	__le32 fcserror;
	__le32 txframe;
	__le32 wepundecryptable;
} __attribute__((packed));

struct cmd_ds_mac_control {
	struct cmd_header hdr;
	__le16 action;
	u16 reserved;
} __attribute__((packed));

struct cmd_ds_mac_multicast_adr {
	struct cmd_header hdr;
	__le16 action;
	__le16 nr_of_adrs;
	u8 maclist[6 * 32];
} __attribute__((packed));

struct cmd_ds_gspi_bus_config {
	struct cmd_header hdr;
	__le16 action;
	__le16 bus_delay_mode;
	__le16 host_time_delay_to_read_port;
	__le16 host_time_delay_to_read_register;
} __attribute__((packed));

struct cmd_ds_802_11_authenticate {
	struct cmd_header hdr;

	u8 bssid[6];
	u8 authtype;
	u8 reserved[10];
} __attribute__((packed));

struct cmd_ds_802_11_deauthenticate {
	struct cmd_header hdr;

	u8 macaddr[6];
	__le16 reasoncode;
} __attribute__((packed));

struct cmd_ds_802_11_associate {
	struct cmd_header hdr;

	u8 bssid[6];
	__le16 capability;
	__le16 listeninterval;
	__le16 bcnperiod;
	u8 dtimperiod;
	u8 iebuf[512];     
} __attribute__((packed));

struct cmd_ds_802_11_associate_response {
	struct cmd_header hdr;

	__le16 capability;
	__le16 statuscode;
	__le16 aid;
	u8 iebuf[512];
} __attribute__((packed));

struct cmd_ds_802_11_set_wep {
	struct cmd_header hdr;

	 
	__le16 action;

	 
	__le16 keyindex;

	 
	uint8_t keytype[4];
	uint8_t keymaterial[4][16];
} __attribute__((packed));

struct cmd_ds_802_3_get_stat {
	__le32 xmitok;
	__le32 rcvok;
	__le32 xmiterror;
	__le32 rcverror;
	__le32 rcvnobuffer;
	__le32 rcvcrcerror;
} __attribute__((packed));

struct cmd_ds_802_11_get_stat {
	__le32 txfragmentcnt;
	__le32 mcasttxframecnt;
	__le32 failedcnt;
	__le32 retrycnt;
	__le32 Multipleretrycnt;
	__le32 rtssuccesscnt;
	__le32 rtsfailurecnt;
	__le32 ackfailurecnt;
	__le32 frameduplicatecnt;
	__le32 rxfragmentcnt;
	__le32 mcastrxframecnt;
	__le32 fcserrorcnt;
	__le32 bcasttxframecnt;
	__le32 bcastrxframecnt;
	__le32 txbeacon;
	__le32 rxbeacon;
	__le32 wepundecryptable;
} __attribute__((packed));

struct cmd_ds_802_11_snmp_mib {
	struct cmd_header hdr;

	__le16 action;
	__le16 oid;
	__le16 bufsize;
	u8 value[128];
} __attribute__((packed));

struct cmd_ds_mac_reg_map {
	__le16 buffersize;
	u8 regmap[128];
	__le16 reserved;
} __attribute__((packed));

struct cmd_ds_bbp_reg_map {
	__le16 buffersize;
	u8 regmap[128];
	__le16 reserved;
} __attribute__((packed));

struct cmd_ds_rf_reg_map {
	__le16 buffersize;
	u8 regmap[64];
	__le16 reserved;
} __attribute__((packed));

struct cmd_ds_mac_reg_access {
	__le16 action;
	__le16 offset;
	__le32 value;
} __attribute__((packed));

struct cmd_ds_bbp_reg_access {
	__le16 action;
	__le16 offset;
	u8 value;
	u8 reserved[3];
} __attribute__((packed));

struct cmd_ds_rf_reg_access {
	__le16 action;
	__le16 offset;
	u8 value;
	u8 reserved[3];
} __attribute__((packed));

struct cmd_ds_802_11_radio_control {
	struct cmd_header hdr;

	__le16 action;
	__le16 control;
} __attribute__((packed));

struct cmd_ds_802_11_beacon_control {
	__le16 action;
	__le16 beacon_enable;
	__le16 beacon_period;
} __attribute__((packed));

struct cmd_ds_802_11_sleep_params {
	struct cmd_header hdr;

	 
	__le16 action;

	 
	__le16 error;

	 
	__le16 offset;

	 
	__le16 stabletime;

	 
	uint8_t calcontrol;

	 
	uint8_t externalsleepclk;

	 
	__le16 reserved;
} __attribute__((packed));

struct cmd_ds_802_11_inactivity_timeout {
	struct cmd_header hdr;

	 
	__le16 action;

	 
	__le16 timeout;
} __attribute__((packed));

struct cmd_ds_802_11_rf_channel {
	struct cmd_header hdr;

	__le16 action;
	__le16 channel;
	__le16 rftype;       
	__le16 reserved;     
	u8 channellist[32];  
} __attribute__((packed));

struct cmd_ds_802_11_rssi {
	 
	__le16 N;

	__le16 reserved_0;
	__le16 reserved_1;
	__le16 reserved_2;
} __attribute__((packed));

struct cmd_ds_802_11_rssi_rsp {
	__le16 SNR;
	__le16 noisefloor;
	__le16 avgSNR;
	__le16 avgnoisefloor;
} __attribute__((packed));

struct cmd_ds_802_11_mac_address {
	struct cmd_header hdr;

	__le16 action;
	u8 macadd[6];
} __attribute__((packed));

struct cmd_ds_802_11_rf_tx_power {
	struct cmd_header hdr;

	__le16 action;
	__le16 curlevel;
	s8 maxlevel;
	s8 minlevel;
} __attribute__((packed));

struct cmd_ds_802_11_rf_antenna {
	__le16 action;

	 
	__le16 antennamode;

} __attribute__((packed));

struct cmd_ds_802_11_monitor_mode {
	__le16 action;
	__le16 mode;
} __attribute__((packed));

struct cmd_ds_set_boot2_ver {
	struct cmd_header hdr;

	__le16 action;
	__le16 version;
} __attribute__((packed));

struct cmd_ds_802_11_fw_wake_method {
	struct cmd_header hdr;

	__le16 action;
	__le16 method;
} __attribute__((packed));

struct cmd_ds_802_11_sleep_period {
	struct cmd_header hdr;

	__le16 action;
	__le16 period;
} __attribute__((packed));

struct cmd_ds_802_11_ps_mode {
	__le16 action;
	__le16 nullpktinterval;
	__le16 multipledtim;
	__le16 reserved;
	__le16 locallisteninterval;
} __attribute__((packed));

struct cmd_confirm_sleep {
	struct cmd_header hdr;

	__le16 action;
	__le16 nullpktinterval;
	__le16 multipledtim;
	__le16 reserved;
	__le16 locallisteninterval;
} __attribute__((packed));

struct cmd_ds_802_11_data_rate {
	struct cmd_header hdr;

	__le16 action;
	__le16 reserved;
	u8 rates[14];
} __attribute__((packed));

struct cmd_ds_802_11_rate_adapt_rateset {
	struct cmd_header hdr;
	__le16 action;
	__le16 enablehwauto;
	__le16 bitmap;
} __attribute__((packed));

struct cmd_ds_802_11_ad_hoc_start {
	struct cmd_header hdr;

	u8 ssid[32];
	u8 bsstype;
	__le16 beaconperiod;
	u8 dtimperiod;    
	 struct ieee_ie_ibss_param_set ibss;
	u8 reserved1[4];
	 struct ieee_ie_ds_param_set ds;
	u8 reserved2[4];
	__le16 probedelay;   
	__le16 capability;
	u8 rates[14];
	u8 tlv_memory_size_pad[100];
} __attribute__((packed));

struct cmd_ds_802_11_ad_hoc_result {
	struct cmd_header hdr;

	u8 pad[3];
	u8 bssid[6];
} __attribute__((packed));

struct adhoc_bssdesc {
	u8 bssid[6];
	u8 ssid[32];
	u8 type;
	__le16 beaconperiod;
	u8 dtimperiod;
	__le64 timestamp;
	__le64 localtime;
	 struct ieee_ie_ds_param_set ds;
	u8 reserved1[4];
	 struct ieee_ie_ibss_param_set ibss;
	u8 reserved2[4];
	__le16 capability;
	u8 rates[14];
} __attribute__((packed));

struct cmd_ds_802_11_ad_hoc_join {
	struct cmd_header hdr;

	struct adhoc_bssdesc bss;
	__le16 failtimeout;    
	__le16 probedelay;     
} __attribute__((packed));

struct cmd_ds_802_11_ad_hoc_stop {
	struct cmd_header hdr;
} __attribute__((packed));

struct cmd_ds_802_11_enable_rsn {
	struct cmd_header hdr;

	__le16 action;
	__le16 enable;
} __attribute__((packed));

struct MrvlIEtype_keyParamSet {
	 
	__le16 type;

	 
	__le16 length;

	 
	__le16 keytypeid;

	 
	__le16 keyinfo;

	 
	__le16 keylen;

	 
	u8 key[32];
} __attribute__((packed));



struct host_wol_rule {
	uint8_t rule_no;
	uint8_t rule_ops;
	__le16 sig_offset;
	__le16 sig_length;
	__le16 reserve;
	__be32 sig_mask;
	__be32 signature;
} __attribute__((packed));

struct wol_config {
	uint8_t action;
	uint8_t pattern;
	uint8_t no_rules_in_cmd;
	uint8_t result;
	struct host_wol_rule rule[16];
} __attribute__((packed));

struct cmd_ds_host_sleep {
	struct cmd_header hdr;
	__le32 criteria;
	uint8_t gpio;
	uint16_t gap;
	struct wol_config wol_conf;
} __attribute__((packed));



struct cmd_ds_802_11_key_material {
	struct cmd_header hdr;

	__le16 action;
	struct MrvlIEtype_keyParamSet keyParamSet[2];
} __attribute__((packed));

struct cmd_ds_802_11_eeprom_access {
	struct cmd_header hdr;
	__le16 action;
	__le16 offset;
	__le16 len;
	 

	u8 value[20];
} __attribute__((packed));

struct cmd_ds_802_11_tpc_cfg {
	struct cmd_header hdr;

	__le16 action;
	uint8_t enable;
	int8_t P0;
	int8_t P1;
	int8_t P2;
	uint8_t usesnr;
} __attribute__((packed));


struct cmd_ds_802_11_pa_cfg {
	struct cmd_header hdr;

	__le16 action;
	uint8_t enable;
	int8_t P0;
	int8_t P1;
	int8_t P2;
} __attribute__((packed));


struct cmd_ds_802_11_led_ctrl {
	__le16 action;
	__le16 numled;
	u8 data[256];
} __attribute__((packed));

struct cmd_ds_802_11_afc {
	__le16 afc_auto;
	union {
		struct {
			__le16 threshold;
			__le16 period;
		}__attribute__((packed)) the;
		struct {
			__le16 timing_offset;  
			__le16 carrier_offset;  
		}__attribute__((packed)) offset;
	}__attribute__((packed)) parm;
} __attribute__((packed));

struct cmd_tx_rate_query {
	__le16 txrate;
} __attribute__((packed));

struct cmd_ds_get_tsf {
	__le64 tsfvalue;
} __attribute__((packed));

struct cmd_ds_bt_access {
	__le16 action;
	__le32 id;
	u8 addr1[6];
	u8 addr2[6];
} __attribute__((packed));

struct cmd_ds_fwt_access {
	__le16 action;
	__le32 id;
	u8 valid;
	u8 da[6];
	u8 dir;
	u8 ra[6];
	__le32 ssn;
	__le32 dsn;
	__le32 metric;
	u8 rate;
	u8 hopcount;
	u8 ttl;
	__le32 expiration;
	u8 sleepmode;
	__le32 snr;
	__le32 references;
	u8 prec[6];
} __attribute__((packed));


struct cmd_ds_mesh_config {
	struct cmd_header hdr;

        __le16 action;
        __le16 channel;
        __le16 type;
        __le16 length;
        u8 data[128];    
} __attribute__((packed));


struct cmd_ds_mesh_access {
	struct cmd_header hdr;

	__le16 action;
	__le32 data[32];	 
} __attribute__((packed));

 


struct cmd_ds_command {
	 
	__le16 command;
	__le16 size;
	__le16 seqnum;
	__le16 result;

	 
	union {
		struct cmd_ds_802_11_ps_mode psmode;
		struct cmd_ds_802_11_get_stat gstat;
		struct cmd_ds_802_3_get_stat gstat_8023;
		struct cmd_ds_802_11_rf_antenna rant;
		struct cmd_ds_802_11_monitor_mode monitor;
		struct cmd_ds_802_11_rssi rssi;
		struct cmd_ds_802_11_rssi_rsp rssirsp;
		struct cmd_ds_mac_reg_access macreg;
		struct cmd_ds_bbp_reg_access bbpreg;
		struct cmd_ds_rf_reg_access rfreg;

		struct cmd_ds_802_11d_domain_info domaininfo;
		struct cmd_ds_802_11d_domain_info domaininforesp;

		struct cmd_ds_802_11_tpc_cfg tpccfg;
		struct cmd_ds_802_11_afc afc;
		struct cmd_ds_802_11_led_ctrl ledgpio;

		struct cmd_tx_rate_query txrate;
		struct cmd_ds_bt_access bt;
		struct cmd_ds_fwt_access fwt;
		struct cmd_ds_get_tsf gettsf;
		struct cmd_ds_802_11_beacon_control bcn_ctrl;
	} __attribute__((packed)) params;
} __attribute__((packed));
#pragma pack()


#line 13 "..\\marvel\\driver\\inc\\dev.h"
#line 14 "..\\marvel\\driver\\inc\\dev.h"
#line 15 "..\\marvel\\driver\\inc\\dev.h"
#line 16 "..\\marvel\\driver\\inc\\dev.h"
#line 17 "..\\marvel\\driver\\inc\\dev.h"
#line 18 "..\\marvel\\driver\\inc\\dev.h"

struct sdio_func;
typedef void (sdio_irq_handler_t)(struct sdio_func *);





 





 
struct chan_freq_power {
	 
	u16 channel;
	 
	u32 freq;
	 
	u16 maxtxpower;
	 
	u8 unsupported;
};

 
struct region_channel {
	 
	u8 valid;
	 
	u8 region;
	 
	u8 band;
	 
	u8 nrcfp;
	 
	struct chan_freq_power *CFP;
};

struct lbs_802_11_security {
	u8 WPAenabled;
	u8 WPA2enabled;
	u8 wep_enabled;
	u8 auth_mode;
	u32 key_mgmt;
};

 
struct current_bss_params {
	 
 	u8 bssid[6];
	 
 	u8 ssid[32 + 1];
	u8 ssid_len;

	 
	u8 band;
	 
	u8 channel;
	 
	u8 rates[14 + 1];
};

 
struct sleep_params {
	uint16_t sp_error;
	uint16_t sp_offset;
	uint16_t sp_stabletime;
	uint8_t  sp_calcontrol;
	uint8_t  sp_extsleepclk;
	uint16_t sp_reserved;
};

 
struct lbs_mesh_stats {
	u32	fwd_bcast_cnt;		 
	u32	fwd_unicast_cnt;	 
	u32	fwd_drop_ttl;		 
	u32	fwd_drop_rbt;		 
	u32	fwd_drop_noroute; 	 
	u32	fwd_drop_nobuf;		 
	u32	drop_blind;		 
	u32	tx_failed_cnt;		 
};
 
 
#pragma pack(1)
struct lbs_offset_value {
	u32 offset;
	u32 value;
} __attribute__((packed));
#pragma pack()

struct kfifo{
	char len;
	u32 env;
};







struct eth_packet{
	u16 len;
	char *data;
};

struct lbs_private {
	struct eth_packet rx_pkt;
	char name[32];
	void *card;
	 
	int scan_channel;
	u8 scan_ssid[32 + 1];
	u8 scan_ssid_len;
	 
	int (*hw_host_to_card) (struct lbs_private *priv, u8 type, u8 *payload, u16 nb);
	
	struct lbs_offset_value offsetvalue;
	 
 	uint32_t wol_criteria;
	uint8_t wol_gpio;
	uint8_t wol_gap; 
	 
	 
	u32 fwrelease;
	u32 fwcapinfo;
	 
	int tx_pending_len;		 
	 
	 
	u16 seqnum;
	 struct cmd_ctrl_node *cmd_array;
	 
	 struct cmd_ctrl_node *cur_cmd;
	int cur_cmd_retcode;
	 
	 
	 struct list_head cmdfreeq;
	 
	 struct list_head cmdpendingq;
	 
	struct kfifo *event_fifo;
	 
	u8 nodename[16];
	int nr_retries;
	int cmd_timed_out;
	 
	struct current_bss_params curbssparams;
	 
	u8 mode;
	 
	struct list_head network_list;
	struct list_head network_free_list;
	struct bss_descriptor *networks;
	struct bss_descriptor *cur_bss;
	u16 beacon_period;
	u8 beacon_enable;
	u8 adhoccreate;
	 
	u16 capability;
	 
	u8 current_addr[6];
	u8 multicastlist[32][6];
	u32 nr_of_multicastmacaddr;
	uint16_t enablehwauto;
	uint16_t ratebitmap;
	u8 txretrycount;
	 
	u16 mac_control;
	u32 connect_status;
	u32 mesh_connect_status;
	u16 regioncode;
	s16 txpower_cur;
	s16 txpower_min;
	s16 txpower_max;
	 
	u8 surpriseremoved;
	u16 psmode;		
 
	u32 psstate;
	u8 needtowakeup;
	struct assoc_request * pending_assoc_req;
	struct assoc_request * in_progress_assoc_req;
	 
	struct lbs_802_11_security secinfo;
	 
	struct enc_key wep_keys[4];
	u16 wep_tx_keyidx;
	 
	 struct enc_key wpa_mcast_key;
	 struct enc_key wpa_unicast_key;
	 
	u16 SNR[MAX_TYPE_B][MAX_TYPE_AVG];
	u16 NF[MAX_TYPE_B][MAX_TYPE_AVG];
	u8 RSSI[MAX_TYPE_B][MAX_TYPE_AVG];
	u8 rawSNR[8];
	u8 rawNF[8];
	u16 nextSNRNF;
	u16 numSNRNF;
	u8 radio_on;
	 
	u8 cur_rate;
	 

	 
	struct region_channel region_channel[2];
	struct region_channel universal_channel[2];
	 
	struct lbs_802_11d_domain_reg domainreg;
	struct parsed_region_chan_11d parsed_region_chan;
	 
	u32 enable11d;
	 
	u32 monitormode;
	u8 fw_ready;
	 
	u8 resp_idx;
	u32 resp_len[1];
	u8 resp_buf[1][1024*3];
	int mesh_open;
	int mesh_fw_ver;
	int infra_open;
	int mesh_autostart_enabled;
	
	u32 mac_offset;
	u32 bbp_offset;
	u32 rf_offset;
	u8 dnld_sent;

	uint16_t mesh_tlv;
	u8 mesh_ssid[32 + 1];
	u8 mesh_ssid_len;
	


 

	 
	u8 wpa_ie[64];
	u8 wpa_ie_len;
	u8 eapol_finish;


	 
	u8 __wpa_ie[64];
	u8 __wpa_ie_len;
	u8 __mac_addr[6];
	
};





 








struct bss_descriptor {
	u8 bssid[6];
	u8 ssid[32 + 1];
	u8 ssid_len;
	u16 capability;
	u32 rssi;
	u32 channel;
	u16 beaconperiod;
	__le16 atimwindow;
	 
	u8 mode;
	 
	u8 rates[14 + 1];
	unsigned long last_scanned;
	 union ieee_phy_param_set phy;
	 union ieee_ss_param_set ss;
	struct  ieee_ie_country_info_full_set countryinfo;
	u8 wpa_ie[64];
	size_t wpa_ie_len;
	u8 rsn_ie[64];
	size_t rsn_ie_len; 
	u8 mesh;
	struct list_head list;

};







 
  
#line 330 "..\\marvel\\driver\\inc\\dev.h"
struct assoc_request {

	unsigned long flags;

	u8 ssid[32 + 1];
	u8 ssid_len;
	u8 channel;
	u8 band;
	u8 mode;
#pragma pack(2)
	u8 bssid[6] __attribute__ ((aligned (2)));
#pragma pack()
	 
	struct enc_key wep_keys[4];
	u16 wep_tx_keyidx;
	 
	struct enc_key wpa_mcast_key;
	struct enc_key wpa_unicast_key;
	struct lbs_802_11_security secinfo;
	 
	u8 wpa_ie[64];
	u8 wpa_ie_len;
	 
	struct bss_descriptor bss;
	u8 * psk;
};












 
#line 382 "..\\marvel\\driver\\inc\\dev.h"
					 



 



 
#line 399 "..\\marvel\\driver\\inc\\dev.h"

 







 








#line 19 "..\\marvel\\driver\\inc\\if_sdio.h"











































struct if_sdio_packet {
	struct if_sdio_packet	*next;
	u16			nb;
	u8			buffer[1024] ;
};
struct firmware {
	u32 size;
	const u8 *data;
};

struct if_sdio_card {
	struct sdio_func	*func;
	struct lbs_private	*priv;

	int					model;
	unsigned long		ioport;
	unsigned int		scratch_reg;

	const struct firmware 	*helper;
	const struct firmware 	*firmware;
	u8			rx_unit;
	struct if_sdio_packet	*packets;
	
	u8			buffer[1600];

	
};


void if_sdio_interrupt(struct sdio_func *func);
u8 sdio_readb(struct sdio_func *func, unsigned int addr, int *err_ret);
int if_sdio_send_data(struct lbs_private *priv, u8 *buf, u16 nb);
static int if_sdio_handle_event(struct if_sdio_card *card,u8 *buffer, unsigned size);
int pool_sdio_interrupt(struct sdio_func *func);
int  wait_for_data_end(void);
struct sdio_func;
struct sdio_device_id;
struct lbs_private *if_sdio_probe(struct sdio_func *func,struct sdio_device_id *id);



#line 22 "..\\sdio\\inc\\sdio_func.h"
#line 23 "..\\sdio\\inc\\sdio_func.h"

struct sdio_func;





 
struct sdio_func_tuple {
	struct sdio_func_tuple *next;
	unsigned char code;
	unsigned char size;
	unsigned char data[255];
};



 

 

 
struct sdio_func {
	struct mmc_card		*card;		 
	struct if_sdio_card		*if_card; 

	sdio_irq_handler_t	*irq_handler;	 
	unsigned int		num;		 
	 
	unsigned char		class;		 
	unsigned short		vendor;		 
	unsigned short		device;		 

	unsigned		max_blksize;	 
	unsigned		cur_blksize;	 

	unsigned		enable_timeout;	 

	unsigned int		state;		 


	u8			tmpbuf[4];	 

	unsigned		num_info;	 
	const char		**info;		 

	struct sdio_func_tuple *tuples; 
};









 



struct sdio_device_id {
	u8	class;			 
	u16	vendor;			 
	u16	device;			 
};




 
struct sdio_driver {
	char *name;
	struct sdio_device_id *id_table;
	char *(*probe)(struct sdio_func *, struct sdio_device_id *);
	void (*remove)(struct sdio_func *);

	
};









#line 22 "..\\sdio\\inc\\sdio.h"



 
 












 










 














 

#line 74 "..\\sdio\\inc\\sdio.h"



 



































#line 121 "..\\sdio\\inc\\sdio.h"



 



















 




























 
 
 

 
   
 



   


   
















 







 



 







 





 





 




 




 


 
struct mmc_host;
struct mmc_card;
int mmc_send_io_op_cond(struct mmc_host *host, u32 ocr, u32 *rocr);
int mmc_send_if_cond(struct mmc_host *host, u32 ocr);
int mmc_send_relative_addr(struct mmc_host *host, unsigned int *rca);
int mmc_io_rw_direct(struct mmc_card *card, int write, unsigned fn,unsigned addr, u8 in, u8* out);
int mmc_select_card(struct mmc_card *card);
int mmc_attach_sdio(struct mmc_host *host, u32 ocr);
int sdio_irq_thread(void *_host);


struct sdio_func;
u8 sdio_readb(struct sdio_func *func, unsigned int addr, int *err_ret);
void sdio_writeb(struct sdio_func *func, u8 b, unsigned int addr, int *err_ret);
int mmc_io_rw_extended(struct mmc_card *card, int write, unsigned fn,
	unsigned addr, int incr_addr, u8 *buf, unsigned blocks, unsigned blksz);
unsigned int sdio_align_size(struct sdio_func *func, unsigned int sz);



 int sdio_io_rw_ext_helper(struct sdio_func *func, int write,
	unsigned addr, int incr_addr, u8 *buf, unsigned size);







#line 11 "..\\sdio\\inc\\card.h"
#line 12 "..\\sdio\\inc\\card.h"


struct mmc_cid {
	unsigned int		manfid;
	char			prod_name[8];
	unsigned int		serial;
	unsigned short		oemid;
	unsigned short		year;
	unsigned char		hwrev;
	unsigned char		fwrev;
	unsigned char		month;
};

struct mmc_csd {
	unsigned char		mmca_vsn;
	unsigned short		cmdclass;
	unsigned short		tacc_clks;
	unsigned int		tacc_ns;
	unsigned int		r2w_factor;
	unsigned int		max_dtr;
	unsigned int		read_blkbits;
	unsigned int		write_blkbits;
	unsigned int		capacity;
	unsigned int		read_partial:1,
				read_misalign:1,
				write_partial:1,
				write_misalign:1;
};

struct mmc_ext_csd {
	u8			rev;
	unsigned int		sa_timeout;		 
	unsigned int		hs_max_dtr;
	unsigned int		sectors;
};

struct sd_scr {
	unsigned char		sda_vsn;
	unsigned char		bus_widths;


};

struct sd_switch_caps {
	unsigned int		hs_max_dtr;
};

struct sdio_cccr {
	unsigned int		sdio_vsn;
	unsigned int		sd_vsn;
	unsigned int		multi_block:1,
				low_speed:1,
				wide_bus:1,
				high_power:1,
				high_speed:1,
				disable_cd:1;
};

struct sdio_cis {
	unsigned short		vendor;
	unsigned short		device;
	unsigned short		blksize;
	unsigned int		max_dtr;
};






 
 




 





 


struct mmc_card {
	struct mmc_host		*host;		 
	
	unsigned int		rca;		 
	unsigned int		type;		 
	unsigned int		state;		 
	unsigned int		quirks; 	 

	u32			raw_cid[4];	 
	u32			raw_csd[4];	 
	u32			raw_scr[2];	 
	struct mmc_cid		cid;		 
	struct mmc_csd		csd;		 
	struct mmc_ext_csd	ext_csd;	 
	struct sd_scr		scr;		 
	struct sd_switch_caps	sw_caps;	 

	unsigned int		sdio_funcs;	 
	struct sdio_cccr	cccr;		 
	struct sdio_cis		cis;		 
	struct sdio_func	*sdio_func[7];  
	unsigned		num_info;	 
	const char		**info;		 
	struct sdio_func_tuple	*tuples;	 

	
};

















#line 9 "..\\sdio\\inc\\host.h"
#line 10 "..\\sdio\\inc\\host.h"
#line 11 "..\\sdio\\inc\\host.h"


 
 


 



 




 



 





struct mmc_ios {
	unsigned int	clock;			 
	unsigned short	vdd;
 
	unsigned char	bus_mode;		 

	unsigned char	chip_select;		 
	
	unsigned char	power_mode;		 
	
	unsigned char	bus_width;		 
	
	unsigned char	timing;			 
};



struct mmc_host_ops {
	

























 
	int (*enable)(struct mmc_host *host);
	int (*disable)(struct mmc_host *host, int lazy);
	void	(*request)(struct mmc_host *host, struct mmc_request *req);
	


















 
	void	(*set_ios)(struct mmc_host *host, struct mmc_ios *ios);
	int	(*get_ro)(struct mmc_host *host);
	int	(*get_cd)(struct mmc_host *host);

	void	(*enable_sdio_irq)(struct mmc_host *host, int enable);
};


#line 129 "..\\sdio\\inc\\host.h"

 
#line 141 "..\\sdio\\inc\\host.h"

struct mmc_host {
	int			index;
	const struct mmc_host_ops *ops; 
	unsigned int		f_min;
	unsigned int		f_max; 
	u32			ocr_avail; 

	unsigned long		caps;		 


	 
	unsigned int		max_seg_size;	 
	unsigned short		max_hw_segs;	 
	unsigned short		max_phys_segs;	 
	unsigned short		unused;
	unsigned int		max_req_size;	 
	unsigned int		max_blk_size;	 
	unsigned int		max_blk_count;	 

	 
	

	struct mmc_ios		ios;		 
	u32			ocr;		 

	 
	unsigned int		use_spi_crc:1;
	unsigned int		claimed:1;	 
	unsigned int		bus_dead:1;	 




	 
	int			enabled;	 
	int			nesting_cnt;	 
	int			en_dis_recurs;	 
	unsigned int		disable_delay;	 
	

	struct mmc_card		*card;		 



	int			claim_cnt;	 



	const struct mmc_bus_ops *bus_ops;	 
	unsigned int		bus_refs;	 

	unsigned int		sdio_irqs;











	struct stm32_host private; 
};













 
static void mmc_signal_sdio_irq(struct mmc_host *host)
{
	host->ops->enable_sdio_irq(host, 0);
	sdio_irq_thread(host);
}






 
#line 16 "..\\sdio\\inc\\core.h"
#line 17 "..\\sdio\\inc\\core.h"
#line 18 "..\\sdio\\inc\\core.h"
#line 19 "..\\sdio\\inc\\core.h"
#line 20 "..\\sdio\\inc\\core.h"





















 




 
#line 56 "..\\sdio\\inc\\core.h"







 
#line 71 "..\\sdio\\inc\\core.h"




struct mmc_data;
struct mmc_command;
struct mmc_request;

struct mmc_data {
	unsigned int		timeout_ns;	 
	unsigned int		timeout_clks;	 
	unsigned int		blksz;		 
	unsigned int		blocks;		 
	
	int		error;		 
	unsigned int		flags;

	unsigned int		bytes_xfered;

	struct mmc_command	*stop;		 
	struct mmc_request	*mrq;		 

	unsigned int		sg_len;		 
	unsigned char 		*sg;		 
};

struct mmc_request {
	struct mmc_command	*cmd;
	struct mmc_data		*data;
	struct mmc_command	*stop;

	void			*done_data;	 
	void			(*done)(void *); 
};



 


struct mmc_command {
	u32			opcode;
	u32			arg;
	u32			resp[4];
	unsigned int		flags;		 
	unsigned int		retries;	 
	
	int		error;		 












 

	struct mmc_data		*data;		 
	struct mmc_request	*mrq;		 
};








void mmc_request_done(struct mmc_host *host, struct mmc_request *mrq);
void mmc_set_chip_select(struct mmc_host *host, int mode);
void mmc_set_clock(struct mmc_host *host, unsigned int hz);
void mmc_set_bus_mode(struct mmc_host *host, unsigned int mode);
void mmc_set_bus_width(struct mmc_host *host, unsigned int width);
void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq);
int mmc_wait_for_cmd(struct mmc_host *host, struct mmc_command *cmd, int retries);
void mmc_set_timing(struct mmc_host *host, unsigned int timing);
int mmc_go_idle(struct mmc_host *host);
u32 mmc_select_voltage(struct mmc_host *host, u32 ocr);
void  mmc_rescan(struct mmc_host *host);
struct mmc_card *mmc_alloc_card(struct mmc_host *host);
int mmc_add_card(struct mmc_card *card);
struct mmc_host *mmc_alloc_host(void);
struct sdio_func *sdio_alloc_func(struct mmc_card *card);
int sdio_add_func(struct sdio_func *func);

	 
struct sdio_func;
struct sdio_driver;
int sdio_bus_match(struct sdio_func *func ,struct sdio_driver *sdrv );
int sdio_set_block_size(struct sdio_func *func, unsigned blksz);
struct lbs_private *sdio_bus_probe(struct sdio_func *func);
int sdio_enable_func(struct sdio_func *func);
unsigned int mmc_align_data_size(struct mmc_card *card, unsigned int sz);
void mmc_set_data_timeout(struct mmc_data *data, const struct mmc_card *card);
int sdio_claim_irq(struct sdio_func *func, sdio_irq_handler_t *handler);



#line 9 "..\\sdio\\src\\s3cmci.c"
#line 10 "..\\sdio\\src\\s3cmci.c"
#line 11 "..\\sdio\\src\\s3cmci.c"
#line 12 "..\\sdio\\src\\s3cmci.c"
#line 13 "..\\sdio\\src\\s3cmci.c"
#line 1 "..\\marvel\\driver\\inc\\marvell_ops.h"



#line 5 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 6 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 7 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 8 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 9 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 10 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 11 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 1 "..\\marvel\\driver\\inc\\rxtx.h"
#line 4 "..\\marvel\\driver\\inc\\rxtx.h"
#line 5 "..\\marvel\\driver\\inc\\rxtx.h"
 




 
int lbs_process_rxed_packet(struct lbs_private *priv, char *buffer,u16 size);
char  lbs_hard_start_xmit(struct lbs_private *priv,struct eth_packet * tx_ethpkt);
u16 wireless_card_rx(u8 *buf);
void wireless_card_tx(u8 *buf,u16 len);
u16 lbs_rev_pkt(void);
int  wait_for_data_end(void);





#line 12 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 1 "..\\marvel\\driver\\inc\\cmd.h"



#line 5 "..\\marvel\\driver\\inc\\cmd.h"
#line 6 "..\\marvel\\driver\\inc\\cmd.h"
#line 7 "..\\marvel\\driver\\inc\\cmd.h"
#line 8 "..\\marvel\\driver\\inc\\cmd.h"
#line 9 "..\\marvel\\driver\\inc\\cmd.h"
#line 10 "..\\marvel\\driver\\inc\\cmd.h"
#line 11 "..\\marvel\\driver\\inc\\cmd.h"
#line 12 "..\\marvel\\driver\\inc\\cmd.h"
#line 13 "..\\marvel\\driver\\inc\\cmd.h"
#line 14 "..\\marvel\\driver\\inc\\cmd.h"
#line 15 "..\\marvel\\driver\\inc\\cmd.h"
#line 16 "..\\marvel\\driver\\inc\\cmd.h"
#line 17 "..\\marvel\\driver\\inc\\cmd.h"
#line 18 "..\\marvel\\driver\\inc\\cmd.h"

struct lbs_private;
struct cmd_header;



int lbs_cmd_copyback(struct lbs_private *priv, unsigned long extra,struct cmd_header *resp);
int __lbs_cmd(struct lbs_private *priv, uint16_t command,
	      struct cmd_header *in_cmd, int in_cmd_size,
	      int (*callback)(struct lbs_private *, unsigned long, struct cmd_header *),
	      unsigned long callback_arg);



 
  

 



	
	


 

struct void_cmd_head{
	struct cmd_header hdr;
};
int  lbs_cmd(struct lbs_private *priv, uint16_t cmdnr, struct void_cmd_head* cmd,
			 int (*callback)(struct lbs_private *, unsigned long, struct cmd_header *),
	      		unsigned long callback_arg);
int  lbs_cmd_with_response(struct lbs_private *priv, uint16_t cmdnr,void *cmd);






 



int lbs_allocate_cmd_buffer(struct lbs_private *priv);

int lbs_update_hw_spec(struct lbs_private *priv);

struct lbs_private;
struct cmd_ctrl_node;
void lbs_complete_command(struct lbs_private *priv, struct cmd_ctrl_node *cmd,int result);
int lbs_process_command_response(struct lbs_private *priv, u8 *data, u32 len);
int lbs_execute_next_command(struct lbs_private *priv);

int lbs_get_tx_power(struct lbs_private *priv, s16 *curlevel, s16 *minlevel,
		     s16 *maxlevel);
void lbs_cmd_async(struct lbs_private *priv, uint16_t command,
	struct cmd_header *in_cmd, int in_cmd_size);
void lbs_set_mac_control(struct lbs_private *priv);
int lbs_update_channel(struct lbs_private *priv);
int lbs_set_snmp_mib(struct lbs_private *priv, u32 oid, u16 val);
int lbs_set_channel(struct lbs_private *priv, u8 channel);
int lbs_cmd_802_11_set_wep(struct lbs_private *priv, uint16_t cmd_action,
			   struct assoc_request *assoc);
int lbs_cmd_802_11_enable_rsn(struct lbs_private *priv, uint16_t cmd_action,
			      uint16_t *enable);

int lbs_set_radio(struct lbs_private *priv, u8 preamble, u8 radio_on);



int lbs_prepare_and_send_command(struct lbs_private *priv,
			  u16 cmd_no,
			  u16 cmd_action,
			  u16 wait_option, u32 cmd_oid, void *pdata_buf);

int lbs_cmd_802_11_key_material(struct lbs_private *priv, uint16_t cmd_action,
				struct assoc_request *assoc);






#line 13 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 1 "..\\marvel\\driver\\inc\\assoc.h"



#line 5 "..\\marvel\\driver\\inc\\assoc.h"
#line 6 "..\\marvel\\driver\\inc\\assoc.h"
#line 7 "..\\marvel\\driver\\inc\\assoc.h"
#line 8 "..\\marvel\\driver\\inc\\assoc.h"
#line 1 "..\\marvel\\driver\\inc\\assoc.h"
#line 9 "..\\marvel\\driver\\inc\\assoc.h"

int test_bit(int nr, const unsigned long *vaddr);
void set_bit(int nr,unsigned long *vaddr);
void clear_bit(int nr,unsigned long *vaddr);


static int get_common_rates(struct lbs_private *priv,
	u8 *rates,
	u16 *rates_size);
static void lbs_set_basic_rate_flags(u8 *rates, size_t len);
static u8 iw_auth_to_ieee_auth(u8 auth);
static int lbs_set_authentication(struct lbs_private *priv, u8 bssid[6], u8 auth);
static int lbs_assoc_post(struct lbs_private *priv,
			  struct cmd_ds_802_11_associate_response *resp);
static int lbs_associate(struct lbs_private *priv,
			 struct assoc_request *assoc_req,
			 u16 command);
static int lbs_try_associate(struct lbs_private *priv,
	struct assoc_request *assoc_req);
static int is_network_compatible(struct lbs_private *priv,
				 struct bss_descriptor *bss, uint8_t mode);
static struct bss_descriptor *lbs_find_bssid_in_list(struct lbs_private *priv,
					      uint8_t *bssid, uint8_t mode);
static int assoc_helper_bssid(struct lbs_private *priv,
                              struct assoc_request * assoc_req);
 int lbs_ssid_cmp(uint8_t *ssid1, uint8_t ssid1_len, uint8_t *ssid2,
		 uint8_t ssid2_len);
static struct bss_descriptor *lbs_find_ssid_in_list(struct lbs_private *priv,
					     uint8_t *ssid, uint8_t ssid_len,
					     uint8_t *bssid, uint8_t mode,
					     int channel);
int lbs_send_specific_ssid_scan(struct lbs_private *priv, uint8_t *ssid,
				uint8_t ssid_len);

static int assoc_helper_essid(struct lbs_private *priv,
                              struct assoc_request * assoc_req);
static int assoc_helper_associate(struct lbs_private *priv,
                                  struct assoc_request * assoc_req);
static int assoc_helper_mode(struct lbs_private *priv,
                             struct assoc_request * assoc_req);
static int assoc_helper_channel(struct lbs_private *priv,
                                struct assoc_request * assoc_req);

static int assoc_helper_wep_keys(struct lbs_private *priv,
				 struct assoc_request *assoc_req);
static int assoc_helper_secinfo(struct lbs_private *priv,
                                struct assoc_request * assoc_req);
static int assoc_helper_wpa_ie(struct lbs_private *priv,
                               struct assoc_request * assoc_req);
static int lbs_adhoc_join(struct lbs_private *priv,
	struct assoc_request *assoc_req);
static int lbs_adhoc_start(struct lbs_private *priv,
	struct assoc_request *assoc_req);
int lbs_adhoc_stop(struct lbs_private *priv);
static int lbs_adhoc_post(struct lbs_private *priv,
			  struct cmd_ds_802_11_ad_hoc_result *resp);

static struct bss_descriptor *lbs_find_best_ssid_in_list(
	struct lbs_private *priv, uint8_t mode);
static int lbs_find_best_network_ssid(struct lbs_private *priv,
	uint8_t *out_ssid, uint8_t *out_ssid_len, uint8_t preferred_mode,
	uint8_t *out_mode);
static int should_deauth_infrastructure(struct lbs_private *priv,
                                        struct assoc_request * assoc_req);
int lbs_ssid_cmp(uint8_t *ssid1, uint8_t ssid1_len, uint8_t *ssid2,
		 uint8_t ssid2_len);

static int should_stop_adhoc(struct lbs_private *priv,
                             struct assoc_request * assoc_req);
void lbs_association_worker(struct lbs_private *priv);
int lbs_cmd_80211_deauthenticate(struct lbs_private *priv, u8 bssid[6],
				 u16 reason);
 int lbs_scan_networks(struct lbs_private *priv, int full_scan);
 void lbs_scan_worker(struct lbs_private *priv);
 
 int lbs_set_encodeext(struct lbs_private *priv,
				   
				   struct iw_point *dwrq,char *extra,
				   struct assoc_request * assoc_req);
 void marvel_assoc_wpa_network(struct lbs_private *priv,
 char *ssid,char *key);
 void marvel_assoc_open_network(struct lbs_private *priv,
	 char *ssid,char *key,char mode);

#line 14 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 15 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 16 "..\\marvel\\driver\\inc\\marvell_ops.h"
#line 1 "..\\marvel\\driver\\inc\\hostcmdcode.h"


 




 





 



 


 


 
#line 92 "..\\marvel\\driver\\inc\\hostcmdcode.h"

 















 











 


 




 







 
#line 148 "..\\marvel\\driver\\inc\\hostcmdcode.h"

 
#line 156 "..\\marvel\\driver\\inc\\hostcmdcode.h"





 



 




#line 176 "..\\marvel\\driver\\inc\\hostcmdcode.h"

 




 




 
#line 199 "..\\marvel\\driver\\inc\\hostcmdcode.h"

 
enum cmd_bt_access_opts {
	


 
	CMD_ACT_BT_ACCESS_ADD = 5,
	CMD_ACT_BT_ACCESS_DEL,
	CMD_ACT_BT_ACCESS_LIST,
	CMD_ACT_BT_ACCESS_RESET,
	CMD_ACT_BT_ACCESS_SET_INVERT,
	CMD_ACT_BT_ACCESS_GET_INVERT
};

 
enum cmd_fwt_access_opts {
	CMD_ACT_FWT_ACCESS_ADD = 1,
	CMD_ACT_FWT_ACCESS_DEL,
	CMD_ACT_FWT_ACCESS_LOOKUP,
	CMD_ACT_FWT_ACCESS_LIST,
	CMD_ACT_FWT_ACCESS_LIST_ROUTE,
	CMD_ACT_FWT_ACCESS_LIST_NEIGHBOR,
	CMD_ACT_FWT_ACCESS_RESET,
	CMD_ACT_FWT_ACCESS_CLEANUP,
	CMD_ACT_FWT_ACCESS_TIME,
};

 
enum cmd_wol_cfg_opts {
	CMD_ACT_ACTION_NONE = 0,
	CMD_ACT_SET_WOL_RULE,
	CMD_ACT_GET_WOL_RULE,
	CMD_ACT_RESET_WOL_RULE,
};

 
enum cmd_mesh_access_opts {
	CMD_ACT_MESH_GET_TTL = 1,
	CMD_ACT_MESH_SET_TTL,
	CMD_ACT_MESH_GET_STATS,
	CMD_ACT_MESH_GET_ANYCAST,
	CMD_ACT_MESH_SET_ANYCAST,
	CMD_ACT_MESH_SET_LINK_COSTS,
	CMD_ACT_MESH_GET_LINK_COSTS,
	CMD_ACT_MESH_SET_BCAST_RATE,
	CMD_ACT_MESH_GET_BCAST_RATE,
	CMD_ACT_MESH_SET_RREQ_DELAY,
	CMD_ACT_MESH_GET_RREQ_DELAY,
	CMD_ACT_MESH_SET_ROUTE_EXP,
	CMD_ACT_MESH_GET_ROUTE_EXP,
	CMD_ACT_MESH_SET_AUTOSTART_ENABLED,
	CMD_ACT_MESH_GET_AUTOSTART_ENABLED,
	CMD_ACT_MESH_SET_GET_PRB_RSP_LIMIT = 17,
};

 
enum cmd_mesh_config_actions {
	CMD_ACT_MESH_CONFIG_STOP = 0,
	CMD_ACT_MESH_CONFIG_START,
	CMD_ACT_MESH_CONFIG_SET,
	CMD_ACT_MESH_CONFIG_GET,
};

enum cmd_mesh_config_types {
	CMD_TYPE_MESH_SET_BOOTFLAG = 1,
	CMD_TYPE_MESH_SET_BOOTTIME,
	CMD_TYPE_MESH_SET_DEF_CHANNEL,
	CMD_TYPE_MESH_SET_MESH_IE,
	CMD_TYPE_MESH_GET_DEFAULTS,
	CMD_TYPE_MESH_GET_MESH_IE,  
};

 
#line 304 "..\\marvel\\driver\\inc\\hostcmdcode.h"



#line 17 "..\\marvel\\driver\\inc\\marvell_ops.h"



extern struct lbs_private *pgmarvel_priv;
extern u8 sdio_sys_wait;


struct lbs_private * init_marvell_driver(void);
void marvel_assoc_network(struct lbs_private *priv,char *ssid,char *key,char mode);
void lbs_scan_worker(struct lbs_private *priv);
u16 lbs_rev_pkt(void);
char  lbs_hard_start_xmit(struct lbs_private *priv,struct eth_packet * tx_ethpkt);
int wpa_L2_send_pkt(u8 *buf,u16 len);
int lbs_set_key_material(struct lbs_private *priv,int key_type,int key_info,u8 *key, u16 key_len);

extern int __lbs_set_key_material(int key_type,int key_info,u8 *key, u16 key_len);


 
void lbs_ps_wakeup(struct lbs_private *priv); 
void lbs_ps_sleep(struct lbs_private *priv);
void init_sleep_mode(void);
void lbs_send_confirmsleep(struct lbs_private *priv);

enum wpa_states {
	





 
	WPA_DISCONNECTED,

	






 
	WPA_INACTIVE,

	




 
	WPA_SCANNING,

	






 
	WPA_AUTHENTICATING,

	







 
	WPA_ASSOCIATING,

	






 
	WPA_ASSOCIATED,

	






 
	WPA_4WAY_HANDSHAKE,

	






 
	WPA_GROUP_HANDSHAKE,

	














 
	WPA_COMPLETED,
	WPA_NO_IMPL
};



#line 286 "..\\marvel\\driver\\inc\\marvell_ops.h"











#line 14 "..\\sdio\\src\\s3cmci.c"






static struct stm32_host *gpstm32_host;










 

static struct mmc_host_ops stm32_ops; 

static void udelay(unsigned int us)
{
	unsigned long i,ii=500;
	for(i=0;i<us;i++){
		ii=500;
		while(ii--);
	}
}
static unsigned int readl(unsigned long addr)
{  
   return (*(volatile unsigned *)addr);
}

static unsigned int writel(unsigned int data,unsigned long addr)
{  
   return (*(volatile unsigned *)addr)=data;
}
void EnableIrq(u32 irq)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = irq;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void DisableIrq(u32 irq)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = irq;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
}











 

 







 
static int stm32_host_usedma(struct stm32_host *host)
{

	return 0;





}






 








 

static u32 enable_imask(struct stm32_host *host, u32 imask)
{
	u32 mask = ((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->MASK;
	SDIO_ITConfig(imask|mask,ENABLE);	
	return 0;
}

static u32 disable_imask(struct stm32_host *host, u32 imask)
{
	u32 mask = ((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->MASK;
	SDIO_ITConfig(~imask&mask,DISABLE);	
	return 0;
}

static void clear_imask(struct stm32_host *host)
{
	u32 mask = ((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->MASK;
	 
	mask &= ((u32)0x00400000);
	((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->MASK=mask;
}












 
static void stm32_check_sdio_irq(struct stm32_host *host)
{
#line 164 "..\\sdio\\src\\s3cmci.c"
}
#line 213 "..\\sdio\\src\\s3cmci.c"












 
static void stm32_enable_irq(struct stm32_host *host, bool more)
{

	bool enable = FALSE;
	host->irq_enabled = more;
	host->irq_disabled = FALSE;

	enable =(bool) (more ||((bool) host->sdio_irqen));

	if (host->irq_state != enable) {
		host->irq_state = enable;

		if (enable)
			EnableIrq(host->irq);
		else
			DisableIrq(host->irq);
	}
}



 
static void stm32_disable_irq(struct stm32_host *host, bool transfer)
{
	host->irq_disabled = transfer;

	if (transfer && host->irq_state) {
		host->irq_state = FALSE;
		DisableIrq(host->irq);
	}
}
#line 387 "..\\sdio\\src\\s3cmci.c"
static void stm32_send_command(struct stm32_host *host,
					struct mmc_command *cmd)
{
	u32 imsk;
	SDIO_CmdInitTypeDef SDIO_CmdInitStructure;
	;
	imsk=((u32)0x00000001)|((u32)0x00000004)|
		((u32)0x00000040)|((u32)0x00000080);
	enable_imask(host, imsk);
	if (cmd->data)
		host->complete_what = COMPLETION_XFERFINISH_RSPFIN;
	else if (cmd->flags & (1 << 0))
		host->complete_what = COMPLETION_RSPFIN;
	else
		host->complete_what = COMPLETION_CMDSENT;
	  ((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->DTIMER=0xFFFFFFFF;
	  SDIO_CmdInitStructure.SDIO_Argument =cmd->arg;
	  SDIO_CmdInitStructure.SDIO_CmdIndex =cmd->opcode;
	  if (cmd->flags & (1 << 0))
		  SDIO_CmdInitStructure.SDIO_Response = ((u32)0x00000040);
	  else if (cmd->flags & (1 << 1))
		  SDIO_CmdInitStructure.SDIO_Response = ((u32)0x000000C0);
	  else
	  	SDIO_CmdInitStructure.SDIO_Response=((u32)0x00000000);
	  SDIO_CmdInitStructure.SDIO_Wait = ((u32)0x00000000);
	  SDIO_CmdInitStructure.SDIO_CPSM = ((u32)0x00000400);
	  SDIO_SendCommand(&SDIO_CmdInitStructure);
	  ;
}



static void DMA_RxConfiguration(u32 *BufferDST, u32 BufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(((u32)0x10002000) | ((u32)0x10008000) | ((u32)0x10004000) | ((u32)0x10001000));

   
  DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444)), DISABLE);

   
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)((u32)0x40018080);
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)BufferDST;
  DMA_InitStructure.DMA_DIR = ((u32)0x00000000);
  DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
  DMA_InitStructure.DMA_PeripheralInc = ((u32)0x00000000);
  DMA_InitStructure.DMA_MemoryInc = ((u32)0x00000080);
  DMA_InitStructure.DMA_PeripheralDataSize = ((u32)0x00000200);
  DMA_InitStructure.DMA_MemoryDataSize = ((u32)0x00000800);
  DMA_InitStructure.DMA_Mode = ((u32)0x00000000);
  DMA_InitStructure.DMA_Priority = ((u32)0x00002000);
  DMA_InitStructure.DMA_M2M = ((u32)0x00000000);
  DMA_Init(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444)), &DMA_InitStructure);

   
  DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444)), ENABLE);
}

static void DMA_TxConfiguration(u32 *BufferSRC, u32 BufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_ClearFlag(((u32)0x10002000) | ((u32)0x10008000) | ((u32)0x10004000) | ((u32)0x10001000));

   
  DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444)), DISABLE);

   
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)((u32)0x40018080);
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)BufferSRC;
  DMA_InitStructure.DMA_DIR = ((u32)0x00000010);
  DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
  DMA_InitStructure.DMA_PeripheralInc = ((u32)0x00000000);
  DMA_InitStructure.DMA_MemoryInc = ((u32)0x00000080);
  DMA_InitStructure.DMA_PeripheralDataSize = ((u32)0x00000200);
  DMA_InitStructure.DMA_MemoryDataSize = ((u32)0x00000800);
  DMA_InitStructure.DMA_Mode = ((u32)0x00000000);
  DMA_InitStructure.DMA_Priority = ((u32)0x00002000);
  DMA_InitStructure.DMA_M2M = ((u32)0x00000000);
  DMA_Init(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444)), &DMA_InitStructure);

   
  DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444)), ENABLE);
}


static int stm32_setup_data(struct stm32_host *host, struct mmc_data *data)
{
	SDIO_DataInitTypeDef SDIO_DataInitStructure;
	u32 blocks=data->blocks;
	u32 blksz=data->blksz;
	u32 total_len;
	u32 imask;
	u8 power = 0;
	 
	;
	if (!data) {
		return 0;
	}
	if ((data->blksz & 3) != 0) {
		
 

		if (data->blocks > 1) {
			printf("can't do non-word sized block transfers (blksz %d)\n",data->blksz);
			return -22;
		}
	}
	
	  SDIO_DataInitStructure.SDIO_DataTimeOut = ((u32)0x000FFFFF);
	  SDIO_DataInitStructure.SDIO_DataLength = 0;
	  SDIO_DataInitStructure.SDIO_DataBlockSize = ((u32)0x00000000);
	  SDIO_DataInitStructure.SDIO_TransferDir = ((u32)0x00000000);
	  SDIO_DataInitStructure.SDIO_TransferMode = ((u32)0x00000000);
	  SDIO_DataInitStructure.SDIO_DPSM = ((u32)0x00000000);
	  SDIO_DataConfig(&SDIO_DataInitStructure);
	  SDIO_DMACmd(DISABLE);
      
      	 SDIO_ClearFlag(0x5FF);
	if (host->bus_width == 2){
		((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->CLKCR&=~(3<<11);
		((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->CLKCR|=((u32)0x00000800);
	}
		 
	
 

  
      if ((blksz > 0) && (blksz <= 2048) && (0 == (blksz & (blksz - 1)))){
	    power = convert_from_bytes_to_power_of_two(blksz);
	    total_len=blksz*blocks;
  	}
     else
   	   return -22;
  
     
  if (total_len > ((u32)0x01FFFFFF))
 		 return -22;
    SDIO_DataInitStructure.SDIO_DataTimeOut = ((u32)0x000FFFFF);
    SDIO_DataInitStructure.SDIO_DataLength = total_len;
    SDIO_DataInitStructure.SDIO_DataBlockSize = (u32) power << 4;
    if (data->flags & (1 << 8))
    		SDIO_DataInitStructure.SDIO_TransferDir = ((u32)0x00000000);
    else if (data->flags & (1 << 9))
		SDIO_DataInitStructure.SDIO_TransferDir = ((u32)0x00000002);
    SDIO_DataInitStructure.SDIO_TransferMode = ((u32)0x00000000);
    SDIO_DataInitStructure.SDIO_DPSM = ((u32)0x00000000);
    SDIO_DataConfig(&SDIO_DataInitStructure);
    if (data->flags & (1 << 9)){
	 	DMA_RxConfiguration((u32 *)data->sg,total_len);
	 	((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->DCTRL|=((1<<3)|((u32)0x00000001));
    	}	 	
   else  if (data->flags & (1 << 8))
		DMA_TxConfiguration((u32 *)data->sg,total_len);
	 imask=((u32)0x00000002) | ((u32)0x00000008) | ((u32)0x00000100); 
	 enable_imask(host, imask);
     ;
	return 0;
}



static void  stm32_enable_dma(void)
{      
	u32 imask=((u32)0x00000002) | ((u32)0x00000008) | ((u32)0x00000100); 
	;
	SDIO_ClearFlag(0x5FF);
	((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->DCTRL|=(((u32)0x00000001)|(1<<3));
    SDIO_ITConfig(imask, ENABLE);
	 while (DMA_GetFlagStatus(((u32)0x10002000)) == RESET);
	 ;

}











#line 596 "..\\sdio\\src\\s3cmci.c"

static void stm32_send_request(struct mmc_host *mmc)
{
	struct stm32_host *host = (struct stm32_host *)(&(mmc->private));
	struct mmc_request *mrq = host->mrq;
	struct mmc_command *cmd;
	
	;
	cmd=host->cmd_is_stop ? mrq->stop : mrq->cmd;
	host->ccnt++;
	SDIO_ClearFlag(0x5FF);
	 if (cmd->data) {
		int res = stm32_setup_data(host, cmd->data);
		host->dcnt++;
		if (res) {
			printf( "setup data error %d\n", res);
			cmd->error = res;
			cmd->data->error = res;
			mmc_request_done(mmc, mrq);
			return;
		}
	} 
	 
	stm32_send_command(host, cmd);
	 
	stm32_enable_irq(host, TRUE);
	;
}

static void finalize_request(struct stm32_host *host)
{
	struct mmc_request *mrq = host->mrq;
	struct mmc_command *cmd = host->cmd_is_stop ? mrq->stop : mrq->cmd;
	u32 clkcr;
	
	if (host->complete_what != COMPLETION_FINALIZE)
		return;

	if (!mrq)
		return;

	if (cmd->data && (cmd->error == 0) &&
	    (cmd->data->error == 0)) {
		if (stm32_host_usedma(host) && (!host->dma_complete)) {
			printf( "DMA Missing (%d)!\n",
			    host->dma_complete);
			return;
		}
	}

	 
	cmd->resp[0] =((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->RESP1;
	cmd->resp[1] =((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->RESP2;
	cmd->resp[2] =((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->RESP3;
	cmd->resp[3] =((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->RESP4;

	
	clkcr=((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->CLKCR&(~(0xFF));
	clkcr|=host->prescaler;
	((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->CLKCR=clkcr;


 


 



	 
	

 
	 SDIO_ClearFlag(0x5FF);

	clear_imask(host);

	if (cmd->data && cmd->error)
		cmd->data->error = cmd->error;

	if (cmd->data && cmd->data->stop && (!host->cmd_is_stop)) {
		host->cmd_is_stop = 1;
		stm32_send_request(host->mmc);
		return;
	}

	 
	if (!mrq->data)
		goto request_done;
#line 716 "..\\sdio\\src\\s3cmci.c"
request_done:
	host->complete_what = COMPLETION_NONE;
	host->mrq = 0;

	stm32_check_sdio_irq(host);
	mmc_request_done(host->mmc, mrq);
}



static void pio_tasklet(unsigned long data)
{
	struct stm32_host *host = (struct stm32_host *) data;
	
	stm32_disable_irq(host, TRUE);
    if(sdio_sys_wait==1)
		udelay(20);





 

	if (host->complete_what == COMPLETION_FINALIZE) {
		clear_imask(host);
		if (host->pio_active != 0) { 
			printf( "unfinished %s "
			    "- pio_count:[%u] pio_bytes:[%u]\n",
			    (host->pio_active == 1) ? "read" : "write",
			    host->pio_count, host->pio_bytes);

			if (host->mrq->data)
				host->mrq->data->error = -22;
		}

		stm32_enable_irq(host, FALSE);
		finalize_request(host);
	} else
		stm32_enable_irq(host, TRUE);
}

static int stm32_card_present(struct mmc_host *mmc) 
{
	return 1;
}

static void stm32_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct stm32_host *host = (struct stm32_host *)(&(mmc->private));
	;
	host->status = "mmc request";
	host->cmd_is_stop = 0;
	host->mrq = mrq;

	if (stm32_card_present(mmc) == 0) {
		;
		host->mrq->cmd->error = -125;
		mmc_request_done(mmc, mrq);
	} else
		stm32_send_request(mmc);
	;
}

static void stm32_set_clk(struct stm32_host *host, struct mmc_ios *ios)
{
	u32 mci_psc;
	SDIO_InitTypeDef SDIO_InitStructure;
	 
	for (mci_psc = 0; mci_psc < 255; mci_psc++) {
		host->real_rate = host->clk_rate / (host->clk_div*(mci_psc+1));

		if (host->real_rate <= ios->clock)
			break;
	}

	if (mci_psc > 255)
		mci_psc = 255;
   
   
  SDIO_InitStructure.SDIO_ClockDiv = mci_psc;  
  SDIO_InitStructure.SDIO_ClockEdge = ((u32)0x00000000);
  SDIO_InitStructure.SDIO_ClockBypass = ((u32)0x00000000);
  SDIO_InitStructure.SDIO_ClockPowerSave = ((u32)0x00000000);
  switch(ios->bus_width){
  case 0:
		SDIO_InitStructure.SDIO_BusWide = ((u32)0x00000000);
		break;
  case 2:
		SDIO_InitStructure.SDIO_BusWide = ((u32)0x00000800);
		break;
  case 3:
		SDIO_InitStructure.SDIO_BusWide = ((u32)0x00001000);
		break;	
  }
  SDIO_InitStructure.SDIO_HardwareFlowControl = ((u32)0x00000000);
  SDIO_Init(&SDIO_InitStructure);

  host->prescaler = mci_psc;
	 
  if (ios->clock == 0)
		host->real_rate = 0;
}














 

static void stm32_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct stm32_host *host = (struct stm32_host *)(&(mmc->private));


	 
	stm32_set_clk(host, ios);

	
	switch (ios->power_mode) {
	case 2:
	case 1:
	  	SDIO_SetPowerState(((u32)0x00000003));
		SDIO_ClockCmd(ENABLE);
		break;

	case 0:
	default:
		SDIO_SetPowerState(((u32)0x00000000));
		SDIO_ClockCmd(DISABLE);
		printf("stm32 power off sdio!\n");
	}
	if ((ios->power_mode == 2) ||
	    (ios->power_mode == 1)) {
		printf("running at %lukHz (requested: %ukHz).\n",
			host->real_rate/1000, ios->clock/1000);
	} else {
		printf("powered down.\n");
	}
	host->bus_width = ios->bus_width;
}

static int stm32_get_ro(struct mmc_host *mmc)
{
	return 0;
}

static void stm32_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct stm32_host *host = (struct stm32_host *)(&(mmc->private));

	u32 con;

	

	con = readl(host->base + (0x00));
	host->sdio_irqen = enable;

	if (enable == host->sdio_irqen)
		goto same_state;

	if (enable) {
		con |= (1<<3);
		enable_imask(host, (1<<12));

		if (!host->irq_state && !host->irq_disabled) {
			host->irq_state = TRUE;
			EnableIrq(host->irq);
		}
	} else {
		disable_imask(host, (1<<12));
		con &= ~(1<<3);

		if (!host->irq_enabled && host->irq_state) {
			DisableIrq(host->irq);
			host->irq_state = FALSE;
		}
	}

	writel(con, host->base + (0x00));

 same_state:
	stm32_check_sdio_irq(host);
}


























 

void  stm32_irq(void)
{
	struct stm32_host *host = gpstm32_host;
	struct mmc_request *mrq = host->mrq;
	struct mmc_command *cmd=host->cmd_is_stop ? mrq->stop : mrq->cmd;
	struct mmc_data *data=cmd->data;
	u32 stm_sta, stm_imsk;
	u32 stm_clear = 0;
	;
	stm_sta = ((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->STA;
	stm_imsk =((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->MASK;
	 
	if (stm_sta & ((u32)0x00400000)) {
		if (stm_imsk & ((u32)0x00400000)) {
			printf("card sdio interupt!\n");
			stm_clear= ((u32)0x00400000);
			((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->ICR=stm_clear;
			mmc_signal_sdio_irq(host->mmc);
			
			return;
		}
	}

	if ((host->complete_what == COMPLETION_NONE) ||
	    (host->complete_what == COMPLETION_FINALIZE)) {
		host->status = "nothing to complete";
		clear_imask(host);
		goto irq_out;
	}

	if (!host->mrq) {
		host->status = "no active mrq";
		clear_imask(host);
		goto irq_out;
	}

	cmd = host->cmd_is_stop ? host->mrq->stop : host->mrq->cmd;

	if (!cmd) {
		host->status = "no active cmd";
		clear_imask(host);
		goto irq_out;
	}
 
	if (stm_sta & ((u32)0x00000004)) {
		printf( "CMDSTAT: error CMDTIMEOUT\n");
		cmd->error = -60;
		host->status = "error: command timeout";
		goto fail_transfer;
	}

	if (stm_sta & ((u32)0x00000080)) {
		if (host->complete_what == COMPLETION_CMDSENT) {
			host->status = "ok: command sent";
			goto close_transfer;
		}

		stm_clear |= ((u32)0x00000080);
	}

	if (stm_sta & ((u32)0x00000001)) {
		if (cmd->flags & (1 << 2)) { 
			if (host->mrq->cmd->flags & (1 << 1)) {
				printf("fixup: ignore CRC fail with long rsp\n");
			} else {
				






 
			}
		}
		stm_clear |= ((u32)0x00000001);
	}

	if (stm_sta & ((u32)0x00000040)) {
		stm_clear |= ((u32)0x00000040);
		if (host->complete_what == COMPLETION_RSPFIN) {
			host->status = "ok: command response received";
			goto close_transfer;
		}
			if (host->complete_what == COMPLETION_XFERFINISH_RSPFIN){
				host->complete_what = COMPLETION_XFERFINISH;
				if(data->flags&(1 << 8)){
					stm32_enable_dma();
					return;
					}				
			}	
	}

	
 

	if (!cmd->data)
		goto clear_status_bits;

	if (stm_sta& ((u32)0x00000002)) {
		printf( "bad data crc (outgoing)\n");
		cmd->data->error = -36;
		host->status = "error: bad data crc (outgoing)";
		goto fail_transfer;
	}
	if (stm_sta & ((u32)0x00000008)) {
		printf( "data timeout\n");
		cmd->data->error = -60;
		host->status = "error: data timeout";
		goto fail_transfer;
	}

	if (stm_sta & ((u32)0x00000100)) {
		if (host->complete_what == COMPLETION_XFERFINISH) {
			host->status = "ok: data transfer completed";
			data->bytes_xfered=data->sg_len;
			host->pio_active = 0;
			goto close_transfer;
		}

		if (host->complete_what == COMPLETION_XFERFINISH_RSPFIN){
			host->complete_what = COMPLETION_RSPFIN;
			while (DMA_GetFlagStatus(((u32)0x10002000)) == RESET);
			data->bytes_xfered=data->sg_len;
			host->pio_active = 0;
			host->status = "ok: data transfer completed";
			SDIO_ClearFlag(((u32)0x00000100));		
			goto close_transfer;
		}
		stm_clear|=((u32)0x00000100);
	}

clear_status_bits:
	((SDIO_TypeDef *) (((u32)0x40000000) + 0x18000))->ICR=stm_clear;
	goto irq_out;

fail_transfer:
	host->pio_active = 0;
close_transfer:
	host->complete_what = COMPLETION_FINALIZE;
	clear_imask(host);
	pio_tasklet((unsigned long)host);
	goto irq_out;
irq_out:
	;	
	;
	return ;

}



 static void init_stm32_struct(struct mmc_host_ops *phost_ops)
{
	



	
	phost_ops->request	= stm32_request;
	phost_ops->set_ios	= stm32_set_ios;
	phost_ops->get_ro	 	= stm32_get_ro;
	phost_ops->get_cd		= stm32_card_present;
	phost_ops->enable_sdio_irq = stm32_enable_sdio_irq;

}
struct mmc_host * stm32_probe(void)
{
	struct mmc_host	*mmc;
	struct stm32_host *host;
	init_stm32_struct(&stm32_ops);
	mmc = mmc_alloc_host();
	host = (struct stm32_host *)(&(mmc->private));
	gpstm32_host=host;
	host->mmc 	= mmc;
	host->complete_what = COMPLETION_NONE;
	host->pio_active 	= 0;
	host->irq=((u8)0x31);
	EnableIrq(host->irq);
	host->irq_state = FALSE;
	host->irq_cd = -1;
	host->clk_div=1;
	host->clk_rate =128000000;
	mmc->ops 	= &stm32_ops;
	mmc->ocr_avail	= 0x00100000 | 0x00200000;

	mmc->caps	= (1 << 0) | (1 << 3);



	mmc->f_min 	= host->clk_rate /257;
	mmc->f_max 	= host->clk_rate;

	
 

	mmc->max_blk_count	= 4095;
	mmc->max_blk_size	= 4095;
	mmc->max_req_size	= 4095 * 512;
	mmc->max_seg_size	= mmc->max_req_size;
	mmc->max_phys_segs	= 128;
	mmc->max_hw_segs	= 128;

	;
	return mmc;
}
