/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _SUM_H_RPCGEN
#define _SUM_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct arr {
	long arr[10];
};
typedef struct arr arr;

struct arrs {
	long arr1[10];
	long arr2[10];
};
typedef struct arrs arrs;

#define SUM_PROG 0x31423456
#define SUM_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define add 1
extern  struct arr * add_1(struct arrs *, CLIENT *);
extern  struct arr * add_1_svc(struct arrs *, struct svc_req *);
extern int sum_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define add 1
extern  struct arr * add_1();
extern  struct arr * add_1_svc();
extern int sum_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_arr (XDR *, arr*);
extern  bool_t xdr_arrs (XDR *, arrs*);

#else /* K&R C */
extern bool_t xdr_arr ();
extern bool_t xdr_arrs ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_SUM_H_RPCGEN */