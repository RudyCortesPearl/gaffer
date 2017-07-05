//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2017, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#include "boost/python.hpp"

#include "IECorePython/ScopedGILRelease.h"

#include "GafferScene/PathMatcher.h"
#include "GafferScene/ScenePlug.h"

#include "GafferSceneUI/ContextAlgo.h"

#include "GafferSceneUIBindings/ContextAlgoBinding.h"

using namespace boost::python;
using namespace Gaffer;
using namespace GafferScene;
using namespace GafferSceneUI::ContextAlgo;

namespace
{

PathMatcher expandDescendantsWrapper( Context &context, PathMatcher &paths, ScenePlug &scene, int depth )
{
	IECorePython::ScopedGILRelease gilRelease;
	return expandDescendants( &context, paths, &scene, depth );
}

} // namespace

void GafferSceneUIBindings::bindContextAlgo()
{
	object module( borrowed( PyImport_AddModule( "GafferSceneUI.ContextAlgo" ) ) );
	scope().attr( "ContextAlgo" ) = module;
	scope moduleScope( module );

	def( "setExpandedPaths", &setExpandedPaths );
	def( "getExpandedPaths", &getExpandedPaths );
	def( "expand", &expand, ( arg( "expandAncestors" ) = true ) );
	def( "expandDescendants", &expandDescendantsWrapper, ( arg( "context" ), arg( "paths" ), arg( "scene" ), arg( "depth" ) = std::numeric_limits<int>::max() ) );
	def( "clearExpansion", &clearExpansion );
	def( "setSelectedPaths", &setSelectedPaths );
	def( "getSelectedPaths", &getSelectedPaths );

}
