/**
 * \file
 * \brief SemaphoreFunctor class header
 *
 * \author Copyright (C) 2014 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2014-12-08
 */

#ifndef INCLUDE_DISTORTOS_SCHEDULER_SEMAPHOREFUNCTOR_HPP_
#define INCLUDE_DISTORTOS_SCHEDULER_SEMAPHOREFUNCTOR_HPP_

#include "distortos/estd/TypeErasedFunctor.hpp"

namespace distortos
{

class Semaphore;

namespace scheduler
{

/**
 * \brief SemaphoreFunctor is a type-erased interface for functors which execute some action on semaphore (wait(),
 * tryWait(), tryWaitFor(), tryWaitUntil(), ...).
 *
 * The functor will be called with one argument - \a semaphore - which is a reference to Semaphore object on which the
 * action will be executed. Functor's operator should return zero if the action was executed successfully, error code
 * otherwise.
 */

using SemaphoreFunctor = estd::TypeErasedFunctor<int(Semaphore&)>;

}	// namespace scheduler

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_SCHEDULER_SEMAPHOREFUNCTOR_HPP_
