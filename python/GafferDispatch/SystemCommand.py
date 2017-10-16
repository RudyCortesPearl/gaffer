##########################################################################
#
#  Copyright (c) 2014, Image Engine Design Inc. All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are
#  met:
#
#      * Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      * Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials provided with
#        the distribution.
#
#      * Neither the name of John Haddon nor the names of
#        any other contributors to this software may be used to endorse or
#        promote products derived from this software without specific prior
#        written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
##########################################################################

import os
import subprocess32 as subprocess

import IECore

import Gaffer
import GafferDispatch

class SystemCommand( GafferDispatch.TaskNode ) :

	def __init__( self, name = "SystemCommand" ) :

		GafferDispatch.TaskNode.__init__( self, name )

		self["command"] = Gaffer.StringPlug()
		self["substitutions"] = Gaffer.CompoundDataPlug()
		self["environmentVariables"] = Gaffer.CompoundDataPlug()

	def execute( self ) :

		substitutions = IECore.CompoundData()
		self["substitutions"].fillCompoundData( substitutions )
		substitutions = { key : str( value ) for ( key, value ) in substitutions.items() }

		command = self["command"].getValue()
		command = command.format( **substitutions )

		env = os.environ.copy()
		environmentVariables = IECore.CompoundData()
		self["environmentVariables"].fillCompoundData( environmentVariables )
		for name, value in environmentVariables.items() :
			env[name] = str( value )

		subprocess.check_call( command, shell = True, env = env )

	def hash( self, context ) :

		h = GafferDispatch.TaskNode.hash( self, context )

		self["command"].hash( h )
		self["substitutions"].hash( h )
		self["environmentVariables"].hash( h )

		return h

IECore.registerRunTimeTyped( SystemCommand, typeName = "GafferDispatch::SystemCommand" )
