/* Include files */

#include "NLGC_2_sfun.h"
#include "c1_NLGC_2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "NLGC_2_sfun_debug_macros.h"
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
static const char * c1_debug_family_names[19] = { "e3", "desired_thrust",
  "z_direction", "x_direction", "y_direction", "nargin", "nargout", "R", "ex",
  "ev", "a", "psi", "kx", "kv", "quadModel", "dbg_simtime", "thrust_magnitude",
  "desired_attitude", "dbg_desiredthrust" };

static const char * c1_b_debug_family_names[4] = { "nargin", "nargout", "a", "A"
};

static const char * c1_c_debug_family_names[4] = { "nargin", "nargout", "a", "A"
};

static const char * c1_d_debug_family_names[4] = { "nargin", "nargout", "a", "A"
};

static const char * c1_e_debug_family_names[8] = { "r", "nargin", "nargout",
  "x1", "x2", "x3", "seq", "dcm" };

static const char * c1_f_debug_family_names[4] = { "nargin", "nargout", "x", "y"
};

static const char * c1_g_debug_family_names[9] = { "Rpsi", "ddv", "pdv",
  "nargin", "nargout", "psi", "thrust_direction", "initial_pitch", "y" };

/* Function Declarations */
static void initialize_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void initialize_params_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void enable_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void disable_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_NLGC_2(SFc1_NLGC_2InstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_NLGC_2(SFc1_NLGC_2InstanceStruct
  *chartInstance);
static void set_sim_state_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_st);
static void finalize_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void sf_gateway_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void mdl_start_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void c1_chartstep_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void initSimStructsc1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance, const
  mxArray *c1_b_dbg_desiredthrust, const char_T *c1_identifier, real_T c1_y[3]);
static void c1_b_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_b_desired_attitude, const char_T *c1_identifier, real_T
  c1_y[9]);
static void c1_d_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_e_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_b_thrust_magnitude, const char_T *c1_identifier);
static real_T c1_f_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_g_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  c1_struct_fGw06pKU762DM8t1dqR94E *c1_y);
static void c1_h_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[12]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_i_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3]);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static real_T c1_norm(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_x[3]);
static real_T c1_cosd(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_x);
static real_T c1_sind(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_x);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_j_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_k_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_NLGC_2, const char_T *c1_identifier);
static uint8_T c1_l_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_cosd(SFc1_NLGC_2InstanceStruct *chartInstance, real_T *c1_x);
static void c1_b_sind(SFc1_NLGC_2InstanceStruct *chartInstance, real_T *c1_x);
static int32_T c1__s32_d_(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_b,
  uint32_T c1_ssid_src_loc, int32_T c1_offset_src_loc, int32_T c1_length_src_loc);
static void init_dsm_address_info(SFc1_NLGC_2InstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_NLGC_2InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_NLGC_2(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_is_active_c1_NLGC_2 = 0U;
}

static void initialize_params_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
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

static void enable_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_NLGC_2(SFc1_NLGC_2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_NLGC_2(SFc1_NLGC_2InstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  const mxArray *c1_b_y = NULL;
  const mxArray *c1_c_y = NULL;
  real_T c1_hoistedGlobal;
  const mxArray *c1_d_y = NULL;
  uint8_T c1_b_hoistedGlobal;
  const mxArray *c1_e_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(4, 1), false);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", *chartInstance->c1_dbg_desiredthrust,
    0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", *chartInstance->c1_desired_attitude,
    0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_hoistedGlobal = *chartInstance->c1_thrust_magnitude;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_b_hoistedGlobal = chartInstance->c1_is_active_c1_NLGC_2;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[3];
  int32_T c1_i0;
  real_T c1_dv1[9];
  int32_T c1_i1;
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                      "dbg_desiredthrust", c1_dv0);
  for (c1_i0 = 0; c1_i0 < 3; c1_i0++) {
    (*chartInstance->c1_dbg_desiredthrust)[c1_i0] = c1_dv0[c1_i0];
  }

  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
                        "desired_attitude", c1_dv1);
  for (c1_i1 = 0; c1_i1 < 9; c1_i1++) {
    (*chartInstance->c1_desired_attitude)[c1_i1] = c1_dv1[c1_i1];
  }

  *chartInstance->c1_thrust_magnitude = c1_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 2)), "thrust_magnitude");
  chartInstance->c1_is_active_c1_NLGC_2 = c1_k_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 3)), "is_active_c1_NLGC_2");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_NLGC_2(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  int32_T c1_i6;
  int32_T c1_i7;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_dbg_simtime, 5U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_psi, 4U);
  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_a)[c1_i2], 3U);
  }

  for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_ev)[c1_i3], 2U);
  }

  for (c1_i4 = 0; c1_i4 < 3; c1_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_ex)[c1_i4], 1U);
  }

  for (c1_i5 = 0; c1_i5 < 9; c1_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_R)[c1_i5], 0U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_NLGC_2(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_NLGC_2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_thrust_magnitude, 6U);
  for (c1_i6 = 0; c1_i6 < 9; c1_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_desired_attitude)[c1_i6], 7U);
  }

  for (c1_i7 = 0; c1_i7 < 3; c1_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_dbg_desiredthrust)[c1_i7], 8U);
  }
}

static void mdl_start_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void c1_chartstep_c1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  int32_T c1_i8;
  int32_T c1_i9;
  real_T c1_b_R[9];
  int32_T c1_i10;
  real_T c1_b_ex[3];
  int32_T c1_i11;
  real_T c1_b_ev[3];
  real_T c1_b_psi;
  real_T c1_b_a[3];
  real_T c1_b_kx;
  real_T c1_b_kv;
  c1_struct_fGw06pKU762DM8t1dqR94E c1_b_quadModel;
  real_T c1_b_dbg_simtime;
  uint32_T c1_debug_family_var_map[19];
  real_T c1_e3[3];
  real_T c1_desired_thrust[3];
  real_T c1_z_direction[3];
  real_T c1_x_direction[3];
  real_T c1_y_direction[3];
  real_T c1_nargin = 9.0;
  real_T c1_nargout = 3.0;
  real_T c1_b_thrust_magnitude;
  real_T c1_b_desired_attitude[9];
  real_T c1_b_dbg_desiredthrust[3];
  int32_T c1_i12;
  static real_T c1_b[3] = { 0.0, 0.0, 1.0 };

  real_T c1_c_a;
  int32_T c1_i13;
  real_T c1_d_a;
  real_T c1_b_b[3];
  int32_T c1_i14;
  real_T c1_e_a;
  real_T c1_c_b[3];
  real_T c1_f_a;
  int32_T c1_i15;
  int32_T c1_i16;
  real_T c1_d_b[3];
  int32_T c1_i17;
  int32_T c1_i18;
  int32_T c1_i19;
  real_T c1_B;
  real_T c1_b_desired_thrust[3];
  int32_T c1_i20;
  real_T c1_c_psi;
  int32_T c1_i21;
  real_T c1_initial_pitch;
  real_T c1_thrust_direction[3];
  uint32_T c1_b_debug_family_var_map[9];
  real_T c1_Rpsi[9];
  real_T c1_ddv[3];
  real_T c1_pdv[3];
  real_T c1_b_nargin = 3.0;
  real_T c1_b_nargout = 1.0;
  real_T c1_x1;
  real_T c1_x2;
  real_T c1_x3;
  real_T c1_seq;
  uint32_T c1_c_debug_family_var_map[8];
  real_T c1_r[3];
  real_T c1_c_nargin = 4.0;
  real_T c1_c_nargout = 1.0;
  real_T c1_g_a;
  real_T c1_h_a;
  real_T c1_i_a;
  real_T c1_j_a;
  uint32_T c1_d_debug_family_var_map[4];
  real_T c1_d_nargin = 1.0;
  real_T c1_e_nargin = 1.0;
  real_T c1_f_nargin = 1.0;
  real_T c1_g_nargin = 1.0;
  real_T c1_d_nargout = 1.0;
  real_T c1_e_nargout = 1.0;
  real_T c1_f_nargout = 1.0;
  real_T c1_g_nargout = 1.0;
  real_T c1_A[9];
  real_T c1_b_A[9];
  real_T c1_c_A[9];
  real_T c1_d_A[9];
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
  int32_T c1_i22;
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_i25;
  int32_T c1_i26;
  int32_T c1_i27;
  static real_T c1_dv2[3] = { 1.0, 0.0, 0.0 };

  int32_T c1_i28;
  int32_T c1_i29;
  static real_T c1_k_a[3] = { 0.0, 0.0, 1.0 };

  real_T c1_l_a;
  real_T c1_m_a;
  real_T c1_n_a;
  real_T c1_o_a;
  real_T c1_h_nargin = 1.0;
  real_T c1_i_nargin = 1.0;
  real_T c1_j_nargin = 1.0;
  real_T c1_k_nargin = 1.0;
  real_T c1_h_nargout = 1.0;
  real_T c1_i_nargout = 1.0;
  real_T c1_j_nargout = 1.0;
  real_T c1_k_nargout = 1.0;
  real_T c1_e_A[9];
  real_T c1_f_A[9];
  real_T c1_g_A[9];
  real_T c1_h_A[9];
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
  real_T c1_d31;
  real_T c1_d32;
  real_T c1_d33;
  int32_T c1_i30;
  int32_T c1_i31;
  int32_T c1_i32;
  int32_T c1_i33;
  int32_T c1_i34;
  int32_T c1_i35;
  int32_T c1_i36;
  int32_T c1_i37;
  static real_T c1_dv3[3] = { 0.0, 1.0, 0.0 };

  int32_T c1_i38;
  int32_T c1_i39;
  int32_T c1_i40;
  int32_T c1_i41;
  int32_T c1_i42;
  real_T c1_p_a[9];
  int32_T c1_i43;
  int32_T c1_i44;
  int32_T c1_i45;
  real_T c1_q_a;
  real_T c1_e_b[9];
  real_T c1_r_a;
  real_T c1_s_a;
  real_T c1_t_a;
  real_T c1_l_nargin = 1.0;
  real_T c1_m_nargin = 1.0;
  real_T c1_n_nargin = 1.0;
  real_T c1_o_nargin = 1.0;
  real_T c1_l_nargout = 1.0;
  real_T c1_m_nargout = 1.0;
  real_T c1_n_nargout = 1.0;
  real_T c1_o_nargout = 1.0;
  real_T c1_i_A[9];
  real_T c1_j_A[9];
  real_T c1_k_A[9];
  real_T c1_l_A[9];
  real_T c1_d34;
  real_T c1_d35;
  real_T c1_d36;
  real_T c1_d37;
  real_T c1_d38;
  real_T c1_d39;
  real_T c1_d40;
  real_T c1_d41;
  real_T c1_d42;
  real_T c1_d43;
  real_T c1_d44;
  real_T c1_d45;
  real_T c1_d46;
  real_T c1_d47;
  real_T c1_d48;
  real_T c1_d49;
  int32_T c1_i46;
  int32_T c1_i47;
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
  real_T c1_f_b[9];
  int32_T c1_i59;
  int32_T c1_i60;
  int32_T c1_i61;
  int32_T c1_i62;
  int32_T c1_i63;
  int32_T c1_i64;
  int32_T c1_i65;
  int32_T c1_i66;
  int32_T c1_i67;
  int32_T c1_i68;
  int32_T c1_i69;
  int32_T c1_i70;
  int32_T c1_i71;
  int32_T c1_i72;
  int32_T c1_i73;
  int32_T c1_i74;
  int32_T c1_i75;
  int32_T c1_i76;
  int32_T c1_i77;
  int32_T c1_i78;
  int32_T c1_i79;
  int32_T c1_i80;
  int32_T c1_i81;
  int32_T c1_i82;
  real_T c1_u_a[9];
  int32_T c1_i83;
  real_T c1_v_a[9];
  int32_T c1_i84;
  real_T c1_w_a[9];
  int32_T c1_i85;
  real_T c1_x_a[9];
  int32_T c1_i86;
  int32_T c1_i87;
  int32_T c1_i88;
  int32_T c1_i89;
  int32_T c1_i90;
  int32_T c1_i91;
  int32_T c1_i92;
  int32_T c1_i93;
  int32_T c1_i94;
  int32_T c1_i95;
  int32_T c1_i96;
  int32_T c1_i97;
  int32_T c1_i98;
  int32_T c1_i99;
  int32_T c1_i100;
  int32_T c1_i101;
  int32_T c1_i102;
  int32_T c1_i103;
  int32_T c1_i104;
  int32_T c1_i105;
  int32_T c1_i106;
  int32_T c1_i107;
  real_T c1_x[3];
  real_T c1_p_nargin = 1.0;
  static real_T c1_g_b[3] = { 1.0, 0.0, 0.0 };

  real_T c1_p_nargout = 1.0;
  real_T c1_y[9];
  int32_T c1_i108;
  real_T c1_b_x[3];
  real_T c1_q_nargin = 1.0;
  real_T c1_q_nargout = 1.0;
  real_T c1_b_y[9];
  int32_T c1_i109;
  int32_T c1_i110;
  int32_T c1_i111;
  int32_T c1_i112;
  int32_T c1_i113;
  real_T c1_y_a[3];
  int32_T c1_i114;
  int32_T c1_i115;
  real_T c1_d50;
  int32_T c1_i116;
  int32_T c1_i117;
  int32_T c1_i118;
  int32_T c1_i119;
  real_T c1_b_B;
  real_T c1_b_pdv[3];
  int32_T c1_i120;
  int32_T c1_i121;
  real_T c1_c_x[3];
  real_T c1_r_nargin = 1.0;
  real_T c1_r_nargout = 1.0;
  real_T c1_c_y[9];
  int32_T c1_i122;
  int32_T c1_i123;
  int32_T c1_i124;
  int32_T c1_i125;
  int32_T c1_i126;
  int32_T c1_i127;
  int32_T c1_i128;
  int32_T c1_i129;
  int32_T c1_i130;
  int32_T c1_i131;
  int32_T c1_i132;
  int32_T c1_i133;
  int32_T c1_i134;
  int32_T c1_i135;
  int32_T c1_i136;
  int32_T c1_i137;
  int32_T c1_i138;
  real_T c1_ab_a[3];
  int32_T c1_i139;
  int32_T c1_i140;
  int32_T c1_i141;
  real_T c1_bb_a[3];
  int32_T c1_i142;
  real_T c1_d_y;
  int32_T c1_k;
  int32_T c1_i143;
  real_T c1_c_desired_thrust[3];
  int32_T c1_i144;
  int32_T c1_i145;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i8 = 0; c1_i8 < 9; c1_i8++) {
    c1_b_R[c1_i8] = (*chartInstance->c1_R)[c1_i8];
  }

  for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
    c1_b_ex[c1_i9] = (*chartInstance->c1_ex)[c1_i9];
  }

  for (c1_i10 = 0; c1_i10 < 3; c1_i10++) {
    c1_b_ev[c1_i10] = (*chartInstance->c1_ev)[c1_i10];
  }

  for (c1_i11 = 0; c1_i11 < 3; c1_i11++) {
    c1_b_a[c1_i11] = (*chartInstance->c1_a)[c1_i11];
  }

  c1_b_psi = *chartInstance->c1_psi;
  c1_b_kx = chartInstance->c1_kx;
  c1_b_kv = chartInstance->c1_kv;
  c1_b_quadModel = chartInstance->c1_quadModel;
  c1_b_dbg_simtime = *chartInstance->c1_dbg_simtime;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 19U, 19U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_e3, 0U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_desired_thrust, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_z_direction, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_x_direction, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_y_direction, 4U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_R, 7U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_ex, 8U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_ev, 9U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_a, 10U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_psi, 11U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_kx, 12U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_kv, 13U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_quadModel, 14U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_dbg_simtime, 15U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_thrust_magnitude, 16U,
    c1_c_sf_marshallOut, c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_desired_attitude, 17U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_dbg_desiredthrust, 18U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  for (c1_i12 = 0; c1_i12 < 3; c1_i12++) {
    c1_e3[c1_i12] = c1_b[c1_i12];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_c_a = -c1_b_kx;
  for (c1_i13 = 0; c1_i13 < 3; c1_i13++) {
    c1_b_b[c1_i13] = c1_b_ex[c1_i13];
  }

  c1_d_a = c1_b_kv;
  for (c1_i14 = 0; c1_i14 < 3; c1_i14++) {
    c1_c_b[c1_i14] = c1_b_ev[c1_i14];
  }

  c1_e_a = c1_b_quadModel.mass * c1_b_quadModel.g;
  c1_f_a = c1_b_quadModel.mass;
  for (c1_i15 = 0; c1_i15 < 3; c1_i15++) {
    c1_d_b[c1_i15] = c1_b_a[c1_i15];
  }

  for (c1_i16 = 0; c1_i16 < 3; c1_i16++) {
    c1_desired_thrust[c1_i16] = ((c1_c_a * c1_b_b[c1_i16] - c1_d_a *
      c1_c_b[c1_i16]) - c1_e_a * c1_b[c1_i16]) + c1_f_a * c1_d_b[c1_i16];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  for (c1_i17 = 0; c1_i17 < 3; c1_i17++) {
    c1_b_dbg_desiredthrust[c1_i17] = c1_desired_thrust[c1_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  for (c1_i18 = 0; c1_i18 < 3; c1_i18++) {
    c1_b_b[c1_i18] = -c1_desired_thrust[c1_i18];
  }

  for (c1_i19 = 0; c1_i19 < 3; c1_i19++) {
    c1_b_desired_thrust[c1_i19] = c1_desired_thrust[c1_i19];
  }

  c1_B = c1_norm(chartInstance, c1_b_desired_thrust);
  for (c1_i20 = 0; c1_i20 < 3; c1_i20++) {
    c1_z_direction[c1_i20] = c1_b_b[c1_i20] / c1_B;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_c_psi = c1_b_psi;
  for (c1_i21 = 0; c1_i21 < 3; c1_i21++) {
    c1_thrust_direction[c1_i21] = c1_z_direction[c1_i21];
  }

  c1_initial_pitch = 0.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c1_g_debug_family_names,
    c1_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Rpsi, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_ddv, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_pdv, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargin, 3U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargout, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_psi, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_thrust_direction, 6U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_initial_pitch, 7U,
    c1_c_sf_marshallOut, c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_x_direction, 8U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
  c1_x1 = 0.0;
  c1_x2 = c1_initial_pitch;
  c1_x3 = c1_c_psi;
  c1_seq = 123.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c1_e_debug_family_names,
    c1_c_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_r, 0U, c1_f_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargin, 1U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargout, 2U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_x1, 3U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_x2, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_x3, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_seq, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Rpsi, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_r[0] = c1_x1;
  c1_r[1] = c1_x2;
  c1_r[2] = c1_x3;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 12);
  switch (c1__s32_d_(chartInstance, sf_integer_check(chartInstance->S, 1U, 801U,
            34U, c1_seq), 1U, 801U, 34U)) {
   case 321:
    CV_SCRIPT_SWITCH(0, 0, 1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 14);
    c1_h_a = c1_r[2];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_b_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_h_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 24);
    c1_d3 = c1_h_a;
    c1_b_cosd(chartInstance, &c1_d3);
    c1_d7 = c1_h_a;
    c1_b_sind(chartInstance, &c1_d7);
    c1_d11 = c1_h_a;
    c1_b_sind(chartInstance, &c1_d11);
    c1_d15 = c1_h_a;
    c1_b_cosd(chartInstance, &c1_d15);
    c1_i23 = 0;
    for (c1_i26 = 0; c1_i26 < 3; c1_i26++) {
      c1_b_A[c1_i23] = c1_dv2[c1_i26];
      c1_i23 += 3;
    }

    c1_b_A[1] = 0.0;
    c1_b_A[4] = c1_d3;
    c1_b_A[7] = c1_d7;
    c1_b_A[2] = 0.0;
    c1_b_A[5] = -c1_d11;
    c1_b_A[8] = c1_d15;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -24);
    _SFD_SYMBOL_SCOPE_POP();
    c1_m_a = c1_r[1];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_c_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_i_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_i_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_m_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_f_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 2);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 27);
    c1_d19 = c1_m_a;
    c1_b_cosd(chartInstance, &c1_d19);
    c1_d23 = c1_m_a;
    c1_b_sind(chartInstance, &c1_d23);
    c1_d27 = c1_m_a;
    c1_b_sind(chartInstance, &c1_d27);
    c1_d31 = c1_m_a;
    c1_b_cosd(chartInstance, &c1_d31);
    c1_f_A[0] = c1_d19;
    c1_f_A[3] = 0.0;
    c1_f_A[6] = -c1_d23;
    c1_i33 = 0;
    for (c1_i36 = 0; c1_i36 < 3; c1_i36++) {
      c1_f_A[c1_i33 + 1] = c1_dv3[c1_i36];
      c1_i33 += 3;
    }

    c1_f_A[2] = c1_d27;
    c1_f_A[5] = 0.0;
    c1_f_A[8] = c1_d31;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -27);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i39 = 0; c1_i39 < 9; c1_i39++) {
      c1_p_a[c1_i39] = c1_b_A[c1_i39];
    }

    for (c1_i43 = 0; c1_i43 < 9; c1_i43++) {
      c1_e_b[c1_i43] = c1_f_A[c1_i43];
    }

    c1_r_a = c1_r[0];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_d_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_m_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_m_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_r_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_j_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 3);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
    c1_d35 = c1_r_a;
    c1_b_cosd(chartInstance, &c1_d35);
    c1_d39 = c1_r_a;
    c1_b_sind(chartInstance, &c1_d39);
    c1_d43 = c1_r_a;
    c1_b_sind(chartInstance, &c1_d43);
    c1_d47 = c1_r_a;
    c1_b_cosd(chartInstance, &c1_d47);
    c1_j_A[0] = c1_d35;
    c1_j_A[3] = c1_d39;
    c1_j_A[6] = 0.0;
    c1_j_A[1] = -c1_d43;
    c1_j_A[4] = c1_d47;
    c1_j_A[7] = 0.0;
    c1_i47 = 0;
    for (c1_i51 = 0; c1_i51 < 3; c1_i51++) {
      c1_j_A[c1_i47 + 2] = c1_k_a[c1_i51];
      c1_i47 += 3;
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -30);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i55 = 0; c1_i55 < 9; c1_i55++) {
      c1_f_b[c1_i55] = c1_j_A[c1_i55];
    }

    for (c1_i59 = 0; c1_i59 < 9; c1_i59++) {
      c1_Rpsi[c1_i59] = 0.0;
    }

    for (c1_i63 = 0; c1_i63 < 3; c1_i63++) {
      c1_i69 = 0;
      for (c1_i75 = 0; c1_i75 < 3; c1_i75++) {
        c1_v_a[c1_i69 + c1_i63] = 0.0;
        c1_i87 = 0;
        for (c1_i91 = 0; c1_i91 < 3; c1_i91++) {
          c1_v_a[c1_i69 + c1_i63] += c1_p_a[c1_i87 + c1_i63] * c1_e_b[c1_i91 +
            c1_i69];
          c1_i87 += 3;
        }

        c1_i69 += 3;
      }
    }

    for (c1_i68 = 0; c1_i68 < 3; c1_i68++) {
      c1_i79 = 0;
      for (c1_i83 = 0; c1_i83 < 3; c1_i83++) {
        c1_Rpsi[c1_i79 + c1_i68] = 0.0;
        c1_i96 = 0;
        for (c1_i100 = 0; c1_i100 < 3; c1_i100++) {
          c1_Rpsi[c1_i79 + c1_i68] += c1_v_a[c1_i96 + c1_i68] * c1_f_b[c1_i100 +
            c1_i79];
          c1_i96 += 3;
        }

        c1_i79 += 3;
      }
    }
    break;

   case 313:
    CV_SCRIPT_SWITCH(0, 0, 2);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 16);
    c1_i_a = c1_r[2];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_d_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_f_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_f_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_i_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_c_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 3);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
    c1_d4 = c1_i_a;
    c1_b_cosd(chartInstance, &c1_d4);
    c1_d8 = c1_i_a;
    c1_b_sind(chartInstance, &c1_d8);
    c1_d12 = c1_i_a;
    c1_b_sind(chartInstance, &c1_d12);
    c1_d16 = c1_i_a;
    c1_b_cosd(chartInstance, &c1_d16);
    c1_c_A[0] = c1_d4;
    c1_c_A[3] = c1_d8;
    c1_c_A[6] = 0.0;
    c1_c_A[1] = -c1_d12;
    c1_c_A[4] = c1_d16;
    c1_c_A[7] = 0.0;
    c1_i28 = 0;
    for (c1_i29 = 0; c1_i29 < 3; c1_i29++) {
      c1_c_A[c1_i28 + 2] = c1_k_a[c1_i29];
      c1_i28 += 3;
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -30);
    _SFD_SYMBOL_SCOPE_POP();
    c1_n_a = c1_r[1];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_b_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_j_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_j_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_n_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_g_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 24);
    c1_d20 = c1_n_a;
    c1_b_cosd(chartInstance, &c1_d20);
    c1_d24 = c1_n_a;
    c1_b_sind(chartInstance, &c1_d24);
    c1_d28 = c1_n_a;
    c1_b_sind(chartInstance, &c1_d28);
    c1_d32 = c1_n_a;
    c1_b_cosd(chartInstance, &c1_d32);
    c1_i30 = 0;
    for (c1_i31 = 0; c1_i31 < 3; c1_i31++) {
      c1_g_A[c1_i30] = c1_dv2[c1_i31];
      c1_i30 += 3;
    }

    c1_g_A[1] = 0.0;
    c1_g_A[4] = c1_d20;
    c1_g_A[7] = c1_d24;
    c1_g_A[2] = 0.0;
    c1_g_A[5] = -c1_d28;
    c1_g_A[8] = c1_d32;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -24);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i40 = 0; c1_i40 < 9; c1_i40++) {
      c1_p_a[c1_i40] = c1_c_A[c1_i40];
    }

    for (c1_i44 = 0; c1_i44 < 9; c1_i44++) {
      c1_e_b[c1_i44] = c1_g_A[c1_i44];
    }

    c1_s_a = c1_r[0];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_d_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_n_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_n_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_s_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_k_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 3);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
    c1_d36 = c1_s_a;
    c1_b_cosd(chartInstance, &c1_d36);
    c1_d40 = c1_s_a;
    c1_b_sind(chartInstance, &c1_d40);
    c1_d44 = c1_s_a;
    c1_b_sind(chartInstance, &c1_d44);
    c1_d48 = c1_s_a;
    c1_b_cosd(chartInstance, &c1_d48);
    c1_k_A[0] = c1_d36;
    c1_k_A[3] = c1_d40;
    c1_k_A[6] = 0.0;
    c1_k_A[1] = -c1_d44;
    c1_k_A[4] = c1_d48;
    c1_k_A[7] = 0.0;
    c1_i48 = 0;
    for (c1_i52 = 0; c1_i52 < 3; c1_i52++) {
      c1_k_A[c1_i48 + 2] = c1_k_a[c1_i52];
      c1_i48 += 3;
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -30);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i56 = 0; c1_i56 < 9; c1_i56++) {
      c1_f_b[c1_i56] = c1_k_A[c1_i56];
    }

    for (c1_i60 = 0; c1_i60 < 9; c1_i60++) {
      c1_Rpsi[c1_i60] = 0.0;
    }

    for (c1_i64 = 0; c1_i64 < 3; c1_i64++) {
      c1_i71 = 0;
      for (c1_i76 = 0; c1_i76 < 3; c1_i76++) {
        c1_w_a[c1_i71 + c1_i64] = 0.0;
        c1_i88 = 0;
        for (c1_i92 = 0; c1_i92 < 3; c1_i92++) {
          c1_w_a[c1_i71 + c1_i64] += c1_p_a[c1_i88 + c1_i64] * c1_e_b[c1_i92 +
            c1_i71];
          c1_i88 += 3;
        }

        c1_i71 += 3;
      }
    }

    for (c1_i70 = 0; c1_i70 < 3; c1_i70++) {
      c1_i80 = 0;
      for (c1_i84 = 0; c1_i84 < 3; c1_i84++) {
        c1_Rpsi[c1_i80 + c1_i70] = 0.0;
        c1_i97 = 0;
        for (c1_i101 = 0; c1_i101 < 3; c1_i101++) {
          c1_Rpsi[c1_i80 + c1_i70] += c1_w_a[c1_i97 + c1_i70] * c1_f_b[c1_i101 +
            c1_i80];
          c1_i97 += 3;
        }

        c1_i80 += 3;
      }
    }
    break;

   case 123:
    CV_SCRIPT_SWITCH(0, 0, 3);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 18);
    c1_j_a = c1_r[0];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_b_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_g_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_g_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_j_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_d_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 24);
    c1_d5 = c1_j_a;
    c1_b_cosd(chartInstance, &c1_d5);
    c1_d9 = c1_j_a;
    c1_b_sind(chartInstance, &c1_d9);
    c1_d13 = c1_j_a;
    c1_b_sind(chartInstance, &c1_d13);
    c1_d17 = c1_j_a;
    c1_b_cosd(chartInstance, &c1_d17);
    c1_i24 = 0;
    for (c1_i27 = 0; c1_i27 < 3; c1_i27++) {
      c1_d_A[c1_i24] = c1_dv2[c1_i27];
      c1_i24 += 3;
    }

    c1_d_A[1] = 0.0;
    c1_d_A[4] = c1_d5;
    c1_d_A[7] = c1_d9;
    c1_d_A[2] = 0.0;
    c1_d_A[5] = -c1_d13;
    c1_d_A[8] = c1_d17;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -24);
    _SFD_SYMBOL_SCOPE_POP();
    c1_o_a = c1_r[1];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_c_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_k_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_k_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_o_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_h_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 2);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 27);
    c1_d21 = c1_o_a;
    c1_b_cosd(chartInstance, &c1_d21);
    c1_d25 = c1_o_a;
    c1_b_sind(chartInstance, &c1_d25);
    c1_d29 = c1_o_a;
    c1_b_sind(chartInstance, &c1_d29);
    c1_d33 = c1_o_a;
    c1_b_cosd(chartInstance, &c1_d33);
    c1_h_A[0] = c1_d21;
    c1_h_A[3] = 0.0;
    c1_h_A[6] = -c1_d25;
    c1_i34 = 0;
    for (c1_i37 = 0; c1_i37 < 3; c1_i37++) {
      c1_h_A[c1_i34 + 1] = c1_dv3[c1_i37];
      c1_i34 += 3;
    }

    c1_h_A[2] = c1_d29;
    c1_h_A[5] = 0.0;
    c1_h_A[8] = c1_d33;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -27);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i41 = 0; c1_i41 < 9; c1_i41++) {
      c1_p_a[c1_i41] = c1_d_A[c1_i41];
    }

    for (c1_i45 = 0; c1_i45 < 9; c1_i45++) {
      c1_e_b[c1_i45] = c1_h_A[c1_i45];
    }

    c1_t_a = c1_r[2];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_d_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_o_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_o_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_t_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_l_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 3);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
    c1_d37 = c1_t_a;
    c1_b_cosd(chartInstance, &c1_d37);
    c1_d41 = c1_t_a;
    c1_b_sind(chartInstance, &c1_d41);
    c1_d45 = c1_t_a;
    c1_b_sind(chartInstance, &c1_d45);
    c1_d49 = c1_t_a;
    c1_b_cosd(chartInstance, &c1_d49);
    c1_l_A[0] = c1_d37;
    c1_l_A[3] = c1_d41;
    c1_l_A[6] = 0.0;
    c1_l_A[1] = -c1_d45;
    c1_l_A[4] = c1_d49;
    c1_l_A[7] = 0.0;
    c1_i49 = 0;
    for (c1_i53 = 0; c1_i53 < 3; c1_i53++) {
      c1_l_A[c1_i49 + 2] = c1_k_a[c1_i53];
      c1_i49 += 3;
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -30);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i57 = 0; c1_i57 < 9; c1_i57++) {
      c1_f_b[c1_i57] = c1_l_A[c1_i57];
    }

    for (c1_i61 = 0; c1_i61 < 9; c1_i61++) {
      c1_Rpsi[c1_i61] = 0.0;
    }

    for (c1_i65 = 0; c1_i65 < 3; c1_i65++) {
      c1_i73 = 0;
      for (c1_i77 = 0; c1_i77 < 3; c1_i77++) {
        c1_x_a[c1_i73 + c1_i65] = 0.0;
        c1_i89 = 0;
        for (c1_i93 = 0; c1_i93 < 3; c1_i93++) {
          c1_x_a[c1_i73 + c1_i65] += c1_p_a[c1_i89 + c1_i65] * c1_e_b[c1_i93 +
            c1_i73];
          c1_i89 += 3;
        }

        c1_i73 += 3;
      }
    }

    for (c1_i72 = 0; c1_i72 < 3; c1_i72++) {
      c1_i81 = 0;
      for (c1_i85 = 0; c1_i85 < 3; c1_i85++) {
        c1_Rpsi[c1_i81 + c1_i72] = 0.0;
        c1_i98 = 0;
        for (c1_i102 = 0; c1_i102 < 3; c1_i102++) {
          c1_Rpsi[c1_i81 + c1_i72] += c1_x_a[c1_i98 + c1_i72] * c1_f_b[c1_i102 +
            c1_i81];
          c1_i98 += 3;
        }

        c1_i81 += 3;
      }
    }
    break;

   default:
    CV_SCRIPT_SWITCH(0, 0, 0);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 20);
    c1_g_a = c1_r[0];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_b_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_g_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 24);
    c1_d2 = c1_g_a;
    c1_b_cosd(chartInstance, &c1_d2);
    c1_d6 = c1_g_a;
    c1_b_sind(chartInstance, &c1_d6);
    c1_d10 = c1_g_a;
    c1_b_sind(chartInstance, &c1_d10);
    c1_d14 = c1_g_a;
    c1_b_cosd(chartInstance, &c1_d14);
    c1_i22 = 0;
    for (c1_i25 = 0; c1_i25 < 3; c1_i25++) {
      c1_A[c1_i22] = c1_dv2[c1_i25];
      c1_i22 += 3;
    }

    c1_A[1] = 0.0;
    c1_A[4] = c1_d2;
    c1_A[7] = c1_d6;
    c1_A[2] = 0.0;
    c1_A[5] = -c1_d10;
    c1_A[8] = c1_d14;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -24);
    _SFD_SYMBOL_SCOPE_POP();
    c1_l_a = c1_r[1];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_c_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_h_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_h_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_l_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_e_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 2);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 27);
    c1_d18 = c1_l_a;
    c1_b_cosd(chartInstance, &c1_d18);
    c1_d22 = c1_l_a;
    c1_b_sind(chartInstance, &c1_d22);
    c1_d26 = c1_l_a;
    c1_b_sind(chartInstance, &c1_d26);
    c1_d30 = c1_l_a;
    c1_b_cosd(chartInstance, &c1_d30);
    c1_e_A[0] = c1_d18;
    c1_e_A[3] = 0.0;
    c1_e_A[6] = -c1_d22;
    c1_i32 = 0;
    for (c1_i35 = 0; c1_i35 < 3; c1_i35++) {
      c1_e_A[c1_i32 + 1] = c1_dv3[c1_i35];
      c1_i32 += 3;
    }

    c1_e_A[2] = c1_d26;
    c1_e_A[5] = 0.0;
    c1_e_A[8] = c1_d30;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -27);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i38 = 0; c1_i38 < 9; c1_i38++) {
      c1_p_a[c1_i38] = c1_A[c1_i38];
    }

    for (c1_i42 = 0; c1_i42 < 9; c1_i42++) {
      c1_e_b[c1_i42] = c1_e_A[c1_i42];
    }

    c1_q_a = c1_r[2];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_d_debug_family_names,
      c1_d_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_l_nargin, 0U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_l_nargout, 1U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_q_a, 2U, c1_c_sf_marshallOut,
      c1_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_i_A, 3U, c1_b_sf_marshallOut,
      c1_b_sf_marshallIn);
    CV_SCRIPT_FCN(0, 3);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
    c1_d34 = c1_q_a;
    c1_b_cosd(chartInstance, &c1_d34);
    c1_d38 = c1_q_a;
    c1_b_sind(chartInstance, &c1_d38);
    c1_d42 = c1_q_a;
    c1_b_sind(chartInstance, &c1_d42);
    c1_d46 = c1_q_a;
    c1_b_cosd(chartInstance, &c1_d46);
    c1_i_A[0] = c1_d34;
    c1_i_A[3] = c1_d38;
    c1_i_A[6] = 0.0;
    c1_i_A[1] = -c1_d42;
    c1_i_A[4] = c1_d46;
    c1_i_A[7] = 0.0;
    c1_i46 = 0;
    for (c1_i50 = 0; c1_i50 < 3; c1_i50++) {
      c1_i_A[c1_i46 + 2] = c1_k_a[c1_i50];
      c1_i46 += 3;
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -30);
    _SFD_SYMBOL_SCOPE_POP();
    for (c1_i54 = 0; c1_i54 < 9; c1_i54++) {
      c1_f_b[c1_i54] = c1_i_A[c1_i54];
    }

    for (c1_i58 = 0; c1_i58 < 9; c1_i58++) {
      c1_Rpsi[c1_i58] = 0.0;
    }

    for (c1_i62 = 0; c1_i62 < 3; c1_i62++) {
      c1_i67 = 0;
      for (c1_i74 = 0; c1_i74 < 3; c1_i74++) {
        c1_u_a[c1_i67 + c1_i62] = 0.0;
        c1_i86 = 0;
        for (c1_i90 = 0; c1_i90 < 3; c1_i90++) {
          c1_u_a[c1_i67 + c1_i62] += c1_p_a[c1_i86 + c1_i62] * c1_e_b[c1_i90 +
            c1_i67];
          c1_i86 += 3;
        }

        c1_i67 += 3;
      }
    }

    for (c1_i66 = 0; c1_i66 < 3; c1_i66++) {
      c1_i78 = 0;
      for (c1_i82 = 0; c1_i82 < 3; c1_i82++) {
        c1_Rpsi[c1_i78 + c1_i66] = 0.0;
        c1_i95 = 0;
        for (c1_i99 = 0; c1_i99 < 3; c1_i99++) {
          c1_Rpsi[c1_i78 + c1_i66] += c1_u_a[c1_i95 + c1_i66] * c1_f_b[c1_i99 +
            c1_i78];
          c1_i95 += 3;
        }

        c1_i78 += 3;
      }
    }
    break;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -20);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  for (c1_i94 = 0; c1_i94 < 9; c1_i94++) {
    c1_p_a[c1_i94] = c1_Rpsi[c1_i94];
  }

  for (c1_i103 = 0; c1_i103 < 3; c1_i103++) {
    c1_ddv[c1_i103] = 0.0;
  }

  for (c1_i104 = 0; c1_i104 < 3; c1_i104++) {
    c1_ddv[c1_i104] = 0.0;
    c1_i106 = 0;
    for (c1_i107 = 0; c1_i107 < 3; c1_i107++) {
      c1_ddv[c1_i104] += c1_p_a[c1_i106 + c1_i104] * c1_g_b[c1_i107];
      c1_i106 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
  for (c1_i105 = 0; c1_i105 < 3; c1_i105++) {
    c1_x[c1_i105] = c1_thrust_direction[c1_i105];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_f_debug_family_names,
    c1_d_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_p_nargin, 0U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_p_nargout, 1U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_x, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_y, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 2);
  c1_y[0] = 0.0;
  c1_y[3] = -c1_x[2];
  c1_y[6] = c1_x[1];
  c1_y[1] = c1_x[2];
  c1_y[4] = 0.0;
  c1_y[7] = -c1_x[0];
  c1_y[2] = -c1_x[1];
  c1_y[5] = c1_x[0];
  c1_y[8] = 0.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i108 = 0; c1_i108 < 3; c1_i108++) {
    c1_b_x[c1_i108] = c1_thrust_direction[c1_i108];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_f_debug_family_names,
    c1_d_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_q_nargin, 0U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_q_nargout, 1U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_x, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_y, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 2);
  c1_b_y[0] = 0.0;
  c1_b_y[3] = -c1_b_x[2];
  c1_b_y[6] = c1_b_x[1];
  c1_b_y[1] = c1_b_x[2];
  c1_b_y[4] = 0.0;
  c1_b_y[7] = -c1_b_x[0];
  c1_b_y[2] = -c1_b_x[1];
  c1_b_y[5] = c1_b_x[0];
  c1_b_y[8] = 0.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i109 = 0; c1_i109 < 9; c1_i109++) {
    c1_p_a[c1_i109] = c1_b_y[c1_i109];
  }

  for (c1_i110 = 0; c1_i110 < 3; c1_i110++) {
    c1_b_b[c1_i110] = c1_ddv[c1_i110];
  }

  for (c1_i111 = 0; c1_i111 < 9; c1_i111++) {
    c1_e_b[c1_i111] = c1_y[c1_i111];
  }

  for (c1_i112 = 0; c1_i112 < 3; c1_i112++) {
    c1_y_a[c1_i112] = 0.0;
    c1_i114 = 0;
    for (c1_i115 = 0; c1_i115 < 3; c1_i115++) {
      c1_y_a[c1_i112] += c1_p_a[c1_i114 + c1_i112] * c1_b_b[c1_i115];
      c1_i114 += 3;
    }
  }

  for (c1_i113 = 0; c1_i113 < 3; c1_i113++) {
    c1_d50 = 0.0;
    c1_i117 = 0;
    for (c1_i118 = 0; c1_i118 < 3; c1_i118++) {
      c1_d50 += c1_e_b[c1_i117 + c1_i113] * c1_y_a[c1_i118];
      c1_i117 += 3;
    }

    c1_pdv[c1_i113] = -c1_d50;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  for (c1_i116 = 0; c1_i116 < 3; c1_i116++) {
    c1_b_b[c1_i116] = c1_pdv[c1_i116];
  }

  for (c1_i119 = 0; c1_i119 < 3; c1_i119++) {
    c1_b_pdv[c1_i119] = c1_pdv[c1_i119];
  }

  c1_b_B = c1_norm(chartInstance, c1_b_pdv);
  for (c1_i120 = 0; c1_i120 < 3; c1_i120++) {
    c1_x_direction[c1_i120] = c1_b_b[c1_i120] / c1_b_B;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -32);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  for (c1_i121 = 0; c1_i121 < 3; c1_i121++) {
    c1_c_x[c1_i121] = c1_z_direction[c1_i121];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_f_debug_family_names,
    c1_d_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_r_nargin, 0U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_r_nargout, 1U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_c_x, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_c_y, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 2);
  c1_c_y[0] = 0.0;
  c1_c_y[3] = -c1_c_x[2];
  c1_c_y[6] = c1_c_x[1];
  c1_c_y[1] = c1_c_x[2];
  c1_c_y[4] = 0.0;
  c1_c_y[7] = -c1_c_x[0];
  c1_c_y[2] = -c1_c_x[1];
  c1_c_y[5] = c1_c_x[0];
  c1_c_y[8] = 0.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i122 = 0; c1_i122 < 9; c1_i122++) {
    c1_p_a[c1_i122] = c1_c_y[c1_i122];
  }

  for (c1_i123 = 0; c1_i123 < 3; c1_i123++) {
    c1_b_b[c1_i123] = c1_x_direction[c1_i123];
  }

  for (c1_i124 = 0; c1_i124 < 3; c1_i124++) {
    c1_y_direction[c1_i124] = 0.0;
  }

  for (c1_i125 = 0; c1_i125 < 3; c1_i125++) {
    c1_y_direction[c1_i125] = 0.0;
    c1_i127 = 0;
    for (c1_i128 = 0; c1_i128 < 3; c1_i128++) {
      c1_y_direction[c1_i125] += c1_p_a[c1_i127 + c1_i125] * c1_b_b[c1_i128];
      c1_i127 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  for (c1_i126 = 0; c1_i126 < 3; c1_i126++) {
    c1_b_desired_attitude[c1_i126] = c1_x_direction[c1_i126];
  }

  for (c1_i129 = 0; c1_i129 < 3; c1_i129++) {
    c1_b_desired_attitude[c1_i129 + 3] = c1_y_direction[c1_i129];
  }

  for (c1_i130 = 0; c1_i130 < 3; c1_i130++) {
    c1_b_desired_attitude[c1_i130 + 6] = c1_z_direction[c1_i130];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_i131 = 0;
  for (c1_i132 = 0; c1_i132 < 3; c1_i132++) {
    c1_i134 = 0;
    for (c1_i135 = 0; c1_i135 < 3; c1_i135++) {
      c1_e_b[c1_i135 + c1_i131] = c1_b_R[c1_i134 + c1_i132];
      c1_i134 += 3;
    }

    c1_i131 += 3;
  }

  for (c1_i133 = 0; c1_i133 < 9; c1_i133++) {
    c1_f_b[c1_i133] = c1_b_desired_attitude[c1_i133];
  }

  c1_i136 = 0;
  for (c1_i137 = 0; c1_i137 < 3; c1_i137++) {
    c1_ab_a[c1_i137] = 0.0;
    for (c1_i140 = 0; c1_i140 < 3; c1_i140++) {
      c1_ab_a[c1_i137] += c1_k_a[c1_i140] * c1_e_b[c1_i140 + c1_i136];
    }

    c1_i136 += 3;
  }

  c1_i138 = 0;
  for (c1_i139 = 0; c1_i139 < 3; c1_i139++) {
    c1_bb_a[c1_i139] = 0.0;
    for (c1_i142 = 0; c1_i142 < 3; c1_i142++) {
      c1_bb_a[c1_i139] += c1_ab_a[c1_i142] * c1_f_b[c1_i142 + c1_i138];
    }

    c1_i138 += 3;
  }

  for (c1_i141 = 0; c1_i141 < 3; c1_i141++) {
    c1_b_b[c1_i141] = c1_bb_a[c1_i141];
  }

  c1_d_y = 0.0;
  for (c1_k = 0; c1_k < 3; c1_k++) {
    c1_d_y += c1_b_b[c1_k] * c1_b[c1_k];
  }

  for (c1_i143 = 0; c1_i143 < 3; c1_i143++) {
    c1_c_desired_thrust[c1_i143] = c1_desired_thrust[c1_i143];
  }

  c1_b_thrust_magnitude = c1_norm(chartInstance, c1_c_desired_thrust) * c1_d_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c1_b_dbg_simtime, 5.4, -1,
        5U, c1_b_dbg_simtime >= 5.4))) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -17);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c1_thrust_magnitude = c1_b_thrust_magnitude;
  for (c1_i144 = 0; c1_i144 < 9; c1_i144++) {
    (*chartInstance->c1_desired_attitude)[c1_i144] =
      c1_b_desired_attitude[c1_i144];
  }

  for (c1_i145 = 0; c1_i145 < 3; c1_i145++) {
    (*chartInstance->c1_dbg_desiredthrust)[c1_i145] =
      c1_b_dbg_desiredthrust[c1_i145];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_NLGC_2(SFc1_NLGC_2InstanceStruct *chartInstance)
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
    "C:\\Users\\hoang\\MATLAB\\Projects\\NLGControl_Quadrotor_1\\Functions\\angle2dcm.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, c1_instanceNumber, 1U,
    sf_debug_get_script_id(
    "C:\\Users\\hoang\\MATLAB\\Projects\\NLGControl_Quadrotor_1\\Functions\\hat.m"));
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i146;
  const mxArray *c1_y = NULL;
  real_T c1_u[3];
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i146 = 0; c1_i146 < 3; c1_i146++) {
    c1_u[c1_i146] = (*(real_T (*)[3])c1_inData)[c1_i146];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance, const
  mxArray *c1_b_dbg_desiredthrust, const char_T *c1_identifier, real_T c1_y[3])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_dbg_desiredthrust),
                        &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_dbg_desiredthrust);
}

static void c1_b_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3])
{
  real_T c1_dv4[3];
  int32_T c1_i147;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv4, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i147 = 0; c1_i147 < 3; c1_i147++) {
    c1_y[c1_i147] = c1_dv4[c1_i147];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_dbg_desiredthrust;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i148;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_b_dbg_desiredthrust = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_dbg_desiredthrust),
                        &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_dbg_desiredthrust);
  for (c1_i148 = 0; c1_i148 < 3; c1_i148++) {
    (*(real_T (*)[3])c1_outData)[c1_i148] = c1_y[c1_i148];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i149;
  int32_T c1_i150;
  const mxArray *c1_y = NULL;
  int32_T c1_i151;
  real_T c1_u[9];
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_i149 = 0;
  for (c1_i150 = 0; c1_i150 < 3; c1_i150++) {
    for (c1_i151 = 0; c1_i151 < 3; c1_i151++) {
      c1_u[c1_i151 + c1_i149] = (*(real_T (*)[9])c1_inData)[c1_i151 + c1_i149];
    }

    c1_i149 += 3;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_b_desired_attitude, const char_T *c1_identifier, real_T
  c1_y[9])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_desired_attitude),
                        &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_desired_attitude);
}

static void c1_d_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9])
{
  real_T c1_dv5[9];
  int32_T c1_i152;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv5, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c1_i152 = 0; c1_i152 < 9; c1_i152++) {
    c1_y[c1_i152] = c1_dv5[c1_i152];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_desired_attitude;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[9];
  int32_T c1_i153;
  int32_T c1_i154;
  int32_T c1_i155;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_b_desired_attitude = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_desired_attitude),
                        &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_desired_attitude);
  c1_i153 = 0;
  for (c1_i154 = 0; c1_i154 < 3; c1_i154++) {
    for (c1_i155 = 0; c1_i155 < 3; c1_i155++) {
      (*(real_T (*)[9])c1_outData)[c1_i155 + c1_i153] = c1_y[c1_i155 + c1_i153];
    }

    c1_i153 += 3;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_e_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_b_thrust_magnitude, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_thrust_magnitude),
    &c1_thisId);
  sf_mex_destroy(&c1_b_thrust_magnitude);
  return c1_y;
}

static real_T c1_f_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d51;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d51, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d51;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_thrust_magnitude;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_b_thrust_magnitude = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_thrust_magnitude),
    &c1_thisId);
  sf_mex_destroy(&c1_b_thrust_magnitude);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
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
  int32_T c1_i156;
  const mxArray *c1_k_y = NULL;
  real_T c1_k_u[9];
  int32_T c1_i157;
  const mxArray *c1_l_y = NULL;
  int32_T c1_i158;
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
  int32_T c1_i159;
  const mxArray *c1_ib_y = NULL;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
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
  for (c1_i156 = 0; c1_i156 < 9; c1_i156++) {
    c1_k_u[c1_i156] = c1_u.Jb[c1_i156];
  }

  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", c1_k_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_addfield(c1_y, c1_k_y, "Jb", "Jb", 0);
  for (c1_i157 = 0; c1_i157 < 9; c1_i157++) {
    c1_k_u[c1_i157] = c1_u.Jbinv[c1_i157];
  }

  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", c1_k_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_addfield(c1_y, c1_l_y, "Jbinv", "Jbinv", 0);
  for (c1_i158 = 0; c1_i158 < 12; c1_i158++) {
    c1_l_u[c1_i158] = c1_u.dctcq[c1_i158];
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
  for (c1_i159 = 0; c1_i159 < 9; c1_i159++) {
    c1_k_u[c1_i159] = c1_u.J[c1_i159];
  }

  c1_ib_y = NULL;
  sf_mex_assign(&c1_ib_y, sf_mex_create("y", c1_k_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_addfield(c1_y, c1_ib_y, "J", "J", 0);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_g_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
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
  c1_y->g = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "g", "g", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "d";
  c1_y->d = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "d", "d", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "mass";
  c1_y->mass = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "mass", "mass", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ct";
  c1_y->ct = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ct", "ct", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "cq";
  c1_y->cq = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "cq", "cq", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jx";
  c1_y->Jx = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jx", "Jx", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jy";
  c1_y->Jy = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jy", "Jy", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jz";
  c1_y->Jz = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jz", "Jz", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jm";
  c1_y->Jm = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "Jm", "Jm", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Jb";
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "Jb",
    "Jb", 0)), &c1_thisId, c1_y->Jb);
  c1_thisId.fIdentifier = "Jbinv";
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "Jbinv",
    "Jbinv", 0)), &c1_thisId, c1_y->Jbinv);
  c1_thisId.fIdentifier = "dctcq";
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "dctcq",
    "dctcq", 0)), &c1_thisId, c1_y->dctcq);
  c1_thisId.fIdentifier = "motor_m";
  c1_y->motor_m = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_m", "motor_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "motor_dm";
  c1_y->motor_dm = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_dm", "motor_dm", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "motor_h";
  c1_y->motor_h = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_h", "motor_h", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "motor_r";
  c1_y->motor_r = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "motor_r", "motor_r", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_m";
  c1_y->ESC_m = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_m", "ESC_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_a";
  c1_y->ESC_a = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_a", "ESC_a", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_b";
  c1_y->ESC_b = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_b", "ESC_b", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "ESC_ds";
  c1_y->ESC_ds = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "ESC_ds", "ESC_ds", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "HUB_m";
  c1_y->HUB_m = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "HUB_m", "HUB_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "HUB_r";
  c1_y->HUB_r = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "HUB_r", "HUB_r", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "HUB_H";
  c1_y->HUB_H = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "HUB_H", "HUB_H", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_m";
  c1_y->arms_m = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "arms_m", "arms_m", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_r";
  c1_y->arms_r = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "arms_r", "arms_r", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_L";
  c1_y->arms_L = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "arms_L", "arms_L", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "arms_da";
  c1_y->arms_da = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "arms_da", "arms_da", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "T";
  c1_y->T = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "T", "T", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "minThr";
  c1_y->minThr = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "minThr", "minThr", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "cr";
  c1_y->cr = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "cr", "cr", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "b";
  c1_y->b = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "b", "b", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "plusConfig";
  c1_y->plusConfig = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "plusConfig", "plusConfig", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "J";
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "J", "J",
    0)), &c1_thisId, c1_y->J);
  sf_mex_destroy(&c1_u);
}

static void c1_h_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[12])
{
  real_T c1_dv6[12];
  int32_T c1_i160;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv6, 1, 0, 0U, 1, 0U, 2, 3, 4);
  for (c1_i160 = 0; c1_i160 < 12; c1_i160++) {
    c1_y[c1_i160] = c1_dv6[c1_i160];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_quadModel;
  emlrtMsgIdentifier c1_thisId;
  c1_struct_fGw06pKU762DM8t1dqR94E c1_y;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_b_quadModel = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_quadModel), &c1_thisId,
                        &c1_y);
  sf_mex_destroy(&c1_b_quadModel);
  *(c1_struct_fGw06pKU762DM8t1dqR94E *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i161;
  const mxArray *c1_y = NULL;
  real_T c1_u[3];
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i161 = 0; c1_i161 < 3; c1_i161++) {
    c1_u[c1_i161] = (*(real_T (*)[3])c1_inData)[c1_i161];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 1), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i162;
  const mxArray *c1_y = NULL;
  real_T c1_u[3];
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i162 = 0; c1_i162 < 3; c1_i162++) {
    c1_u[c1_i162] = (*(real_T (*)[3])c1_inData)[c1_i162];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_i_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3])
{
  real_T c1_dv7[3];
  int32_T c1_i163;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv7, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c1_i163 = 0; c1_i163 < 3; c1_i163++) {
    c1_y[c1_i163] = c1_dv7[c1_i163];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_r;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i164;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_r = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_r), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_r);
  for (c1_i164 = 0; c1_i164 < 3; c1_i164++) {
    (*(real_T (*)[3])c1_outData)[c1_i164] = c1_y[c1_i164];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_NLGC_2_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  const char * c1_data[5] = {
    "789ced55dd4ec23018ed1489246ab8f211bcd0848998a05ef12f24808048628c81b115375d5bec3683efe2037869a24fe285cfe3608cfd24cd48c0118d4d9a6f"
    "27a7fd4efbe5db29e02a350e00b063ce88394fb6c0646c5b01c4a7710d78879fe77ceb38ef72b031c9eeecb3f997691409d6e148b780aa605837501f52136001",
    "c1591a8920050b586f3f0f21a05023ea139426cc4051615b41b04a5ca0ac9800955cd40c8ca9f1775e86e2c3a581009535e7b8aa1b00577d7a8cfb4702eae31f"
    "fefaf8d705e94503f43846b4470c6cba503a63eb0d19f982ee67e78f31f4e23e5ec0772a3c924434c58bd6d7d68bfab0a36f311231fa2a74f4de16d4ab33f5bc",
    "fc4df1367fc65f69906abc4cccdbf3b56cbb9acdf10d4aeea1a86b7cbd7a9e377f024ad46ed310244a7442bb49be6460515708d6f859c91228d4fe38d8fff8ca"
    "86db8f61f7ffeaf4468c7cf3f6df2e432feee311bd169064246bb079386aa51e0b1da5d82838e76804e8049d03307058f97b8cfd3fe5cb2c9f9cb74f58efa4ed",
    "8f5eddd38c15f732cbf2c975867e7ccac882f516afca975f17d42b33f5bcfc127cd92c550285e81f9fadf77f3ffeed7e7c5c920d6488834aaa58c117a37a4e4a"
    "77c43fe0c7df266e93a7", "" };

  c1_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c1_data, 3152U, &c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static real_T c1_norm(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_x[3])
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

static real_T c1_cosd(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_x)
{
  real_T c1_b_x;
  c1_b_x = c1_x;
  c1_b_cosd(chartInstance, &c1_b_x);
  return c1_b_x;
}

static real_T c1_sind(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_x)
{
  real_T c1_b_x;
  c1_b_x = c1_x;
  c1_b_sind(chartInstance, &c1_b_x);
  return c1_b_x;
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_j_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i165;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i165, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i165;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_k_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_NLGC_2, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_NLGC_2), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_NLGC_2);
  return c1_y;
}

static uint8_T c1_l_emlrt_marshallIn(SFc1_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_cosd(SFc1_NLGC_2InstanceStruct *chartInstance, real_T *c1_x)
{
  real_T c1_b_x;
  real_T c1_absx;
  int8_T c1_n;
  (void)chartInstance;
  if (!((!muDoubleScalarIsInf(*c1_x)) && (!muDoubleScalarIsNaN(*c1_x)))) {
    *c1_x = rtNaN;
  } else {
    c1_b_x = muDoubleScalarRem(*c1_x, 360.0);
    c1_absx = muDoubleScalarAbs(c1_b_x);
    if (c1_absx > 180.0) {
      if (c1_b_x > 0.0) {
        c1_b_x -= 360.0;
      } else {
        c1_b_x += 360.0;
      }

      c1_absx = muDoubleScalarAbs(c1_b_x);
    }

    if (c1_absx <= 45.0) {
      c1_b_x *= 0.017453292519943295;
      c1_n = 0;
    } else if (c1_absx <= 135.0) {
      if (c1_b_x > 0.0) {
        c1_b_x = 0.017453292519943295 * (c1_b_x - 90.0);
        c1_n = 1;
      } else {
        c1_b_x = 0.017453292519943295 * (c1_b_x + 90.0);
        c1_n = -1;
      }
    } else if (c1_b_x > 0.0) {
      c1_b_x = 0.017453292519943295 * (c1_b_x - 180.0);
      c1_n = 2;
    } else {
      c1_b_x = 0.017453292519943295 * (c1_b_x + 180.0);
      c1_n = -2;
    }

    if ((real_T)c1_n == 0.0) {
      *c1_x = muDoubleScalarCos(c1_b_x);
    } else if ((real_T)c1_n == 1.0) {
      *c1_x = -muDoubleScalarSin(c1_b_x);
    } else if ((real_T)c1_n == -1.0) {
      *c1_x = muDoubleScalarSin(c1_b_x);
    } else {
      *c1_x = -muDoubleScalarCos(c1_b_x);
    }
  }
}

static void c1_b_sind(SFc1_NLGC_2InstanceStruct *chartInstance, real_T *c1_x)
{
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_absx;
  int8_T c1_n;
  (void)chartInstance;
  if (!((!muDoubleScalarIsInf(*c1_x)) && (!muDoubleScalarIsNaN(*c1_x)))) {
    c1_c_x = rtNaN;
  } else {
    c1_b_x = muDoubleScalarRem(*c1_x, 360.0);
    c1_absx = muDoubleScalarAbs(c1_b_x);
    if (c1_absx > 180.0) {
      if (c1_b_x > 0.0) {
        c1_b_x -= 360.0;
      } else {
        c1_b_x += 360.0;
      }

      c1_absx = muDoubleScalarAbs(c1_b_x);
    }

    if (c1_absx <= 45.0) {
      c1_b_x *= 0.017453292519943295;
      c1_n = 0;
    } else if (c1_absx <= 135.0) {
      if (c1_b_x > 0.0) {
        c1_b_x = 0.017453292519943295 * (c1_b_x - 90.0);
        c1_n = 1;
      } else {
        c1_b_x = 0.017453292519943295 * (c1_b_x + 90.0);
        c1_n = -1;
      }
    } else if (c1_b_x > 0.0) {
      c1_b_x = 0.017453292519943295 * (c1_b_x - 180.0);
      c1_n = 2;
    } else {
      c1_b_x = 0.017453292519943295 * (c1_b_x + 180.0);
      c1_n = -2;
    }

    if ((real_T)c1_n == 0.0) {
      c1_c_x = muDoubleScalarSin(c1_b_x);
    } else if ((real_T)c1_n == 1.0) {
      c1_c_x = muDoubleScalarCos(c1_b_x);
    } else if ((real_T)c1_n == -1.0) {
      c1_c_x = -muDoubleScalarCos(c1_b_x);
    } else {
      c1_c_x = -muDoubleScalarSin(c1_b_x);
    }
  }

  *c1_x = c1_c_x;
}

static int32_T c1__s32_d_(SFc1_NLGC_2InstanceStruct *chartInstance, real_T c1_b,
  uint32_T c1_ssid_src_loc, int32_T c1_offset_src_loc, int32_T c1_length_src_loc)
{
  int32_T c1_b_a;
  real_T c1_b_b;
  (void)chartInstance;
  c1_b_a = (int32_T)c1_b;
  if (c1_b < 0.0) {
    c1_b_b = muDoubleScalarCeil(c1_b);
  } else {
    c1_b_b = muDoubleScalarFloor(c1_b);
  }

  if ((real_T)c1_b_a != c1_b_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c1_ssid_src_loc, c1_offset_src_loc,
      c1_length_src_loc);
  }

  return c1_b_a;
}

static void init_dsm_address_info(SFc1_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_NLGC_2InstanceStruct *chartInstance)
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
  chartInstance->c1_dbg_simtime = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_dbg_desiredthrust = (real_T (*)[3])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 3);
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

void sf_c1_NLGC_2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1540319747U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(221677243U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4122485954U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3792662861U);
}

mxArray* sf_c1_NLGC_2_get_post_codegen_info(void);
mxArray *sf_c1_NLGC_2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("y20yNR8sHmX1kfagV5Tad");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_NLGC_2_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_NLGC_2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_NLGC_2_jit_fallback_info(void)
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

mxArray *sf_c1_NLGC_2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_NLGC_2_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c1_NLGC_2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[17],T\"dbg_desiredthrust\",},{M[1],M[12],T\"desired_attitude\",},{M[1],M[5],T\"thrust_magnitude\",},{M[8],M[0],T\"is_active_c1_NLGC_2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_NLGC_2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_NLGC_2InstanceStruct *chartInstance = (SFc1_NLGC_2InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _NLGC_2MachineNumber_,
           1,
           1,
           1,
           0,
           12,
           0,
           0,
           0,
           0,
           2,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_NLGC_2MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_NLGC_2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _NLGC_2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"R");
          _SFD_SET_DATA_PROPS(1,1,1,0,"ex");
          _SFD_SET_DATA_PROPS(2,1,1,0,"ev");
          _SFD_SET_DATA_PROPS(3,1,1,0,"a");
          _SFD_SET_DATA_PROPS(4,1,1,0,"psi");
          _SFD_SET_DATA_PROPS(5,1,1,0,"dbg_simtime");
          _SFD_SET_DATA_PROPS(6,2,0,1,"thrust_magnitude");
          _SFD_SET_DATA_PROPS(7,2,0,1,"desired_attitude");
          _SFD_SET_DATA_PROPS(8,2,0,1,"dbg_desiredthrust");
          _SFD_SET_DATA_PROPS(9,10,0,0,"kv");
          _SFD_SET_DATA_PROPS(10,10,0,0,"kx");
          _SFD_SET_DATA_PROPS(11,10,0,0,"quadModel");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,684);
        _SFD_CV_INIT_EML_FCN(0,1,"findDirection",731,-1,1334);
        _SFD_CV_INIT_EML_IF(0,1,0,646,667,-1,680);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,650,666,-1,5);
        _SFD_CV_INIT_SCRIPT(0,4,0,0,0,0,1,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"angle2dcm",0,-1,433);
        _SFD_CV_INIT_SCRIPT_FCN(0,1,"Tx",433,-1,503);
        _SFD_CV_INIT_SCRIPT_FCN(0,2,"Ty",503,-1,573);
        _SFD_CV_INIT_SCRIPT_FCN(0,3,"Tz",573,-1,641);

        {
          static int caseStart[] = { 380, 233, 282, 331 };

          static int caseExprEnd[] = { 389, 241, 290, 339 };

          _SFD_CV_INIT_SCRIPT_SWITCH(0,0,220,231,431,4,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"hat",0,-1,77);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_d_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _NLGC_2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_NLGC_2InstanceStruct *chartInstance = (SFc1_NLGC_2InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c1_R);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c1_thrust_magnitude);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c1_ex);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c1_ev);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c1_a);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c1_psi);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c1_desired_attitude);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)&chartInstance->c1_kx);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)&chartInstance->c1_kv);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)&chartInstance->c1_quadModel);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c1_dbg_simtime);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c1_dbg_desiredthrust);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s37rW4iMnAjmtOxwQepVbOE";
}

static void sf_opaque_initialize_c1_NLGC_2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_NLGC_2InstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*) chartInstanceVar);
  initialize_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_NLGC_2(void *chartInstanceVar)
{
  enable_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_NLGC_2(void *chartInstanceVar)
{
  disable_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_NLGC_2(void *chartInstanceVar)
{
  sf_gateway_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_NLGC_2(SimStruct* S)
{
  return get_sim_state_c1_NLGC_2((SFc1_NLGC_2InstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_NLGC_2(SimStruct* S, const mxArray *st)
{
  set_sim_state_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*)sf_get_chart_instance_ptr
    (S), st);
}

static void sf_opaque_terminate_c1_NLGC_2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_NLGC_2InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_NLGC_2_optimization_info();
    }

    finalize_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_NLGC_2((SFc1_NLGC_2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_NLGC_2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_NLGC_2((SFc1_NLGC_2InstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c1_NLGC_2(SimStruct *S)
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
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_NLGC_2_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
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
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 6; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2014024050U));
  ssSetChecksum1(S,(2085701406U));
  ssSetChecksum2(S,(25043674U));
  ssSetChecksum3(S,(2939248341U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_NLGC_2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_NLGC_2(SimStruct *S)
{
  SFc1_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc1_NLGC_2InstanceStruct *)utMalloc(sizeof
    (SFc1_NLGC_2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_NLGC_2InstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_NLGC_2;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_NLGC_2;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_NLGC_2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_NLGC_2;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_NLGC_2;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_NLGC_2;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_NLGC_2;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_NLGC_2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_NLGC_2;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_NLGC_2;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_NLGC_2;
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
  mdl_start_c1_NLGC_2(chartInstance);
}

void c1_NLGC_2_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_NLGC_2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_NLGC_2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_NLGC_2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_NLGC_2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
