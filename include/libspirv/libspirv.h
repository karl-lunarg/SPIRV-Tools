// Copyright (c) 2015 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
// KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
// SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
//    https://www.khronos.org/registry/
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.

#ifndef _CODEPLAY_SPIRV_SPIRV_H_
#define _CODEPLAY_SPIRV_SPIRV_H_

#include <headers/spirv.hpp>
#include <headers/GLSL.std.450.h>
#include <headers/OpenCLLib.h>

#ifdef __cplusplus
using namespace spv;
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

// Magic numbers

#define SPV_MAGIC_NUMBER 0x07230203
#define SPV_VERSION_NUMBER 99u

// Header indices

#define SPV_INDEX_MAGIC_NUMBER 0u
#define SPV_INDEX_VERSION_NUMBER 1u
#define SPV_INDEX_GENERATOR_NUMBER 2u
#define SPV_INDEX_BOUND 3u
#define SPV_INDEX_SCHEMA 4u
#define SPV_INDEX_INSTRUCTION 5u

// Universal limits

// NOTE: These are set to the minimum maximum values
#define SPV_LIMIT_LITERAL_NAME_MAX 0x00000400
#define SPV_LIMIT_LITERAL_STRING_MAX 0x00010000
#define SPV_LIMIT_INSTRUCTION_WORD_COUNT_MAX 0x00000108
#define SPV_LIMIT_RESULT_ID_BOUND 0x00400000
#define SPV_LIMIT_CONTROL_FLOW_NEST_DEPTH 0x00000400
#define SPV_LIMIT_GLOBAL_VARIABLES_MAX 0x00010000
#define SPV_LIMIT_LOCAL_VARIABLES_MAX 0x00080000
// TODO: Decorations per target ID max, depends on decoration table size
#define SPV_LIMIT_EXECUTION_MODE_PER_ENTRY_POINT_MAX 0x00000100
#define SPV_LIMIT_INDICIES_MAX_ACCESS_CHAIN_COMPOSITE_MAX 0x00000100
#define SPV_LIMIT_FUNCTION_PARAMETERS_PER_FUNCTION_DECL 0x00000100
#define SPV_LIMIT_FUNCTION_CALL_ARGUMENTS_MAX 0x00000100
#define SPV_LIMIT_EXT_FUNCTION_CALL_ARGUMENTS_MAX 0x00000100
#define SPV_LIMIT_SWITCH_LITERAL_LABEL_PAIRS_MAX 0x00004000
#define SPV_LIMIT_STRUCT_MEMBERS_MAX 0x0000400
#define SPV_LIMIT_STRUCT_NESTING_DEPTH_MAX 0x00000100

// Helpers

#define spvCheck(condition, action) \
  if (condition) {                  \
    action;                         \
  }

#define spvCheckReturn(expression)     \
  {                                    \
    spv_result_t error = (expression); \
    if (error) {                       \
      return error;                    \
    }                                  \
  }

#define spvIsInBitfield(value, bitfield) (value == (value & bitfield))

#define SPV_BIT(shift) (1 << (shift))

#define SPV_FORCE_16_BIT_ENUM(name) _##name = 0x7fff
#define SPV_FORCE_32_BIT_ENUM(name) _##name = 0x7fffffff

// Enumerations

typedef enum spv_generator_t {
  SPV_GENERATOR_KHRONOS = 0,
  SPV_GENERATOR_VALVE = 1,
  SPV_GENERATOR_LUNARG = 2,
  SPV_GENERATOR_CODEPLAY = 3,
  SPV_FORCE_32_BIT_ENUM(spv_generator_t)
} spv_generator_t;

typedef enum spv_result_t {
  SPV_SUCCESS = 0,
  SPV_UNSUPPORTED = 1,
  SPV_END_OF_STREAM = 2,
  SPV_WARNING = 3,
  SPV_ERROR_INTERNAL = -1,
  SPV_ERROR_OUT_OF_MEMORY = -2,
  SPV_ERROR_INVALID_POINTER = -3,
  SPV_ERROR_INVALID_BINARY = -4,
  SPV_ERROR_INVALID_TEXT = -5,
  SPV_ERROR_INVALID_TABLE = -6,
  SPV_ERROR_INVALID_VALUE = -7,
  SPV_ERROR_INVALID_DIAGNOSTIC = -8,
  SPV_ERROR_INVALID_LOOKUP = -9,
  SPV_ERROR_INVALID_ID = -10,
  SPV_FORCE_32_BIT_ENUM(spv_result_t)
} spv_result_t;

typedef enum spv_endianness_t {
  SPV_ENDIANNESS_LITTLE,
  SPV_ENDIANNESS_BIG,
  SPV_FORCE_32_BIT_ENUM(spv_endianness_t)
} spv_endianness_t;

typedef enum spv_opcode_flags_t {
  SPV_OPCODE_FLAGS_NONE = 0,
  SPV_OPCODE_FLAGS_VARIABLE = 1,
  SPV_OPCODE_FLAGS_CAPABILITIES = 2,
  SPV_FORCE_32_BIT_ENUM(spv_opcode_flags_t)
} spv_opcode_flags_t;

typedef enum spv_operand_type_t {
  SPV_OPERAND_TYPE_NONE,
  SPV_OPERAND_TYPE_ID,
  SPV_OPERAND_TYPE_RESULT_ID,
  SPV_OPERAND_TYPE_LITERAL,
  SPV_OPERAND_TYPE_LITERAL_NUMBER,
  SPV_OPERAND_TYPE_LITERAL_STRING,
  SPV_OPERAND_TYPE_SOURCE_LANGUAGE,
  SPV_OPERAND_TYPE_EXECUTION_MODEL,
  SPV_OPERAND_TYPE_ADDRESSING_MODEL,
  SPV_OPERAND_TYPE_MEMORY_MODEL,
  SPV_OPERAND_TYPE_EXECUTION_MODE,
  SPV_OPERAND_TYPE_STORAGE_CLASS,
  SPV_OPERAND_TYPE_DIMENSIONALITY,
  SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE,
  SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE,
  SPV_OPERAND_TYPE_FP_FAST_MATH_MODE,
  SPV_OPERAND_TYPE_FP_ROUNDING_MODE,
  SPV_OPERAND_TYPE_LINKAGE_TYPE,
  SPV_OPERAND_TYPE_ACCESS_QUALIFIER,
  SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE,
  SPV_OPERAND_TYPE_DECORATION,
  SPV_OPERAND_TYPE_BUILT_IN,
  SPV_OPERAND_TYPE_SELECTION_CONTROL,
  SPV_OPERAND_TYPE_LOOP_CONTROL,
  SPV_OPERAND_TYPE_FUNCTION_CONTROL,
  SPV_OPERAND_TYPE_MEMORY_SEMANTICS,
  SPV_OPERAND_TYPE_MEMORY_ACCESS,
  SPV_OPERAND_TYPE_EXECUTION_SCOPE,
  SPV_OPERAND_TYPE_GROUP_OPERATION,
  SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS,
  SPV_OPERAND_TYPE_KERENL_PROFILING_INFO,
  SPV_OPERAND_TYPE_CAPABILITY,

  SPV_OPERAND_TYPE_ELLIPSIS,  // NOTE: Unspecified variable operands
  SPV_FORCE_32_BIT_ENUM(spv_operand_type_t)
} spv_operand_type_t;

typedef enum spv_ext_inst_type_t {
  SPV_EXT_INST_TYPE_NONE,
  SPV_EXT_INST_TYPE_GLSL_STD_450,
  SPV_EXT_INST_TYPE_OPENCL_STD_12,
  SPV_EXT_INST_TYPE_OPENCL_STD_20,
  SPV_EXT_INST_TYPE_OPENCL_STD_21,

  SPV_FORCE_32_BIT_ENUM(spv_ext_inst_type_t)
} spv_ext_inst_type_t;

typedef enum spv_binary_to_text_options_t {
  SPV_BINARY_TO_TEXT_OPTION_NONE = SPV_BIT(0),
  SPV_BINARY_TO_TEXT_OPTION_PRINT = SPV_BIT(1),
  SPV_BINARY_TO_TEXT_OPTION_COLOR = SPV_BIT(2),
  SPV_FORCE_32_BIT_ENUM(spv_binary_to_text_options_t)
} spv_binary_to_text_options_t;

typedef enum spv_validate_options_t {
  SPV_VALIDATE_BASIC_BIT = SPV_BIT(0),
  SPV_VALIDATE_LAYOUT_BIT = SPV_BIT(1),
  SPV_VALIDATE_ID_BIT = SPV_BIT(2),
  SPV_VALIDATE_RULES_BIT = SPV_BIT(3),
  SPV_VALIDATE_ALL = SPV_VALIDATE_BASIC_BIT | SPV_VALIDATE_LAYOUT_BIT |
                     SPV_VALIDATE_ID_BIT | SPV_VALIDATE_RULES_BIT,
  SPV_FORCE_32_BIT_ENUM(spv_validation_options_t)
} spv_validate_options_t;

// Structures

typedef struct spv_header_t {
  uint32_t magic;
  uint32_t version;
  uint32_t generator;
  uint32_t bound;
  uint32_t schema;               // NOTE: Reserved
  const uint32_t *instructions;  // NOTE: Unfixed pointer to instruciton stream
} spv_header_t;

typedef struct spv_opcode_desc_t {
  const char *name;
  const uint16_t wordCount;
  const Op opcode;
  const uint32_t flags;                       // Bitfield of spv_opcode_flags_t
  const uint32_t capabilities;                // spv_language_capabilities_t
  const spv_operand_type_t operandTypes[16];  // TODO: Smaller/larger?
} spv_opcode_desc_t;

typedef struct spv_opcode_table_t {
  const uint32_t count;
  const spv_opcode_desc_t *entries;
} spv_opcode_table_t;

typedef struct spv_operand_desc_t {
  const char *name;
  const uint32_t value;
  const uint32_t flags;                       // Bitfield of spv_opcode_flags_t
  const uint32_t capabilities;                // spv_language_capabilities_t
  const spv_operand_type_t operandTypes[16];  // TODO: Smaller/larger?
} spv_operand_desc_t;

typedef struct spv_operand_desc_group_t {
  const spv_operand_type_t type;
  const uint32_t count;
  const spv_operand_desc_t *entries;
} spv_operand_desc_group_t;

typedef struct spv_operand_table_t {
  const uint32_t count;
  const spv_operand_desc_group_t *types;
} spv_operand_table_t;

typedef struct spv_ext_inst_desc_t {
  const char *name;
  const uint32_t ext_inst;
  const spv_operand_type_t operandTypes[16];  // TODO: Smaller/larger?
} spv_ext_inst_desc_t;

typedef struct spv_ext_inst_group_t {
  const spv_ext_inst_type_t type;
  const uint32_t count;
  const spv_ext_inst_desc_t *entries;
} spv_ext_inst_group_t;

typedef struct spv_ext_inst_table_t {
  const uint32_t count;
  const spv_ext_inst_group_t *groups;
} spv_ext_inst_table_t;

typedef struct spv_binary_t {
  uint32_t *code;
  uint64_t wordCount;
} spv_binary_t;

typedef struct spv_text_t {
  const char *str;
  uint64_t length;
} spv_text_t;

typedef struct spv_instruction_t {
  uint16_t wordCount;
  Op opcode;
  spv_ext_inst_type_t extInstType;
  uint32_t words[SPV_LIMIT_INSTRUCTION_WORD_COUNT_MAX];
} spv_instruction_t;

typedef struct spv_position_t {
  uint64_t line;
  uint64_t column;
  uint64_t index;
} spv_position_t;

typedef struct spv_diagnostic_t {
  spv_position_t position;
  char *error;
} spv_diagnostic_t;

// Type Definitions

typedef const spv_opcode_desc_t *spv_opcode_desc;
typedef const spv_opcode_table_t *spv_opcode_table;
typedef const spv_operand_desc_t *spv_operand_desc;
typedef const spv_operand_table_t *spv_operand_table;
typedef const spv_ext_inst_desc_t *spv_ext_inst_desc;
typedef const spv_ext_inst_table_t *spv_ext_inst_table;
typedef spv_binary_t *spv_binary;
typedef spv_text_t *spv_text;
typedef spv_position_t *spv_position;
typedef spv_diagnostic_t *spv_diagnostic;

// Platform API

// Opcode API

/// @brief Populate the Opcode table
///
/// @param[out] pOpcodeTable table to be populated
///
/// @return result code
spv_result_t spvOpcodeTableGet(spv_opcode_table *pOpcodeTable);

/// @brief Populate the operand table
///
/// @param[in] pOperandTable table to be populated
///
/// @return result code
spv_result_t spvOperandTableGet(spv_operand_table *pOperandTable);

/// @brief Populate the extended instruction table
///
/// @param pTable table to be populated
///
/// @return result code
spv_result_t spvExtInstTableGet(spv_ext_inst_table *pTable);

// Text API

/// @brief Entry point to covert text form to binary form
///
/// @param[in] text input text
/// @param[in] opcodeTable of specified Opcodes
/// @param[in] operandTable of specified operands
/// @param[in] extInstTable of specified extended instructions
/// @param[out] pBinary the binary module
/// @param[out] pDiagnostic contains diagnostic on failure
///
/// @return result code
spv_result_t spvTextToBinary(const spv_text text,
                             const spv_opcode_table opcodeTable,
                             const spv_operand_table operandTable,
                             const spv_ext_inst_table extInstTable,
                             spv_binary *pBinary, spv_diagnostic *pDiagnostic);

/// @brief Free an allocated text stream
///
/// @param text the text object to be destored
void spvTextDestroy(spv_text text);

// Binary API

/// @brief Entry point to convert binary to text form
///
/// @param[in] binary the input binary stream
/// @param[in] options bitfield of spv_binary_to_text_options_t values
/// @param[in] opcodeTable table of specified Opcodes
/// @param[in] operandTable table of specified operands
/// @param[in] extInstTable of specified extended instructions
/// @param[out] pText the textual form
/// @param[out] pDiagnostic contains diagnostic on failure
///
/// @return result code
spv_result_t spvBinaryToText(const spv_binary binary, const uint32_t options,
                             const spv_opcode_table opcodeTable,
                             const spv_operand_table operandTable,
                             const spv_ext_inst_table extInstTable,
                             spv_text *pText, spv_diagnostic *pDiagnostic);

/// @brief Free a binary stream from memory
///
/// @param binary stream to destroy
void spvBinaryDestroy(spv_binary binary);

// Validation API

/// @brief Validate a SPIR-V binary for correctness
///
/// @param[in] binary the input binary stream
/// @param[in] opcodeTable table of specified Opcodes
/// @param[in] operandTable table of specified operands
/// @param[in] extInstTable of specified extended instructions
/// @param[in] options bitfield of spv_validation_options_t
/// @param[out] pDiagnostic contains diagnostic on failure
///
/// @return result code
spv_result_t spvValidate(const spv_binary binary,
                         const spv_opcode_table opcodeTable,
                         const spv_operand_table operandTable,
                         const spv_ext_inst_table extInstTable,
                         const uint32_t options, spv_diagnostic *pDiagnostic);

// Diagnostic API

/// @brief Create a diagnostic object
///
/// @param position position in the text or binary stream
/// @param message error message to display, is copied
///
/// @return the diagnostic object
spv_diagnostic spvDiagnosticCreate(const spv_position position,
                                   const char *message);

/// @brief Destroy a diagnostic object
///
/// @param diagnostic object to destory
void spvDiagnosticDestroy(spv_diagnostic diagnostic);

/// @brief Print the diagnostic to stderr
///
/// @param[in] diagnostic to print
///
/// @return result code
spv_result_t spvDiagnosticPrint(const spv_diagnostic diagnostic);

#ifdef __cplusplus
}
#endif

#endif