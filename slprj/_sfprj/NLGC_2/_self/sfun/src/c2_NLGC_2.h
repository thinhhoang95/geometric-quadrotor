#ifndef __c2_NLGC_2_h__
#define __c2_NLGC_2_h__

/* Type Definitions */
#ifndef typedef_SFc2_NLGC_2InstanceStruct
#define typedef_SFc2_NLGC_2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_NLGC_2;
  real_T c2_kr;
  real_T c2_ko;
  void *c2_fEmlrtCtx;
  real_T (*c2_J)[9];
  real_T (*c2_moment)[3];
  real_T (*c2_O)[3];
  real_T (*c2_R)[9];
  real_T (*c2_Od)[3];
  real_T (*c2_Odd)[3];
  real_T (*c2_Rd)[9];
  real_T (*c2_er)[3];
  real_T (*c2_eo)[3];
} SFc2_NLGC_2InstanceStruct;

#endif                                 /*typedef_SFc2_NLGC_2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_NLGC_2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_NLGC_2_get_check_sum(mxArray *plhs[]);
extern void c2_NLGC_2_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
