/* auto-generated by gen_syscalls.py, don't edit */

#ifndef Z_INCLUDE_SYSCALLS_RADIO_CONTROLLER_H
#define Z_INCLUDE_SYSCALLS_RADIO_CONTROLLER_H


#include <zephyr/tracing/tracing_syscall.h>

#ifndef _ASMLANGUAGE

#include <stdarg.h>

#include <syscall_list.h>
#include <zephyr/syscall.h>

#include <zephyr/linker/sections.h>


#ifdef __cplusplus
extern "C" {
#endif

extern int z_impl_radio_controller_port_registration(const struct device * dev, const struct device * port, radio_device_callback_t callback);

__pinned_func
static inline int radio_controller_port_registration(const struct device * dev, const struct device * port, radio_device_callback_t callback)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; const struct device * val; } parm1 = { .val = port };
		union { uintptr_t x; radio_device_callback_t val; } parm2 = { .val = callback };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_RADIO_CONTROLLER_PORT_REGISTRATION);
	}
#endif
	compiler_barrier();
	return z_impl_radio_controller_port_registration(dev, port, callback);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define radio_controller_port_registration(dev, port, callback) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_RADIO_CONTROLLER_PORT_REGISTRATION, radio_controller_port_registration, dev, port, callback); 	syscall__retval = radio_controller_port_registration(dev, port, callback); 	sys_port_trace_syscall_exit(K_SYSCALL_RADIO_CONTROLLER_PORT_REGISTRATION, radio_controller_port_registration, dev, port, callback, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_radio_controller_pin_registration(const struct device * dev, radio_port_id port_id, uint32_t pin);

__pinned_func
static inline int radio_controller_pin_registration(const struct device * dev, radio_port_id port_id, uint32_t pin)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; radio_port_id val; } parm1 = { .val = port_id };
		union { uintptr_t x; uint32_t val; } parm2 = { .val = pin };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_RADIO_CONTROLLER_PIN_REGISTRATION);
	}
#endif
	compiler_barrier();
	return z_impl_radio_controller_pin_registration(dev, port_id, pin);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define radio_controller_pin_registration(dev, port_id, pin) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_RADIO_CONTROLLER_PIN_REGISTRATION, radio_controller_pin_registration, dev, port_id, pin); 	syscall__retval = radio_controller_pin_registration(dev, port_id, pin); 	sys_port_trace_syscall_exit(K_SYSCALL_RADIO_CONTROLLER_PIN_REGISTRATION, radio_controller_pin_registration, dev, port_id, pin, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_radio_controller_port_remove(const struct device * dev, radio_port_id port_id);

__pinned_func
static inline int radio_controller_port_remove(const struct device * dev, radio_port_id port_id)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; radio_port_id val; } parm1 = { .val = port_id };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_RADIO_CONTROLLER_PORT_REMOVE);
	}
#endif
	compiler_barrier();
	return z_impl_radio_controller_port_remove(dev, port_id);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define radio_controller_port_remove(dev, port_id) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_RADIO_CONTROLLER_PORT_REMOVE, radio_controller_port_remove, dev, port_id); 	syscall__retval = radio_controller_port_remove(dev, port_id); 	sys_port_trace_syscall_exit(K_SYSCALL_RADIO_CONTROLLER_PORT_REMOVE, radio_controller_port_remove, dev, port_id, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_radio_controller_pin_remove(const struct device * dev, radio_port_id port_id, uint32_t pin);

__pinned_func
static inline int radio_controller_pin_remove(const struct device * dev, radio_port_id port_id, uint32_t pin)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; radio_port_id val; } parm1 = { .val = port_id };
		union { uintptr_t x; uint32_t val; } parm2 = { .val = pin };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_RADIO_CONTROLLER_PIN_REMOVE);
	}
#endif
	compiler_barrier();
	return z_impl_radio_controller_pin_remove(dev, port_id, pin);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define radio_controller_pin_remove(dev, port_id, pin) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_RADIO_CONTROLLER_PIN_REMOVE, radio_controller_pin_remove, dev, port_id, pin); 	syscall__retval = radio_controller_pin_remove(dev, port_id, pin); 	sys_port_trace_syscall_exit(K_SYSCALL_RADIO_CONTROLLER_PIN_REMOVE, radio_controller_pin_remove, dev, port_id, pin, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_radio_controller_port_set(const struct device * dev, radio_port_id port_id, struct radio_data * data);

__pinned_func
static inline int radio_controller_port_set(const struct device * dev, radio_port_id port_id, struct radio_data * data)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; radio_port_id val; } parm1 = { .val = port_id };
		union { uintptr_t x; struct radio_data * val; } parm2 = { .val = data };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_RADIO_CONTROLLER_PORT_SET);
	}
#endif
	compiler_barrier();
	return z_impl_radio_controller_port_set(dev, port_id, data);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define radio_controller_port_set(dev, port_id, data) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_RADIO_CONTROLLER_PORT_SET, radio_controller_port_set, dev, port_id, data); 	syscall__retval = radio_controller_port_set(dev, port_id, data); 	sys_port_trace_syscall_exit(K_SYSCALL_RADIO_CONTROLLER_PORT_SET, radio_controller_port_set, dev, port_id, data, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_radio_controller_pin_set(const struct device * dev, radio_port_id port_id, uint32_t pin);

__pinned_func
static inline int radio_controller_pin_set(const struct device * dev, radio_port_id port_id, uint32_t pin)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; radio_port_id val; } parm1 = { .val = port_id };
		union { uintptr_t x; uint32_t val; } parm2 = { .val = pin };
		return (int) arch_syscall_invoke3(parm0.x, parm1.x, parm2.x, K_SYSCALL_RADIO_CONTROLLER_PIN_SET);
	}
#endif
	compiler_barrier();
	return z_impl_radio_controller_pin_set(dev, port_id, pin);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define radio_controller_pin_set(dev, port_id, pin) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_RADIO_CONTROLLER_PIN_SET, radio_controller_pin_set, dev, port_id, pin); 	syscall__retval = radio_controller_pin_set(dev, port_id, pin); 	sys_port_trace_syscall_exit(K_SYSCALL_RADIO_CONTROLLER_PIN_SET, radio_controller_pin_set, dev, port_id, pin, syscall__retval); 	syscall__retval; })
#endif
#endif


extern int z_impl_radio_controller_get_events_pointer(const struct device * dev, struct k_event ** events_pointer);

__pinned_func
static inline int radio_controller_get_events_pointer(const struct device * dev, struct k_event ** events_pointer)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { uintptr_t x; const struct device * val; } parm0 = { .val = dev };
		union { uintptr_t x; struct k_event ** val; } parm1 = { .val = events_pointer };
		return (int) arch_syscall_invoke2(parm0.x, parm1.x, K_SYSCALL_RADIO_CONTROLLER_GET_EVENTS_POINTER);
	}
#endif
	compiler_barrier();
	return z_impl_radio_controller_get_events_pointer(dev, events_pointer);
}

#if defined(CONFIG_TRACING_SYSCALL)
#ifndef DISABLE_SYSCALL_TRACING

#define radio_controller_get_events_pointer(dev, events_pointer) ({ 	int syscall__retval; 	sys_port_trace_syscall_enter(K_SYSCALL_RADIO_CONTROLLER_GET_EVENTS_POINTER, radio_controller_get_events_pointer, dev, events_pointer); 	syscall__retval = radio_controller_get_events_pointer(dev, events_pointer); 	sys_port_trace_syscall_exit(K_SYSCALL_RADIO_CONTROLLER_GET_EVENTS_POINTER, radio_controller_get_events_pointer, dev, events_pointer, syscall__retval); 	syscall__retval; })
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif
#endif /* include guard */
