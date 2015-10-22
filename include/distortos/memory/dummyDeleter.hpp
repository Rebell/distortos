/**
 * \file
 * \brief dummyDeleter() declaration
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-10-20
 */

#ifndef INCLUDE_DISTORTOS_MEMORY_DUMMYDELETER_HPP_
#define INCLUDE_DISTORTOS_MEMORY_DUMMYDELETER_HPP_

namespace distortos
{

namespace memory
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' declarations
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief A "no-op" dummy deleter that can be used with StorageUniquePointer and automatic storage.
 *
 * \param [in] storage is a pointer to storage that will be deleted
 */

void dummyDeleter(void* storage);

}	// namespace memory

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_MEMORY_DUMMYDELETER_HPP_