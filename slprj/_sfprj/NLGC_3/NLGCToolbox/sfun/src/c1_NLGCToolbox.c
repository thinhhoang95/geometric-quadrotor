/* Include files */

#include "NLGCToolbox_sfun.h"
#include "c1_NLGCToolbox.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "NLGCToolbox_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c1_debug_family_names[17] = { "e3", "desired_thrust",
  "z_direction", "x_direction", "y_direction", "nargin", "nargout", "R", "ex",
  "ev", "a", "psi", "kx", "kv", "quadModel", "thrust_magnitude",
  "desired_attitude" };

static const char * c1_b_debug_family_names[7] = { "ZYXib", "nargin", "nargout",
  "Psi", "The", "Phi", "dcm" };

static const char * c1_c_debug_family_names[4] = { "nargin", "nargout", "x", "y"
};

static const char * c1_d_debug_family_names[9] = { "Rpsi", "ddv", "pdv",
  "nargin", "nargout", "psi", "thrust_direction", "initial_pitch", "y" };

/* Function Declarations */
static void initialize_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance);
static void initialize_params_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance);
static void enable_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct *chartInstance);
static void disable_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_NLGCToolbox
  (SFc1_NLGCToolboxInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_NLGCToolbox
  (SFc1_NLGCToolboxInstanceStruct *chartInstance);
static void set_sim_state_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance);
static void sf_gateway_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance);
static void mdl_start_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance);
static void initSimStructsc1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_b_desired_attitude, const char_T *c1_identifier, real_T
  c1_y[9]);
static void c1_b_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_b_thrust_magnitude, const char_T
  *c1_identifier);
static real_T c1_d_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  c1_struct_fGw06pKU762DM8t1dqR94E *c1_y);
static void c1_f_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[12]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_g_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static real_T c1_norm(SFc1_NLGCToolboxInstanceStruct *chartInstance, real_T
                      c1_x[3]);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_h_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_i_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_NLGCToolbox, const char_T
  *c1_identifier);
static uint8_T c1_j_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_NLGCToolboxInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_NLGCToolboxInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_NLGCToolbox(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_is_active_c1_NLGCToolbox = 0U;
}

static void initialize_params_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance)
{
  real_T c1_d0;
  real_T c1_d1;
  const mxArray *c1_m0 = NULL;
  static const char * c1_fieldNames[33] = { "g", "d", "mass", "ct", "cq", "Jx",
    "Jy", "Jz", "Jm", "Jb", "Jbinv", "dctcq", "motor_m", "motor_dm", "motor_h",
    "motor_r", "ESC_m", "ESC_a", "ESC_b", "ESC_ds", "HUB_m", "HUB_r", "HUB_H",
    "arms_m", "arms_r", "arms_L", "arms_da", "T", "minThr", "cr", "b",
    "plusConfig", "J" };

  const mxArray *c1_mxField;
  c1_struct_fGw06pKU762DM8t1dqR94E c1_r0;
  sf_mex_import_named("kx", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c1_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_kx = c1_d0;
  sf_mex_import_named("kv", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c1_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_kv = c1_d1;
  c1_m0 = sf_mex_get_sfun_param(chartInstance->S, 2, 1);
  sf_mex_check_bus_parameter(c1_m0, 0, NULL, 33, c1_fieldNames, "quadModel",
    "struct_fGw06pKU762DM8t1dqR94E");
  c1_mxField = sf_mex_getfield(c1_m0, "g", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.g, 1, 0, 0U, 0,
                      0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "d", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.d, 1, 0, 0U, 0,
                      0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "mass", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.mass, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "ct", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.ct, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "cq", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.cq, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "Jx", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.Jx, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "Jy", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.Jy, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "Jz", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.Jz, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "Jm", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.Jm, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "Jb", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), c1_r0.Jb, 1, 0, 0U, 1,
                      0U, 2, 3, 3);
  c1_mxField = sf_mex_getfield(c1_m0, "Jbinv", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), c1_r0.Jbinv, 1, 0, 0U,
                      1, 0U, 2, 3, 3);
  c1_mxField = sf_mex_getfield(c1_m0, "dctcq", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), c1_r0.dctcq, 1, 0, 0U,
                      1, 0U, 2, 3, 4);
  c1_mxField = sf_mex_getfield(c1_m0, "motor_m", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.motor_m, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "motor_dm", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.motor_dm, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "motor_h", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.motor_h, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "motor_r", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.motor_r, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "ESC_m", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.ESC_m, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "ESC_a", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.ESC_a, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "ESC_b", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.ESC_b, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "ESC_ds", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.ESC_ds, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "HUB_m", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.HUB_m, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "HUB_r", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.HUB_r, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "HUB_H", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.HUB_H, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "arms_m", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.arms_m, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "arms_r", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.arms_r, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "arms_L", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.arms_L, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "arms_da", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.arms_da, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "T", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.T, 1, 0, 0U, 0,
                      0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "minThr", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.minThr, 1, 0,
                      0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "cr", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.cr, 1, 0, 0U,
                      0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "b", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.b, 1, 0, 0U, 0,
                      0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "plusConfig", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), &c1_r0.plusConfig, 1,
                      0, 0U, 0, 0U, 0);
  c1_mxField = sf_mex_getfield(c1_m0, "J", "quadModel", 0);
  sf_mex_import_named("quadModel", sf_mex_dup(c1_mxField), c1_r0.J, 1, 0, 0U, 1,
                      0U, 2, 3, 3);
  sf_mex_destroy(&c1_m0);
  chartInstance->c1_quadModel = c1_r0;
}

static void enable_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_NLGCToolbox
  (SFc1_NLGCToolboxInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_NLGCToolbox
  (SFc1_NLGCToolboxInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  const mxArray *c1_b_y = NULL;
  real_T c1_hoistedGlobal;
  const mxArray *c1_c_y = NULL;
  uint8_T c1_b_hoistedGlobal;
  const mxArray *c1_d_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(3, 1), false);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", *chartInstance->c1_desired_attitude,
    0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = *chartInstance->c1_thrust_magnitude;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_b_hoistedGlobal = chartInstance->c1_is_active_c1_NLGCToolbox;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[9];
  int32_T c1_i0;
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                      "desired_attitude", c1_dv0);
  for (c1_i0 = 0; c1_i0 < 9; c1_i0++) {
    (*chartInstance->c1_desired_attitude)[c1_i0] = c1_dv0[c1_i0];
  }

  *chartInstance->c1_thrust_magnitude = c1_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "thrust_magnitude");
  chartInstance->c1_is_active_c1_NLGCToolbox = c1_i_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)),
     "is_active_c1_NLGCToolbox");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_NLGCToolbox(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance)
{
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  int32_T c1_i6;
  real_T c1_b_R[9];
  int32_T c1_i7;
  real_T c1_b_ex[3];
  int32_T c1_i8;
  real_T c1_b_ev[3];
  real_T c1_b_psi;
  real_T c1_b_a[3];
  real_T c1_b_kx;
  real_T c1_b_kv;
  c1_struct_fGw06pKU762DM8t1dqR94E c1_b_quadModel;
  uint32_T c1_debug_family_var_map[17];
  real_T c1_e3[3];
  real_T c1_desired_thrust[3];
  real_T c1_z_direction[3];
  real_T c1_x_direction[3];
  real_T c1_y_direction[3];
  real_T c1_nargin = 8.0;
  real_T c1_nargout = 2.0;
  real_T c1_b_thrust_magnitude;
  real_T c1_b_desired_attitude[9];
  int32_T c1_i9;
  static real_T c1_b[3] = { 0.0, 0.0, 1.0 };

  int32_T c1_i10;
  int32_T c1_i11;
  real_T c1_c_a[3];
  real_T c1_d_a[3];
  int32_T c1_i12;
  real_T c1_e_a;
  int32_T c1_i13;
  real_T c1_f_a;
  real_T c1_b_b[3];
  int32_T c1_i14;
  real_T c1_g_a;
  real_T c1_c_b[3];
  real_T c1_h_a;
  int32_T c1_i15;
  int32_T c1_i16;
  real_T c1_d_b[3];
  int32_T c1_i17;
  int32_T c1_i18;
  real_T c1_B;
  real_T c1_b_desired_thrust[3];
  int32_T c1_i19;
  real_T c1_c_psi;
  int32_T c1_i20;
  real_T c1_initial_pitch;
  real_T c1_thrust_direction[3];
  uint32_T c1_b_debug_family_var_map[9];
  real_T c1_Rpsi[9];
  real_T c1_ddv[3];
  real_T c1_pdv[3];
  real_T c1_b_nargin = 3.0;
  real_T c1_b_nargout = 1.0;
  real_T c1_Psi;
  real_T c1_The;
  real_T c1_Phi;
  uint32_T c1_c_debug_family_var_map[7];
  real_T c1_ZYXib[9];
  real_T c1_c_nargin = 3.0;
  real_T c1_c_nargout = 1.0;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_i_x;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_m_x;
  real_T c1_n_x;
  real_T c1_o_x;
  real_T c1_p_x;
  real_T c1_q_x;
  real_T c1_r_x;
  real_T c1_s_x;
  real_T c1_t_x;
  real_T c1_u_x;
  real_T c1_v_x;
  real_T c1_w_x;
  real_T c1_x_x;
  real_T c1_y_x;
  real_T c1_ab_x;
  real_T c1_bb_x;
  real_T c1_cb_x;
  real_T c1_db_x;
  real_T c1_d2;
  real_T c1_d3;
  real_T c1_d4;
  real_T c1_d5;
  real_T c1_d6;
  real_T c1_d7;
  real_T c1_d8;
  real_T c1_d9;
  real_T c1_d10;
  real_T c1_d11;
  real_T c1_d12;
  real_T c1_d13;
  real_T c1_d14;
  real_T c1_d15;
  real_T c1_d16;
  real_T c1_d17;
  real_T c1_d18;
  real_T c1_d19;
  real_T c1_d20;
  real_T c1_d21;
  real_T c1_d22;
  real_T c1_d23;
  real_T c1_d24;
  real_T c1_d25;
  real_T c1_d26;
  real_T c1_d27;
  real_T c1_d28;
  real_T c1_d29;
  real_T c1_d30;
  int32_T c1_i21;
  int32_T c1_i22;
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_i25;
  int32_T c1_i26;
  int32_T c1_i27;
  int32_T c1_i28;
  int32_T c1_i29;
  int32_T c1_i30;
  real_T c1_i_a[9];
  int32_T c1_i31;
  int32_T c1_i32;
  int32_T c1_i33;
  uint32_T c1_d_debug_family_var_map[4];
  real_T c1_eb_x[3];
  real_T c1_d_nargin = 1.0;
  static real_T c1_e_b[3] = { 1.0, 0.0, 0.0 };

  real_T c1_d_nargout = 1.0;
  real_T c1_y[9];
  int32_T c1_i34;
  real_T c1_fb_x[3];
  real_T c1_e_nargin = 1.0;
  real_T c1_e_nargout = 1.0;
  real_T c1_b_y[9];
  int32_T c1_i35;
  int32_T c1_i36;
  int32_T c1_i37;
  int32_T c1_i38;
  real_T c1_j_a[9];
  int32_T c1_i39;
  real_T c1_k_a[3];
  int32_T c1_i40;
  int32_T c1_i41;
  real_T c1_d31;
  int32_T c1_i42;
  int32_T c1_i43;
  int32_T c1_i44;
  int32_T c1_i45;
  real_T c1_b_B;
  real_T c1_b_pdv[3];
  int32_T c1_i46;
  int32_T c1_i47;
  real_T c1_gb_x[3];
  real_T c1_f_nargin = 1.0;
  real_T c1_f_nargout = 1.0;
  real_T c1_c_y[9];
  int32_T c1_i48;
  int32_T c1_i49;
  int32_T c1_i50;
  int32_T c1_i51;
  int32_T c1_i52;
  int32_T c1_i53;
  int32_T c1_i54;
  int32_T c1_i55;
  int32_T c1_i56;
  int32_T c1_i57;
  int32_T c1_i58;
  int32_T c1_i59;
  int32_T c1_i60;
  int32_T c1_i61;
  int32_T c1_i62;
  int32_T c1_i63;
  int32_T c1_i64;
  real_T c1_l_a[3];
  int32_T c1_i65;
  int32_T c1_i66;
  int32_T c1_i67;
  real_T c1_m_a[3];
  static real_T c1_n_a[3] = { 0.0, 0.0, 1.0 };

  int32_T c1_i68;
  real_T c1_d_y;
  int32_T c1_k;
  int32_T c1_i69;
  real_T c1_c_desired_thrust[3];
  int32_T c1_i70;
  int32_T c1_i71;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_psi, 4U);
  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_a)[c1_i1], 3U);
  }

  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_ev)[c1_i2], 2U);
  }

  for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_ex)[c1_i3], 1U);
  }

  for (c1_i4 = 0; c1_i4 < 9; c1_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_R)[c1_i4], 0U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i5 = 0; c1_i5 < 9; c1_i5++) {
    c1_b_R[c1_i5] = (*chartInstance->c1_R)[c1_i5];
  }

  for (c1_i6 = 0; c1_i6 < 3; c1_i6++) {
    c1_b_ex[c1_i6] = (*chartInstance->c1_ex)[c1_i6];
  }

  for (c1_i7 = 0; c1_i7 < 3; c1_i7++) {
    c1_b_ev[c1_i7] = (*chartInstance->c1_ev)[c1_i7];
  }

  for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
    c1_b_a[c1_i8] = (*chartInstance->c1_a)[c1_i8];
  }

  c1_b_psi = *chartInstance->c1_psi;
  c1_b_kx = chartInstance->c1_kx;
  c1_b_kv = chartInstance->c1_kv;
  c1_b_quadModel = chartInstance->c1_quadModel;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_e3, 0U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_desired_thrust, 1U,
    c1_e_sf_marshallOut, c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_z_direction, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_x_direction, 3U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_y_direction, 4U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 6U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_R, 7U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_ex, 8U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_ev, 9U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_a, 10U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_psi, 11U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_kx, 12U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_kv, 13U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_quadModel, 14U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_thrust_magnitude, 15U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_desired_attitude, 16U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
    c1_e3[c1_i9] = c1_b[c1_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  for (c1_i10 = 0; c1_i10 < 3; c1_i10++) {
    c1_c_a[c1_i10] = c1_b_a[c1_i10];
  }

  for (c1_i11 = 0; c1_i11 < 3; c1_i11++) {
    c1_d_a[c1_i11] = c1_b_a[c1_i11];
  }

  if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c1_norm(chartInstance,
         c1_c_a), 100.0, -1, 4U, c1_norm(chartInstance, c1_d_a) > 100.0))) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
    for (c1_i12 = 0; c1_i12 < 3; c1_i12++) {
      c1_b_a[c1_i12] = 0.0;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_e_a = -c1_b_kx;
  for (c1_i13 = 0; c1_i13 < 3; c1_i13++) {
    c1_b_b[c1_i13] = c1_b_ex[c1_i13];
  }

  c1_f_a = c1_b_kv;
  for (c1_i14 = 0; c1_i14 < 3; c1_i14++) {
    c1_c_b[c1_i14] = c1_b_ev[c1_i14];
  }

  c1_g_a = c1_b_quadModel.mass * c1_b_quadModel.g;
  c1_h_a = c1_b_quadModel.mass;
  for (c1_i15 = 0; c1_i15 < 3; c1_i15++) {
    c1_d_b[c1_i15] = c1_b_a[c1_i15];
  }

  for (c1_i16 = 0; c1_i16 < 3; c1_i16++) {
    c1_desired_thrust[c1_i16] = ((c1_e_a * c1_b_b[c1_i16] - c1_f_a *
      c1_c_b[c1_i16]) - c1_g_a * c1_b[c1_i16]) + c1_h_a * c1_d_b[c1_i16];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  for (c1_i17 = 0; c1_i17 < 3; c1_i17++) {
    c1_b_b[c1_i17] = -c1_desired_thrust[c1_i17];
  }

  for (c1_i18 = 0; c1_i18 < 3; c1_i18++) {
    c1_b_desired_thrust[c1_i18] = c1_desired_thrust[c1_i18];
  }

  c1_B = c1_norm(chartInstance, c1_b_desired_thrust);
  for (c1_i19 = 0; c1_i19 < 3; c1_i19++) {
    c1_z_direction[c1_i19] = c1_b_b[c1_i19] / c1_B;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_c_psi = c1_b_psi;
  for (c1_i20 = 0; c1_i20 < 3; c1_i20++) {
    c1_thrust_direction[c1_i20] = c1_z_direction[c1_i20];
  }

  c1_initial_pitch = 0.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c1_d_debug_family_names,
    c1_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Rpsi, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_ddv, 1U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_pdv, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargin, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargout, 4U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_psi, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_thrust_direction, 6U,
    c1_e_sf_marshallOut, c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_initial_pitch, 7U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_x_direction, 8U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
  c1_Psi = c1_c_psi;
  c1_The = c1_initial_pitch;
  c1_Phi = 0.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c1_b_debug_family_names,
    c1_c_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_ZYXib, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargin, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargout, 2U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Psi, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_The, 4U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Phi, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Rpsi, 6U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 3);
  c1_x = c1_Psi;
  c1_b_x = c1_The;
  c1_c_x = c1_Psi;
  c1_d_x = c1_The;
  c1_e_x = c1_Phi;
  c1_f_x = c1_Psi;
  c1_g_x = c1_Phi;
  c1_h_x = c1_Psi;
  c1_i_x = c1_The;
  c1_j_x = c1_Phi;
  c1_k_x = c1_Psi;
  c1_l_x = c1_Phi;
  c1_m_x = c1_Psi;
  c1_n_x = c1_The;
  c1_o_x = c1_Psi;
  c1_p_x = c1_The;
  c1_q_x = c1_Phi;
  c1_r_x = c1_Psi;
  c1_s_x = c1_Phi;
  c1_t_x = c1_Psi;
  c1_u_x = c1_The;
  c1_v_x = c1_Phi;
  c1_w_x = c1_Psi;
  c1_x_x = c1_Phi;
  c1_y_x = c1_The;
  c1_ab_x = c1_The;
  c1_bb_x = c1_Phi;
  c1_cb_x = c1_The;
  c1_db_x = c1_Phi;
  c1_d2 = muDoubleScalarCos(c1_x);
  c1_d3 = muDoubleScalarCos(c1_b_x);
  c1_d4 = muDoubleScalarCos(c1_c_x);
  c1_d5 = muDoubleScalarSin(c1_d_x);
  c1_d6 = muDoubleScalarSin(c1_e_x);
  c1_d7 = muDoubleScalarSin(c1_f_x);
  c1_d8 = muDoubleScalarCos(c1_g_x);
  c1_d9 = muDoubleScalarCos(c1_h_x);
  c1_d10 = muDoubleScalarSin(c1_i_x);
  c1_d11 = muDoubleScalarCos(c1_j_x);
  c1_d12 = muDoubleScalarSin(c1_k_x);
  c1_d13 = muDoubleScalarSin(c1_l_x);
  c1_d14 = muDoubleScalarSin(c1_m_x);
  c1_d15 = muDoubleScalarCos(c1_n_x);
  c1_d16 = muDoubleScalarSin(c1_o_x);
  c1_d17 = muDoubleScalarSin(c1_p_x);
  c1_d18 = muDoubleScalarSin(c1_q_x);
  c1_d19 = muDoubleScalarCos(c1_r_x);
  c1_d20 = muDoubleScalarCos(c1_s_x);
  c1_d21 = muDoubleScalarSin(c1_t_x);
  c1_d22 = muDoubleScalarSin(c1_u_x);
  c1_d23 = muDoubleScalarCos(c1_v_x);
  c1_d24 = muDoubleScalarCos(c1_w_x);
  c1_d25 = muDoubleScalarSin(c1_x_x);
  c1_d26 = muDoubleScalarSin(c1_y_x);
  c1_d27 = muDoubleScalarCos(c1_ab_x);
  c1_d28 = muDoubleScalarSin(c1_bb_x);
  c1_d29 = muDoubleScalarCos(c1_cb_x);
  c1_d30 = muDoubleScalarCos(c1_db_x);
  c1_ZYXib[0] = c1_d2 * c1_d3;
  c1_ZYXib[3] = c1_d4 * c1_d5 * c1_d6 - c1_d7 * c1_d8;
  c1_ZYXib[6] = c1_d9 * c1_d10 * c1_d11 + c1_d12 * c1_d13;
  c1_ZYXib[1] = c1_d14 * c1_d15;
  c1_ZYXib[4] = c1_d16 * c1_d17 * c1_d18 + c1_d19 * c1_d20;
  c1_ZYXib[7] = c1_d21 * c1_d22 * c1_d23 - c1_d24 * c1_d25;
  c1_ZYXib[2] = -c1_d26;
  c1_ZYXib[5] = c1_d27 * c1_d28;
  c1_ZYXib[8] = c1_d29 * c1_d30;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 6);
  c1_i21 = 0;
  for (c1_i22 = 0; c1_i22 < 3; c1_i22++) {
    c1_i23 = 0;
    for (c1_i24 = 0; c1_i24 < 3; c1_i24++) {
      c1_Rpsi[c1_i24 + c1_i21] = c1_ZYXib[c1_i23 + c1_i22];
      c1_i23 += 3;
    }

    c1_i21 += 3;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  c1_i25 = 0;
  for (c1_i26 = 0; c1_i26 < 3; c1_i26++) {
    c1_i28 = 0;
    for (c1_i29 = 0; c1_i29 < 3; c1_i29++) {
      c1_i_a[c1_i29 + c1_i25] = c1_Rpsi[c1_i28 + c1_i26];
      c1_i28 += 3;
    }

    c1_i25 += 3;
  }

  for (c1_i27 = 0; c1_i27 < 3; c1_i27++) {
    c1_ddv[c1_i27] = 0.0;
  }

  for (c1_i30 = 0; c1_i30 < 3; c1_i30++) {
    c1_ddv[c1_i30] = 0.0;
    c1_i32 = 0;
    for (c1_i33 = 0; c1_i33 < 3; c1_i33++) {
      c1_ddv[c1_i30] += c1_i_a[c1_i32 + c1_i30] * c1_e_b[c1_i33];
      c1_i32 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
  for (c1_i31 = 0; c1_i31 < 3; c1_i31++) {
    c1_eb_x[c1_i31] = c1_thrust_direction[c1_i31];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_c_debug_family_names,
    c1_d_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargin, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargout, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_eb_x, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_y, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 2);
  c1_y[0] = 0.0;
  c1_y[3] = -c1_eb_x[2];
  c1_y[6] = c1_eb_x[1];
  c1_y[1] = c1_eb_x[2];
  c1_y[4] = 0.0;
  c1_y[7] = -c1_eb_x[0];
  c1_y[2] = -c1_eb_x[1];
  c1_y[5] = c1_eb_x[0];
  c1_y[8] = 0.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i34 = 0; c1_i34 < 3; c1_i34++) {
    c1_fb_x[c1_i34] = c1_thrust_direction[c1_i34];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_c_debug_family_names,
    c1_d_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargin, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargout, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fb_x, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_y, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 2);
  c1_b_y[0] = 0.0;
  c1_b_y[3] = -c1_fb_x[2];
  c1_b_y[6] = c1_fb_x[1];
  c1_b_y[1] = c1_fb_x[2];
  c1_b_y[4] = 0.0;
  c1_b_y[7] = -c1_fb_x[0];
  c1_b_y[2] = -c1_fb_x[1];
  c1_b_y[5] = c1_fb_x[0];
  c1_b_y[8] = 0.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i35 = 0; c1_i35 < 9; c1_i35++) {
    c1_i_a[c1_i35] = c1_b_y[c1_i35];
  }

  for (c1_i36 = 0; c1_i36 < 3; c1_i36++) {
    c1_b_b[c1_i36] = c1_ddv[c1_i36];
  }

  for (c1_i37 = 0; c1_i37 < 9; c1_i37++) {
    c1_j_a[c1_i37] = c1_y[c1_i37];
  }

  for (c1_i38 = 0; c1_i38 < 3; c1_i38++) {
    c1_k_a[c1_i38] = 0.0;
    c1_i40 = 0;
    for (c1_i41 = 0; c1_i41 < 3; c1_i41++) {
      c1_k_a[c1_i38] += c1_i_a[c1_i40 + c1_i38] * c1_b_b[c1_i41];
      c1_i40 += 3;
    }
  }

  for (c1_i39 = 0; c1_i39 < 3; c1_i39++) {
    c1_d31 = 0.0;
    c1_i43 = 0;
    for (c1_i44 = 0; c1_i44 < 3; c1_i44++) {
      c1_d31 += c1_j_a[c1_i43 + c1_i39] * c1_k_a[c1_i44];
      c1_i43 += 3;
    }

    c1_pdv[c1_i39] = -c1_d31;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  for (c1_i42 = 0; c1_i42 < 3; c1_i42++) {
    c1_b_b[c1_i42] = c1_pdv[c1_i42];
  }

  for (c1_i45 = 0; c1_i45 < 3; c1_i45++) {
    c1_b_pdv[c1_i45] = c1_pdv[c1_i45];
  }

  c1_b_B = c1_norm(chartInstance, c1_b_pdv);
  for (c1_i46 = 0; c1_i46 < 3; c1_i46++) {
    c1_x_direction[c1_i46] = c1_b_b[c1_i46] / c1_b_B;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -24);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  for (c1_i47 = 0; c1_i47 < 3; c1_i47++) {
    c1_gb_x[c1_i47] = c1_z_direction[c1_i47];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_c_debug_family_names,
    c1_d_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_f_nargin, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_f_nargout, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_gb_x, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_c_y, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 2);
  c1_c_y[0] = 0.0;
  c1_c_y[3] = -c1_gb_x[2];
  c1_c_y[6] = c1_gb_x[1];
  c1_c_y[1] = c1_gb_x[2];
  c1_c_y[4] = 0.0;
  c1_c_y[7] = -c1_gb_x[0];
  c1_c_y[2] = -c1_gb_x[1];
  c1_c_y[5] = c1_gb_x[0];
  c1_c_y[8] = 0.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i48 = 0; c1_i48 < 9; c1_i48++) {
    c1_i_a[c1_i48] = c1_c_y[c1_i48];
  }

  for (c1_i49 = 0; c1_i49 < 3; c1_i49++) {
    c1_b_b[c1_i49] = c1_x_direction[c1_i49];
  }

  for (c1_i50 = 0; c1_i50 < 3; c1_i50++) {
    c1_y_direction[c1_i50] = 0.0;
  }

  for (c1_i51 = 0; c1_i51 < 3; c1_i51++) {
    c1_y_direction[c1_i51] = 0.0;
    c1_i53 = 0;
    for (c1_i54 = 0; c1_i54 < 3; c1_i54++) {
      c1_y_direction[c1_i51] += c1_i_a[c1_i53 + c1_i51] * c1_b_b[c1_i54];
      c1_i53 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  for (c1_i52 = 0; c1_i52 < 3; c1_i52++) {
    c1_b_desired_attitude[c1_i52] = c1_x_direction[c1_i52];
  }

  for (c1_i55 = 0; c1_i55 < 3; c1_i55++) {
    c1_b_desired_attitude[c1_i55 + 3] = c1_y_direction[c1_i55];
  }

  for (c1_i56 = 0; c1_i56 < 3; c1_i56++) {
    c1_b_desired_attitude[c1_i56 + 6] = c1_z_direction[c1_i56];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  c1_i57 = 0;
  for (c1_i58 = 0; c1_i58 < 3; c1_i58++) {
    c1_i60 = 0;
    for (c1_i61 = 0; c1_i61 < 3; c1_i61++) {
      c1_i_a[c1_i61 + c1_i57] = c1_b_R[c1_i60 + c1_i58];
      c1_i60 += 3;
    }

    c1_i57 += 3;
  }

  for (c1_i59 = 0; c1_i59 < 9; c1_i59++) {
    c1_j_a[c1_i59] = c1_b_desired_attitude[c1_i59];
  }

  c1_i62 = 0;
  for (c1_i63 = 0; c1_i63 < 3; c1_i63++) {
    c1_l_a[c1_i63] = 0.0;
    for (c1_i66 = 0; c1_i66 < 3; c1_i66++) {
      c1_l_a[c1_i63] += c1_n_a[c1_i66] * c1_i_a[c1_i66 + c1_i62];
    }

    c1_i62 += 3;
  }

  c1_i64 = 0;
  for (c1_i65 = 0; c1_i65 < 3; c1_i65++) {
    c1_m_a[c1_i65] = 0.0;
    for (c1_i68 = 0; c1_i68 < 3; c1_i68++) {
      c1_m_a[c1_i65] += c1_l_a[c1_i68] * c1_j_a[c1_i68 + c1_i64];
    }

    c1_i64 += 3;
  }

  for (c1_i67 = 0; c1_i67 < 3; c1_i67++) {
    c1_b_b[c1_i67] = c1_m_a[c1_i67];
  }

  c1_d_y = 0.0;
  for (c1_k = 0; c1_k < 3; c1_k++) {
    c1_d_y += c1_b_b[c1_k] * c1_b[c1_k];
  }

  for (c1_i69 = 0; c1_i69 < 3; c1_i69++) {
    c1_c_desired_thrust[c1_i69] = c1_desired_thrust[c1_i69];
  }

  c1_b_thrust_magnitude = c1_norm(chartInstance, c1_c_desired_thrust) * c1_d_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -15);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c1_thrust_magnitude = c1_b_thrust_magnitude;
  for (c1_i70 = 0; c1_i70 < 9; c1_i70++) {
    (*chartInstance->c1_desired_attitude)[c1_i70] = c1_b_desired_attitude[c1_i70];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_NLGCToolboxMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_thrust_magnitude, 5U);
  for (c1_i71 = 0; c1_i71 < 9; c1_i71++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_desired_attitude)[c1_i71], 6U);
  }
}

static void mdl_start_c1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc1_NLGCToolbox(SFc1_NLGCToolboxInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)(c1_machineNumber);
  (void)(c1_chartNumber);
  (void)(c1_instanceNumber);
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, c1_instanceNumber, 0U,
    sf_debug_get_script_id(
    "C:\\Users\\hoang\\MATLAB\\Projects\\NLGControl_Quadrotor_1\\Functions\\tangle2dcm.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, c1_instanceNumber, 1U,
    sf_debug_get_script_id(
    "C:\\Users\\hoang\\MATLAB\\Projects\\NLGControl_Quadrotor_1\\Functions\\hat.m"));
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i72;
  int32_T c1_i73;
  const mxArray *c1_y = NULL;
  int32_T c1_i74;
  real_T c1_u[9];
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_i72 = 0;
  for (c1_i73 = 0; c1_i73 < 3; c1_i73++) {
    for (c1_i74 = 0; c1_i74 < 3; c1_i74++) {
      c1_u[c1_i74 + c1_i72] = (*(real_T (*)[9])c1_inData)[c1_i74 + c1_i72];
    }

    c1_i72 += 3;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_b_desired_attitude, const char_T *c1_identifier, real_T
  c1_y[9])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_desired_attitude),
                        &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_desired_attitude);
}

static void c1_b_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9])
{
  real_T c1_dv1[9];
  int32_T c1_i75;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv1, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c1_i75 = 0; c1_i75 < 9; c1_i75++) {
    c1_y[c1_i75] = c1_dv1[c1_i75];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_desired_attitude;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[9];
  int32_T c1_i76;
  int32_T c1_i77;
  int32_T c1_i78;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_b_desired_attitude = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_desired_attitude),
                        &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_desired_attitude);
  c1_i76 = 0;
  for (c1_i77 = 0; c1_i77 < 3; c1_i77++) {
    for (c1_i78 = 0; c1_i78 < 3; c1_i78++) {
      (*(real_T (*)[9])c1_outData)[c1_i78 + c1_i76] = c1_y[c1_i78 + c1_i76];
    }

    c1_i76 += 3;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_b_thrust_magnitude, const char_T
  *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_thrust_magnitude),
    &c1_thisId);
  sf_mex_destroy(&c1_b_thrust_magnitude);
  return c1_y;
}

static real_T c1_d_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d32;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d32, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d32;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_thrust_magnitude;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_b_thrust_magnitude = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_thrust_magnitude),
    &c1_thisId);
  sf_mex_destroy(&c1_b_thrust_magnitude);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  c1_struct_fGw06pKU762DM8t1dqR94E c1_u;
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_c_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_d_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_e_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_f_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_g_u;
  const mxArray *c1_g_y = NULL;
  real_T c1_h_u;
  const mxArray *c1_h_y = NULL;
  real_T c1_i_u;
  const mxArray *c1_i_y = NULL;
  real_T c1_j_u;
  const mxArray *c1_j_y = NULL;
  int32_T c1_i79;
  const mxArray *c1_k_y = NULL;
  real_T c1_k_u[9];
  int32_T c1_i80;
  const mxArray *c1_l_y = NULL;
  int32_T c1_i81;
  const mxArray *c1_m_y = NULL;
  real_T c1_l_u[12];
  real_T c1_m_u;
  const mxArray *c1_n_y = NULL;
  real_T c1_n_u;
  const mxArray *c1_o_y = NULL;
  real_T c1_o_u;
  const mxArray *c1_p_y = NULL;
  real_T c1_p_u;
  const mxArray *c1_q_y = NULL;
  real_T c1_q_u;
  const mxArray *c1_r_y = NULL;
  real_T c1_r_u;
  const mxArray *c1_s_y = NULL;
  real_T c1_s_u;
  const mxArray *c1_t_y = NULL;
  real_T c1_t_u;
  const mxArray *c1_u_y = NULL;
  real_T c1_u_u;
  const mxArray *c1_v_y = NULL;
  real_T c1_v_u;
  const mxArray *c1_w_y = NULL;
  real_T c1_w_u;
  const mxArray *c1_x_y = NULL;
  real_T c1_x_u;
  const mxArray *c1_y_y = NULL;
  real_T c1_y_u;
  const mxArray *c1_ab_y = NULL;
  real_T c1_ab_u;
  const mxArray *c1_bb_y = NULL;
  real_T c1_bb_u;
  const mxArray *c1_cb_y = NULL;
  real_T c1_cb_u;
  const mxArray *c1_db_y = NULL;
  real_T c1_db_u;
  const mxArray *c1_eb_y = NULL;
  real_T c1_eb_u;
  const mxArray *c1_fb_y = NULL;
  real_T c1_fb_u;
  const mxArray *c1_gb_y = NULL;
  real_T c1_gb_u;
  const mxArray *c1_hb_y = NULL;
  int32_T c1_i82;
  const mxArray *c1_ib_y = NULL;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(c1_struct_fGw06pKU762DM8t1dqR94E *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c1_b_u = c1_u.g;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_b_y, "g", "g", 0);
  c1_c_u = c1_u.d;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_c_y, "d", "d", 0);
  c1_d_u = c1_u.mass;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_d_y, "mass", "mass", 0);
  c1_e_u = c1_u.ct;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_e_y, "ct", "ct", 0);
  c1_f_u = c1_u.cq;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_f_y, "cq", "cq", 0);
  c1_g_u = c1_u.Jx;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_g_y, "Jx", "Jx", 0);
  c1_h_u = c1_u.Jy;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_h_y, "Jy", "Jy", 0);
  c1_i_u = c1_u.Jz;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_i_y, "Jz", "Jz", 0);
  c1_j_u = c1_u.Jm;
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_j_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_j_y, "Jm", "Jm", 0);
  for (c1_i79 = 0; c1_i79 < 9; c1_i79++) {
    c1_k_u[c1_i79] = c1_u.Jb[c1_i79];
  }

  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", c1_k_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_addfield(c1_y, c1_k_y, "Jb", "Jb", 0);
  for (c1_i80 = 0; c1_i80 < 9; c1_i80++) {
    c1_k_u[c1_i80] = c1_u.Jbinv[c1_i80];
  }

  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", c1_k_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_addfield(c1_y, c1_l_y, "Jbinv", "Jbinv", 0);
  for (c1_i81 = 0; c1_i81 < 12; c1_i81++) {
    c1_l_u[c1_i81] = c1_u.dctcq[c1_i81];
  }

  c1_m_y = NULL;
  sf_mex_assign(&c1_m_y, sf_mex_create("y", c1_l_u, 0, 0U, 1U, 0U, 2, 3, 4),
                false);
  sf_mex_addfield(c1_y, c1_m_y, "dctcq", "dctcq", 0);
  c1_m_u = c1_u.motor_m;
  c1_n_y = NULL;
  sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_m_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_n_y, "motor_m", "motor_m", 0);
  c1_n_u = c1_u.motor_dm;
  c1_o_y = NULL;
  sf_mex_assign(&c1_o_y, sf_mex_create("y", &c1_n_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_o_y, "motor_dm", "motor_dm", 0);
  c1_o_u = c1_u.motor_h;
  c1_p_y = NULL;
  sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_o_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_p_y, "motor_h", "motor_h", 0);
  c1_p_u = c1_u.motor_r;
  c1_q_y = NULL;
  sf_mex_assign(&c1_q_y, sf_mex_create("y", &c1_p_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_q_y, "motor_r", "motor_r", 0);
  c1_q_u = c1_u.ESC_m;
  c1_r_y = NULL;
  sf_mex_assign(&c1_r_y, sf_mex_create("y", &c1_q_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_r_y, "ESC_m", "ESC_m", 0);
  c1_r_u = c1_u.ESC_a;
  c1_s_y = NULL;
  sf_mex_assign(&c1_s_y, sf_mex_create("y", &c1_r_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_s_y, "ESC_a", "ESC_a", 0);
  c1_s_u = c1_u.ESC_b;
  c1_t_y = NULL;
  sf_mex_assign(&c1_t_y, sf_mex_create("y", &c1_s_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_t_y, "ESC_b", "ESC_b", 0);
  c1_t_u = c1_u.ESC_ds;
  c1_u_y = NULL;
  sf_mex_assign(&c1_u_y, sf_mex_create("y", &c1_t_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_u_y, "ESC_ds", "ESC_ds", 0);
  c1_u_u = c1_u.HUB_m;
  c1_v_y = NULL;
  sf_mex_assign(&c1_v_y, sf_mex_create("y", &c1_u_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_v_y, "HUB_m", "HUB_m", 0);
  c1_v_u = c1_u.HUB_r;
  c1_w_y = NULL;
  sf_mex_assign(&c1_w_y, sf_mex_create("y", &c1_v_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_w_y, "HUB_r", "HUB_r", 0);
  c1_w_u = c1_u.HUB_H;
  c1_x_y = NULL;
  sf_mex_assign(&c1_x_y, sf_mex_create("y", &c1_w_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_x_y, "HUB_H", "HUB_H", 0);
  c1_x_u = c1_u.arms_m;
  c1_y_y = NULL;
  sf_mex_assign(&c1_y_y, sf_mex_create("y", &c1_x_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_y_y, "arms_m", "arms_m", 0);
  c1_y_u = c1_u.arms_r;
  c1_ab_y = NULL;
  sf_mex_assign(&c1_ab_y, sf_mex_create("y", &c1_y_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_ab_y, "arms_r", "arms_r", 0);
  c1_ab_u = c1_u.arms_L;
  c1_bb_y = NULL;
  sf_mex_assign(&c1_bb_y, sf_mex_create("y", &c1_ab_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_bb_y, "arms_L", "arms_L", 0);
  c1_bb_u = c1_u.arms_da;
  c1_cb_y = NULL;
  sf_mex_assign(&c1_cb_y, sf_mex_create("y", &c1_bb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_cb_y, "arms_da", "arms_da", 0);
  c1_cb_u = c1_u.T;
  c1_db_y = NULL;
  sf_mex_assign(&c1_db_y, sf_mex_create("y", &c1_cb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_db_y, "T", "T", 0);
  c1_db_u = c1_u.minThr;
  c1_eb_y = NULL;
  sf_mex_assign(&c1_eb_y, sf_mex_create("y", &c1_db_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_eb_y, "minThr", "minThr", 0);
  c1_eb_u = c1_u.cr;
  c1_fb_y = NULL;
  sf_mex_assign(&c1_fb_y, sf_mex_create("y", &c1_eb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_fb_y, "cr", "cr", 0);
  c1_fb_u = c1_u.b;
  c1_gb_y = NULL;
  sf_mex_assign(&c1_gb_y, sf_mex_create("y", &c1_fb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_gb_y, "b", "b", 0);
  c1_gb_u = c1_u.plusConfig;
  c1_hb_y = NULL;
  sf_mex_assign(&c1_hb_y, sf_mex_create("y", &c1_gb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_hb_y, "plusConfig", "plusConfig", 0);
  for (c1_i82 = 0; c1_i82 < 9; c1_i82++) {
    c1_k_u[c1_i82] = c1_u.J[c1_i82];
  }

  c1_ib_y = NULL;
  sf_mex_assign(&c1_ib_y, sf_mex_create("y", c1_k_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_addfield(c1_y, c1_ib_y, "J", "J", 0);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  c1_struct_fGw06pKU762DM8t1dqR94E *c1_y)
{
  emlrtMsgIdentifier c1_thisId;
  static const char * c1_fieldNames[33] = { "g", "d", "mass", "ct", "cq", "Jx",
    "Jy", "Jz", "Jm", "Jb", "Jbinv", "dctcq", "motor_m", "motor_dm", "motor_h",
    "motor_r", "ESC_m", "ESC_a", "ESC_b", "ESC_ds", "HUB_m", "HUB_r", "HUB_H",
    "arms_m", "arms_r", "arms_L", "arms_da", "T", "minThr", "cr", "b",
    "plusConfig", "J" };

  c1_thisId.fParent = c1_parentId;
  c1_thisId.bParentIsCell = false;
  sf_mex_check_struct(c1_parentId, c1_u, 33, c1_fieldNames, 0U, NULL);
  c1_thisId.fIdentifier = "g";
  c1_y->g = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "g", "g", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "d";
  c1_y->d = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "d", "d", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "mass";
  c1_y->mass = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "mass", "mass", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ct";
  c1_y->ct = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ct", "ct", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "cq";
  c1_y->cq = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "cq", "cq", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jx";
  c1_y->Jx = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jx", "Jx", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jy";
  c1_y->Jy = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jy", "Jy", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jz";
  c1_y->Jz = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jz", "Jz", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jm";
  c1_y->Jm = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jm", "Jm", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jb";
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "Jb",
    "Jb", 0)), &c1_thisId, c1_y->Jb);
  c1_thisId.fIdentifier = "Jbinv";
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "Jbinv",
    "Jbinv", 0)), &c1_thisId, c1_y->Jbinv);
  c1_thisId.fIdentifier = "dctcq";
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "dctcq",
    "dctcq", 0)), &c1_thisId, c1_y->dctcq);
  c1_thisId.fIdentifier = "motor_m";
  c1_y->motor_m = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_m", "motor_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "motor_dm";
  c1_y->motor_dm = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_dm", "motor_dm", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "motor_h";
  c1_y->motor_h = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_h", "motor_h", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "motor_r";
  c1_y->motor_r = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_r", "motor_r", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_m";
  c1_y->ESC_m = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_m", "ESC_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_a";
  c1_y->ESC_a = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_a", "ESC_a", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_b";
  c1_y->ESC_b = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_b", "ESC_b", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_ds";
  c1_y->ESC_ds = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_ds", "ESC_ds", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "HUB_m";
  c1_y->HUB_m = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "HUB_m", "HUB_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "HUB_r";
  c1_y->HUB_r = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "HUB_r", "HUB_r", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "HUB_H";
  c1_y->HUB_H = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "HUB_H", "HUB_H", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_m";
  c1_y->arms_m = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "arms_m", "arms_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_r";
  c1_y->arms_r = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "arms_r", "arms_r", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_L";
  c1_y->arms_L = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "arms_L", "arms_L", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_da";
  c1_y->arms_da = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "arms_da", "arms_da", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "T";
  c1_y->T = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "T", "T", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "minThr";
  c1_y->minThr = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "minThr", "minThr", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "cr";
  c1_y->cr = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "cr", "cr", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "b";
  c1_y->b = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "b", "b", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "plusConfig";
  c1_y->plusConfig = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "plusConfig", "plusConfig", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "J";
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "J", "J",
    0)), &c1_thisId, c1_y->J);
  sf_mex_destroy(&c1_u);
}

static void c1_f_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[12])
{
  real_T c1_dv2[12];
  int32_T c1_i83;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv2, 1, 0, 0U, 1, 0U, 2, 3, 4);
  for (c1_i83 = 0; c1_i83 < 12; c1_i83++) {
    c1_y[c1_i83] = c1_dv2[c1_i83];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_quadModel;
  emlrtMsgIdentifier c1_thisId;
  c1_struct_fGw06pKU762DM8t1dqR94E c1_y;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_b_quadModel = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_quadModel), &c1_thisId,
                        &c1_y);
  sf_mex_destroy(&c1_b_quadModel);
  *(c1_struct_fGw06pKU762DM8t1dqR94E *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i84;
  const mxArray *c1_y = NULL;
  real_T c1_u[3];
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i84 = 0; c1_i84 < 3; c1_i84++) {
    c1_u[c1_i84] = (*(real_T (*)[3])c1_inData)[c1_i84];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 1), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i85;
  const mxArray *c1_y = NULL;
  real_T c1_u[3];
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i85 = 0; c1_i85 < 3; c1_i85++) {
    c1_u[c1_i85] = (*(real_T (*)[3])c1_inData)[c1_i85];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_g_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3])
{
  real_T c1_dv3[3];
  int32_T c1_i86;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i86 = 0; c1_i86 < 3; c1_i86++) {
    c1_y[c1_i86] = c1_dv3[c1_i86];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_y_direction;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i87;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_y_direction = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y_direction), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_y_direction);
  for (c1_i87 = 0; c1_i87 < 3; c1_i87++) {
    (*(real_T (*)[3])c1_outData)[c1_i87] = c1_y[c1_i87];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_NLGCToolbox_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  const char * c1_data[5] = {
    "789ced55cb4ac340149d682d5654ba12bfc185c167adab3eb43650fbd0ea46a49d26a3896666649248fd173fc0a520fe880bbfc7d4b44d326448404911bc106e"
    "0e67e69e99cbcd099094530900b0ea3ea37cb00cbe63c54b203fce73201c3c2f71eba4f072b00032a17d13fe799c554a6c34b43d601a04351d3c40cc05046234",
    "2da3516c1048eceed303020c59d47c44da37736398a86b60d4a00150375c806b016a0a46d4e8bdaa23f5fedcc180e9967f5c330840a03f7dc1fd3331fde183ef"
    "0fbf2e4a4f0aaccb46e8057949902791038b01b4579ae83d08ea45dd2f4a6f49a097e7781b925b136d6b2af670dc7d93ea6739eceb7b8c469d81897cbdd71fea",
    "b5847a61feeaf8ba7a285f588859b24eddcbcba7e56ea35c91db8cde21d5b6e466e3a4ea7e048c9abd8e0335466dca7a5b72cd21aa6d5062c97ecb36719af351"
    "5c7fff2ca73b8f69cfffecf486827a49e76f4da097e7f8a373a841d632f04051f771e7b6086b68bbea9fa31da313770e20c069d5ef0bf6c7f5918fa4be2cf2c9",
    "a47322fa4fe622750b252f6f947ecb27e705faf931a343ef5f3c2b5f7ef9a15e5da817e67fc197dd566de214fde3e3eceddf8fffba1fefd674073bea8db273ac"
    "90d6b059d10a97ead1dff7e32f2b0c945d", "" };

  c1_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c1_data, 3152U, &c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static real_T c1_norm(SFc1_NLGCToolboxInstanceStruct *chartInstance, real_T
                      c1_x[3])
{
  real_T c1_y;
  real_T c1_scale;
  int32_T c1_k;
  real_T c1_absxk;
  real_T c1_t;
  (void)chartInstance;
  c1_y = 0.0;
  c1_scale = 3.3121686421112381E-170;
  for (c1_k = 0; c1_k < 3; c1_k++) {
    c1_absxk = muDoubleScalarAbs(c1_x[c1_k]);
    if (c1_absxk > c1_scale) {
      c1_t = c1_scale / c1_absxk;
      c1_y = 1.0 + c1_y * c1_t * c1_t;
      c1_scale = c1_absxk;
    } else {
      c1_t = c1_absxk / c1_scale;
      c1_y += c1_t * c1_t;
    }
  }

  return c1_scale * muDoubleScalarSqrt(c1_y);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_h_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i88;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i88, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i88;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_i_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_NLGCToolbox, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_NLGCToolbox), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_NLGCToolbox);
  return c1_y;
}

static uint8_T c1_j_emlrt_marshallIn(SFc1_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_NLGCToolboxInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_NLGCToolboxInstanceStruct
  *chartInstance)
{
  chartInstance->c1_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c1_R = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_thrust_magnitude = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_ex = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_ev = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_a = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_psi = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_desired_attitude = (real_T (*)[9])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 2);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_NLGCToolbox_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1180349770U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1851483343U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1212103372U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3401561775U);
}

mxArray* sf_c1_NLGCToolbox_get_post_codegen_info(void);
mxArray *sf_c1_NLGCToolbox_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("2znqgORC67Gb01isqDNyuD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_NLGCToolbox_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_NLGCToolbox_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_NLGCToolbox_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_NLGCToolbox_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_NLGCToolbox_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c1_NLGCToolbox(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[12],T\"desired_attitude\",},{M[1],M[5],T\"thrust_magnitude\",},{M[8],M[0],T\"is_active_c1_NLGCToolbox\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_NLGCToolbox_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_NLGCToolboxInstanceStruct *chartInstance =
      (SFc1_NLGCToolboxInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _NLGCToolboxMachineNumber_,
           1,
           1,
           1,
           0,
           10,
           0,
           0,
           0,
           0,
           2,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_NLGCToolboxMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_NLGCToolboxMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _NLGCToolboxMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"R");
          _SFD_SET_DATA_PROPS(1,1,1,0,"ex");
          _SFD_SET_DATA_PROPS(2,1,1,0,"ev");
          _SFD_SET_DATA_PROPS(3,1,1,0,"a");
          _SFD_SET_DATA_PROPS(4,1,1,0,"psi");
          _SFD_SET_DATA_PROPS(5,2,0,1,"thrust_magnitude");
          _SFD_SET_DATA_PROPS(6,2,0,1,"desired_attitude");
          _SFD_SET_DATA_PROPS(7,10,0,0,"kv");
          _SFD_SET_DATA_PROPS(8,10,0,0,"kx");
          _SFD_SET_DATA_PROPS(9,10,0,0,"quadModel");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,2,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,748);
        _SFD_CV_INIT_EML_FCN(0,1,"findDirection",795,-1,1093);
        _SFD_CV_INIT_EML_IF(0,1,0,109,125,-1,182);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,113,124,-1,4);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"tangle2dcm",0,-1,429);
        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"hat",0,-1,77);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _NLGCToolboxMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_NLGCToolboxInstanceStruct *chartInstance =
      (SFc1_NLGCToolboxInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c1_R);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c1_thrust_magnitude);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c1_ex);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c1_ev);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c1_a);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c1_psi);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c1_desired_attitude);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)&chartInstance->c1_kx);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)&chartInstance->c1_kv);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)&chartInstance->c1_quadModel);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "ssl7tSDOcwOWGN30YoKfJdG";
}

static void sf_opaque_initialize_c1_NLGCToolbox(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_NLGCToolboxInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*)
    chartInstanceVar);
  initialize_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_NLGCToolbox(void *chartInstanceVar)
{
  enable_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_NLGCToolbox(void *chartInstanceVar)
{
  disable_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_NLGCToolbox(void *chartInstanceVar)
{
  sf_gateway_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_NLGCToolbox(SimStruct* S)
{
  return get_sim_state_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_NLGCToolbox(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c1_NLGCToolbox(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_NLGCToolboxInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_NLGCToolbox_optimization_info();
    }

    finalize_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_NLGCToolbox(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_NLGCToolbox((SFc1_NLGCToolboxInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c1_NLGCToolbox(SimStruct *S)
{
  /* Actual parameters from chart:
     kv kx quadModel
   */
  const char_T *rtParamNames[] = { "kv", "kx", "quadModel" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for kv*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for kx*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2],
    sf_get_param_data_type_id(S,2));

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_NLGCToolbox_optimization_info(sim_mode_is_rtw_gen
      (S), sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 1);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2390134394U));
  ssSetChecksum1(S,(4170627119U));
  ssSetChecksum2(S,(4158052513U));
  ssSetChecksum3(S,(4170841609U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_NLGCToolbox(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_NLGCToolbox(SimStruct *S)
{
  SFc1_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGCToolboxInstanceStruct *)utMalloc(sizeof
    (SFc1_NLGCToolboxInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_NLGCToolboxInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_NLGCToolbox;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_NLGCToolbox;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_NLGCToolbox;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_NLGCToolbox;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_NLGCToolbox;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_NLGCToolbox;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_NLGCToolbox;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_NLGCToolbox;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_NLGCToolbox;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_NLGCToolbox;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_NLGCToolbox;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c1_NLGCToolbox(chartInstance);
}

void c1_NLGCToolbox_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_NLGCToolbox(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_NLGCToolbox(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_NLGCToolbox(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_NLGCToolbox_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
