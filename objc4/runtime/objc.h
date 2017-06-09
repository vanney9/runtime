/*
 * Copyright (c) 1999-2007 Apple Inc.  All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 *	objc.h
 *	Copyright 1988-1996, NeXT Software, Inc.
 */

#ifndef _OBJC_OBJC_H_
#define _OBJC_OBJC_H_

#include <sys/types.h>      // for __DARWIN_NULL
#include <Availability.h>
#include "objc-api.h"
#include <stdbool.h>

#if !OBJC_TYPES_DEFINED
/// An opaque type that represents an Objective-C class.
typedef struct objc_class *Class;

/// Represents an instance of a class.
struct objc_object {
    Class isa  OBJC_ISA_AVAILABILITY;
};

/// A pointer to an instance of a class.
typedef struct objc_object *id;
#endif

/// An opaque type that represents a method selector.
typedef struct objc_selector *SEL;

/// A pointer to the function of a method implementation. 
#if !OBJC_OLD_DISPATCH_PROTOTYPES
typedef void (*IMP)(void /* id, SEL, ... */ ); 
#else
typedef id (*IMP)(id, SEL, ...); 
#endif

/// Type to represent a boolean value.

#if defined(__OBJC_BOOL_IS_BOOL)
    // Honor __OBJC_BOOL_IS_BOOL when available.
#   if __OBJC_BOOL_IS_BOOL
#       define OBJC_BOOL_IS_BOOL 1
#   else
#       define OBJC_BOOL_IS_BOOL 0
#   endif
#else
    // __OBJC_BOOL_IS_BOOL not set.
#   if TARGET_OS_OSX || (TARGET_OS_IOS && !__LP64__ && !__ARM_ARCH_7K)
#      define OBJC_BOOL_IS_BOOL 0
#   else
#      define OBJC_BOOL_IS_BOOL 1
#   endif
#endif

#if OBJC_BOOL_IS_BOOL
    typedef bool BOOL;
#else
#   define OBJC_BOOL_IS_CHAR 1
    typedef signed char BOOL; 
    // BOOL is explicitly signed so @encode(BOOL) == "c" rather than "C" 
    // even if -funsigned-char is used.
#endif

#define OBJC_BOOL_DEFINED

#if __has_feature(objc_bool)
#define YES __objc_yes
#define NO  __objc_no
#else
#define YES ((BOOL)1)
#define NO  ((BOOL)0)
#endif

#ifndef Nil
# if __has_feature(cxx_nullptr)
#   define Nil nullptr
# else
#   define Nil __DARWIN_NULL
# endif
#endif

#ifndef nil
# if __has_feature(cxx_nullptr)
#   define nil nullptr
# else
#   define nil __DARWIN_NULL
# endif
#endif

#ifndef __strong
# if !__has_feature(objc_arc)
#   define __strong /* empty */
# endif
#endif

#ifndef __unsafe_unretained
# if !__has_feature(objc_arc)
#   define __unsafe_unretained /* empty */
# endif
#endif

#ifndef __autoreleasing
# if !__has_feature(objc_arc)
#   define __autoreleasing /* empty */
# endif
#endif


/** 
 * Returns the name of the method specified by a given selector.
 *
 * 返回给定的选择子的方法名，也就是返回sel对应的名字
 *
 * @param sel A pointer of type \c SEL. Pass the selector whose name you wish to determine.
 * 
 * @return A C string indicating the name of the selector.
 */
OBJC_EXPORT const char *sel_getName(SEL sel)
    OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/** 
 * Registers a method with the Objective-C runtime system, maps the method 
 * name to a selector, and returns the selector value.
 *
 * 运行时动态新增方法，并返回方法的SEL
 * 
 * @param str A pointer to a C string. Pass the name of the method you wish to register.
 * 
 * @return A pointer of type SEL specifying the selector for the named method.
 * 
 * @note You must register a method name with the Objective-C runtime system to obtain the
 *  method’s selector before you can add the method to a class definition. If the method name
 *  has already been registered, this function simply returns the selector.
 */
OBJC_EXPORT SEL sel_registerName(const char *str)
    OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/** 
 * Returns the class name of a given object.
 *
 * 获取对象的类的名字并返回
 *
 * @param obj An Objective-C object.
 * 
 * @return The name of the class of which \e obj is an instance.
 */
OBJC_EXPORT const char *object_getClassName(id obj)
    OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/** 
 * Returns a pointer to any extra bytes allocated with an instance given object.
 *
 * 返回分配个对象的额外内存空间的首地址，从这个地址开始 存放的就是对象的实例变量。返回的地址是8字节（指针内存大小，相对于64位系统）地址对齐的
 *
 * @param obj An Objective-C object.
 * 
 * @return A pointer to any extra bytes allocated with \e obj. If \e obj was
 *   not allocated with any extra bytes, then dereferencing the returned pointer is undefined.
 * 
 * @note This function returns a pointer to any extra bytes allocated with the instance
 *  (as specified by \c class_createInstance with extraBytes>0). This memory follows the
 *  object's ordinary ivars, but may not be adjacent to the last ivar.
 * @note The returned pointer is guaranteed to be pointer-size aligned, even if the area following
 *  the object's last ivar is less aligned than that. Alignment greater than pointer-size is never
 *  guaranteed, even if the area following the object's last ivar is more aligned than that.
 * @note In a garbage-collected environment, the memory is scanned conservatively.
 */
OBJC_EXPORT void *object_getIndexedIvars(id obj)
    OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
    OBJC_ARC_UNAVAILABLE;

/** 
 * Identifies a selector as being valid or invalid.
 *
 * 查看SEL方法是否被map到对象上面？
 *
 * @param sel The selector you want to identify.
 * 
 * @return YES if selector is valid and has a function implementation, NO otherwise. 
 * 
 * @warning On some platforms, an invalid reference (to invalid memory addresses) can cause
 *  a crash. 
 */
OBJC_EXPORT BOOL sel_isMapped(SEL sel)
    OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/** 
 * Registers a method name with the Objective-C runtime system.
 *
 * runtime注册一个方法，并返回SEL
 *
 * @param str A pointer to a C string. Pass the name of the method you wish to register.
 * 
 * @return A pointer of type SEL specifying the selector for the named method.
 * 
 * @note The implementation of this method is identical to the implementation of \c sel_registerName.
 * @note Prior to OS X version 10.0, this method tried to find the selector mapped to the given name
 *  and returned \c NULL if the selector was not found. This was changed for safety, because it was
 *  observed that many of the callers of this function did not check the return value for \c NULL.
 */
OBJC_EXPORT SEL sel_getUid(const char *str)
    OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);



/**
 * not understand
 */

typedef const void* objc_objectptr_t;


// Obsolete ARC conversions.

OBJC_EXPORT id objc_retainedObject(objc_objectptr_t obj)
    OBJC_UNAVAILABLE("use CFBridgingRelease() or a (__bridge_transfer id) cast instead");
OBJC_EXPORT id objc_unretainedObject(objc_objectptr_t obj)
    OBJC_UNAVAILABLE("use a (__bridge id) cast instead");
OBJC_EXPORT objc_objectptr_t objc_unretainedPointer(id obj)
    OBJC_UNAVAILABLE("use a __bridge cast instead");


#if !__OBJC2__

// The following declarations are provided here for source compatibility.

#if defined(__LP64__)
    typedef long arith_t;
    typedef unsigned long uarith_t;
#   define ARITH_SHIFT 32
#else
    typedef int arith_t;
    typedef unsigned uarith_t;
#   define ARITH_SHIFT 16
#endif

typedef char *STR;

#define ISSELECTOR(sel) sel_isMapped(sel)
#define SELNAME(sel)	sel_getName(sel)
#define SELUID(str)	sel_getUid(str)
#define NAMEOF(obj)     object_getClassName(obj)
#define IV(obj)         object_getIndexedIvars(obj)

#endif

#endif  /* _OBJC_OBJC_H_ */
