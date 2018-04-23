/* Include files */

#include "NLGC_2_sfun.h"
#include "c2_NLGC_2.h"
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
static const char * c2_debug_family_names[13] = { "nargin", "nargout", "J", "O",
  "R", "Od", "Odd", "Rd", "er", "eo", "kr", "ko", "moment" };

static const char * c2_b_debug_family_names[4] = { "nargin", "nargout", "x", "y"
};

/* Function Declarations */
static void initialize_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void initialize_params_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void enable_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void disable_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_NLGC_2(SFc2_NLGC_2InstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_NLGC_2(SFc2_NLGC_2InstanceStruct
  *chartInstance);
static void set_sim_state_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void sf_gateway_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void mdl_start_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void initSimStructsc2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance, const
  mxArray *c2_b_moment, const char_T *c2_identifier, real_T c2_y[3]);
static void c2_b_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_f_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_g_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_NLGC_2, const char_T *c2_identifier);
static uint8_T c2_h_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_NLGC_2InstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_NLGC_2InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_NLGC_2(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_NLGC_2 = 0U;
}

static void initialize_params_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  real_T c2_d0;
  real_T c2_d1;
  sf_mex_import_named("kr", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c2_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_kr = c2_d0;
  sf_mex_import_named("ko", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c2_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_ko = c2_d1;
}

static void enable_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_NLGC_2(SFc2_NLGC_2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_NLGC_2(SFc2_NLGC_2InstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  const mxArray *c2_c_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", *chartInstance->c2_moment, 0, 0U, 1U,
    0U, 2, 3, 1), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_NLGC_2;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[3];
  int32_T c2_i0;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "moment", c2_dv0);
  for (c2_i0 = 0; c2_i0 < 3; c2_i0++) {
    (*chartInstance->c2_moment)[c2_i0] = c2_dv0[c2_i0];
  }

  chartInstance->c2_is_active_c2_NLGC_2 = c2_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_NLGC_2");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_NLGC_2(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  int32_T c2_i1;
  int32_T c2_i2;
  int32_T c2_i3;
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  real_T c2_b_J[9];
  int32_T c2_i11;
  real_T c2_b_O[3];
  int32_T c2_i12;
  real_T c2_b_R[9];
  int32_T c2_i13;
  real_T c2_b_Od[3];
  int32_T c2_i14;
  real_T c2_b_Odd[3];
  int32_T c2_i15;
  real_T c2_b_Rd[9];
  int32_T c2_i16;
  real_T c2_b_er[3];
  real_T c2_b_kr;
  real_T c2_b_eo[3];
  real_T c2_b_ko;
  uint32_T c2_debug_family_var_map[13];
  real_T c2_nargin = 10.0;
  real_T c2_nargout = 1.0;
  real_T c2_b_moment[3];
  int32_T c2_i17;
  uint32_T c2_b_debug_family_var_map[4];
  real_T c2_x[3];
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_y[9];
  int32_T c2_i18;
  int32_T c2_i19;
  real_T c2_a[9];
  int32_T c2_i20;
  real_T c2_b[3];
  int32_T c2_i21;
  real_T c2_b_a[9];
  real_T c2_b_x[3];
  real_T c2_c_nargin = 1.0;
  real_T c2_c_nargout = 1.0;
  real_T c2_b_y[9];
  int32_T c2_i22;
  int32_T c2_i23;
  real_T c2_c_a[9];
  int32_T c2_i24;
  int32_T c2_i25;
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  real_T c2_b_b[9];
  real_T c2_c_b[9];
  int32_T c2_i29;
  real_T c2_d_b[3];
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  real_T c2_e_b[9];
  real_T c2_d_a[9];
  real_T c2_e_a;
  real_T c2_f_b[3];
  int32_T c2_i35;
  real_T c2_f_a;
  real_T c2_g_b[3];
  int32_T c2_i36;
  int32_T c2_i37;
  real_T c2_h_b[3];
  int32_T c2_i38;
  real_T c2_g_a[9];
  int32_T c2_i39;
  real_T c2_h_a[3];
  int32_T c2_i40;
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  real_T c2_i_a[9];
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  real_T c2_j_a[9];
  int32_T c2_i53;
  int32_T c2_i54;
  real_T c2_k_a[3];
  int32_T c2_i55;
  int32_T c2_i56;
  real_T c2_l_a[9];
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  real_T c2_m_a[3];
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  real_T c2_n_a[3];
  int32_T c2_i64;
  real_T c2_o_a[3];
  int32_T c2_i65;
  int32_T c2_i66;
  int32_T c2_i67;
  real_T c2_p_a[3];
  int32_T c2_i68;
  int32_T c2_i69;
  int32_T c2_i70;
  int32_T c2_i71;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i1 = 0; c2_i1 < 3; c2_i1++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_eo)[c2_i1], 7U);
  }

  for (c2_i2 = 0; c2_i2 < 3; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_er)[c2_i2], 6U);
  }

  for (c2_i3 = 0; c2_i3 < 9; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_Rd)[c2_i3], 5U);
  }

  for (c2_i4 = 0; c2_i4 < 3; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_Odd)[c2_i4], 4U);
  }

  for (c2_i5 = 0; c2_i5 < 3; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_Od)[c2_i5], 3U);
  }

  for (c2_i6 = 0; c2_i6 < 9; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_R)[c2_i6], 2U);
  }

  for (c2_i7 = 0; c2_i7 < 3; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_O)[c2_i7], 1U);
  }

  for (c2_i8 = 0; c2_i8 < 9; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_J)[c2_i8], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i9 = 0; c2_i9 < 9; c2_i9++) {
    c2_b_J[c2_i9] = (*chartInstance->c2_J)[c2_i9];
  }

  for (c2_i10 = 0; c2_i10 < 3; c2_i10++) {
    c2_b_O[c2_i10] = (*chartInstance->c2_O)[c2_i10];
  }

  for (c2_i11 = 0; c2_i11 < 9; c2_i11++) {
    c2_b_R[c2_i11] = (*chartInstance->c2_R)[c2_i11];
  }

  for (c2_i12 = 0; c2_i12 < 3; c2_i12++) {
    c2_b_Od[c2_i12] = (*chartInstance->c2_Od)[c2_i12];
  }

  for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
    c2_b_Odd[c2_i13] = (*chartInstance->c2_Odd)[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 9; c2_i14++) {
    c2_b_Rd[c2_i14] = (*chartInstance->c2_Rd)[c2_i14];
  }

  for (c2_i15 = 0; c2_i15 < 3; c2_i15++) {
    c2_b_er[c2_i15] = (*chartInstance->c2_er)[c2_i15];
  }

  for (c2_i16 = 0; c2_i16 < 3; c2_i16++) {
    c2_b_eo[c2_i16] = (*chartInstance->c2_eo)[c2_i16];
  }

  c2_b_kr = chartInstance->c2_kr;
  c2_b_ko = chartInstance->c2_ko;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_J, 2U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_O, 3U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_R, 4U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_Od, 5U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_Odd, 6U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_Rd, 7U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_er, 8U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_eo, 9U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_kr, 10U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_ko, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_moment, 12U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 2);
  for (c2_i17 = 0; c2_i17 < 3; c2_i17++) {
    c2_x[c2_i17] = c2_b_O[c2_i17];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_x, 2U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_y, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 2);
  c2_y[0] = 0.0;
  c2_y[3] = -c2_x[2];
  c2_y[6] = c2_x[1];
  c2_y[1] = c2_x[2];
  c2_y[4] = 0.0;
  c2_y[7] = -c2_x[0];
  c2_y[2] = -c2_x[1];
  c2_y[5] = c2_x[0];
  c2_y[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i18 = 0; c2_i18 < 9; c2_i18++) {
    c2_a[c2_i18] = c2_b_J[c2_i18];
  }

  for (c2_i19 = 0; c2_i19 < 3; c2_i19++) {
    c2_b[c2_i19] = c2_b_O[c2_i19];
  }

  for (c2_i20 = 0; c2_i20 < 9; c2_i20++) {
    c2_b_a[c2_i20] = c2_y[c2_i20];
  }

  for (c2_i21 = 0; c2_i21 < 3; c2_i21++) {
    c2_b_x[c2_i21] = c2_b_O[c2_i21];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargin, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargout, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_x, 2U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_y, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 2);
  c2_b_y[0] = 0.0;
  c2_b_y[3] = -c2_b_x[2];
  c2_b_y[6] = c2_b_x[1];
  c2_b_y[1] = c2_b_x[2];
  c2_b_y[4] = 0.0;
  c2_b_y[7] = -c2_b_x[0];
  c2_b_y[2] = -c2_b_x[1];
  c2_b_y[5] = c2_b_x[0];
  c2_b_y[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i22 = 0; c2_i22 < 9; c2_i22++) {
    c2_c_a[c2_i22] = c2_b_y[c2_i22];
  }

  c2_i23 = 0;
  for (c2_i24 = 0; c2_i24 < 3; c2_i24++) {
    c2_i26 = 0;
    for (c2_i27 = 0; c2_i27 < 3; c2_i27++) {
      c2_c_b[c2_i27 + c2_i23] = c2_b_R[c2_i26 + c2_i24];
      c2_i26 += 3;
    }

    c2_i23 += 3;
  }

  for (c2_i25 = 0; c2_i25 < 9; c2_i25++) {
    c2_b_b[c2_i25] = c2_b_Rd[c2_i25];
  }

  for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
    c2_d_b[c2_i28] = c2_b_Od[c2_i28];
  }

  c2_i29 = 0;
  for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
    c2_i32 = 0;
    for (c2_i33 = 0; c2_i33 < 3; c2_i33++) {
      c2_d_a[c2_i33 + c2_i29] = c2_b_R[c2_i32 + c2_i30];
      c2_i32 += 3;
    }

    c2_i29 += 3;
  }

  for (c2_i31 = 0; c2_i31 < 9; c2_i31++) {
    c2_e_b[c2_i31] = c2_b_Rd[c2_i31];
  }

  for (c2_i34 = 0; c2_i34 < 3; c2_i34++) {
    c2_f_b[c2_i34] = c2_b_Odd[c2_i34];
  }

  c2_e_a = c2_b_kr;
  for (c2_i35 = 0; c2_i35 < 3; c2_i35++) {
    c2_g_b[c2_i35] = c2_b_er[c2_i35];
  }

  c2_f_a = c2_b_ko;
  for (c2_i36 = 0; c2_i36 < 3; c2_i36++) {
    c2_h_b[c2_i36] = c2_b_eo[c2_i36];
  }

  for (c2_i37 = 0; c2_i37 < 9; c2_i37++) {
    c2_g_a[c2_i37] = c2_b_J[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 3; c2_i38++) {
    c2_h_a[c2_i38] = 0.0;
    c2_i40 = 0;
    for (c2_i41 = 0; c2_i41 < 3; c2_i41++) {
      c2_h_a[c2_i38] += c2_a[c2_i40 + c2_i38] * c2_b[c2_i41];
      c2_i40 += 3;
    }
  }

  for (c2_i39 = 0; c2_i39 < 3; c2_i39++) {
    c2_i43 = 0;
    for (c2_i44 = 0; c2_i44 < 3; c2_i44++) {
      c2_i_a[c2_i43 + c2_i39] = 0.0;
      c2_i48 = 0;
      for (c2_i51 = 0; c2_i51 < 3; c2_i51++) {
        c2_i_a[c2_i43 + c2_i39] += c2_c_a[c2_i48 + c2_i39] * c2_c_b[c2_i51 +
          c2_i43];
        c2_i48 += 3;
      }

      c2_i43 += 3;
    }
  }

  for (c2_i42 = 0; c2_i42 < 3; c2_i42++) {
    c2_i46 = 0;
    for (c2_i47 = 0; c2_i47 < 3; c2_i47++) {
      c2_j_a[c2_i46 + c2_i42] = 0.0;
      c2_i53 = 0;
      for (c2_i55 = 0; c2_i55 < 3; c2_i55++) {
        c2_j_a[c2_i46 + c2_i42] += c2_i_a[c2_i53 + c2_i42] * c2_b_b[c2_i55 +
          c2_i46];
        c2_i53 += 3;
      }

      c2_i46 += 3;
    }
  }

  for (c2_i45 = 0; c2_i45 < 3; c2_i45++) {
    c2_i50 = 0;
    for (c2_i52 = 0; c2_i52 < 3; c2_i52++) {
      c2_l_a[c2_i50 + c2_i45] = 0.0;
      c2_i58 = 0;
      for (c2_i60 = 0; c2_i60 < 3; c2_i60++) {
        c2_l_a[c2_i50 + c2_i45] += c2_d_a[c2_i58 + c2_i45] * c2_e_b[c2_i60 +
          c2_i50];
        c2_i58 += 3;
      }

      c2_i50 += 3;
    }
  }

  for (c2_i49 = 0; c2_i49 < 3; c2_i49++) {
    c2_k_a[c2_i49] = 0.0;
    c2_i56 = 0;
    for (c2_i57 = 0; c2_i57 < 3; c2_i57++) {
      c2_k_a[c2_i49] += c2_j_a[c2_i56 + c2_i49] * c2_d_b[c2_i57];
      c2_i56 += 3;
    }
  }

  for (c2_i54 = 0; c2_i54 < 3; c2_i54++) {
    c2_m_a[c2_i54] = 0.0;
    c2_i61 = 0;
    for (c2_i62 = 0; c2_i62 < 3; c2_i62++) {
      c2_m_a[c2_i54] += c2_l_a[c2_i61 + c2_i54] * c2_f_b[c2_i62];
      c2_i61 += 3;
    }
  }

  for (c2_i59 = 0; c2_i59 < 3; c2_i59++) {
    c2_n_a[c2_i59] = ((c2_k_a[c2_i59] - c2_m_a[c2_i59]) + c2_e_a * c2_g_b[c2_i59])
      + c2_f_a * c2_h_b[c2_i59];
  }

  for (c2_i63 = 0; c2_i63 < 3; c2_i63++) {
    c2_o_a[c2_i63] = 0.0;
    c2_i65 = 0;
    for (c2_i66 = 0; c2_i66 < 3; c2_i66++) {
      c2_o_a[c2_i63] += c2_b_a[c2_i65 + c2_i63] * c2_h_a[c2_i66];
      c2_i65 += 3;
    }
  }

  for (c2_i64 = 0; c2_i64 < 3; c2_i64++) {
    c2_p_a[c2_i64] = 0.0;
    c2_i68 = 0;
    for (c2_i69 = 0; c2_i69 < 3; c2_i69++) {
      c2_p_a[c2_i64] += c2_g_a[c2_i68 + c2_i64] * c2_n_a[c2_i69];
      c2_i68 += 3;
    }
  }

  for (c2_i67 = 0; c2_i67 < 3; c2_i67++) {
    c2_b_moment[c2_i67] = c2_o_a[c2_i67] - c2_p_a[c2_i67];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i70 = 0; c2_i70 < 3; c2_i70++) {
    (*chartInstance->c2_moment)[c2_i70] = c2_b_moment[c2_i70];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_NLGC_2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i71 = 0; c2_i71 < 3; c2_i71++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_moment)[c2_i71], 8U);
  }
}

static void mdl_start_c2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc2_NLGC_2(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)(c2_machineNumber);
  (void)(c2_chartNumber);
  (void)(c2_instanceNumber);
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 0U,
    sf_debug_get_script_id(
    "C:\\Users\\hoang\\MATLAB\\Projects\\NLGControl_Quadrotor_1\\Functions\\hat.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i72;
  const mxArray *c2_y = NULL;
  real_T c2_u[3];
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i72 = 0; c2_i72 < 3; c2_i72++) {
    c2_u[c2_i72] = (*(real_T (*)[3])c2_inData)[c2_i72];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 1), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance, const
  mxArray *c2_b_moment, const char_T *c2_identifier, real_T c2_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_moment), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_moment);
}

static void c2_b_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3])
{
  real_T c2_dv1[3];
  int32_T c2_i73;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 2, 3, 1);
  for (c2_i73 = 0; c2_i73 < 3; c2_i73++) {
    c2_y[c2_i73] = c2_dv1[c2_i73];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_moment;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i74;
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_b_moment = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_moment), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_moment);
  for (c2_i74 = 0; c2_i74 < 3; c2_i74++) {
    (*(real_T (*)[3])c2_outData)[c2_i74] = c2_y[c2_i74];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_ko;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_b_ko = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_ko), &c2_thisId);
  sf_mex_destroy(&c2_b_ko);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i75;
  int32_T c2_i76;
  const mxArray *c2_y = NULL;
  int32_T c2_i77;
  real_T c2_u[9];
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i75 = 0;
  for (c2_i76 = 0; c2_i76 < 3; c2_i76++) {
    for (c2_i77 = 0; c2_i77 < 3; c2_i77++) {
      c2_u[c2_i77 + c2_i75] = (*(real_T (*)[9])c2_inData)[c2_i77 + c2_i75];
    }

    c2_i75 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9])
{
  real_T c2_dv2[9];
  int32_T c2_i78;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c2_i78 = 0; c2_i78 < 9; c2_i78++) {
    c2_y[c2_i78] = c2_dv2[c2_i78];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_y;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[9];
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_y = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
  c2_i79 = 0;
  for (c2_i80 = 0; c2_i80 < 3; c2_i80++) {
    for (c2_i81 = 0; c2_i81 < 3; c2_i81++) {
      (*(real_T (*)[9])c2_outData)[c2_i81 + c2_i79] = c2_b_y[c2_i81 + c2_i79];
    }

    c2_i79 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i82;
  const mxArray *c2_y = NULL;
  real_T c2_u[3];
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i82 = 0; c2_i82 < 3; c2_i82++) {
    c2_u[c2_i82] = (*(real_T (*)[3])c2_inData)[c2_i82];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3])
{
  real_T c2_dv3[3];
  int32_T c2_i83;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv3, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i83 = 0; c2_i83 < 3; c2_i83++) {
    c2_y[c2_i83] = c2_dv3[c2_i83];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_x;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i84;
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_x = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_x), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_x);
  for (c2_i84 = 0; c2_i84 < 3; c2_i84++) {
    (*(real_T (*)[3])c2_outData)[c2_i84] = c2_y[c2_i84];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_NLGC_2_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  const char * c2_data[4] = {
    "789cc552c14ec240101d14881e349cfc0c1ba38989274b05210144452fc66069075bedee9aed2ec1bff003fc00effe8907bfc7a505ba343635417192c9eecbdb"
    "9937333b5068b60b00b0adbca4fca50c916d292f2aafc410d660d1d27c21e39c59297a1dc7e9fcebf4741815381631087c8a1d4906c815a036c1791a97119fda",
    "54f49e9f1038862c18a11b31433fc09e4fb0c534d0f01520758d9a830935b95b1e3a8f979200f7c2a4dc4007a0cde74eeb1fb4fe8bdfcc47e7d3969e4ffa5d9e"
    "5e39472fef3f36614387c7cbf637cbbf9ea15799329e1dfff16fe9955338d18b1997c9418089dedb927a8d4cbd45fea6766b1d195721f2d0f0984def8db6d96b",
    "9955a3cbd9033a22343aad534b2d3d6741ff5cda2e6782f1fe9e5197d4113ea32acc16bb64857bf071f1fe69ae78ef56bde7ffa637cec8f7d3bddbc9d0aba4f8"
    "83ba27897486cdfd5a939e8d3b55f7f0da3949eae8e6e8e4d50119f8aff37f01886b5cf6",
    "" };

  c2_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c2_data, 1704U, &c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_f_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i85;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i85, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i85;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_NLGC_2, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_NLGC_2), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_NLGC_2);
  return c2_y;
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_NLGC_2InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_NLGC_2InstanceStruct *chartInstance)
{
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_J = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_moment = (real_T (*)[3])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_O = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_R = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_Od = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_Odd = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_Rd = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_er = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c2_eo = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
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

void sf_c2_NLGC_2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3177421748U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2528721294U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(955168098U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2651864308U);
}

mxArray* sf_c2_NLGC_2_get_post_codegen_info(void);
mxArray *sf_c2_NLGC_2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("1gLK9XvuPTaVHosO9fZA5F");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

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
      pr[1] = (double)(3);
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
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
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
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
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
    mxArray* mxPostCodegenInfo = sf_c2_NLGC_2_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_NLGC_2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_NLGC_2_jit_fallback_info(void)
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

mxArray *sf_c2_NLGC_2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_NLGC_2_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c2_NLGC_2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"moment\",},{M[8],M[0],T\"is_active_c2_NLGC_2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_NLGC_2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_NLGC_2InstanceStruct *chartInstance = (SFc2_NLGC_2InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _NLGC_2MachineNumber_,
           2,
           1,
           1,
           0,
           11,
           0,
           0,
           0,
           0,
           1,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"J");
          _SFD_SET_DATA_PROPS(1,1,1,0,"O");
          _SFD_SET_DATA_PROPS(2,1,1,0,"R");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Od");
          _SFD_SET_DATA_PROPS(4,1,1,0,"Odd");
          _SFD_SET_DATA_PROPS(5,1,1,0,"Rd");
          _SFD_SET_DATA_PROPS(6,1,1,0,"er");
          _SFD_SET_DATA_PROPS(7,1,1,0,"eo");
          _SFD_SET_DATA_PROPS(8,2,0,1,"moment");
          _SFD_SET_DATA_PROPS(9,10,0,0,"ko");
          _SFD_SET_DATA_PROPS(10,10,0,0,"kr");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,133);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"hat",0,-1,77);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 1U;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
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
    SFc2_NLGC_2InstanceStruct *chartInstance = (SFc2_NLGC_2InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c2_J);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c2_moment);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c2_O);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c2_R);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c2_Od);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c2_Odd);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c2_Rd);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c2_er);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c2_eo);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)&chartInstance->c2_kr);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)&chartInstance->c2_ko);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sCkxQ5dK5myrCpsaY4JNb9";
}

static void sf_opaque_initialize_c2_NLGC_2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_NLGC_2InstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*) chartInstanceVar);
  initialize_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_NLGC_2(void *chartInstanceVar)
{
  enable_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_NLGC_2(void *chartInstanceVar)
{
  disable_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_NLGC_2(void *chartInstanceVar)
{
  sf_gateway_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_NLGC_2(SimStruct* S)
{
  return get_sim_state_c2_NLGC_2((SFc2_NLGC_2InstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_NLGC_2(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*)sf_get_chart_instance_ptr
    (S), st);
}

static void sf_opaque_terminate_c2_NLGC_2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_NLGC_2InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_NLGC_2_optimization_info();
    }

    finalize_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_NLGC_2((SFc2_NLGC_2InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_NLGC_2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_NLGC_2((SFc2_NLGC_2InstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_NLGC_2(SimStruct *S)
{
  /* Actual parameters from chart:
     ko kr
   */
  const char_T *rtParamNames[] = { "ko", "kr" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ko*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for kr*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  ssSetInputPortDirectFeedThrough(S, 6, 1);
  ssSetInputPortDirectFeedThrough(S, 7, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_NLGC_2_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3140384756U));
  ssSetChecksum1(S,(2778521191U));
  ssSetChecksum2(S,(3556249847U));
  ssSetChecksum3(S,(1330233193U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_NLGC_2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_NLGC_2(SimStruct *S)
{
  SFc2_NLGC_2InstanceStruct *chartInstance;
  chartInstance = (SFc2_NLGC_2InstanceStruct *)utMalloc(sizeof
    (SFc2_NLGC_2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_NLGC_2InstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_NLGC_2;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_NLGC_2;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_NLGC_2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_NLGC_2;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_NLGC_2;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_NLGC_2;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_NLGC_2;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_NLGC_2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_NLGC_2;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_NLGC_2;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_NLGC_2;
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
  mdl_start_c2_NLGC_2(chartInstance);
}

void c2_NLGC_2_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_NLGC_2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_NLGC_2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_NLGC_2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_NLGC_2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
