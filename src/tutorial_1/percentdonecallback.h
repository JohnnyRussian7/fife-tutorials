/***************************************************************************
*   Copyright (C) 2005-2008 by the FIFE team                              *
*   http://www.fifengine.de                                               *
*   This file is part of FIFE.                                            *
*                                                                         *
*   FIFE is free software; you can redistribute it and/or                 *
*   modify it under the terms of the GNU Lesser General Public            *
*   License as published by the Free Software Foundation; either          *
*   version 2.1 of the License, or (at your option) any later version.    *
*                                                                         *
*   This library is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
*   Lesser General Public License for more details.                       *
*                                                                         *
*   You should have received a copy of the GNU Lesser General Public      *
*   License along with this library; if not, write to the                 *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
***************************************************************************/
#ifndef FIFE_PERCENT_DONE_CALLBACK_H
#define FIFE_PERCENT_DONE_CALLBACK_H

// Standard C++ library includes
#include <vector>

// 3rd party library includes
#include "util/base/fife_stdint.h"

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder

namespace FIFE
{
	class PercentDoneListener
	{
	public:
		virtual ~PercentDoneListener();
		virtual void OnEvent(unsigned int percentDone);
	};

	class PercentDoneCallback
	{
	public:
		PercentDoneCallback();
		virtual ~PercentDoneCallback();

		void setTotalNumberOfElements(unsigned int totalElements);
		void setPercentDoneInterval(unsigned int percent);
		void incrementCount();
		void reset();
		void addListener(PercentDoneListener* listener);
		void removeListener(PercentDoneListener* listener);

	private:
		void fireEvent(unsigned int percent);

	private:
		uint32_t m_totalElements;
		uint32_t m_percent;
		uint32_t m_numberOfEvents;
		uint32_t m_count;

		typedef std::vector<PercentDoneListener*> ListenerContainer;
		ListenerContainer m_listeners;
	};

	PercentDoneListener* createPercentDoneListener();
}

#endif
