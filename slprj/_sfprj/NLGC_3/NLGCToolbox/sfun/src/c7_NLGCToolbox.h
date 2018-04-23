#ifndef __c7_NLGCToolbox_h__
#define __c7_NLGCToolbox_h__

/* Type Definitions */
#ifndef typedef_SFc7_NLGCToolboxInstanceStruct
#define typedef_SFc7_NLGCToolboxInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c7_sfEvent;
  boolean_T c7_doneDoubleBufferReInit;
  uint8_T c7_is_active_c7_NLGCToolbox;
  real_T c7_Ct;
  real_T c7_dctcq[12];
  void *c7_fEmlrtCtx;
  real_T *c7_f;
  real_T *c7_o1;
  real_T (*c7_M)[3];
  real_T *c7_o2;
  real_T *c7_o3;
  real_T *c7_o4;
} SFc7_NLGCToolboxInstanceStruct;

#endif                                 /*typedef_SFc7_NLGCToolboxInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c7_NLGCToolbox_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c7_NLGCToolbox_get_check_sum(mxArray *plhs[]);
extern void c7_NLGCToolbox_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
