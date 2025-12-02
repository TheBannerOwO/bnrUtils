#ifndef COMMON_UTILS
#define COMMON_UTILS

/**
 * Enum for the function exit status
 *
 * @enum FuncStatus
 */
typedef enum {
  RES_SUCCESS = 0,
  RES_MEMERR,
  RES_INVALIDPARAM,
  RES_INTERNALERR,
  RES_UNKNOWN
} FuncStatus;

#endif