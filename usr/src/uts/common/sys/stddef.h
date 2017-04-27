/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 */

/*
 * Copyright 2017 Toomas Soome <tsoome@me.com>
 */

#ifndef _SYS_STDDEF_H
#define	_SYS_STDDEF_H

/*
 * Commonly used macros and definitions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(offsetof)
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#define	offsetof(s, m)	__builtin_offsetof(s, m)
#else
#if __cplusplus >= 199711L
#define	offsetof(s, m)	(std::size_t)(&(((s *)NULL)->m))
#else
#define	offsetof(s, m)	((size_t)(&(((s *)NULL)->m)))
#endif
#endif
#endif /* !offsetof */

#if !defined(container_of)

/*
 * We must not expose container_of() to userland, but we want it
 * to be available for early boot and for the kernel.
 */
#if ((defined(_KERNEL) || defined(_FAKE_KERNEL)) && !defined(_KMEMUSER)) || \
	(defined(_BOOT) && defined(_KMEMUSER))
#define	container_of(m, s, name)			\
	(void *)((uintptr_t)(m) - (uintptr_t)offsetof(s, name))
#endif
#endif /* !container_of */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_STDDEF_H */
