/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * See LICENSE.txt included in this distribution for the specific
 * language governing permissions and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at LICENSE.txt.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Portions Copyright 2009 Matt Ingenthron
 */
#ifndef _METRICS_H
#define _METRICS_H

#include <sys/time.h>
#include <stdint.h>
#include "config.h"

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef HAVE_GETHRTIME
typedef uint64_t hrtime_t;
extern hrtime_t gethrtime();
#endif

enum TxnType { TX_GET, TX_ADD, TX_REPLACE, TX_APPEND, TX_PREPEND, TX_CAS };

void record_tx(enum TxnType, hrtime_t);
void record_error(enum TxnType, hrtime_t);
struct ResultMetrics *calc_metrics(enum TxnType tx_type);

struct ResultMetrics {
    hrtime_t max_result;
    hrtime_t min_result;
    hrtime_t max90th_result;
    hrtime_t max95th_result;
    hrtime_t average;
    long success_count;
    long error_count;
};

#ifdef	__cplusplus
}
#endif

#endif	/* _METRICS_H */