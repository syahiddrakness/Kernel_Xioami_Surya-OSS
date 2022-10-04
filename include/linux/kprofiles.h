// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021 Dakkshesh <dakkshesh5@gmail.com>.
 */

#ifndef _KPROFILES_H_
#define _KPROFILES_H_

#include <linux/types.h>
#include <linux/delay.h>

#ifdef CONFIG_KPROFILES
void kp_set_mode_rollback(unsigned int level, unsigned int duration_ms);
void kp_set_mode(unsigned int level);

static bool auto_kprofiles __read_mostly = true;
static unsigned int kp_mode = CONFIG_DEFAULT_KP_MODE;
int kp_active_mode(void);
#else
static inline void kp_set_mode_rollback(unsigned int level, unsigned int duration_ms)
{
}
static inline void kp_set_mode(unsigned int level)
{
}
static inline int kp_active_mode(void)
{
	return 0;
}
#endif

#ifdef CONFIG_AUTO_KPROFILES
static bool screen_on = true;
#endif

#endif /* _KPROFILES_H_ */ 
