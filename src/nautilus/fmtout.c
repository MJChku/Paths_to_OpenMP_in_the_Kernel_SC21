/*
 * This code was originally part of klibc-0.103.
 * It was adapted by David Hovemeyer <daveho@cs.umd.edu>
 * for use in GeekOS (http://geekos.sourceforge.net).
 *
 * For information/source for klibc, visit
 *   http://www.kernel.org/pub/linux/libs/klibc/
 *   http://www.zytor.com/mailman/listinfo/klibc/
 *   http://www.zytor.com/cvsweb.cgi/klibc/
 *
 * Modifications are marked with "DHH".
 * Summary of modifications:
 *
 * 1. Use struct Output_Sink to emit formatted output, rather than a
 *    character buffer, to allow output polymorphism.
 *
 * 2. Buffer generated numbers so that all output is generated in order.
 *
 * 3. Don't use long long types: unsigned long is largest
 *    supported type.  Arithmetic on 64 bit types requires runtime support
 *    (at least on x86).
 *
 *
 * Modifications by Kyle Hale 2015 <kh@u.northwestern.edu>
 */

/*
 * vsnprintf.c
 *
 * vsnprintf(), from which the rest of the printf()
 * family is built
 */

#include <stdarg.h>
#include <stddef.h>
#include <nautilus/naut_string.h>
#include <nautilus/fmtout.h> /* DHH: for struct Output_Sink */

#define CHAR_BIT 8
/*
 * DHH: Hack, long long arithmetic requires runtime support.
 * Use unsigned long as greatest unsigned integer supported.
 */
typedef long intmax_t;
typedef unsigned long uintmax_t;
typedef unsigned long uintptr_t;

/* DHH */
#define ASSERT(exp) \
do { if (!(exp)) while(1); } while (0)

enum flags {
  FL_ZERO   = 0x01,		/* Zero modifier */
  FL_MINUS  = 0x02,		/* Minus modifier */
  FL_PLUS   = 0x04,		/* Plus modifier */
  FL_TICK   = 0x08,		/* ' modifier */
  FL_SPACE  = 0x10,		/* Space modifier */
  FL_HASH   = 0x20,		/* # modifier */
  FL_SIGNED = 0x40,		/* Number is signed */
  FL_UPPER  = 0x80		/* Upper case digits */
};

/* These may have to be adjusted on certain implementations */
enum ranks {
  rank_char	= -2,
  rank_short	= -1,
  rank_int 	= 0,
  rank_long	= 1,
#if 0
  rank_longlong	= 2,
#endif
};

#define MIN_RANK	rank_char
#define MAX_RANK	rank_long

#define INTMAX_RANK	rank_long
#define SIZE_T_RANK	rank_long
#define PTRDIFF_T_RANK	rank_long

/* DHH */
#define EMIT(x) do { (q)->Emit((q), (x)); } while (0)

/*
 * DHH - As a hack, we buffer this many digits when generating
 * a number.  Because this code originally was an implementation
 * of vnsprintf(), it generated some digits backwards in a buffer.
 * Obviously we can't do this when emitting output directly
 * to the console or a file.  So, we buffer the generated digits
 * and then emit them in order.
 *
 * This value should be adequate to emit values up to 2^32-1 in
 * bases 2 or greater, including tick marks.
 */
#define NDIGITS_MAX 43

static size_t
format_int(struct Output_Sink *q, uintmax_t val, enum flags flags,
	   int base, int width, int prec)
{
  char *qq;
  size_t o = 0, oo;
  static const char lcdigits[] = "0123456789abcdef";
  static const char ucdigits[] = "0123456789ABCDEF";
  const char *digits;
  uintmax_t tmpval;
  int minus = 0;
  int ndigits = 0, nchars;
  int tickskip, b4tick;
  char digit_buffer[NDIGITS_MAX]; /* DHH */
  size_t ndigits_save; /* DHH */

  /* Select type of digits */
  digits = (flags & FL_UPPER) ? ucdigits : lcdigits;

  /* If signed, separate out the minus */
  if ( flags & FL_SIGNED && (intmax_t)val < 0 ) {
    minus = 1;
    val = (uintmax_t)(-(intmax_t)val);
  }

  /* Count the number of digits needed.  This returns zero for 0. */
  tmpval = val;
  while ( tmpval ) {
    tmpval /= base;
    ndigits++;
  }

  /* Adjust ndigits for size of output */

  if ( flags & FL_HASH && base == 8 ) {
    if ( prec < ndigits+1 )
      prec = ndigits+1;
  }

  if ( ndigits < prec ) {
    ndigits = prec;		/* Mandatory number padding */
  } else if ( val == 0 ) {
    ndigits = 1;		/* Zero still requires space */
  }

  /* For ', figure out what the skip should be */
  if ( flags & FL_TICK ) {
    tickskip = (base == 16) ? 4 : 3;
  } else {
    tickskip = ndigits;		/* No tick marks */
  }

  /* Tick marks aren't digits, but generated by the number converter */
  ndigits += (ndigits-1)/tickskip;

  /* Now compute the number of nondigits */
  nchars = ndigits;

  if ( minus || (flags & (FL_PLUS|FL_SPACE)) )
    nchars++;			/* Need space for sign */
  if ( (flags & FL_HASH) && base == 16 ) {
    nchars += 2;		/* Add 0x for hex */
  }

  /* Emit early space padding */
  if ( !(flags & (FL_MINUS|FL_ZERO)) && width > nchars ) {
    while ( width > nchars ) {
      EMIT(' ');
      width--;
    }
  }

  /* Emit nondigits */
  if ( minus )
    EMIT('-');
  else if ( flags & FL_PLUS )
    EMIT('+');
  else if ( flags & FL_SPACE )
    EMIT(' ');

  if ( (flags & FL_HASH) && base == 16 ) {
    EMIT('0');
    EMIT((flags & FL_UPPER) ? 'X' : 'x');
  }

  /* Emit zero padding */
  if ( (flags & (FL_MINUS|FL_ZERO)) == FL_ZERO && width > ndigits ) {
    while ( width > nchars ) {
      EMIT('0');
      width--;
    }
  }

  /* Generate the number.  This is done from right to left. */
  ASSERT(ndigits <= NDIGITS_MAX); /* DHH */
  ndigits_save = ndigits;
  qq = digit_buffer + ndigits;
  oo = o;

  /* Emit digits to temp buffer */
  b4tick = tickskip;
  while ( ndigits > 0 ) {
    if ( !b4tick-- ) {
      qq--; oo--; ndigits--;
      *qq = '_';
      b4tick = tickskip-1;
    }
    qq--; oo--; ndigits--;
    *qq = digits[val%base];
    val /= base;
  }

  /* Copy digits to Output_Sink */
  for (oo = 0; oo < ndigits_save; ++oo)
    EMIT(digit_buffer[oo]);

  /* Emit late space padding */
  while ( (flags & FL_MINUS) && width > nchars ) {
    EMIT(' ');
    width--;
  }

  return o;
}

/*
 * DHH - This function was originally vsnprintf().
 * I renamed it to Format_Output() and changed it to take
 * a struct Output_Sink instead of a buffer.  That way, it can
 * be used for any kind of formatted output (string, console,
 * file, etc.)
 */
int Format_Output(struct Output_Sink *q, const char *format, va_list ap)
{
  const char *p = format;
  char ch;
  size_t o = 0;			/* Number of characters output */
  uintmax_t val = 0;
  int rank = rank_int;		/* Default rank */
  int width = 0;
  int prec  = -1;
  int base;
  size_t sz;
  enum flags flags = 0;
  enum {
    st_normal,			/* Ground state */
    st_flags,			/* Special flags */
    st_width,			/* Field width */
    st_prec,			/* Field precision */
    st_modifiers		/* Length or conversion modifiers */
  } state = st_normal;
  const char *sarg;		/* %s string argument */
  char carg;			/* %c char argument */
  int slen;			/* String length */

  while ( (ch = *p++) ) {
    switch ( state ) {
    case st_normal:
      if ( ch == '%' ) {
	state = st_flags;
	flags = 0; rank = rank_int; width = 0; prec = -1;
      } else {
	EMIT(ch);
      }
      break;

    case st_flags:
      switch ( ch ) {
      case '-':
	flags |= FL_MINUS;
	break;
      case '+':
	flags |= FL_PLUS;
	break;
      case '\'':
	flags |= FL_TICK;
	break;
      case ' ':
	flags |= FL_SPACE;
	break;
      case '#':
	flags |= FL_HASH;
	break;
      case '0':
	flags |= FL_ZERO;
	break;
      default:
	state = st_width;
	p--;			/* Process this character again */
	break;
      }
      break;

    case st_width:
      if ( ch >= '0' && ch <= '9' ) {
	width = width*10+(ch-'0');
      } else if ( ch == '*' ) {
	width = va_arg(ap, int);
	if ( width < 0 ) {
	  width = -width;
	  flags |= FL_MINUS;
	}
      } else if ( ch == '.' ) {
	prec = 0;		/* Precision given */
	state = st_prec;
      } else {
	state = st_modifiers;
	p--;			/* Process this character again */
      }
      break;

    case st_prec:
      if ( ch >= '0' && ch <= '9' ) {
	prec = prec*10+(ch-'0');
      } else if ( ch == '*' ) {
	prec = va_arg(ap, int);
	if ( prec < 0 )
	  prec = -1;
      } else {
	state = st_modifiers;
	p--;			/* Process this character again */
      }
      break;

    case st_modifiers:
      switch ( ch ) {
	/* Length modifiers - nonterminal sequences */
      case 'h':
	rank--;			/* Shorter rank */
	break;
      case 'l':
	rank++;			/* Longer rank */
	break;
      case 'j':
	rank = INTMAX_RANK;
	break;
      case 'z':
	rank = SIZE_T_RANK;
	break;
      case 't':
	rank = PTRDIFF_T_RANK;
	break;
      case 'L':
      case 'q':
	rank += 2;
	break;
      default:
	/* Output modifiers - terminal sequences */
	state = st_normal;	/* Next state will be normal */
	if ( rank < MIN_RANK )	/* Canonicalize rank */
	  rank = MIN_RANK;
	else if ( rank > MAX_RANK )
	  rank = MAX_RANK;

	switch ( ch ) {
	case 'P':		/* Upper case pointer */
	  flags |= FL_UPPER;
	  /* fall through */
	case 'p':		/* Pointer */
	  base = 16;
	  prec = (CHAR_BIT*sizeof(void *)+3)/4;
	  flags |= FL_HASH;
	  val = (uintmax_t)(uintptr_t)va_arg(ap, void *);
	  goto is_integer;

	case 'd':		/* Signed decimal output */
	case 'i':
	  base = 10;
	  flags |= FL_SIGNED;
	  switch (rank) {
	  case rank_char:
	    /* Yes, all these casts are needed... */
	    val = (uintmax_t)(intmax_t)(signed char)va_arg(ap, signed int);
	    break;
	  case rank_short:
	    val = (uintmax_t)(intmax_t)(signed short)va_arg(ap, signed int);
	    break;
	  case rank_int:
	    val = (uintmax_t)(intmax_t)va_arg(ap, signed int);
	    break;
	  case rank_long:
	    val = (uintmax_t)(intmax_t)va_arg(ap, signed long);
	    break;
#if 0
	  case rank_longlong:
	    val = (uintmax_t)(intmax_t)va_arg(ap, signed long long);
	    break;
#endif
	  }
	  goto is_integer;
	case 'o':		/* Octal */
	  base = 8;
	  goto is_unsigned;
	case 'u':		/* Unsigned decimal */
	  base = 10;
	  goto is_unsigned;
	case 'X':		/* Upper case hexadecimal */
	  flags |= FL_UPPER;
	  /* fall through */
	case 'x':		/* Hexadecimal */
	  base = 16;
	  goto is_unsigned;

	is_unsigned:
	  switch (rank) {
	  case rank_char:
	    val = (uintmax_t)(unsigned char)va_arg(ap, unsigned int);
	    break;
	  case rank_short:
	    val = (uintmax_t)(unsigned short)va_arg(ap, unsigned int);
	    break;
	  case rank_int:
	    val = (uintmax_t)va_arg(ap, unsigned int);
	    break;
	  case rank_long:
	    val = (uintmax_t)va_arg(ap, unsigned long);
	    break;
#if 0
	  case rank_longlong:
	    val = (uintmax_t)va_arg(ap, unsigned long long);
	    break;
#endif
	  }
	  /* fall through */

	is_integer:
	  sz = format_int(q, val, flags, base, width, prec);
	  o += sz;
	  break;

	case 'c':		/* Character */
	  carg = (char)va_arg(ap, int);
	  sarg = &carg;
	  slen = 1;
	  goto is_string;
	case 's':		/* String */
	  sarg = va_arg(ap, const char *);
	  sarg = sarg ? sarg : "(null)";
	  slen = strlen(sarg);
	  goto is_string;

	is_string:
	  {
	    char sch;
	    int i;
	    
	    if ( prec != -1 && slen > prec )
	      slen = prec;
	    
	    if ( width > slen && !(flags & FL_MINUS) ) {
	      char pad = (flags & FL_ZERO) ? '0' : ' ';
	      while ( width > slen ) {
		EMIT(pad);
		width--;
	      }
	    }
	    for ( i = slen ; i ; i-- ) {
	      sch = *sarg++;
	      EMIT(sch);
	    }
	    if ( width > slen && (flags & FL_MINUS) ) {
	      while ( width > slen ) {
		EMIT(' ');
		width--;
	      }
	    }
	  }
	  break;

	case 'n':		/* Output the number of characters written */
	  {
	    switch (rank) {
	    case rank_char:
	      *va_arg(ap, signed char *) = o;
	      break;
	    case rank_short:
	      *va_arg(ap, signed short *) = o;
	      break;
	    case rank_int:
	      *va_arg(ap, signed int *) = o;
	      break;
	    case rank_long:
	      *va_arg(ap, signed long *) = o;
	      break;
#if 0
	    case rank_longlong:
	      *va_arg(ap, signed long long *) = o;
	      break;
#endif
	    }
	  }
	  break;
	  
	default:		/* Anything else, including % */
	  EMIT(ch);
	  break;
	}
      }
    }
  }

  /* Null-terminate the string */
#if 0
  if ( o<n )
    *q = '\0';			/* No overflow */
  else if ( n>0 )
    buffer[n-1] = '\0';		/* Overflow - terminate at end of buffer */
#endif
  q->Finish(q);

  return o;
}