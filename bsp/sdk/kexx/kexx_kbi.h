/** @file
 *  @defgroup KBI KBI
 *  @ingroup KEXX
 *  @brief Keboard interrupts.
 */

#pragma once

/** @addtogroup KBI
  * @{ */

/** @brief Callback type for timeout event. */
typedef void (*KBICallbackFcn_t)(uint8_t pin);

typedef enum
{
    KBIEdgeFalling,
    KBIEdgeRising,
} KBIEdge_t;

typedef enum
{
    KBIModeEdgeOnly,
    KBIModeEdgeAndLevel,
} KBIMode_t;

typedef struct
{
    KBI_Type* base;
    uint32_t pin;
    KBIEdge_t edge;
} KBIPin_t;

bool KBI_init(KBI_Type* const base, const KBIMode_t mode, const KBICallbackFcn_t const callback);

void KBI_deInit(const KBI_Type* const base);

void KBI_enablePin(KBIPin_t* const pin);

void KBI_enableNVIC(KBIPin_t* const pin);
void KBI_disableNVIC(KBIPin_t* const pin);

void KBI_disablePin(KBIPin_t* const pin);

/** @} *//* end group */
