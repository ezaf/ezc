/*  ezc_status.h
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
 */

#ifndef EZC_STATUS_H
#define EZC_STATUS_H

/** @file       ezc_status.h
 *  @brief      Function status macros.
 */

#ifdef __cplusplus
extern C
{
#endif



/** @brief      Macro defining the `EZC_STATUS` type.
 *  @details    This type is pretty frugal; all we need is to represent two
 *              states.
 */
#define EZC_STATUS unsigned char



/** @brief      Macro defining the value of `EZC_OK`.
 *  @details    Similar to `EXIT_SUCCESS`, this macro's value is `0`.
 */
#define EZC_OK 0



/** @brief      Macro defining the value of `EZC_FAIL`.
 *  @details    Similar to `EXIT_FAILURE`, this macro's value is `1`.
 */
#define EZC_FAIL 1



#ifdef __cplusplus
}
#endif

#endif /* EZC_STATUS_H */
