/* prevent including the file twice */
// check if not defined
# ifndef __dbg_h__
// define it if not
# define __dbg_h__

/* standard libs includes */
# include <stdio.h>
# include <errono.h>
# include <string.h>

/* define debug macro */
# ifdef NDEBUG
# define debug(M, ...)
# else
// ... -> means unspecified, variable number of parameters
// allows 
# define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", \
         __FILE__, __LINE__, ##__VA_ARGS__)
# endif
