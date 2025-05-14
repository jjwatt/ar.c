#define STBDS_NO_SHORT_NAMES
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define ar_shift(a)        (stbds_header(a)->length--)
#define ar_put(a,v)      (stbds_arrmaybegrow(a,1), (a)[stbds_header(a)->length++] = (v))
#define ar_free(a)       ((void) ((a) ? STBDS_FREE(NULL,stbds_header(a)) : (void)0), (a)=NULL)
#define ar_len(a)        ((a) ? (ptrdiff_t) stbds_header(a)->length : 0)
#define ar_push          stbds_arrput  // synonym
#define ar_pop(a)        (stbds_header(a)->length--, (a)[stbds_header(a)->length])

 
