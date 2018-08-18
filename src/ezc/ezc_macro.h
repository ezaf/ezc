/*  ezc_macro.h
 *
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************
 *
 *  Copyright (C) 2012 William Swanson <github.com/swansontec/map-macro>
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy,
 *  modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 *  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  Except as contained in this notice, the names of the authors or
 *  their institutions shall not be used in advertising or otherwise to
 *  promote the sale, use or other dealings in this Software without
 *  prior written authorization from the authors.
 */

#ifndef EZC_MACRO_H
#define EZC_MACRO_H

/** @file       ezc_macro.h
 *  @brief      Macros for helping you write your own featureful macros.
 *  @details    All macros with the `SST_` prefix are authored by William
 *              "swansontec" Swanson. The only modification made to his code
 *              is the adding of the aformentioned prefix to all his macros.
 */



#define SST_EVAL0(...) __VA_ARGS__
#define SST_EVAL1(...) SST_EVAL0(SST_EVAL0(SST_EVAL0(__VA_ARGS__)))
#define SST_EVAL2(...) SST_EVAL1(SST_EVAL1(SST_EVAL1(__VA_ARGS__)))
#define SST_EVAL3(...) SST_EVAL2(SST_EVAL2(SST_EVAL2(__VA_ARGS__)))
#define SST_EVAL4(...) SST_EVAL3(SST_EVAL3(SST_EVAL3(__VA_ARGS__)))
#define SST_EVAL(...)  SST_EVAL4(SST_EVAL4(SST_EVAL4(__VA_ARGS__)))

#define SST_MAP_END(...)
#define SST_MAP_OUT
#define SST_MAP_COMMA ,

#define SST_MAP_GET_END2() 0, SST_MAP_END
#define SST_MAP_GET_END1(...) SST_MAP_GET_END2
#define SST_MAP_GET_END(...) SST_MAP_GET_END1
#define SST_MAP_NEXT0(test, next, ...) next SST_MAP_OUT
#define SST_MAP_NEXT1(test, next) SST_MAP_NEXT0(test, next, 0)
#define SST_MAP_NEXT(test, next)  SST_MAP_NEXT1(SST_MAP_GET_END test, next)

#define SST_MAP0(f, x, peek, ...) \
    f(x) SST_MAP_NEXT(peek, SST_MAP1)(f, peek, __VA_ARGS__)
#define SST_MAP1(f, x, peek, ...) \
    f(x) SST_MAP_NEXT(peek, SST_MAP0)(f, peek, __VA_ARGS__)

#define SST_MAP_LIST_NEXT1(test, next) \
    SST_MAP_NEXT0(test, SST_MAP_COMMA next, 0)
#define SST_MAP_LIST_NEXT(test, next) \
    SST_MAP_LIST_NEXT1(SST_MAP_GET_END test, next)

#define SST_MAP_LIST0(f, x, peek, ...) \
    f(x) SST_MAP_LIST_NEXT(peek, SST_MAP_LIST1)(f, peek, __VA_ARGS__)
#define SST_MAP_LIST1(f, x, peek, ...) \
    f(x) SST_MAP_LIST_NEXT(peek, SST_MAP_LIST0)(f, peek, __VA_ARGS__)



/** @brief      Map function to specified variables.
 *  @details    Applies the function macro `f` to each of the arguments.
 *  @param      f       Function macro.
 *  @param      ...     Arguments to be passed to `f`.
 *  @returns    N/A
 */
#define SST_MAP(f, ...) \
    SST_EVAL(SST_MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))



/** @brief      Map function to specified variables and return their results.
 *  @details    Applies the function macro `f` to each of the arguments and
 *              and inserts commas between the results.
 *  @param      f       Function macro.
 *  @param      ...     Arguments to be passed to `f`.
 *  @returns    The comma seperated results of `f` for each arguments it was
 *              called with.
 */
#define SST_MAP_LIST(f, ...) \
    SST_EVAL(SST_MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))



#define EZC_TO_ZERO(ptr) ((ptr) = 0)

#define EZC_DO_FREE(ptr) (free((ptr)))



#endif /* EZC_MACRO_H */
