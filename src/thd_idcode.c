#include "mrilib.h"
#include "thd.h"


/**********************************************************************
  Routine to return a (hopefully) unique ID code to be used to identify
  a dataset to other datasets.  This is to prevent the former strategy
  of relying on the user input "self_name" being unique, since that
  turns out not to be a good idea (users -- they make software so
  much harder to write).  The method used was dreamed up while the
  author (RWCox) had the flu, so it is probably pitiful.
***********************************************************************/

#include <sys/utsname.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

/*-- 23 May 2000: modified to use upper and lower case --*/

static char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
#define NALPH 52

MCW_idcode MCW_new_idcode(void)
{
   struct utsname ubuf ;
   struct timeval tv ;
   struct timezone tz ;
   time_t tnow ;
   long   tt ;
   int    nn , tq , ic ;
   MCW_idcode newid ;

   static int  nbuf=0   , iq ;
   static char *buf=NULL ;

   /* first time in: initialize buf string */

   if( nbuf == 0 ){
      nn = uname( &ubuf ) ;
      if( nn == -1 ){                     /* should never transpire */
         strcpy( ubuf.nodename , "E" ) ;
         strcpy( ubuf.sysname  , "L" ) ;
         strcpy( ubuf.release  , "V" ) ;
         strcpy( ubuf.version  , "I" ) ;
         strcpy( ubuf.machine  , "S" ) ;
      }
      nbuf = strlen(ubuf.nodename)+strlen(ubuf.sysname)
            +strlen(ubuf.release )+strlen(ubuf.version)+strlen(ubuf.machine) ;

      buf = malloc(nbuf+1) ;        /* buf = amalgam of system ID stuff */
      strcpy(buf,ubuf.nodename) ;
      strcat(buf,ubuf.sysname ) ;
      strcat(buf,ubuf.release ) ;
      strcat(buf,ubuf.version ) ;
      strcat(buf,ubuf.machine ) ;

      iq = lrand48() % nbuf ;  /* random starting point in buf */
   }

   nn = gettimeofday( &tv , NULL ) ;
   if( nn == -1 ){ tv.tv_sec = lrand48()%9999999; tv.tv_usec = lrand48()%999999; }
   tt = tv.tv_sec + 13*tv.tv_usec + lrand48() % 9999999 ;

   strcpy(newid.str,MCW_IDPREFIX) ; ic = strlen(newid.str) ;

   for( ; ic < MCW_IDSIZE-1 ; ic++ ){
     tq  = (tt % NALPH) + (int) buf[iq] ; tq  = tq % NALPH ;
     iq  = (iq+1) % nbuf ; tt /= 5 ;
     newid.str[ic] = alphabet[tq] ;
   }
   newid.str[ic] = '\0' ;

   tnow = time(NULL) ;
   MCW_strncpy( newid.date , ctime(&tnow) , MCW_IDDATE ) ;
   nn = strlen(newid.date) ;
   if( nn > 0 && newid.date[nn-1] == '\n' ) newid.date[nn-1] = '\0' ;

   return newid ;
}
