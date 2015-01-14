/**
 * \file
 * \brief MessageQueueBase class header
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-01-14
 */

#ifndef INCLUDE_DISTORTOS_SYNCHRONIZATION_MESSAGEQUEUEBASE_HPP_
#define INCLUDE_DISTORTOS_SYNCHRONIZATION_MESSAGEQUEUEBASE_HPP_

#include "distortos/Semaphore.hpp"

#include "distortos/allocators/FeedablePool.hpp"

#include "distortos/estd/TypeErasedFunctor.hpp"

#include <forward_list>

namespace distortos
{

namespace synchronization
{

/// MessageQueueBase class implements basic functionality of MessageQueue template class
class MessageQueueBase
{
public:

	/// entry in the MessageQueueBase
	struct Entry
	{
		/**
		 * \brief Entry's constructor
		 *
		 * \param [in] priorityy is the priority of the entry
		 * \param [in] storagee is the storage for the entry
		 */

		constexpr Entry(const uint8_t priorityy, void* const storagee) :
				priority{priorityy},
				storage{storagee}
		{

		}

		/// default copy constructor
		constexpr Entry(const Entry&) = default;

		/// priority of the entry
		uint8_t priority;

		/// storage for the entry
		void* storage;
	};

	/**
	 * \brief Functor is a type-erased interface for functors which execute some action on queue's storage (like
	 * copy-constructing, swapping, destroying, emplacing, ...).
	 *
	 * The functor will be called by MessageQueueBase internals with one argument - \a storage - which is a pointer to
	 * storage with/for element.
	 */

	using Functor = estd::TypeErasedFunctor<void(void*)>;

	/// link and Entry
	using LinkAndEntry = std::pair<void*, Entry>;

	/**
	 * type of uninitialized storage for data
	 *
	 * \param T is the type of data in queue
	 */

	template<typename T>
	struct Storage
	{
		/// storage for Entry
		typename std::aligned_storage<sizeof(LinkAndEntry), alignof(LinkAndEntry)>::type entryStorage;

		/// storage for value
		typename std::aligned_storage<sizeof(T), alignof(T)>::type valueStorage;
	};

	/// functor which gives descending priority order of elements on the list
	struct DescendingPriority
	{
		/**
		 * \brief operator()
		 *
		 * \param [in] left is the object on the left side of comparison
		 * \param [in] right is the object on the right side of comparison
		 *
		 * \return true if left's priority is less than right's priority
		 */

		bool operator()(const Entry& left, const Entry& right)
		{
			return left.priority < right.priority;
		}
	};

	/// type of pool
	using Pool = allocators::FeedablePool;

	/// type of pool allocator
	using PoolAllocator = allocators::PoolAllocator<Entry, Pool>;

	/// type of entry list
	using EntryList = containers::SortedContainer<std::forward_list<Entry, PoolAllocator>, DescendingPriority>;

	/// type of free entry list
	using FreeEntryList = std::forward_list<Entry, PoolAllocator>;

	/**
	 * \brief InternalFunctor is a type-erased interface for functors which execute common code of pop() and push()
	 * operations.
	 *
	 * The functor will be called by MessageQueueBase internals with references to \a entryList_ and \a freeEntryList_.
	 * It should perform common actions and execute the Functor passed from callers.
	 */

	using InternalFunctor = estd::TypeErasedFunctor<void(EntryList&, FreeEntryList&)>;

	/**
	 * \brief MessageQueueBase's constructor
	 *
	 * \param T is the type of data in queue
	 *
	 * \param [in] storage is an array of Storage elements
	 * \param [in] maxElements is the number of elements in \a storage array
	 */

	template<typename T>
	MessageQueueBase(Storage<T>* const storage, const size_t maxElements) :
			MessageQueueBase{maxElements}
	{
		for (size_t i = 0; i < maxElements; ++i)
		{
			pool_.feed(storage[i].entryStorage);
			freeEntryList_.emplace_front(uint8_t{}, &storage[i].valueStorage);
		}
	}

private:

	/**
	 * \brief MessageQueueBase's constructor - internal version
	 *
	 * \param [in] maxElements is the maximum number of elements the queue can hold
	 */

	explicit MessageQueueBase(size_t maxElements);

	/// semaphore guarding access to "pop" functions - its value is equal to the number of available elements
	Semaphore popSemaphore_;

	/// semaphore guarding access to "push" functions - its value is equal to the number of free slots
	Semaphore pushSemaphore_;

	/// FeedablePool used by \a poolAllocator_
	Pool pool_;

	/// PoolAllocator used by \a entryList_ and \a freeList_
	PoolAllocator poolAllocator_;

	/// list of available entries, sorted in descending order of priority
	EntryList entryList_;

	/// list of "free" entries
	FreeEntryList freeEntryList_;
};

}	// namespace synchronization

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_SYNCHRONIZATION_MESSAGEQUEUEBASE_HPP_