#ifndef __c1_NLGCToolbox_h__
#define __c1_NLGCToolbox_h__

/* Type Definitions */
#ifndef struct_struct_fGw06pKU762DM8t1dqR94E_tag
#define struct_struct_fGw06pKU762DM8t1dqR94E_tag

struct struct_fGw06pKU762DM8t1dqR94E_tag
{
  real_T g;
  real_T d;
  real_T mass;
  real_T ct;
  real_T cq;
  real_T Jx;
  real_T Jy;
  real_T Jz;
  real_T Jm;
  real_T Jb[9];
  real_T Jbinv[9];
  real_T dctcq[12];
  real_T motor_m;
  real_T motor_dm;
  real_T motor_h;
  real_T motor_r;
  real_T ESC_m;
  real_T ESC_a;
  real_T ESC_b;
  real_T ESC_ds;
  real_T HUB_m;
  real_T HUB_r;
  real_T HUB_H;
  real_T arms_m;
  real_T arms_r;
  real_T arms_L;
  real_T arms_da;
  real_T T;
  real_T minThr;
  real_T cr;
  real_T b;
  real_T plusConfig;
  real_T J[9];
};

#endif                                 /*struct_struct_fGw06pKU762DM8t1dqR94E_tag*/

#ifndef typedef_c1_struct_fGw06pKU762DM8t1dqR94E
#define typedef_c1_struct_fGw06pKU762DM8t1dqR94E

typedef struct struct_fGw06pKU762DM8t1dqR94E_tag
  c1_struct_fGw06pKU762DM8t1dqR94E;

#endif                                 /*typedef_c1_struct_fGw06pKU762DM8t1dqR94E*/

#ifndef typedef_SFc1_NLGCToolboxInstanceStruct
#define typedef_SFc1_NLGCToolboxInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_NLGCToolbox;
  real_T c1_kx;
  real_T c1_kv;
  c1_struct_fGw06pKU762DM8t1dqR94E c1_quadModel;
  void *c1_fEmlrtCtx;
  real_T (*c1_R)[9];
  real_T *c1_thrust_magnitude;
  real_T (*c1_ex)[3];
  real_T (*c1_ev)[3];
  real_T (*c1_a)[3];
  real_T *c1_psi;
  real_T (*c1_desired_attitude)[9];
} SFc1_NLGCToolboxInstanceStruct;

#endif                                 /*typedef_SFc1_NLGCToolboxInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_NLGCToolbox_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_NLGCToolbox_get_check_sum(mxArray *plhs[]);
extern void c1_NLGCToolbox_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
