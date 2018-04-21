/* Include files */

#include "NLGC_2_sfun.h"
#include "c7_NLGC_2.h"
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
static const char * c7_debug_family_names[14] = { "force", "gamma", "omega",
  "nargin", "nargout", "f", "M", "Ct", "d", "Cq", "o1", "o2", "o3", "o4" };

/* Function Declarations */
static void initialize_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void initialize_params_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void enable_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void disable_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void c7_update_debugger_state_c7_NLGC_2(SFc7_NLGC_2InstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c7_NLGC_2(SFc7_NLGC_2InstanceStruct
  *chartInstance);
static void set_sim_state_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_st);
static void finalize_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void sf_gateway_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void mdl_start_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void initSimStructsc7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static real_T c7_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_b_o4, const char_T *c7_identifier);
static real_T c7_b_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_c_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[4]);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_d_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[16]);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static void c7_mldivide(SFc7_NLGC_2InstanceStruct *chartInstance, real_T c7_A[16],
  real_T c7_B[4], real_T c7_Y[4]);
static void c7_check_forloop_overflow_error(SFc7_NLGC_2InstanceStruct
  *chartInstance, boolean_T c7_overflow);
static void c7_warning(SFc7_NLGC_2InstanceStruct *chartInstance);
static void c7_error(SFc7_NLGC_2InstanceStruct *chartInstance);
static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static int32_T c7_e_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static uint8_T c7_f_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_b_is_active_c7_NLGC_2, const char_T *c7_identifier);
static uint8_T c7_g_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_b_mldivide(SFc7_NLGC_2InstanceStruct *chartInstance, real_T c7_A
  [16], real_T c7_B[4]);
static void init_dsm_address_info(SFc7_NLGC_2InstanceStruct *chartInstance);
static void init_simulink_io_address(SFc7_NLGC_2InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc7_NLGC_2(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c7_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c7_is_active_c7_NLGC_2 = 0U;
}

static void initialize_params_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  real_T c7_d0;
  real_T c7_d1;
  real_T c7_d2;
  sf_mex_import_named("Ct", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c7_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c7_Ct = c7_d0;
  sf_mex_import_named("d", sf_mex_get_sfun_param(chartInstance->S, 2, 0), &c7_d1,
                      0, 0, 0U, 0, 0U, 0);
  chartInstance->c7_d = c7_d1;
  sf_mex_import_named("Cq", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c7_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c7_Cq = c7_d2;
}

static void enable_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c7_update_debugger_state_c7_NLGC_2(SFc7_NLGC_2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c7_NLGC_2(SFc7_NLGC_2InstanceStruct
  *chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  real_T c7_hoistedGlobal;
  const mxArray *c7_b_y = NULL;
  real_T c7_b_hoistedGlobal;
  const mxArray *c7_c_y = NULL;
  real_T c7_c_hoistedGlobal;
  const mxArray *c7_d_y = NULL;
  real_T c7_d_hoistedGlobal;
  const mxArray *c7_e_y = NULL;
  uint8_T c7_e_hoistedGlobal;
  const mxArray *c7_f_y = NULL;
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellmatrix(5, 1), false);
  c7_hoistedGlobal = *chartInstance->c7_o1;
  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c7_y, 0, c7_b_y);
  c7_b_hoistedGlobal = *chartInstance->c7_o2;
  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", &c7_b_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c7_y, 1, c7_c_y);
  c7_c_hoistedGlobal = *chartInstance->c7_o3;
  c7_d_y = NULL;
  sf_mex_assign(&c7_d_y, sf_mex_create("y", &c7_c_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c7_y, 2, c7_d_y);
  c7_d_hoistedGlobal = *chartInstance->c7_o4;
  c7_e_y = NULL;
  sf_mex_assign(&c7_e_y, sf_mex_create("y", &c7_d_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c7_y, 3, c7_e_y);
  c7_e_hoistedGlobal = chartInstance->c7_is_active_c7_NLGC_2;
  c7_f_y = NULL;
  sf_mex_assign(&c7_f_y, sf_mex_create("y", &c7_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c7_y, 4, c7_f_y);
  sf_mex_assign(&c7_st, c7_y, false);
  return c7_st;
}

static void set_sim_state_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_st)
{
  const mxArray *c7_u;
  chartInstance->c7_doneDoubleBufferReInit = true;
  c7_u = sf_mex_dup(c7_st);
  *chartInstance->c7_o1 = c7_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 0)), "o1");
  *chartInstance->c7_o2 = c7_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 1)), "o2");
  *chartInstance->c7_o3 = c7_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 2)), "o3");
  *chartInstance->c7_o4 = c7_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 3)), "o4");
  chartInstance->c7_is_active_c7_NLGC_2 = c7_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c7_u, 4)), "is_active_c7_NLGC_2");
  sf_mex_destroy(&c7_u);
  c7_update_debugger_state_c7_NLGC_2(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void finalize_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  int32_T c7_i0;
  real_T c7_b_f;
  int32_T c7_i1;
  real_T c7_b_Ct;
  real_T c7_b_M[3];
  real_T c7_b_d;
  real_T c7_b_Cq;
  uint32_T c7_debug_family_var_map[14];
  real_T c7_force[4];
  real_T c7_gamma[16];
  real_T c7_omega[4];
  real_T c7_nargin = 5.0;
  real_T c7_nargout = 4.0;
  real_T c7_b_o1;
  real_T c7_b_o2;
  real_T c7_b_o3;
  real_T c7_b_o4;
  int32_T c7_i2;
  int32_T c7_i3;
  int32_T c7_i4;
  real_T c7_x[4];
  real_T c7_b_gamma[16];
  int32_T c7_i5;
  int32_T c7_i6;
  boolean_T c7_p;
  int32_T c7_k;
  int32_T c7_i7;
  boolean_T c7_b_p;
  int32_T c7_i8;
  int32_T c7_b_k;
  real_T c7_b_x;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c7_sfEvent);
  for (c7_i0 = 0; c7_i0 < 3; c7_i0++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c7_M)[c7_i0], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c7_f, 0U);
  chartInstance->c7_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c7_sfEvent);
  c7_b_f = *chartInstance->c7_f;
  for (c7_i1 = 0; c7_i1 < 3; c7_i1++) {
    c7_b_M[c7_i1] = (*chartInstance->c7_M)[c7_i1];
  }

  c7_b_Ct = chartInstance->c7_Ct;
  c7_b_d = chartInstance->c7_d;
  c7_b_Cq = chartInstance->c7_Cq;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 14U, 14U, c7_debug_family_names,
    c7_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_force, 0U, c7_c_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_gamma, 1U, c7_d_sf_marshallOut,
    c7_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_omega, 2U, c7_c_sf_marshallOut,
    c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargin, 3U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargout, 4U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c7_b_f, 5U, c7_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_b_M, 6U, c7_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_Ct, 7U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_d, 8U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_Cq, 9U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_o1, 10U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_o2, 11U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_o3, 12U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_o4, 13U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 2);
  c7_force[0] = c7_b_f;
  for (c7_i2 = 0; c7_i2 < 3; c7_i2++) {
    c7_force[c7_i2 + 1] = c7_b_M[c7_i2];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 3);
  c7_gamma[0] = c7_b_Ct;
  c7_gamma[4] = c7_b_Ct;
  c7_gamma[8] = c7_b_Ct;
  c7_gamma[12] = c7_b_Ct;
  c7_gamma[1] = 0.0;
  c7_gamma[5] = c7_b_d * c7_b_Ct;
  c7_gamma[9] = 0.0;
  c7_gamma[13] = -c7_b_d * c7_b_Ct;
  c7_gamma[2] = -c7_b_d * c7_b_Ct;
  c7_gamma[6] = 0.0;
  c7_gamma[10] = c7_b_d * c7_b_Ct;
  c7_gamma[14] = 0.0;
  c7_gamma[3] = -c7_b_Cq;
  c7_gamma[7] = c7_b_Cq;
  c7_gamma[11] = -c7_b_Cq;
  c7_gamma[15] = c7_b_Cq;
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 7);
  for (c7_i3 = 0; c7_i3 < 4; c7_i3++) {
    c7_x[c7_i3] = c7_force[c7_i3];
  }

  for (c7_i4 = 0; c7_i4 < 16; c7_i4++) {
    c7_b_gamma[c7_i4] = c7_gamma[c7_i4];
  }

  c7_b_mldivide(chartInstance, c7_b_gamma, c7_x);
  for (c7_i5 = 0; c7_i5 < 4; c7_i5++) {
    c7_omega[c7_i5] = c7_x[c7_i5];
  }

  for (c7_i6 = 0; c7_i6 < 4; c7_i6++) {
    c7_x[c7_i6] = c7_omega[c7_i6];
  }

  c7_p = false;
  for (c7_k = 0; c7_k < 4; c7_k++) {
    if (c7_p || (c7_x[c7_k] < 0.0)) {
      c7_b_p = true;
    } else {
      c7_b_p = false;
    }

    c7_p = c7_b_p;
  }

  if (c7_p) {
    c7_error(chartInstance);
  }

  for (c7_i7 = 0; c7_i7 < 4; c7_i7++) {
    c7_x[c7_i7] = c7_omega[c7_i7];
  }

  for (c7_i8 = 0; c7_i8 < 4; c7_i8++) {
    c7_omega[c7_i8] = c7_x[c7_i8];
  }

  for (c7_b_k = 0; c7_b_k < 4; c7_b_k++) {
    c7_b_x = c7_omega[c7_b_k];
    c7_omega[c7_b_k] = muDoubleScalarSqrt(c7_b_x);
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 8);
  c7_b_o1 = c7_omega[0];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 9);
  c7_b_o2 = c7_omega[1];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 10);
  c7_b_o3 = c7_omega[2];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 11);
  c7_b_o4 = c7_omega[3];
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c7_o1 = c7_b_o1;
  *chartInstance->c7_o2 = c7_b_o2;
  *chartInstance->c7_o3 = c7_b_o3;
  *chartInstance->c7_o4 = c7_b_o4;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c7_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_NLGC_2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c7_o1, 2U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c7_o2, 3U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c7_o3, 4U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c7_o4, 5U);
}

static void mdl_start_c7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc7_NLGC_2(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber)
{
  (void)(c7_machineNumber);
  (void)(c7_chartNumber);
  (void)(c7_instanceNumber);
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static real_T c7_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_b_o4, const char_T *c7_identifier)
{
  real_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = (const char *)c7_identifier;
  c7_thisId.fParent = NULL;
  c7_thisId.bParentIsCell = false;
  c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_o4), &c7_thisId);
  sf_mex_destroy(&c7_b_o4);
  return c7_y;
}

static real_T c7_b_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d3;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d3, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d3;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_o4;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_b_o4 = sf_mex_dup(c7_mxArrayInData);
  c7_thisId.fIdentifier = (const char *)c7_varName;
  c7_thisId.fParent = NULL;
  c7_thisId.bParentIsCell = false;
  c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_o4), &c7_thisId);
  sf_mex_destroy(&c7_b_o4);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  int32_T c7_i9;
  const mxArray *c7_y = NULL;
  real_T c7_u[3];
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  for (c7_i9 = 0; c7_i9 < 3; c7_i9++) {
    c7_u[c7_i9] = (*(real_T (*)[3])c7_inData)[c7_i9];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 3, 1), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  int32_T c7_i10;
  const mxArray *c7_y = NULL;
  real_T c7_u[4];
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  for (c7_i10 = 0; c7_i10 < 4; c7_i10++) {
    c7_u[c7_i10] = (*(real_T (*)[4])c7_inData)[c7_i10];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_c_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[4])
{
  real_T c7_dv0[4];
  int32_T c7_i11;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv0, 1, 0, 0U, 1, 0U, 1, 4);
  for (c7_i11 = 0; c7_i11 < 4; c7_i11++) {
    c7_y[c7_i11] = c7_dv0[c7_i11];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_omega;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[4];
  int32_T c7_i12;
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_omega = sf_mex_dup(c7_mxArrayInData);
  c7_thisId.fIdentifier = (const char *)c7_varName;
  c7_thisId.fParent = NULL;
  c7_thisId.bParentIsCell = false;
  c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_omega), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_omega);
  for (c7_i12 = 0; c7_i12 < 4; c7_i12++) {
    (*(real_T (*)[4])c7_outData)[c7_i12] = c7_y[c7_i12];
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  int32_T c7_i13;
  int32_T c7_i14;
  const mxArray *c7_y = NULL;
  int32_T c7_i15;
  real_T c7_u[16];
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  c7_i13 = 0;
  for (c7_i14 = 0; c7_i14 < 4; c7_i14++) {
    for (c7_i15 = 0; c7_i15 < 4; c7_i15++) {
      c7_u[c7_i15 + c7_i13] = (*(real_T (*)[16])c7_inData)[c7_i15 + c7_i13];
    }

    c7_i13 += 4;
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_d_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[16])
{
  real_T c7_dv1[16];
  int32_T c7_i16;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv1, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c7_i16 = 0; c7_i16 < 16; c7_i16++) {
    c7_y[c7_i16] = c7_dv1[c7_i16];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_gamma;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[16];
  int32_T c7_i17;
  int32_T c7_i18;
  int32_T c7_i19;
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_gamma = sf_mex_dup(c7_mxArrayInData);
  c7_thisId.fIdentifier = (const char *)c7_varName;
  c7_thisId.fParent = NULL;
  c7_thisId.bParentIsCell = false;
  c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_gamma), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_gamma);
  c7_i17 = 0;
  for (c7_i18 = 0; c7_i18 < 4; c7_i18++) {
    for (c7_i19 = 0; c7_i19 < 4; c7_i19++) {
      (*(real_T (*)[16])c7_outData)[c7_i19 + c7_i17] = c7_y[c7_i19 + c7_i17];
    }

    c7_i17 += 4;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

const mxArray *sf_c7_NLGC_2_get_eml_resolved_functions_info(void)
{
  const mxArray *c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  sf_mex_assign(&c7_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c7_nameCaptureInfo;
}

static void c7_mldivide(SFc7_NLGC_2InstanceStruct *chartInstance, real_T c7_A[16],
  real_T c7_B[4], real_T c7_Y[4])
{
  int32_T c7_i20;
  int32_T c7_i21;
  real_T c7_b_A[16];
  for (c7_i20 = 0; c7_i20 < 4; c7_i20++) {
    c7_Y[c7_i20] = c7_B[c7_i20];
  }

  for (c7_i21 = 0; c7_i21 < 16; c7_i21++) {
    c7_b_A[c7_i21] = c7_A[c7_i21];
  }

  c7_b_mldivide(chartInstance, c7_b_A, c7_Y);
}

static void c7_check_forloop_overflow_error(SFc7_NLGC_2InstanceStruct
  *chartInstance, boolean_T c7_overflow)
{
  const mxArray *c7_y = NULL;
  static char_T c7_cv0[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  const mxArray *c7_b_y = NULL;
  static char_T c7_cv1[5] = { 'i', 'n', 't', '3', '2' };

  (void)chartInstance;
  if (!c7_overflow) {
  } else {
    c7_y = NULL;
    sf_mex_assign(&c7_y, sf_mex_create("y", c7_cv0, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    c7_b_y = NULL;
    sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_cv1, 10, 0U, 1U, 0U, 2, 1, 5),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c7_y, 14, c7_b_y));
  }
}

static void c7_warning(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  const mxArray *c7_y = NULL;
  static char_T c7_cv2[7] = { 'w', 'a', 'r', 'n', 'i', 'n', 'g' };

  const mxArray *c7_b_y = NULL;
  static char_T c7_cv3[7] = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

  const mxArray *c7_c_y = NULL;
  static char_T c7_msgID[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a', 't',
    'r', 'i', 'x' };

  (void)chartInstance;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_cv2, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_cv3, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", c7_msgID, 10, 0U, 1U, 0U, 2, 1, 27),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 0U, 2U, 14, c7_y, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 1U,
    2U, 14, c7_b_y, 14, c7_c_y));
}

static void c7_error(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  const mxArray *c7_y = NULL;
  static char_T c7_cv4[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  const mxArray *c7_b_y = NULL;
  static char_T c7_cv5[4] = { 's', 'q', 'r', 't' };

  (void)chartInstance;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_cv4, 10, 0U, 1U, 0U, 2, 1, 30),
                false);
  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_cv5, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c7_y, 14, c7_b_y));
}

static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static int32_T c7_e_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i22;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i22, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i22;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_sfEvent;
  emlrtMsgIdentifier c7_thisId;
  int32_T c7_y;
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)chartInstanceVoid;
  c7_b_sfEvent = sf_mex_dup(c7_mxArrayInData);
  c7_thisId.fIdentifier = (const char *)c7_varName;
  c7_thisId.fParent = NULL;
  c7_thisId.bParentIsCell = false;
  c7_y = c7_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_sfEvent),
    &c7_thisId);
  sf_mex_destroy(&c7_b_sfEvent);
  *(int32_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static uint8_T c7_f_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_b_is_active_c7_NLGC_2, const char_T *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = (const char *)c7_identifier;
  c7_thisId.fParent = NULL;
  c7_thisId.bParentIsCell = false;
  c7_y = c7_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_b_is_active_c7_NLGC_2), &c7_thisId);
  sf_mex_destroy(&c7_b_is_active_c7_NLGC_2);
  return c7_y;
}

static uint8_T c7_g_emlrt_marshallIn(SFc7_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u0, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_b_mldivide(SFc7_NLGC_2InstanceStruct *chartInstance, real_T c7_A
  [16], real_T c7_B[4])
{
  int32_T c7_i23;
  int32_T c7_i24;
  real_T c7_b_A[16];
  int32_T c7_info;
  int32_T c7_ipiv[4];
  int32_T c7_j;
  int32_T c7_c;
  int32_T c7_idxmax;
  int32_T c7_ix;
  int32_T c7_xi;
  real_T c7_smax;
  boolean_T c7_overflow;
  int32_T c7_jA;
  int32_T c7_b;
  int32_T c7_b_ix;
  int32_T c7_k;
  int32_T c7_jy;
  boolean_T c7_b_overflow;
  int32_T c7_iy;
  real_T c7_temp;
  int32_T c7_b_k;
  boolean_T c7_c_overflow;
  int32_T c7_c_k;
  int32_T c7_d_k;
  int32_T c7_kAcol;
  int32_T c7_i;
  int32_T c7_b_j;
  real_T c7_b_temp;
  int32_T c7_b_i;
  real_T c7_s;
  int32_T c7_b_kAcol;
  real_T c7_yjy;
  boolean_T c7_d_overflow;
  int32_T c7_c_ix;
  int32_T c7_b_b;
  boolean_T c7_e_overflow;
  int32_T c7_c_i;
  int32_T c7_ijA;
  for (c7_i23 = 0; c7_i23 < 16; c7_i23++) {
    c7_b_A[c7_i23] = c7_A[c7_i23];
  }

  for (c7_i24 = 0; c7_i24 < 4; c7_i24++) {
    c7_ipiv[c7_i24] = 1 + c7_i24;
  }

  c7_info = 0;
  for (c7_j = 0; c7_j < 3; c7_j++) {
    c7_c = c7_j * 5;
    if (4 - c7_j < 1) {
      c7_idxmax = 0;
    } else {
      c7_idxmax = 1;
      if (4 - c7_j > 1) {
        c7_ix = c7_c;
        c7_smax = muDoubleScalarAbs(c7_b_A[c7_c]) + muDoubleScalarAbs(0.0);
        c7_overflow = ((!(2 > 4 - c7_j)) && (4 - c7_j > 2147483646));
        if (c7_overflow) {
          c7_check_forloop_overflow_error(chartInstance, c7_overflow);
        }

        for (c7_b_k = 2; c7_b_k <= 4 - c7_j; c7_b_k++) {
          c7_ix++;
          c7_s = muDoubleScalarAbs(c7_b_A[c7_ix]) + muDoubleScalarAbs(0.0);
          if (c7_s > c7_smax) {
            c7_idxmax = c7_b_k;
            c7_smax = c7_s;
          }
        }
      }
    }

    if (c7_b_A[(c7_c + c7_idxmax) - 1] != 0.0) {
      if (c7_idxmax - 1 != 0) {
        c7_ipiv[c7_j] = c7_j + c7_idxmax;
        c7_b_ix = c7_j;
        c7_iy = (c7_j + c7_idxmax) - 1;
        for (c7_c_k = 0; c7_c_k < 4; c7_c_k++) {
          c7_b_temp = c7_b_A[c7_b_ix];
          c7_b_A[c7_b_ix] = c7_b_A[c7_iy];
          c7_b_A[c7_iy] = c7_b_temp;
          c7_b_ix += 4;
          c7_iy += 4;
        }
      }

      c7_b = (c7_c - c7_j) + 4;
      c7_b_overflow = ((!(c7_c + 2 > c7_b)) && (c7_b > 2147483646));
      if (c7_b_overflow) {
        c7_check_forloop_overflow_error(chartInstance, c7_b_overflow);
      }

      for (c7_i = c7_c + 1; c7_i + 1 <= c7_b; c7_i++) {
        c7_b_A[c7_i] /= c7_b_A[c7_c];
      }
    } else {
      c7_info = c7_j + 1;
    }

    c7_jA = c7_c + 6;
    c7_jy = c7_c + 4;
    c7_c_overflow = ((!(1 > 3 - c7_j)) && (3 - c7_j > 2147483646));
    if (c7_c_overflow) {
      c7_check_forloop_overflow_error(chartInstance, c7_c_overflow);
    }

    for (c7_b_j = 1; c7_b_j <= 3 - c7_j; c7_b_j++) {
      c7_yjy = c7_b_A[c7_jy];
      if (c7_b_A[c7_jy] != 0.0) {
        c7_c_ix = c7_c;
        c7_b_b = (c7_jA - c7_j) + 2;
        c7_e_overflow = ((!(c7_jA > c7_b_b)) && (c7_b_b > 2147483646));
        if (c7_e_overflow) {
          c7_check_forloop_overflow_error(chartInstance, c7_e_overflow);
        }

        for (c7_ijA = c7_jA - 1; c7_ijA + 1 <= c7_b_b; c7_ijA++) {
          c7_b_A[c7_ijA] += c7_b_A[c7_c_ix + 1] * -c7_yjy;
          c7_c_ix++;
        }
      }

      c7_jy += 4;
      c7_jA += 4;
    }
  }

  if (((real_T)c7_info == 0.0) && (!(c7_b_A[15] != 0.0))) {
    c7_info = 4;
  }

  if ((real_T)c7_info > 0.0) {
    c7_warning(chartInstance);
  }

  for (c7_xi = 0; c7_xi < 3; c7_xi++) {
    if (c7_ipiv[c7_xi] != c7_xi + 1) {
      c7_temp = c7_B[c7_xi];
      c7_B[c7_xi] = c7_B[c7_ipiv[c7_xi] - 1];
      c7_B[c7_ipiv[c7_xi] - 1] = c7_temp;
    }
  }

  for (c7_k = 0; c7_k < 4; c7_k++) {
    c7_kAcol = (c7_k << 2) - 1;
    if (c7_B[c7_k] != 0.0) {
      for (c7_b_i = c7_k + 1; c7_b_i + 1 < 5; c7_b_i++) {
        c7_B[c7_b_i] -= c7_B[c7_k] * c7_b_A[(c7_b_i + c7_kAcol) + 1];
      }
    }
  }

  for (c7_d_k = 3; c7_d_k > -1; c7_d_k--) {
    c7_b_kAcol = c7_d_k << 2;
    if (c7_B[c7_d_k] != 0.0) {
      c7_B[c7_d_k] /= c7_b_A[c7_d_k + c7_b_kAcol];
      c7_d_overflow = ((!(1 > c7_d_k)) && (c7_d_k > 2147483646));
      if (c7_d_overflow) {
        c7_check_forloop_overflow_error(chartInstance, c7_d_overflow);
      }

      for (c7_c_i = 0; c7_c_i + 1 <= c7_d_k; c7_c_i++) {
        c7_B[c7_c_i] -= c7_B[c7_d_k] * c7_b_A[c7_c_i + c7_b_kAcol];
      }
    }
  }
}

static void init_dsm_address_info(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc7_NLGC_2InstanceStruct *chartInstance)
{
  chartInstance->c7_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c7_f = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c7_o1 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c7_M = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c7_o2 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c7_o3 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c7_o4 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
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

void sf_c7_NLGC_2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(609604365U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1076131411U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2330206083U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1400068220U);
}

mxArray* sf_c7_NLGC_2_get_post_codegen_info(void);
mxArray *sf_c7_NLGC_2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("nGBTSuebcTyrYXnMSoxlh");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c7_NLGC_2_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c7_NLGC_2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c7_NLGC_2_jit_fallback_info(void)
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

mxArray *sf_c7_NLGC_2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c7_NLGC_2_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c7_NLGC_2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"o1\",},{M[1],M[9],T\"o2\",},{M[1],M[10],T\"o3\",},{M[1],M[11],T\"o4\",},{M[8],M[0],T\"is_active_c7_NLGC_2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_NLGC_2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_NLGC_2InstanceStruct *chartInstance = (SFc7_NLGC_2InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _NLGC_2MachineNumber_,
           7,
           1,
           1,
           0,
           9,
           0,
           0,
           0,
           0,
           0,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"f");
          _SFD_SET_DATA_PROPS(1,1,1,0,"M");
          _SFD_SET_DATA_PROPS(2,2,0,1,"o1");
          _SFD_SET_DATA_PROPS(3,2,0,1,"o2");
          _SFD_SET_DATA_PROPS(4,2,0,1,"o3");
          _SFD_SET_DATA_PROPS(5,2,0,1,"o4");
          _SFD_SET_DATA_PROPS(6,10,0,0,"Cq");
          _SFD_SET_DATA_PROPS(7,10,0,0,"Ct");
          _SFD_SET_DATA_PROPS(8,10,0,0,"d");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,225);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
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
    SFc7_NLGC_2InstanceStruct *chartInstance = (SFc7_NLGC_2InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c7_f);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c7_o1);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c7_M);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c7_o2);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c7_o3);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c7_o4);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)&chartInstance->c7_Ct);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)&chartInstance->c7_d);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)&chartInstance->c7_Cq);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s8o3LjQm1jyHiI6rlHbgwQE";
}

static void sf_opaque_initialize_c7_NLGC_2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc7_NLGC_2InstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*) chartInstanceVar);
  initialize_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c7_NLGC_2(void *chartInstanceVar)
{
  enable_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c7_NLGC_2(void *chartInstanceVar)
{
  disable_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c7_NLGC_2(void *chartInstanceVar)
{
  sf_gateway_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c7_NLGC_2(SimStruct* S)
{
  return get_sim_state_c7_NLGC_2((SFc7_NLGC_2InstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c7_NLGC_2(SimStruct* S, const mxArray *st)
{
  set_sim_state_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*)sf_get_chart_instance_ptr
    (S), st);
}

static void sf_opaque_terminate_c7_NLGC_2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_NLGC_2InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_NLGC_2_optimization_info();
    }

    finalize_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_NLGC_2((SFc7_NLGC_2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_NLGC_2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c7_NLGC_2((SFc7_NLGC_2InstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c7_NLGC_2(SimStruct *S)
{
  /* Actual parameters from chart:
     Cq Ct d
   */
  const char_T *rtParamNames[] = { "Cq", "Ct", "d" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for Cq*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for Ct*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for d*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_NLGC_2_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,7);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,7,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 7);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,7);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,7,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,7,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,7);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(761815477U));
  ssSetChecksum1(S,(533170226U));
  ssSetChecksum2(S,(43448425U));
  ssSetChecksum3(S,(2091468226U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c7_NLGC_2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c7_NLGC_2(SimStruct *S)
{
  SFc7_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc7_NLGC_2InstanceStruct *)utMalloc(sizeof
    (SFc7_NLGC_2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc7_NLGC_2InstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c7_NLGC_2;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c7_NLGC_2;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c7_NLGC_2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c7_NLGC_2;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c7_NLGC_2;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c7_NLGC_2;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c7_NLGC_2;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c7_NLGC_2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c7_NLGC_2;
  chartInstance->chartInfo.mdlStart = mdlStart_c7_NLGC_2;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c7_NLGC_2;
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
  mdl_start_c7_NLGC_2(chartInstance);
}

void c7_NLGC_2_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_NLGC_2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_NLGC_2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_NLGC_2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_NLGC_2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
