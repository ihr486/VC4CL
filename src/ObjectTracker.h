/*
 * Author: doe300
 *
 * See the file "LICENSE" for the full license governing this code.
 */

#ifndef VC4CL_OBJECT_TRACKER_H
#define VC4CL_OBJECT_TRACKER_H

#include "types.h"

#include <memory>
#include <mutex>
#include <set>

namespace vc4cl
{
	class BaseObject;
	/*
	 * Tracks all live OpenCL objects
	 */
	class ObjectTracker
	{
		using ReportFunction = void(CL_CALLBACK*)(void* userData, void* objPtr, const char* typeName, cl_uint refCount);

	public:
		~ObjectTracker();

		static void addObject(BaseObject* obj);
		static void removeObject(BaseObject* obj);

		void iterateObjects(ReportFunction func, void* userData);
	private:
		std::set<std::unique_ptr<BaseObject>> liveObjects;
		//recursive-mutex required, since a #removeObject() can cause #removeObject() to be called multiple times (e.g. for last CommandQueue also releasing the Context)
		std::recursive_mutex trackerMutex;
	};

} /* namespace vc4cl */

#endif /* VC4CL_OBJECT_TRACKER_H */
