#include "math.h"
double sqrt
    (
    double x	/* value to compute the square root of */
    )

    {
        double q,s,b,r;
        double t,zero=0.0;
        int m,n,i;

#if defined(vax)||defined(tahoe)
        int k=54;
#else	/* defined(vax)||defined(tahoe) */
        int k=51;
#endif	/* defined(vax)||defined(tahoe) */

	/* Select hardware/software square root */
#if	(CPU_FAMILY == SPARC) || (CPU_FAMILY == SPARCV9)
        extern unsigned char sparcHardSqrt;
		
        if (sparcHardSqrt == 1)
	    {
	    double  sqrtHw();

	    return (sqrtHw (x));
	    }
#endif	/* (CPU_FAMILY == SPARC) */

    /* sqrt(NaN) is NaN, sqrt(+-0) = +-0 */
        if(x!=x||x==zero) return(x);

    /* sqrt(negative) is invalid */
        if(x<zero) {
#if defined(vax)||defined(tahoe)
		extern double infnan();
		return (infnan(EDOM));	/* NaN */
#else	/* defined(vax)||defined(tahoe) */
		errno = EDOM;
		return(zero/zero);
#endif	/* defined(vax)||defined(tahoe) */
	}

    /* sqrt(INF) is INF */
        if(!finite(x)) return(x);

    /* scale x to [1,4) */
        n=logb(x);
        x=scalb(x,-n);
        if((m=logb(x))!=0) x=scalb(x,-m);       /* subnormal number */
        m += n;
        n = m/2;
        if((n+n)!=m) {x *= 2; m -=1; n=m/2;}

    /* generate sqrt(x) bit by bit (accumulating in q) */
            q=1.0; s=4.0; x -= 1.0; r=1;
            for(i=1;i<=k;i++) {
                t=s+1; x *= 4; r /= 2;
                if(t<=x) {
                    s=t+t+2, x -= t; q += r;}
                else
                    s *= 2;
                }

    /* generate the last bit and determine the final rounding */
            r/=2; x *= 4;
            if(x==zero) goto end; 100+r; /* trigger inexact flag */
            if(s<x) {
                q+=r; x -=s; s += 2; s *= 2; x *= 4;
                t = (x-s)-5;
                b=1.0+3*r/4; if(b==1.0) goto end; /* b==1 : Round-to-zero */
                b=1.0+r/4;   if(b>1.0) t=1;	/* b>1 : Round-to-(+INF) */
                if(t>=0) q+=r; }	      /* else: Round-to-nearest */
            else {
                s *= 2; x *= 4;
                t = (x-s)-1;
                b=1.0+3*r/4; if(b==1.0) goto end;
                b=1.0+r/4;   if(b>1.0) t=1;
                if(t>=0) q+=r; }

end:        return(scalb(q,n));
    }
