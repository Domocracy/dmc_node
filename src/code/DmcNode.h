////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Project: DMC Server
//		Date:	2015-06-16
//		Author:	Pablo R.S.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



#ifndef _DMC_NODE_DMC_NODE_H_
#define _DMC_NODE_DMC_NODE_H_

#include <string>

namespace dmc{

	/// Main process of Domocracy. Initialize application.
	class DmcNode{
	public:	// Public interface
		/// Constructor. Receive params from command line with information for properly initialization.
		/// \param _argc Number of input arguments
		/// \param _argv Array with arguments.
		DmcNode	(int _argc, const char** _argv);

	private:	// Private methods
		void processArguments	(int _argc, char **_argv);
		void initServer			();

	private:	// Members

	};


}	//	namespace dmc



#endif	//	_DMC_NODE_DMC_NODE_H_