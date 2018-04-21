#ifndef __c3_NLGCToolbox_h__
#define __c3_NLGCToolbox_h__

/* Type Definitions */
#ifndef typedef_SFc3_NLGCToolboxInstanceStruct
#define typedef_SFc3_NLGCToolboxInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_NLGCToolbox;
  real_T c3_Ts;
  void *c3_fEmlrtCtx;
  real_T (*c3_Rd1)[9];
  real_T (*c3_Omega)[3];
  real_T (*c3_Rd2)[9];
} SFc3_NLGCToolboxInstanceStruct;

#endif                                 /*typedef_SFc3_NLGCToolboxInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_NLGCToolbox_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_NLGCToolbox_get_check_sum(mxArray *plhs[]);
extern void c3_NLGCToolbox_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
