#include "platform.h"

#ifdef PORT0
#undef PORT0
#define PORT0_defined
#endif
#ifdef PORT1
#undef PORT1
#define PORT1_defined
#endif
#ifdef PORT2
#undef PORT2
#define PORT2_defined
#endif
#ifdef PORT3
#undef PORT3
#define PORT3_defined
#endif
#ifdef PORT4
#undef PORT4
#define PORT4_defined
#endif
#ifdef PORT5
#undef PORT5
#define PORT5_defined
#endif
#ifdef PORT6
#undef PORT6
#define PORT6_defined
#endif
#ifdef PORT7
#undef PORT7
#define PORT7_defined
#endif
#ifdef PORT8
#undef PORT8
#define PORT8_defined
#endif
#ifdef PORT9
#undef PORT9
#define PORT9_defined
#endif
#ifdef PORTA
#undef PORTA
#define PORTA_defined
#endif
#ifdef PORTB
#undef PORTB
#define PORTB_defined
#endif
#ifdef PORTC
#undef PORTC
#define PORTC_defined
#endif
#ifdef PORTD
#undef PORTD
#define PORTD_defined
#endif
#ifdef PORTE
#undef PORTE
#define PORTE_defined
#endif
#ifdef PORTF
#undef PORTF
#define PORTF_defined
#endif
#ifdef PORTG
#undef PORTG
#define PORTG_defined
#endif
#ifdef PORTH
#undef PORTH
#define PORTH_defined
#endif
/* There are no PORTI. */
#ifdef PORTJ
#undef PORTJ
#define PORTJ_defined
#endif

#ifdef PORT0_defined
VOLATILE st_port0_t * const PORT0 = (st_port0_t *)0x8C000;
#endif
#ifdef PORT1_defined
VOLATILE st_port1_t * const PORT1 = (st_port1_t *)0x8C001;
#endif
#ifdef PORT2_defined
VOLATILE st_port2_t * const PORT2 = (st_port2_t *)0x8C002;
#endif
#ifdef PORT3_defined
VOLATILE st_port3_t * const PORT3 = (st_port3_t *)0x8C003;
#endif
#ifdef PORT4_defined
VOLATILE st_port4_t * const PORT4 = (st_port4_t *)0x8C004;
#endif
#ifdef PORT5_defined
VOLATILE st_port5_t * const PORT5 = (st_port5_t *)0x8C005;
#endif
#ifdef PORT6_defined
VOLATILE st_port6_t * const PORT6 = (st_port6_t *)0x8C006;
#endif
#ifdef PORT7_defined
VOLATILE st_port7_t * const PORT7 = (st_port7_t *)0x8C007;
#endif
#ifdef PORT8_defined
VOLATILE st_port8_t * const PORT8 = (st_port8_t *)0x8C008;
#endif
#ifdef PORT9_defined
VOLATILE st_port9_t * const PORT9 = (st_port9_t *)0x8C009;
#endif
#ifdef PORTA_defined
VOLATILE st_porta_t * const PORTA = (st_porta_t *)0x8C00A;
#endif
#ifdef PORTB_defined
VOLATILE st_portb_t * const PORTB = (st_portb_t *)0x8C00B;
#endif
#ifdef PORTC_defined
VOLATILE st_portc_t * const PORTC = (st_portc_t *)0x8C00C;
#endif
#ifdef PORTD_defined
VOLATILE st_portd_t * const PORTD = (st_portd_t *)0x8C00D;
#endif
#ifdef PORTE_defined
VOLATILE st_porte_t * const PORTE = (st_porte_t *)0x8C00E;
#endif
#ifdef PORTF_defined
VOLATILE st_portf_t * const PORTF = (st_portf_t *)0x8C00F;
#endif
#ifdef PORTG_defined
VOLATILE st_portg_t * const PORTG = (st_portg_t *)0x8C010;
#endif
#ifdef PORTH_defined
VOLATILE st_porth_t * const PORTH = (st_porth_t *)0x8C011;
#endif
/* There are no PORTI. */
#ifdef PORTJ_defined
VOLATILE st_portj_t * const PORTJ = (st_portj_t *)0x8C012;
#endif

static const void * const e2_studio_visual_expression_view_helper_v[] = 
{
#ifdef PORT0_defined
    (const void *) &PORT0,
#endif
#ifdef PORT1_defined
    (const void *) &PORT1,
#endif
#ifdef PORT2_defined
    (const void *) &PORT2,
#endif
#ifdef PORT3_defined
    (const void *) &PORT3,
#endif
#ifdef PORT4_defined
    (const void *) &PORT4,
#endif
#ifdef PORT5_defined
    (const void *) &PORT5,
#endif
#ifdef PORT6_defined
    (const void *) &PORT6,
#endif
#ifdef PORT7_defined
    (const void *) &PORT7,
#endif
#ifdef PORT8_defined
    (const void *) &PORT8,
#endif
#ifdef PORT9_defined
    (const void *) &PORT9,
#endif
#ifdef PORTA_defined
    (const void *) &PORTA,
#endif
#ifdef PORTB_defined
    (const void *) &PORTB,
#endif
#ifdef PORTC_defined
    (const void *) &PORTC,
#endif
#ifdef PORTD_defined
    (const void *) &PORTD,
#endif
#ifdef PORTE_defined
    (const void *) &PORTE,
#endif
#ifdef PORTF_defined
    (const void *) &PORTF,
#endif
#ifdef PORTG_defined
    (const void *) &PORTG,
#endif
#ifdef PORTH_defined
    (const void *) &PORTH,
#endif
/* There are no PORTI. */
#ifdef PORTJ_defined
    (const void *) &PORTJ,
#endif
    (const void *) 0
};

/* The following function is just to prevent the symbol getting optimized away
 * for e2 studio's Visual Expression View. */
void e2_studio_visual_expression_view_helper(void)
{
    void * volatile e;

    e = (void *)e2_studio_visual_expression_view_helper_v;

    INTERNAL_NOT_USED( e );
}
