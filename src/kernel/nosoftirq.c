/**
 *  @brief Implements softirq interface.
 *  @details This header in use if and only if
 *           mod 'irq' is not enable.
 *  @date 13.07.11
 */

#include <kernel/softirq.h>
#include <kernel/critical/api.h>

void softirq_lock() {
	critical_enter(__CRITICAL_SOFTIRQ);
}

void softirq_unlock() {
	critical_leave(__CRITICAL_SOFTIRQ);
	critical_check_pending(__CRITICAL_SOFTIRQ);
}

void softirq_try_dispatch(void) {
	if (critical_allows(__CRITICAL_SOFTIRQ)) {
		softirq_dispatch();
	} else
		__critical_count_set_bit(__CRITICAL_SOFTIRQ);
}
