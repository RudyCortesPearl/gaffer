//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2011, John Haddon. All rights reserved.
//  Copyright (c) 2012, Image Engine Design Inc. All rights reserved.
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

#ifndef GAFFERUI_LINEARCONTAINER_H
#define GAFFERUI_LINEARCONTAINER_H

#include "GafferUI/ContainerGadget.h"

namespace GafferUI
{

class LinearContainer : public ContainerGadget
{

	public :

		enum Orientation
		{
			InvalidOrientation,
			X,
			Y,
			Z
		};
		
		enum Alignment
		{
			InvalidAlignment,
			Min,
			Centre,
			Max
		};
		
		LinearContainer( const std::string &name=staticTypeName(), Orientation orientation=X,
			Alignment alignment=Centre, float spacing = 0.0f );
			
		virtual ~LinearContainer();

		IE_CORE_DECLARERUNTIMETYPEDEXTENSION( LinearContainer, LinearContainerTypeId, ContainerGadget );

		void setOrientation( Orientation orientation );
		Orientation getOrientation() const;

		void setAlignment( Alignment alignment );
		Alignment getAlignment() const;
		
		void setSpacing( float spacing );
		float getSpacing() const;

		virtual Imath::Box3f bound() const;

	protected :

		virtual void doRender( const Style *style ) const;
				
	private :
	
		void renderRequested( GadgetPtr gadget );
	
		Orientation m_orientation;
		Alignment m_alignment;
		float m_spacing;
		
		mutable bool m_clean;
		void calculateChildTransforms() const;
		
};

IE_CORE_DECLAREPTR( LinearContainer );

} // namespace GafferUI

#endif // GAFFERUI_LINEARCONTAINER_H
