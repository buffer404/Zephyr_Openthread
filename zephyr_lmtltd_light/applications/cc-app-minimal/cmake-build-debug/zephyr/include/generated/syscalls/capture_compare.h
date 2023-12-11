/* auto-generated by gen_syscalls.py, don't edit */

#ifndef Z_INCLUDE_SYSCALLS_CAPTURE_COMPARE_H
#define Z_INCLUDE_SYSCALLS_CAPTURE_COMPARE_H


#include <zephyr/tracing/tracing_syscall.h>

#ifndef _ASMLANGUAGE

#include <stdarg.h>

#include <syscall_list.h>
#include <zephyr/syscall.h>

#include <zephyr/linker/sections.h>


#ifdef __cplusplus
extern "C" {
#endif

extern int z_impl_cc_transmit(const struct device * dev, uint32_t * buf, size_t len, k_timeout_t timeout);

__pinned_func
static inline int cc_transmit(const struct device * dev, uint32_t * buf, size_t len, k_timeout_t timeout)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; uint32_t * val; } parm1 = { .val = buf };
		union { uintptr_t x; size_t val; } parm2 = { .val = len };
		union { struct { uintptr_t lo, hi; } split; k_timeout_t val; } parm3 = { .val = timeout };
		return (int) arch_syscall_invoke5(parm0.x, parm1.x, parm2.x, parm3.split.lo, parm3.split.hi, K_SYSCALL_CC_TRANSMIT);
	}
#endif
	compiler_barrier();
	return z_impl_cc_transmit(dev, buf, len, timeout);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define cc_transmit(dev, buf, len, timeout) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_CC_TRANSMIT, cc_transmit, dev, buf, len, timeout); 	syscall__retval = cc_transmit(dev, buf, len, timeout); 	sys_port_trace_syscall_exit(K_SYSCALL_CC_TRANSMIT, cc_transmit, dev, buf, len, timeout, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_cc_transmit_async(const struct device * dev, uint32_t * buf, size_t len, cc_callback_t cb);

__pinned_func
static inline int cc_transmit_async(const struct device * dev, uint32_t * buf, size_t len, cc_callback_t cb)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; uint32_t * val; } parm1 = { .val = buf };
		union { uintptr_t x; size_t val; } parm2 = { .val = len };
		union { uintptr_t x; cc_callback_t val; } parm3 = { .val = cb };
		return (int) arch_syscall_invoke4(parm0.x, parm1.x, parm2.x, parm3.x, K_SYSCALL_CC_TRANSMIT_ASYNC);
	}
#endif
	compiler_barrier();
	return z_impl_cc_transmit_async(dev, buf, len, cb);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define cc_transmit_async(dev, buf, len, cb) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_CC_TRANSMIT_ASYNC, cc_transmit_async, dev, buf, len, cb); 	syscall__retval = cc_transmit_async(dev, buf, len, cb); 	sys_port_trace_syscall_exit(K_SYSCALL_CC_TRANSMIT_ASYNC, cc_transmit_async, dev, buf, len, cb, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_cc_receive_configure(const struct device * dev, struct capture_config_t config, uint32_t * buf, size_t len, cc_callback_t cb, void * user_data);

__pinned_func
static inline int cc_receive_configure(const struct device * dev, struct capture_config_t config, uint32_t * buf, size_t len, cc_callback_t cb, void * user_data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; struct capture_config_t val; } parm1 = { .val = config };
		union { uintptr_t x; uint32_t * val; } parm2 = { .val = buf };
		union { uintptr_t x; size_t val; } parm3 = { .val = len };
		union { uintptr_t x; cc_callback_t val; } parm4 = { .val = cb };
		union { uintptr_t x; void * val; } parm5 = { .val = user_data };
		return (int) arch_syscall_invoke6(parm0.x, parm1.x, parm2.x, parm3.x, parm4.x, parm5.x, K_SYSCALL_CC_RECEIVE_CONFIGURE);
	}
#endif
	compiler_barrier();
	return z_impl_cc_receive_configure(dev, config, buf, len, cb, user_data);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define cc_receive_configure(dev, config, buf, len, cb, user_data) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_CC_RECEIVE_CONFIGURE, cc_receive_configure, dev, config, buf, len, cb, user_data); 	syscall__retval = cc_receive_configure(dev, config, buf, len, cb, user_data); 	sys_port_trace_syscall_exit(K_SYSCALL_CC_RECEIVE_CONFIGURE, cc_receive_configure, dev, config, buf, len, cb, user_data, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_cc_receive_enable(const struct device * dev);

__pinned_func
static inline int cc_receive_enable(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		return (int) arch_syscall_invoke1(parm0.x, K_SYSCALL_CC_RECEIVE_ENABLE);
	}
#endif
	compiler_barrier();
	return z_impl_cc_receive_enable(dev);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define cc_receive_enable(dev) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_CC_RECEIVE_ENABLE, cc_receive_enable, dev); 	syscall__retval = cc_receive_enable(dev); 	sys_port_trace_syscall_exit(K_SYSCALL_CC_RECEIVE_ENABLE, cc_receive_enable, dev, syscall__retval); 	syscall__retval; })
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
#endif /* include guard */