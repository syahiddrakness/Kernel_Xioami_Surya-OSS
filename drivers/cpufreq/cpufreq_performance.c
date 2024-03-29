/*
 *  linux/drivers/cpufreq/cpufreq_performance.c
 *
 *  Copyright (C) 2002 - 2003 Dominik Brodowski <linux@brodo.de>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpufreq.h>
#include <linux/init.h>
#include <linux/module.h>


#ifdef CONFIG_KPROFILES
extern int kp_active_mode(void);
#endif

static void cpufreq_gov_performance_limits(struct cpufreq_policy *policy)
{

#ifdef CONFIG_KPROFILES
		switch (kp_active_mode()) {
		case 0:
		case 1:
			pr_debug("setting to %u kHz\n", policy->min);
			__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
			break;
		case 2:
			pr_debug("setting to %u kHz\n", policy->max);
			__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
			break;
		case 3:
			pr_debug("setting to %u kHz\n", policy->max);
			__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
			break;
		case 4:
			pr_debug("setting to %u kHz\n", policy->max);
			__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
			break;
		default:
			break;
		}
#else
	pr_debug("setting to %u kHz\n", policy->max);
	__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);

#endif
}

static struct cpufreq_governor cpufreq_gov_performance = {
	.name		= "performance",
	.owner		= THIS_MODULE,
	.limits		= cpufreq_gov_performance_limits,
};

static int __init cpufreq_gov_performance_init(void)
{
	return cpufreq_register_governor(&cpufreq_gov_performance);
}

static void __exit cpufreq_gov_performance_exit(void)
{
	cpufreq_unregister_governor(&cpufreq_gov_performance);
}

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_PERFORMANCE
struct cpufreq_governor *cpufreq_default_governor(void)
{
	return &cpufreq_gov_performance;
}
#endif
#ifndef CONFIG_CPU_FREQ_GOV_PERFORMANCE_MODULE
struct cpufreq_governor *cpufreq_fallback_governor(void)
{
	return &cpufreq_gov_performance;
}
#endif

MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("CPUfreq policy governor 'performance'");
MODULE_LICENSE("GPL");

fs_initcall(cpufreq_gov_performance_init);
module_exit(cpufreq_gov_performance_exit);
