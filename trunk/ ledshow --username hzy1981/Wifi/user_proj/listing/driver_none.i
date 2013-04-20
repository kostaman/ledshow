#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver_none.c"












 

#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"
















 






 
#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\build_config.h"


















 




 

#line 55 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\build_config.h"

#line 77 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\build_config.h"

#line 104 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\build_config.h"

#line 26 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"

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


 
#line 28 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"
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



 
#line 29 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdarg.h"
 
 
 





 









#line 26 "C:\\Keil\\ARM\\RV31\\INC\\stdarg.h"








 

 
 
  typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 






#line 118 "C:\\Keil\\ARM\\RV31\\INC\\stdarg.h"











 
#line 30 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"
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



 
#line 31 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"






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



 
#line 39 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\time.h"
 
 
 
 









 





 












#line 40 "C:\\Keil\\ARM\\RV31\\INC\\time.h"


  
  typedef unsigned int size_t;








    
 
#line 64 "C:\\Keil\\ARM\\RV31\\INC\\time.h"





typedef unsigned int clock_t;     
typedef unsigned int time_t;      

#pragma push
#pragma anon_unions

struct tm {
    int tm_sec;   
 
    int tm_min;    
    int tm_hour;   
    int tm_mday;   
    int tm_mon;    
    int tm_year;   
    int tm_wday;   
    int tm_yday;   
    int tm_isdst;  
    union {        
        struct {
            int __extra_1, __extra_2;
        };
        struct {
            long __extra_1_long, __extra_2_long;
        };
        struct {
            char *__extra_1_cptr, *__extra_2_cptr;
        };
        struct {
            void *__extra_1_vptr, *__extra_2_vptr;
        };
    };
};

#pragma pop

   



 

extern __declspec(__nothrow) clock_t clock(void);
   





 
extern __declspec(__nothrow) double difftime(time_t  , time_t  );
   


 
extern __declspec(__nothrow) time_t mktime(struct tm *  ) __attribute__((__nonnull__(1)));
   













 
extern __declspec(__nothrow) time_t time(time_t *  );
   






 

extern __declspec(__nothrow) char *asctime(const struct tm *  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) char *_asctime_r(const struct tm *  ,
                                char * __restrict  ) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) char *asctime_r(const struct tm *  ,
                               char * __restrict  ) __attribute__((__nonnull__(1,2)));

   



 
extern __declspec(__nothrow) char *ctime(const time_t *  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) struct tm *gmtime(const time_t *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) struct tm *localtime(const time_t *  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) struct tm *_localtime_r(const time_t * __restrict  ,
                                       struct tm * __restrict  ) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) struct tm *localtime_r(const time_t * __restrict  ,
                                      struct tm * __restrict  ) __attribute__((__nonnull__(1,2)));

   



 
extern __declspec(__nothrow) size_t strftime(char * __restrict  , size_t  ,
                       const char * __restrict  ,
                       const struct tm * __restrict  ) __attribute__((__nonnull__(1,3,4)));
   











































 











#line 271 "C:\\Keil\\ARM\\RV31\\INC\\time.h"



 
#line 40 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"







#line 60 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"


#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\wpa_supp_linux_plat\\byteswap.h"













#line 63 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\includes.h"

#line 16 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver_none.c"

#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"












 




#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\os.h"












 




typedef long os_time_t;





 
void os_sleep(os_time_t sec, os_time_t usec);

struct os_time {
	os_time_t sec;
	os_time_t usec;
};





 
int os_get_time(struct os_time *t);


 





#line 54 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\os.h"















 
int os_mktime(int year, int month, int day, int hour, int min, int sec,
	      os_time_t *t);






 
int os_daemonize(const char *pid_file);




 
void os_daemonize_terminate(const char *pid_file);






 
int os_get_random(unsigned char *buf, size_t len);




 
unsigned long os_random(void);













 
char * os_rel2abs_path(const char *rel_path);








 
int os_program_init(void);








 
void os_program_deinit(void);










 
int os_setenv(const char *name, const char *value, int overwrite);








 
int os_unsetenv(const char *name);










 
char * os_readfile(const char *name, size_t *len);







 
void * os_zalloc(size_t size);
















 









 
void * os_malloc(size_t size);










 
void * os_realloc(void *ptr, size_t size);




 
void os_free(void *ptr);










 
void * os_memcpy(void *dest, const void *src, size_t n);









 
void * os_memmove(void *dest, const void *src, size_t n);







 
void * os_memset(void *s, int c, size_t n);









 
int os_memcmp(const void *s1, const void *s2, size_t n);







 
char * os_strdup(const char *s);





 
size_t os_strlen(const char *s);







 
int os_strcasecmp(const char *s1, const char *s2);









 
int os_strncasecmp(const char *s1, const char *s2, size_t n);






 
char * os_strchr(const char *s, int c);






 
char * os_strrchr(const char *s, int c);







 
int os_strcmp(const char *s1, const char *s2);









 
int os_strncmp(const char *s1, const char *s2, size_t n);







 
char * os_strncpy(char *dest, const char *src, size_t n);






 
char * os_strstr(const char *haystack, const char *needle);





















 
int os_snprintf(char *str, size_t size, const char *format, ...);

#line 464 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\os.h"











 
size_t os_strlcpy(char *dest, const char *src, size_t siz);


#line 507 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\os.h"

#line 19 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"




static void dbug_buf(const char * name , const unsigned char * buf , const int len)
{
	
#line 35 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"
}










#line 66 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 84 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 94 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"







#line 111 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 120 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"


 

#line 135 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 147 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"








 













#line 178 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 195 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"


 

#line 223 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"




#line 238 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 270 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"





 

#line 283 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 290 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 299 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 309 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 319 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 335 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"







#line 363 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"


#line 372 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"


#line 429 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"













 
#line 450 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

#line 463 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"


#line 472 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

int hwaddr_aton(const char *txt, unsigned char *addr);
int hwaddr_aton2(const char *txt, unsigned char *addr);
int hexstr2bin(const char *hex, unsigned char *buf, size_t len);
void inc_byte_array(unsigned char *counter, size_t len);
void wpa_get_ntp_timestamp(unsigned char *buf);
int wpa_snprintf_hex(char *buf, size_t buf_size, const unsigned char *data, size_t len);
int wpa_snprintf_hex_uppercase(char *buf, size_t buf_size, const unsigned char *data,
			       size_t len);

#line 489 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"

const char * wpa_ssid_txt(const unsigned char *ssid, size_t ssid_len);

static int is_zero_ether_addr(const unsigned char *a)
{
	return !(a[0] | a[1] | a[2] | a[3] | a[4] | a[5]);
}

#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_debug.h"












 




#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpabuf.h"












 











 
struct wpabuf {
	size_t size;  
	size_t used;  
	unsigned char *ext_data; 
 
	 
};


int wpabuf_resize(struct wpabuf **buf, size_t add_len);
struct wpabuf * wpabuf_alloc(size_t len);
struct wpabuf * wpabuf_alloc_ext_data(unsigned char *data, size_t len);
struct wpabuf * wpabuf_alloc_copy(const void *data, size_t len);
struct wpabuf * wpabuf_dup(const struct wpabuf *src);
void wpabuf_free(struct wpabuf *buf);
void * wpabuf_put(struct wpabuf *buf, size_t len);
struct wpabuf * wpabuf_concat(struct wpabuf *a, struct wpabuf *b);
struct wpabuf * wpabuf_zeropad(struct wpabuf *buf, size_t len);
void wpabuf_printf(struct wpabuf *buf, char *fmt, ...) ;






 
static  size_t wpabuf_size(const struct wpabuf *buf)
{
	return buf->size;
}





 
static  size_t wpabuf_len(const struct wpabuf *buf)
{
	return buf->used;
}





 
static  size_t wpabuf_tailroom(const struct wpabuf *buf)
{
	return buf->size - buf->used;
}





 
static  const void * wpabuf_head(const struct wpabuf *buf)
{
	if (buf->ext_data)
		return buf->ext_data;
	return buf + 1;
}

static  const unsigned char * wpabuf_head_u8(const struct wpabuf *buf)
{
	return wpabuf_head(buf);
}





 
static  void * wpabuf_mhead(struct wpabuf *buf)
{
	if (buf->ext_data)
		return buf->ext_data;
	return buf + 1;
}

static  unsigned char * wpabuf_mhead_u8(struct wpabuf *buf)
{
	return wpabuf_mhead(buf);
}

static  void wpabuf_put_u8(struct wpabuf *buf, unsigned char data)
{
	unsigned char *pos = wpabuf_put(buf, 1);
	*pos = data;
}

static  void wpabuf_put_le16(struct wpabuf *buf, unsigned short data)
{
	unsigned char *pos = wpabuf_put(buf, 2);
	do { (pos)[1] = ((unsigned short) (data)) >> 8; (pos)[0] = ((unsigned short) (data)) & 0xff; } while (0);
}

static  void wpabuf_put_be16(struct wpabuf *buf, unsigned short data)
{
	unsigned char *pos = wpabuf_put(buf, 2);
	do { (pos)[0] = ((unsigned short) (data)) >> 8; (pos)[1] = ((unsigned short) (data)) & 0xff; } while (0);
}

static  void wpabuf_put_be24(struct wpabuf *buf, unsigned int data)
{
	unsigned char *pos = wpabuf_put(buf, 3);
	do { (pos)[0] = (unsigned char) ((((unsigned int) (data)) >> 16) & 0xff); (pos)[1] = (unsigned char) ((((unsigned int) (data)) >> 8) & 0xff); (pos)[2] = (unsigned char) (((unsigned int) (data)) & 0xff); } while (0);
}

static  void wpabuf_put_be32(struct wpabuf *buf, unsigned int data)
{
	unsigned char *pos = wpabuf_put(buf, 4);
	do { (pos)[0] = (unsigned char) ((((unsigned int) (data)) >> 24) & 0xff); (pos)[1] = (unsigned char) ((((unsigned int) (data)) >> 16) & 0xff); (pos)[2] = (unsigned char) ((((unsigned int) (data)) >> 8) & 0xff); (pos)[3] = (unsigned char) (((unsigned int) (data)) & 0xff); } while (0);
}

static  void wpabuf_put_data(struct wpabuf *buf, const void *data,
				   size_t len)
{
	if (data)
		os_memcpy(wpabuf_put(buf, len), data, len);
}

static  void wpabuf_put_buf(struct wpabuf *dst,
				  const struct wpabuf *src)
{
	wpabuf_put_data(dst, wpabuf_head(src), wpabuf_len(src));
}

static  void wpabuf_set(struct wpabuf *buf, const void *data, size_t len)
{
	buf->ext_data = (unsigned char *) data;
	buf->size = buf->used = len;
}

static  void wpabuf_put_str(struct wpabuf *dst, const char *str)
{
	wpabuf_put_data(dst, str, os_strlen(str));
}

#line 19 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_debug.h"


 



#line 32 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_debug.h"


#line 48 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_debug.h"

int wpa_debug_open_file(const char *path);
void wpa_debug_close_file(void);







 
void wpa_debug_print_timestamp(void);











 
void wpa_printf(int level, const char *fmt, ...)
;











 
void wpa_hexdump(int level, const char *title, const unsigned char *buf, size_t len);

static  void wpa_hexdump_buf(int level, const char *title,
				   const struct wpabuf *buf)
{
	wpa_hexdump(level, title, wpabuf_head(buf), wpabuf_len(buf));
}













 
void wpa_hexdump_key(int level, const char *title, const unsigned char *buf, size_t len);

static  void wpa_hexdump_buf_key(int level, const char *title,
				       const struct wpabuf *buf)
{
	wpa_hexdump_key(level, title, wpabuf_head(buf), wpabuf_len(buf));
}













 
void wpa_hexdump_ascii(int level, const char *title, const unsigned char *buf,
		       size_t len);














 
void wpa_hexdump_ascii_key(int level, const char *title, const unsigned char *buf,
			   size_t len);






















 
void wpa_msg(void *ctx, int level, const char *fmt, ...) ;












 
void wpa_msg_ctrl(void *ctx, int level, const char *fmt, ...)
;

typedef void (*wpa_msg_cb_func)(void *ctx, int level, const char *txt,
				size_t len);




 
void wpa_msg_register_cb(wpa_msg_cb_func func);







void hostapd_logger(void *ctx, const unsigned char *addr, unsigned int module, int level,
		    const char *fmt, ...) ;

typedef void (*hostapd_logger_cb_func)(void *ctx, const unsigned char *addr,
				       unsigned int module, int level,
				       const char *txt, size_t len);




 
void hostapd_logger_register_cb(hostapd_logger_cb_func func);


#line 223 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_debug.h"

enum hostapd_logger_level {
	HOSTAPD_LEVEL_DEBUG_VERBOSE = 0,
	HOSTAPD_LEVEL_DEBUG = 1,
	HOSTAPD_LEVEL_INFO = 2,
	HOSTAPD_LEVEL_NOTICE = 3,
	HOSTAPD_LEVEL_WARNING = 4
};


#line 239 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_debug.h"

static  void wpa_debug_open_syslog(void)
{
}

static  void wpa_debug_close_syslog(void)
{
}




#line 264 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_debug.h"

#line 498 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\utils\\wpa_common.h"










 
void * __hide_aliasing_typecast(void *foo);



#line 18 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver_none.c"
#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver.h"




















 






#line 1 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\common/defs.h"












 





#line 25 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\common/defs.h"





#line 38 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\common/defs.h"

#line 49 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\common/defs.h"



static  int wpa_key_mgmt_wpa_ieee8021x(int akm)
{
	return akm == (1 << (0)) ||
		akm == (1 << (5)) ||
		akm == (1 << (7));
}

static  int wpa_key_mgmt_wpa_psk(int akm)
{
	return akm == (1 << (1)) ||
		akm == (1 << (6)) ||
		akm == (1 << (8));
}

static  int wpa_key_mgmt_ft(int akm)
{
	return akm == (1 << (6)) ||
		akm == (1 << (5));
}

static  int wpa_key_mgmt_sha256(int akm)
{
	return akm == (1 << (8)) ||
		akm == (1 << (7));
}











enum wpa_alg {
	WPA_ALG_NONE,
	WPA_ALG_WEP,
	WPA_ALG_TKIP,
	WPA_ALG_CCMP,
	WPA_ALG_IGTK,
	WPA_ALG_PMK,
	WPA_BOTH
};



 
enum wpa_cipher {
	CIPHER_NONE,
	CIPHER_WEP40,
	CIPHER_TKIP,
	CIPHER_CCMP,
	CIPHER_WEP104
};



 
enum wpa_key_mgmt {
	KEY_MGMT_802_1X,
	KEY_MGMT_PSK,
	KEY_MGMT_NONE,
	KEY_MGMT_802_1X_NO_WPA,
	KEY_MGMT_WPA_NONE,
	KEY_MGMT_FT_802_1X,
	KEY_MGMT_FT_PSK,
	KEY_MGMT_802_1X_SHA256,
	KEY_MGMT_PSK_SHA256,
	KEY_MGMT_WPS
};










 
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












 
enum mfp_options {
	NO_MGMT_FRAME_PROTECTION = 0,
	MGMT_FRAME_PROTECTION_OPTIONAL = 1,
	MGMT_FRAME_PROTECTION_REQUIRED = 2
};



 
enum hostapd_hw_mode {
	HOSTAPD_MODE_IEEE80211B,
	HOSTAPD_MODE_IEEE80211G,
	HOSTAPD_MODE_IEEE80211A,
	NUM_HOSTAPD_MODES
};

#line 29 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver.h"








 
struct hostapd_channel_data {
	

 
	short chan;

	

 
	short freq;

	

 
	int flag;

	

 
	unsigned char max_tx_power;
};



 
struct hostapd_hw_modes {
	

 
	enum hostapd_hw_mode mode;

	

 
	int num_channels;

	

 
	struct hostapd_channel_data *channels;

	

 
	int num_rates;

	

 
	int *rates;

	

 
	unsigned short ht_capab;

	

 
	unsigned char mcs_set[16];

	

 
	unsigned char a_mpdu_params;
};










#line 120 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver.h"

























 
struct wpa_scan_res {
	unsigned int flags;
	unsigned char bssid[6];
	int freq;
	unsigned short beacon_int;
	unsigned short caps;
	int qual;
	int noise;
	int level;
	unsigned long tsf;
	unsigned int age;
	size_t ie_len;
	size_t beacon_ie_len;
	





 
};





 
struct wpa_scan_results {
	struct wpa_scan_res **res;
	size_t num;
};










 
struct wpa_interface_info {
	struct wpa_interface_info *next;
	char *ifname;
	char *desc;
	const char *drv_name;
};






 
struct wpa_driver_scan_params {
	

 
	struct wpa_driver_scan_ssid {
		



 
		const unsigned char *ssid;
		

 
		size_t ssid_len;
	} ssids[4];

	


 
	size_t num_ssids;

	

 
	const unsigned char *extra_ies;

	

 
	size_t extra_ies_len;

	



 
	int *freqs;

	












 
	struct wpa_driver_scan_filter {
		unsigned char ssid[32];
		size_t ssid_len;
	} *filter_ssids;

	

 
	size_t num_filter_ssids;
};




 
struct wpa_driver_auth_params {
	int freq;
	const unsigned char *bssid;
	const unsigned char *ssid;
	size_t ssid_len;
	int auth_alg;
	const unsigned char *ie;
	size_t ie_len;
	const unsigned char *wep_key[4];
	size_t wep_key_len[4];
	int wep_tx_keyidx;
	int local_state_change;
};




 
struct wpa_driver_associate_params {
	


 
	const unsigned char *bssid;	   

	

 
	const unsigned char *ssid;		   

	

 
	size_t ssid_len;	   

	



 					   
	int freq;

	
















 
	const unsigned char *wpa_ie;		

	

 
	size_t wpa_ie_len;

	



 
	enum wpa_cipher pairwise_suite;

	



 
	enum wpa_cipher group_suite;

	



 
	enum wpa_key_mgmt key_mgmt_suite;

	


 
	int auth_alg;

	

 
	int mode;

	

 
	const unsigned char *wep_key[4];

	

 
	size_t wep_key_len[4];

	

 
	int wep_tx_keyidx;

	

 
	enum mfp_options mgmt_frame_protection;

	



















 
	const unsigned char *ft_ies;

	

 
	size_t ft_ies_len;

	





 
	const unsigned char *ft_md;

	







 
	const char *passphrase;

	






 
	const unsigned char *psk;

	





 
	int drop_unencrypted;

	




 
	const unsigned char *prev_bssid;
};



 
struct wpa_driver_capa {
#line 476 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver.h"
	unsigned int key_mgmt;





	unsigned int enc;




	unsigned int auth;

 

 



 



 

 

 

	unsigned int flags;

	int max_scan_ssids;

	

 
	unsigned int max_remain_on_chan;
};


struct hostapd_data;

struct hostap_sta_driver_data {
	unsigned long rx_packets, tx_packets, rx_bytes, tx_bytes;
	unsigned long current_tx_rate;
	unsigned long inactive_msec;
	unsigned long flags;
	unsigned long num_ps_buf_frames;
	unsigned long tx_retry_failed;
	unsigned long tx_retry_count;
	int last_rssi;
	int last_ack_rssi;
};

struct hostapd_sta_add_params {
	const unsigned char *addr;
	unsigned short aid;
	unsigned short capability;
	const unsigned char *supp_rates;
	size_t supp_rates_len;
	unsigned short listen_interval;
	const struct ieee80211_ht_capabilities *ht_capabilities;
};

struct hostapd_freq_params {
	int mode;
	int freq;
	int channel;
	int ht_enabled;
	int sec_channel_offset; 

 
};

enum wpa_driver_if_type {
	

 
	WPA_IF_STATION,

	




 
	WPA_IF_AP_VLAN,

	



 
	WPA_IF_AP_BSS,
};

struct wpa_init_params {
	const unsigned char *bssid;
	const char *ifname;
	const unsigned char *ssid;
	size_t ssid_len;
	const char *test_socket;
	int use_pae_group_addr;
	char **bridge;
	size_t num_bridge;

	unsigned char *own_addr;  
};


struct wpa_bss_params {
	 
	const char *ifname;
	 
	int enabled;

	int wpa;
	int ieee802_1x;
	int wpa_group;
	int wpa_pairwise;
	int wpa_key_mgmt;
	int rsn_preauth;
};












 
struct wpa_driver_ops {
	 
	const char *name;													  
	 
	const char *desc;													  

	









 																	   
	int (*get_bssid)(void *priv, unsigned char *bssid);

	













 
	int (*get_ssid)(void *priv, unsigned char *ssid);									

	










































 
	int (*set_key)(const char *ifname, void *priv, enum wpa_alg alg,		 
		       const unsigned char *addr, int key_idx, int set_tx,
		       const unsigned char *seq, size_t seq_len,
		       const unsigned char *key, size_t key_len);

	





















 
	void * (*init)(void *ctx, const char *ifname);							 

	





 
	void (*deinit)(void *priv);												

	








 
	int (*set_param)(void *priv, const char *param);						

	








 
	int (*set_countermeasures)(void *priv, int enabled);				  

	







 
	int (*deauthenticate)(void *priv, const unsigned char *addr, int reason_code);	  

	







 
	int (*disassociate)(void *priv, const unsigned char *addr, int reason_code);	   

	





 
	int (*associate)(void *priv,
			 struct wpa_driver_associate_params *params);				   

	















 
	int (*add_pmkid)(void *priv, const unsigned char *bssid, const unsigned char *pmkid);		  

	
















 
	int (*remove_pmkid)(void *priv, const unsigned char *bssid, const unsigned char *pmkid);	   

	














 
	int (*flush_pmkid)(void *priv);							   

	






 
	int (*get_capa)(void *priv, struct wpa_driver_capa *capa);	  

	










 
	void (*poll)(void *priv);									 

	









 
	const char * (*get_ifname)(void *priv);					  

	








 
	const unsigned char * (*get_mac_addr)(void *priv);					  

	
















 
	int (*send_eapol)(void *priv, const unsigned char *dest, unsigned short proto,
			  const unsigned char *data, size_t data_len);						   

	










 
	int (*set_operstate)(void *priv, int state);					  

	














 
	int (*mlme_setprotection)(void *priv, const unsigned char *addr, int protect_type,
				  int key_type);											   

	









 
	struct hostapd_hw_modes * (*get_hw_feature_data)(void *priv,
							 unsigned short *num_modes,
							 unsigned short *flags);								

	









 
	int (*set_channel)(void *priv, enum hostapd_hw_mode phymode, int chan,
			   int freq);										   

	








 
	int (*set_ssid)(void *priv, const unsigned char *ssid, size_t ssid_len);	   

	







 
	int (*set_bssid)(void *priv, const unsigned char *bssid);				 

	








 
	int (*send_mlme)(void *priv, const unsigned char *data, size_t data_len);		

	













 
	int (*mlme_add_sta)(void *priv, const unsigned char *addr, const unsigned char *supp_rates,
			    size_t supp_rates_len);							   

	







 
	int (*mlme_remove_sta)(void *priv, const unsigned char *addr);				  

	













 
	int (*update_ft_ies)(void *priv, const unsigned char *md, const unsigned char *ies,
			     size_t ies_len);									  

	











 
	int (*send_ft_action)(void *priv, unsigned char action, const unsigned char *target_ap,
			      const unsigned char *ies, size_t ies_len);					   

	





 
	 struct wpa_scan_results * (*get_scan_results2)(void *priv);	   

	







 
	int (*set_country)(void *priv, const char *alpha2);				  

	









 
	void * (*global_init)(void);										 

	





 
	void (*global_deinit)(void *priv);									   

	









 
	void * (*init2)(void *ctx, const char *ifname, void *global_priv);		 

	





 
	struct wpa_interface_info * (*get_interfaces)(void *global_priv);		 

	









 
	int (*scan2)(void *priv, struct wpa_driver_scan_params *params);		

	










 
	int (*authenticate)(void *priv,
			    struct wpa_driver_auth_params *params);					 

	














 
	int (*set_beacon)(void *priv, const unsigned char *head, size_t head_len,
			  const unsigned char *tail, size_t tail_len, int dtim_period,
			  int beacon_int);											 

	







 
	void * (*hapd_init)(struct hostapd_data *hapd,
			    struct wpa_init_params *params);						

	


 
	void (*hapd_deinit)(void *priv);								   

	










 
	int (*set_ieee8021x)(void *priv, struct wpa_bss_params *params);	   

	








 
	int (*set_privacy)(void *priv, int enabled);						   

	












 
	int (*get_seqnum)(const char *ifname, void *priv, const unsigned char *addr,
			  int idx, unsigned char *seq);									   

	







 
	int (*flush)(void *priv);										  

	










 
	int (*set_generic_elem)(void *priv, const unsigned char *elem, size_t elem_len);	

	





 
	int (*read_sta_data)(void *priv, struct hostap_sta_driver_data *data,
			     const unsigned char *addr);								 

	









 
	int (*hapd_send_eapol)(void *priv, const unsigned char *addr, const unsigned char *data,
			       size_t data_len, int encrypt,
			       const unsigned char *own_addr);								   

	









 
	int (*sta_deauth)(void *priv, const unsigned char *own_addr, const unsigned char *addr,
			  int reason);											   

	









 
	int (*sta_disassoc)(void *priv, const unsigned char *own_addr, const unsigned char *addr,
			    int reason);										   

	




 
	int (*sta_remove)(void *priv, const unsigned char *addr);					

	









 
	int (*hapd_get_ssid)(void *priv, unsigned char *buf, int len);				

	





 
	int (*hapd_set_ssid)(void *priv, const unsigned char *buf, int len);		

	







 
	int (*hapd_set_countermeasures)(void *priv, int enabled);	   

	








 
	int (*sta_add)(void *priv, struct hostapd_sta_add_params *params);	  

	




 
	int (*get_inact_sec)(void *priv, const unsigned char *addr);				 

	




 
	int (*sta_clear_stats)(void *priv, const unsigned char *addr);			   

	




 
	int (*set_freq)(void *priv, struct hostapd_freq_params *freq);	

	




 
	int (*set_rts)(void *priv, int rts);							

	




 
	int (*set_frag)(void *priv, int frag);						   

	







 
	int (*sta_set_flags)(void *priv, const unsigned char *addr,
			     int total_flags, int flags_or, int flags_and);		 

	






 
	int (*set_rate_sets)(void *priv, int *supp_rates, int *basic_rates,
			     int mode);													 

	




 
	int (*set_cts_protect)(void *priv, int value);						   

	




 
	int (*set_preamble)(void *priv, int value);							

	




 
	int (*set_short_slot_time)(void *priv, int value);					

	







 
	int (*set_tx_queue_params)(void *priv, int queue, int aifs, int cw_min,
				   int cw_max, int burst_time);									

	







 
	int (*valid_bss_mask)(void *priv, const unsigned char *addr, const unsigned char *mask);			 

	















 
	int (*if_add)(void *priv, enum wpa_driver_if_type type,
		      const char *ifname, const unsigned char *addr, void *bss_ctx,
		      void **drv_priv, char *force_ifname, unsigned char *if_addr);			  

	





 
	int (*if_remove)(void *priv, enum wpa_driver_if_type type,
			 const char *ifname);										   

	












 
	int (*set_sta_vlan)(void *priv, const unsigned char *addr, const char *ifname,
			    int vlan_id);												   

	








 
	int (*commit)(void *priv);												   

	








 
	int (*send_ether)(void *priv, const unsigned char *dst, const unsigned char *src, unsigned short proto,
			  const unsigned char *data, size_t data_len);									  

	






 
	int (*set_radius_acl_auth)(void *priv, const unsigned char *mac, int accepted, 
				   unsigned int session_timeout);											 

	




 
	int (*set_radius_acl_expire)(void *priv, const unsigned char *mac);						 

	







 
	int (*set_ht_params)(void *priv,
			     const unsigned char *ht_capab, size_t ht_capab_len,
			     const unsigned char *ht_oper, size_t ht_oper_len);							 

	











 
	int (*set_ap_wps_ie)(void *priv, const struct wpabuf *beacon,
			     const struct wpabuf *proberesp);								   

	




 
	int (*set_supp_port)(void *priv, int authorized);							  

	






 
	int (*set_wds_sta)(void *priv, const unsigned char *addr, int aid, int val);			 

	
















 
	int (*send_action)(void *priv, unsigned int freq,
			   const unsigned char *dst, const unsigned char *src, const unsigned char *bssid,
			   const unsigned char *data, size_t data_len);									

	




















 
	int (*remain_on_channel)(void *priv, unsigned int freq,
				 unsigned int duration);										   

	









 
	int (*cancel_remain_on_channel)(void *priv);								   

	












 
	int (*probe_req_report)(void *priv, int report);							   

	









 
	int (*disable_11b_rates)(void *priv, int disabled);							  

	







 
	int (*deinit_ap)(void *priv);												   

	


 
	void (*suspend)(void *priv);													

	


 
	void (*resume)(void *priv);														

	












 
	int (*signal_monitor)(void *priv, int threshold, int hysteresis);				

	









 
	int (*send_frame)(void *priv, const unsigned char *data, size_t data_len,
			  int encrypt);														   
};




 
enum wpa_event_type {
	










 
	EVENT_ASSOC,

	








 
	EVENT_DISASSOC,

	







 
	EVENT_MICHAEL_MIC_FAILURE,

	












 
	EVENT_SCAN_RESULTS,

	









 
	EVENT_ASSOCINFO,

	







 
	EVENT_INTERFACE_STATUS,

	






















 
	EVENT_PMKID_CANDIDATE,

	







 
	EVENT_STKSTART,

	





 
	EVENT_FT_RESPONSE,

	






 
	EVENT_IBSS_RSN_START,

	







 
	EVENT_AUTH,

	






 
	EVENT_DEAUTH,

	





 
	EVENT_ASSOC_REJECT,

	

 
	EVENT_AUTH_TIMED_OUT,

	

 
	EVENT_ASSOC_TIMED_OUT,

	

 
	EVENT_FT_RRB_RX,

	

 
	EVENT_WPS_BUTTON_PUSHED,

	

 
	EVENT_TX_STATUS,

	

 
	EVENT_RX_FROM_UNKNOWN,

	

 
	EVENT_RX_MGMT,

	





 
	EVENT_RX_ACTION,

	





 
	EVENT_REMAIN_ON_CHANNEL,

	






 
	EVENT_CANCEL_REMAIN_ON_CHANNEL,

	



 
	EVENT_MLME_RX,

	









 
	EVENT_RX_PROBE_REQ,

	







 
	EVENT_NEW_STA,

	






 
	EVENT_EAPOL_RX,

	





 
	EVENT_SIGNAL_CHANGE
};




 
union wpa_event_data {
	






 
	struct assoc_info {
		









 
		const unsigned char *req_ies;

		

 
		size_t req_ies_len;

		









 
		const unsigned char *resp_ies;

		

 
		size_t resp_ies_len;

		














 
		const unsigned char *beacon_ies;

		
 
		size_t beacon_ies_len;

		

 
		unsigned int freq;

		

 
		const unsigned char *addr;
	} assoc_info;

	

 
	struct disassoc_info {
		

 
		const unsigned char *addr;

		


 
		unsigned short reason_code;
	} disassoc_info;

	

 
	struct deauth_info {
		

 
		const unsigned char *addr;

		


 
		unsigned short reason_code;
	} deauth_info;

	

 
	struct michael_mic_failure {
		int unicast;
		const unsigned char *src;
	} michael_mic_failure;

	

 
	struct interface_status {
		char ifname[100];
		enum {
			EVENT_INTERFACE_ADDED, EVENT_INTERFACE_REMOVED
		} ievent;
	} interface_status;

	

 
	struct pmkid_candidate {
		 
		unsigned char bssid[6];
		 
		int index;
		 
		int preauth;
	} pmkid_candidate;

	

 
	struct stkstart {
		unsigned char peer[6];
	} stkstart;

	







 
	struct ft_ies {
		const unsigned char *ies;
		size_t ies_len;
		int ft_action;
		unsigned char target_ap[6];
		 
		const unsigned char *ric_ies;
		 
		size_t ric_ies_len;
	} ft_ies;

	

 
	struct ibss_rsn_start {
		unsigned char peer[6];
	} ibss_rsn_start;

	

 
	struct auth_info {
		unsigned char peer[6];
		unsigned short auth_type;
		unsigned short status_code;
		const unsigned char *ies;
		size_t ies_len;
	} auth;

	

 
	struct assoc_reject {
		









 
		unsigned char *resp_ies;

		

 
		size_t resp_ies_len;

		

 
		unsigned short status_code;
	} assoc_reject;

	struct timeout_event {
		unsigned char addr[6];
	} timeout_event;

	

 
	struct ft_rrb_rx {
		const unsigned char *src;
		const unsigned char *data;
		size_t data_len;
	} ft_rrb_rx;

	

 
	struct tx_status {
		unsigned short type;
		unsigned short stype;
		const unsigned char *dst;
		const unsigned char *data;
		size_t data_len;
		int ack;
	} tx_status;

	

 
	struct rx_from_unknown {
		const unsigned char *frame;
		size_t len;
	} rx_from_unknown;

	

 
	struct rx_mgmt {
		const unsigned char *frame;
		size_t frame_len;
		unsigned int datarate;
		unsigned int ssi_signal;
	} rx_mgmt;

	

 
	struct rx_action {
		

 
		const unsigned char *da;

		

 
		const unsigned char *sa;

		

 
		const unsigned char *bssid;

		

 
		unsigned char category;

		

 
		const unsigned char *data;

		

 
		size_t len;

		

 
		int freq;
	} rx_action;

	



 
	struct remain_on_channel {
		

 
		unsigned int freq;

		

 
		unsigned int duration;
	} remain_on_channel;

	







 
	struct scan_info {
		int aborted;
		const int *freqs;
		size_t num_freqs;
		struct wpa_driver_scan_ssid ssids[4];
		size_t num_ssids;
	} scan_info;

	

 
	struct mlme_rx {
		const unsigned char *buf;
		size_t len;
		int freq;
		int channel;
		int ssi;
	} mlme_rx;

	

 
	struct rx_probe_req {
		

 
		const unsigned char *sa;

		

 
		const unsigned char *ie;

		

 
		size_t ie_len;
	} rx_probe_req;

	

 
	struct new_sta {
		const unsigned char *addr;
	} new_sta;

	

 
	struct eapol_rx {
		const unsigned char *src;
		const unsigned char *data;
		size_t data_len;
	} eapol_rx;

	

 
	struct signal_change {
		int above_threshold;
	} signal_change;
};










 
void wpa_supplicant_event(void *ctx, enum wpa_event_type event,
			  union wpa_event_data *data);





 

static  void drv_event_assoc(void *ctx, const unsigned char *addr, const unsigned char *ie,
				   size_t ielen)
{
	union wpa_event_data event;
	os_memset(&event, 0, sizeof(event));
	event.assoc_info.req_ies = ie;
	event.assoc_info.req_ies_len = ielen;
	event.assoc_info.addr = addr;
	wpa_supplicant_event(ctx, EVENT_ASSOC, &event);
}

static  void drv_event_disassoc(void *ctx, const unsigned char *addr)
{
	union wpa_event_data event;
	os_memset(&event, 0, sizeof(event));
	event.disassoc_info.addr = addr;
	wpa_supplicant_event(ctx, EVENT_DISASSOC, &event);
}

static  void drv_event_eapol_rx(void *ctx, const unsigned char *src, const unsigned char *data,
				      size_t data_len)
{
	union wpa_event_data event;
	os_memset(&event, 0, sizeof(event));
	event.eapol_rx.src = src;
	event.eapol_rx.data = data;
	event.eapol_rx.data_len = data_len;
	wpa_supplicant_event(ctx, EVENT_EAPOL_RX, &event);
}

#line 19 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver_none.c"


struct none_driver_data {
	struct hostapd_data *hapd;
	void *ctx;
};


static void * none_driver_hapd_init(struct hostapd_data *hapd,
				    struct wpa_init_params *params)
{
	struct none_driver_data *drv;
	;
	drv = os_zalloc(sizeof(struct none_driver_data));
	if (drv == 0) {
		wpa_printf(0, "Could not allocate memory for none "
			   "driver data");
		return 0;
	}
	drv->hapd = hapd;

	return drv;
}


static void none_driver_hapd_deinit(void *priv)
{
	struct none_driver_data *drv = priv;
	;
	os_free(drv);
}


static int none_driver_send_ether(void *priv, const unsigned char *dst, const unsigned char *src,
				  unsigned short proto, const unsigned char *data, size_t data_len)
{
	;
	return 0;
}


static void * none_driver_init(void *ctx, const char *ifname)
{
	struct none_driver_data *drv;
	;

	drv = os_zalloc(sizeof(struct none_driver_data));
	if (drv == 0) {
		wpa_printf(0, "Could not allocate memory for none "
			   "driver data");
		return 0;
	}
	drv->ctx = ctx;

	return drv;
}


static void none_driver_deinit(void *priv)
{
	struct none_driver_data *drv = priv;
	;
	os_free(drv);
}


static int none_driver_send_eapol(void *priv, const unsigned char *dest, unsigned short proto,
				  const unsigned char *data, size_t data_len)
{
	;
	return -1;
}

#line 104 "..\\wpa_supplicant-0.7.3\\wpa_supplicant-0.7.3\\src\\drivers\\driver_none.c"
const struct wpa_driver_ops wpa_driver_none_ops = {
	"none",
	"no driver (RADIUS server/WPS ER)",
	none_driver_hapd_init,
	none_driver_hapd_deinit,
	none_driver_send_ether,
	none_driver_init,
	none_driver_deinit,
	none_driver_send_eapol,
};



