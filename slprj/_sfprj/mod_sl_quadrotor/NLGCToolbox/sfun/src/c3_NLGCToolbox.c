/* Include files */

#include "NLGCToolbox_sfun.h"
#include "c3_NLGCToolbox.h"
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
static const char * c3_debug_family_names[6] = { "nargin", "nargout", "Rd1",
  "Rd2", "Ts", "Omega" };

static const char * c3_b_debug_family_names[9] = { "nr", "nc", "one", "nargin",
  "nargout", "a", "b", "tol", "test" };

static const char * c3_c_debug_family_names[4] = { "nargin", "nargout", "R", "y"
};

static const char * c3_d_debug_family_names[10] = { "A", "term", "theta",
  "OmegaS", "nargin", "nargout", "Ri", "Rf", "Ts", "Omega" };

/* Function Declarations */
static void initialize_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance);
static void initialize_params_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance);
static void enable_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct *chartInstance);
static void disable_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_NLGCToolbox
  (SFc3_NLGCToolboxInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_NLGCToolbox
  (SFc3_NLGCToolboxInstanceStruct *chartInstance);
static void set_sim_state_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance);
static void sf_gateway_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance);
static void mdl_start_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance);
static void initSimStructsc3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance);
static boolean_T c3_isalmost(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  real_T c3_a, real_T c3_b, real_T c3_tol);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_b_Omega, const char_T *c3_identifier, real_T c3_y[3]);
static void c3_b_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_c_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static boolean_T c3_d_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_e_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3]);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_f_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[9]);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_error(SFc3_NLGCToolboxInstanceStruct *chartInstance);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_g_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_h_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_NLGCToolbox, const char_T
  *c3_identifier);
static uint8_T c3_i_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_NLGCToolboxInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc3_NLGCToolboxInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc3_NLGCToolbox(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_is_active_c3_NLGCToolbox = 0U;
}

static void initialize_params_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance)
{
  real_T c3_d0;
  sf_mex_import_named("Ts", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c3_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Ts = c3_d0;
}

static void enable_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_NLGCToolbox
  (SFc3_NLGCToolboxInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c3_NLGCToolbox
  (SFc3_NLGCToolboxInstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  const mxArray *c3_b_y = NULL;
  uint8_T c3_hoistedGlobal;
  const mxArray *c3_c_y = NULL;
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(2, 1), false);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", *chartInstance->c3_Omega, 0, 0U, 1U,
    0U, 2, 3, 1), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_NLGCToolbox;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[3];
  int32_T c3_i0;
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                      "Omega", c3_dv0);
  for (c3_i0 = 0; c3_i0 < 3; c3_i0++) {
    (*chartInstance->c3_Omega)[c3_i0] = c3_dv0[c3_i0];
  }

  chartInstance->c3_is_active_c3_NLGCToolbox = c3_h_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
     "is_active_c3_NLGCToolbox");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_NLGCToolbox(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance)
{
  int32_T c3_i1;
  int32_T c3_i2;
  int32_T c3_i3;
  int32_T c3_i4;
  real_T c3_b_Rd1[9];
  real_T c3_b_Ts;
  real_T c3_b_Rd2[9];
  uint32_T c3_debug_family_var_map[6];
  real_T c3_nargin = 3.0;
  real_T c3_nargout = 1.0;
  real_T c3_b_Omega[3];
  int32_T c3_i5;
  int32_T c3_i6;
  real_T c3_Ri[9];
  real_T c3_c_Ts;
  real_T c3_Rf[9];
  uint32_T c3_b_debug_family_var_map[10];
  real_T c3_A[9];
  real_T c3_term;
  real_T c3_theta;
  real_T c3_OmegaS[9];
  real_T c3_b_nargin = 3.0;
  real_T c3_b_nargout = 1.0;
  real_T c3_c_Omega[3];
  int32_T c3_i7;
  int32_T c3_i8;
  real_T c3_a[9];
  int32_T c3_i9;
  int32_T c3_i10;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  real_T c3_b[9];
  int32_T c3_i14;
  int32_T c3_i15;
  int32_T c3_i16;
  real_T c3_t;
  int32_T c3_k;
  int32_T c3_i17;
  int32_T c3_b_k;
  int32_T c3_i18;
  real_T c3_x;
  real_T c3_b_x;
  boolean_T c3_p;
  real_T c3_c_x;
  real_T c3_d_x;
  real_T c3_B;
  int32_T c3_i19;
  real_T c3_e_x;
  real_T c3_b_A;
  real_T c3_y;
  int32_T c3_i20;
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_i23;
  int32_T c3_i24;
  int32_T c3_i25;
  int32_T c3_i26;
  int32_T c3_i27;
  uint32_T c3_c_debug_family_var_map[4];
  real_T c3_R[9];
  real_T c3_c_nargin = 1.0;
  real_T c3_c_nargout = 1.0;
  int32_T c3_i28;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  for (c3_i1 = 0; c3_i1 < 9; c3_i1++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_Rd2)[c3_i1], 1U);
  }

  for (c3_i2 = 0; c3_i2 < 9; c3_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_Rd1)[c3_i2], 0U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  for (c3_i3 = 0; c3_i3 < 9; c3_i3++) {
    c3_b_Rd1[c3_i3] = (*chartInstance->c3_Rd1)[c3_i3];
  }

  for (c3_i4 = 0; c3_i4 < 9; c3_i4++) {
    c3_b_Rd2[c3_i4] = (*chartInstance->c3_Rd2)[c3_i4];
  }

  c3_b_Ts = chartInstance->c3_Ts;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_Rd1, 2U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_Rd2, 3U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_Ts, 4U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_Omega, 5U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 2);
  for (c3_i5 = 0; c3_i5 < 9; c3_i5++) {
    c3_Ri[c3_i5] = c3_b_Rd1[c3_i5];
  }

  for (c3_i6 = 0; c3_i6 < 9; c3_i6++) {
    c3_Rf[c3_i6] = c3_b_Rd2[c3_i6];
  }

  c3_c_Ts = c3_b_Ts;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c3_d_debug_family_names,
    c3_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_A, 0U, c3_c_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_term, 1U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_theta, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_OmegaS, 3U, c3_c_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 4U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 5U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_Ri, 6U, c3_c_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_Rf, 7U, c3_c_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_Ts, 8U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_c_Omega, 9U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 4);
  for (c3_i7 = 0; c3_i7 < 9; c3_i7++) {
    c3_a[c3_i7] = c3_Rf[c3_i7];
  }

  c3_i8 = 0;
  for (c3_i9 = 0; c3_i9 < 3; c3_i9++) {
    c3_i11 = 0;
    for (c3_i12 = 0; c3_i12 < 3; c3_i12++) {
      c3_b[c3_i12 + c3_i8] = c3_Ri[c3_i11 + c3_i9];
      c3_i11 += 3;
    }

    c3_i8 += 3;
  }

  for (c3_i10 = 0; c3_i10 < 9; c3_i10++) {
    c3_A[c3_i10] = 0.0;
  }

  for (c3_i13 = 0; c3_i13 < 3; c3_i13++) {
    c3_i14 = 0;
    for (c3_i16 = 0; c3_i16 < 3; c3_i16++) {
      c3_A[c3_i14 + c3_i13] = 0.0;
      c3_i17 = 0;
      for (c3_i18 = 0; c3_i18 < 3; c3_i18++) {
        c3_A[c3_i14 + c3_i13] += c3_a[c3_i17 + c3_i13] * c3_b[c3_i18 + c3_i14];
        c3_i17 += 3;
      }

      c3_i14 += 3;
    }
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 5);
  for (c3_i15 = 0; c3_i15 < 9; c3_i15++) {
    c3_a[c3_i15] = c3_A[c3_i15];
  }

  c3_t = 0.0;
  c3_k = 0;
  for (c3_b_k = 0; c3_b_k < 3; c3_b_k++) {
    c3_t += c3_a[c3_k];
    c3_k += 4;
  }

  c3_term = (c3_t - 1.0) / 2.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 6);
  if (CV_SCRIPT_IF(0, 0, c3_isalmost(chartInstance, c3_term, 1.0, 1.0E-5))) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 7);
    c3_term = 1.0;
  } else {
    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 8);
    if (CV_SCRIPT_IF(0, 1, c3_isalmost(chartInstance, c3_term, -1.0, 1.0E-5))) {
      _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 9);
      c3_term = -1.0;
    }
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 11);
  c3_x = c3_term;
  c3_theta = c3_x;
  c3_b_x = c3_theta;
  c3_p = ((c3_b_x < -1.0) || (c3_b_x > 1.0));
  if (c3_p) {
    c3_error(chartInstance);
  }

  c3_c_x = c3_theta;
  c3_theta = c3_c_x;
  c3_d_x = c3_theta;
  c3_theta = c3_d_x;
  c3_theta = muDoubleScalarAcos(c3_theta);
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 12);
  if (CV_SCRIPT_IF(0, 2, c3_isalmost(chartInstance, c3_theta, 0.0, 1.0E-5))) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 13);
    for (c3_i19 = 0; c3_i19 < 3; c3_i19++) {
      c3_c_Omega[c3_i19] = 0.0;
    }
  } else {
    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 15);
    c3_B = 2.0 * c3_c_Ts;
    c3_e_x = c3_theta;
    c3_b_A = 1.0 / c3_B * c3_theta;
    c3_y = c3_b_A / muDoubleScalarSin(c3_e_x);
    c3_i20 = 0;
    for (c3_i21 = 0; c3_i21 < 3; c3_i21++) {
      c3_i24 = 0;
      for (c3_i25 = 0; c3_i25 < 3; c3_i25++) {
        c3_b[c3_i25 + c3_i20] = c3_A[c3_i25 + c3_i20] - c3_A[c3_i24 + c3_i21];
        c3_i24 += 3;
      }

      c3_i20 += 3;
    }

    for (c3_i23 = 0; c3_i23 < 9; c3_i23++) {
      c3_OmegaS[c3_i23] = c3_y * c3_b[c3_i23];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 16);
    for (c3_i27 = 0; c3_i27 < 9; c3_i27++) {
      c3_R[c3_i27] = c3_OmegaS[c3_i27];
    }

    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c3_c_debug_family_names,
      c3_c_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargin, 0U, c3_b_sf_marshallOut,
      c3_b_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargout, 1U, c3_b_sf_marshallOut,
      c3_b_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_R, 2U, c3_c_sf_marshallOut,
      c3_e_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_c_Omega, 3U, c3_e_sf_marshallOut,
      c3_d_sf_marshallIn);
    CV_SCRIPT_FCN(2, 0);
    _SFD_SCRIPT_CALL(2U, chartInstance->c3_sfEvent, 2);
    c3_c_Omega[0] = c3_R[5];
    c3_c_Omega[1] = c3_R[6];
    c3_c_Omega[2] = c3_R[1];
    _SFD_SCRIPT_CALL(2U, chartInstance->c3_sfEvent, -2);
    _SFD_SYMBOL_SCOPE_POP();
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, -16);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i22 = 0; c3_i22 < 3; c3_i22++) {
    c3_b_Omega[c3_i22] = c3_c_Omega[c3_i22];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i26 = 0; c3_i26 < 3; c3_i26++) {
    (*chartInstance->c3_Omega)[c3_i26] = c3_b_Omega[c3_i26];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_NLGCToolboxMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c3_i28 = 0; c3_i28 < 3; c3_i28++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_Omega)[c3_i28], 2U);
  }
}

static void mdl_start_c3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc3_NLGCToolbox(SFc3_NLGCToolboxInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static boolean_T c3_isalmost(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  real_T c3_a, real_T c3_b, real_T c3_tol)
{
  boolean_T c3_test;
  uint32_T c3_debug_family_var_map[9];
  real_T c3_nr;
  real_T c3_nc;
  real_T c3_one;
  real_T c3_nargin = 3.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_y;
  boolean_T c3_b0;
  boolean_T c3_b1;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c3_b_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nr, 0U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nc, 1U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_one, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 3U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 4U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_a, 5U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b, 6U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_tol, 7U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_test, 8U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 33);
  c3_nr = 1.0;
  c3_nc = 1.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 36);
  c3_y = true;
  CV_SCRIPT_IF(1, 0, CV_SCRIPT_MCDC(1, 0, !CV_SCRIPT_COND(1, 0, c3_y)));
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 45);
  c3_one = 1.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 48);
  c3_b0 = (c3_a <= c3_b + c3_tol * c3_one);
  c3_b1 = (c3_a >= c3_b - c3_tol * c3_one);
  c3_test = (c3_b0 && c3_b1);
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, -48);
  _SFD_SYMBOL_SCOPE_POP();
  return c3_test;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)(c3_machineNumber);
  (void)(c3_chartNumber);
  (void)(c3_instanceNumber);
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, c3_instanceNumber, 0U,
    sf_debug_get_script_id(
    "C:\\Users\\hoang\\Documents\\MATLAB\\NLGControl_Quadrotor_1\\Functions\\rr2ar.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, c3_instanceNumber, 1U,
    sf_debug_get_script_id(
    "C:\\Users\\hoang\\Documents\\MATLAB\\NLGControl_Quadrotor_1\\Functions\\isalmost.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, c3_instanceNumber, 2U,
    sf_debug_get_script_id(
    "C:\\Users\\hoang\\Documents\\MATLAB\\NLGControl_Quadrotor_1\\Functions\\vee.m"));
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i29;
  const mxArray *c3_y = NULL;
  real_T c3_u[3];
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  for (c3_i29 = 0; c3_i29 < 3; c3_i29++) {
    c3_u[c3_i29] = (*(real_T (*)[3])c3_inData)[c3_i29];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 1), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_b_Omega, const char_T *c3_identifier, real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Omega), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_Omega);
}

static void c3_b_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3])
{
  real_T c3_dv1[3];
  int32_T c3_i30;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv1, 1, 0, 0U, 1, 0U, 2, 3, 1);
  for (c3_i30 = 0; c3_i30 < 3; c3_i30++) {
    c3_y[c3_i30] = c3_dv1[c3_i30];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_Omega;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i31;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_b_Omega = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Omega), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_Omega);
  for (c3_i31 = 0; c3_i31 < 3; c3_i31++) {
    (*(real_T (*)[3])c3_outData)[c3_i31] = c3_y[c3_i31];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_c_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d1;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d1, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_Ts;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_b_Ts = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Ts), &c3_thisId);
  sf_mex_destroy(&c3_b_Ts);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i32;
  int32_T c3_i33;
  const mxArray *c3_y = NULL;
  int32_T c3_i34;
  real_T c3_u[9];
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_i32 = 0;
  for (c3_i33 = 0; c3_i33 < 3; c3_i33++) {
    for (c3_i34 = 0; c3_i34 < 3; c3_i34++) {
      c3_u[c3_i34 + c3_i32] = (*(real_T (*)[9])c3_inData)[c3_i34 + c3_i32];
    }

    c3_i32 += 3;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static boolean_T c3_d_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b2;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b2, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b2;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_test;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_test = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_test), &c3_thisId);
  sf_mex_destroy(&c3_test);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i35;
  const mxArray *c3_y = NULL;
  real_T c3_u[3];
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  for (c3_i35 = 0; c3_i35 < 3; c3_i35++) {
    c3_u[c3_i35] = (*(real_T (*)[3])c3_inData)[c3_i35];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_e_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3])
{
  real_T c3_dv2[3];
  int32_T c3_i36;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c3_i36 = 0; c3_i36 < 3; c3_i36++) {
    c3_y[c3_i36] = c3_dv2[c3_i36];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_y;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_b_y[3];
  int32_T c3_i37;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_y = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_y), &c3_thisId, c3_b_y);
  sf_mex_destroy(&c3_y);
  for (c3_i37 = 0; c3_i37 < 3; c3_i37++) {
    (*(real_T (*)[3])c3_outData)[c3_i37] = c3_b_y[c3_i37];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_f_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[9])
{
  real_T c3_dv3[9];
  int32_T c3_i38;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv3, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c3_i38 = 0; c3_i38 < 9; c3_i38++) {
    c3_y[c3_i38] = c3_dv3[c3_i38];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_R;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[9];
  int32_T c3_i39;
  int32_T c3_i40;
  int32_T c3_i41;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_R = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_R), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_R);
  c3_i39 = 0;
  for (c3_i40 = 0; c3_i40 < 3; c3_i40++) {
    for (c3_i41 = 0; c3_i41 < 3; c3_i41++) {
      (*(real_T (*)[9])c3_outData)[c3_i41 + c3_i39] = c3_y[c3_i41 + c3_i39];
    }

    c3_i39 += 3;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_NLGCToolbox_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  const char * c3_data[6] = {
    "789ced57cd4ee25018bd3860703113320b635cb99cd554083ac11558010dd08c081a638c96f62a85fb33dcb6447c161fc28571ed53f83cd3d216da263735b1e9"
    "4c136e42be1e4efb9ddb8fd3d30032279d0c00e09bf5b1ebed77305f5f9d020a6e5d03c115e6336efd12c2deca816ce03a8f7f72ab4289011f0c07208d40c9c4",
    "03c82c40640c176d548a352213a337fb0301833a4553a8ce993b0dc19e86619bfac0b16601dcf0510b6053f6b13884caf8ccc4800df5e576911f00ff7c38f79f"
    "8d984f7885e7133e2f4a6f3d422fc3a9deda00793fac7ef6febcfe398e5ec165182bc9f6af1a97de7a082ff51c46a5e600c1a5def327f55a5cbd207f55bf160f",
    "84be0e992e0ca94cee8523aa98181243173ab55ebb762848eda668b99e5174736aca2aa306653745a16112c5d028d185f9ac7ee279bfe4fcf0a6f65fdf6b09fb"
    "2f69bfff33bd074ebf8ffa6f93a35708f1a3fa7e79da989d353a5db1322e9d2bb232a3c7cb7dfc8ed089da07e0e0a4faa7fd39e6f9e0a3bee3bd6737dcba15f8",
    "76abead41db7fe882deff3210c16e7398ca6cb0853dd486bde4b5cbd201f874fbc59d95649309feab99755dea73defeb930a7ebc34cb93c1185279f2ab4b5b83"
    "aeb8cafbff25ef6f39fb8bd777bbb1e53aeffd5270992974fe94a535d74fb87a413e0e3f58b372dd90a41faad2f62ad7539febf7caf05411514bda4395e6787f",
    "542a5e8cdacdf4e7fa5f9cea001d", "" };

  c3_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c3_data, 4728U, &c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_error(SFc3_NLGCToolboxInstanceStruct *chartInstance)
{
  const mxArray *c3_y = NULL;
  static char_T c3_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  const mxArray *c3_b_y = NULL;
  static char_T c3_cv1[4] = { 'a', 'c', 'o', 's' };

  (void)chartInstance;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_cv0, 10, 0U, 1U, 0U, 2, 1, 30),
                false);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_cv1, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c3_y, 14, c3_b_y));
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_g_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i42;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i42, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i42;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_h_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_NLGCToolbox, const char_T
  *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_NLGCToolbox), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_NLGCToolbox);
  return c3_y;
}

static uint8_T c3_i_emlrt_marshallIn(SFc3_NLGCToolboxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_NLGCToolboxInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc3_NLGCToolboxInstanceStruct
  *chartInstance)
{
  chartInstance->c3_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c3_Rd1 = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c3_Omega = (real_T (*)[3])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_Rd2 = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
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

void sf_c3_NLGCToolbox_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(602546824U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3849950903U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1970894778U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2205516228U);
}

mxArray* sf_c3_NLGCToolbox_get_post_codegen_info(void);
mxArray *sf_c3_NLGCToolbox_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("1qqTSt3fCcUhnatyUzpiwG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c3_NLGCToolbox_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_NLGCToolbox_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_NLGCToolbox_jit_fallback_info(void)
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

mxArray *sf_c3_NLGCToolbox_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c3_NLGCToolbox_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c3_NLGCToolbox(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"Omega\",},{M[8],M[0],T\"is_active_c3_NLGCToolbox\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_NLGCToolbox_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_NLGCToolboxInstanceStruct *chartInstance =
      (SFc3_NLGCToolboxInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _NLGCToolboxMachineNumber_,
           3,
           1,
           1,
           0,
           4,
           0,
           0,
           0,
           0,
           3,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"Rd1");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Rd2");
          _SFD_SET_DATA_PROPS(2,2,0,1,"Omega");
          _SFD_SET_DATA_PROPS(3,10,0,0,"Ts");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,79);
        _SFD_CV_INIT_SCRIPT(0,1,0,3,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"rr2ar",0,-1,988);
        _SFD_CV_INIT_SCRIPT_IF(0,0,215,240,255,285);
        _SFD_CV_INIT_SCRIPT_IF(0,1,255,285,-1,285);
        _SFD_CV_INIT_SCRIPT_IF(0,2,325,353,373,457);
        _SFD_CV_INIT_SCRIPT(1,1,0,2,0,0,0,0,0,1,1);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"isalmost",0,-1,1216);
        _SFD_CV_INIT_SCRIPT_IF(1,0,841,868,-1,1136);
        _SFD_CV_INIT_SCRIPT_IF(1,1,872,896,981,1132);

        {
          static int condStart[] = { 845 };

          static int condEnd[] = { 868 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_SCRIPT_MCDC(1,0,844,868,1,0,&(condStart[0]),&(condEnd[0]),
            2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"vee",0,-1,53);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
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
    SFc3_NLGCToolboxInstanceStruct *chartInstance =
      (SFc3_NLGCToolboxInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c3_Rd1);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c3_Omega);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c3_Rd2);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)&chartInstance->c3_Ts);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sJ9Wcf0772tDjp23SlGFWjG";
}

static void sf_opaque_initialize_c3_NLGCToolbox(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_NLGCToolboxInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*)
    chartInstanceVar);
  initialize_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_NLGCToolbox(void *chartInstanceVar)
{
  enable_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_NLGCToolbox(void *chartInstanceVar)
{
  disable_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_NLGCToolbox(void *chartInstanceVar)
{
  sf_gateway_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c3_NLGCToolbox(SimStruct* S)
{
  return get_sim_state_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c3_NLGCToolbox(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c3_NLGCToolbox(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_NLGCToolboxInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_NLGCToolbox_optimization_info();
    }

    finalize_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_NLGCToolbox(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_NLGCToolbox((SFc3_NLGCToolboxInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c3_NLGCToolbox(SimStruct *S)
{
  /* Actual parameters from chart:
     Ts
   */
  const char_T *rtParamNames[] = { "Ts" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for Ts*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_NLGCToolbox_optimization_info(sim_mode_is_rtw_gen
      (S), sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 3);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2540438079U));
  ssSetChecksum1(S,(4144313580U));
  ssSetChecksum2(S,(1050089405U));
  ssSetChecksum3(S,(457089839U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_NLGCToolbox(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_NLGCToolbox(SimStruct *S)
{
  SFc3_NLGCToolboxInstanceStruct *chartInstance;
  chartInstance = (SFc3_NLGCToolboxInstanceStruct *)utMalloc(sizeof
    (SFc3_NLGCToolboxInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc3_NLGCToolboxInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_NLGCToolbox;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_NLGCToolbox;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_NLGCToolbox;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_NLGCToolbox;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_NLGCToolbox;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_NLGCToolbox;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_NLGCToolbox;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_NLGCToolbox;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_NLGCToolbox;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_NLGCToolbox;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_NLGCToolbox;
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
  mdl_start_c3_NLGCToolbox(chartInstance);
}

void c3_NLGCToolbox_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_NLGCToolbox(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_NLGCToolbox(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_NLGCToolbox(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_NLGCToolbox_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
