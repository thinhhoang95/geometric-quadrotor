#ifndef __c7_NLGC_2_h__
#define __c7_NLGC_2_h__

/* Type Definitions */
#ifndef typedef_SFc7_NLGC_2InstanceStruct
#define typedef_SFc7_NLGC_2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c7_sfEvent;
  boolean_T c7_doneDoubleBufferReInit;
  uint8_T c7_is_active_c7_NLGC_2;
  real_T c7_Ct;
  real_T c7_d;
  real_T c7_Cq;
  void *c7_fEmlrtCtx;
  real_T *c7_f;
  real_T *c7_o1;
  real_T (*c7_M)[3];
  real_T *c7_o2;
  real_T *c7_o3;
  real_T *c7_o4;
} SFc7_NLGC_2InstanceStruct;

#endif                                 /*typedef_SFc7_NLGC_2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c7_NLGC_2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c7_NLGC_2_get_check_sum(mxArray *plhs[]);
extern void c7_NLGC_2_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
