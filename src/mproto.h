#ifndef MAD_PROTO_H_
#define MAD_PROTO_H_
/* Old-style (no pragma) protection used for compatibility */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

/* Define number of possible units */
/* When initialized more than this number - _init() returns NULL */
/* Don`t use more than you plan to use */
#define MADPROTO_CONTEXT_COUNT  2

/* Define maximum count of command to be registered */
/* Don`t limit sending */
#define MADPROTO_MAX_COMMANDS   20

#define MADPROTO_INPUT_BUFFER   100

/* Type for definition of time */
#define MAX_TIME_VALUE  UINT32_MAX
typedef uint32_t    mptime_t;
typedef uint8_t     mpcmd_t;
typedef void *      mproto_ctx_t;

typedef enum {
    MPROTO_SPIN_NO_DATA = 0,
    MPROTO_SPIN_TIMEOUT = 1
} mproto_spin_result_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mproto_cmd_cb_t)(mpcmd_t cmd, uint8_t *data, size_t len);

typedef struct
{
    /* Each field must be set or undefined behaviour */
    
    /* returns -1 if no data, [0;255] - has data */
    int16_t (*get_byte)(void);
    void (*put_byte)(uint8_t);
    mptime_t (*get_time)(void);

} mproto_func_ctx_t;

mproto_ctx_t mproto_init(mproto_func_ctx_t *func_ctx);
mproto_spin_result_t mproto_spin(mproto_ctx_t ctx, mptime_t spin_max_time);

void mproto_register_command(mproto_ctx_t ctx, mpcmd_t cmd, mproto_cmd_cb_t cb);

void mproto_send_data(mproto_ctx_t ctx, mpcmd_t cmd, uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif // MAD_PROTO_H_
