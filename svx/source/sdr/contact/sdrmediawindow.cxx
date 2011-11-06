/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_svx.hxx"
 
#include "sdrmediawindow.hxx"
#include <svtools/transfer.hxx>

#include <svx/sdr/contact/viewobjectcontactofsdrmediaobj.hxx>
#include <vcl/window.hxx>

namespace sdr {	namespace contact {

// ------------------
// - SdrMediaWindow -
// ------------------

SdrMediaWindow::SdrMediaWindow( Window* pParent, ViewObjectContactOfSdrMediaObj& rViewObjContact ) :
	::avmedia::MediaWindow( pParent, false ),
	mrViewObjectContactOfSdrMediaObj( rViewObjContact )
{
}

// ------------------------------------------------------------------------------

SdrMediaWindow::~SdrMediaWindow()
{
}

// ------------------------------------------------------------------------------
		
void SdrMediaWindow::MouseMove( const MouseEvent& rMEvt )
{
	Window* pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	
	if( pWindow && getWindow() )
	{
		const MouseEvent aTransformedEvent( pWindow->ScreenToOutputPixel( getWindow()->OutputToScreenPixel( rMEvt.GetPosPixel() ) ),
									  		rMEvt.GetClicks(), rMEvt.GetMode(), rMEvt.GetButtons(), rMEvt.GetModifier() );
	
		pWindow->MouseMove( aTransformedEvent );
		setPointer( pWindow->GetPointer() );
	}
}

// ------------------------------------------------------------------------------

void SdrMediaWindow::MouseButtonDown( const MouseEvent& rMEvt )
{
	Window* pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	
	if( pWindow && getWindow() )
	{
		const MouseEvent aTransformedEvent( pWindow->ScreenToOutputPixel( getWindow()->OutputToScreenPixel( rMEvt.GetPosPixel() ) ),
									  		rMEvt.GetClicks(), rMEvt.GetMode(), rMEvt.GetButtons(), rMEvt.GetModifier() );
		
		pWindow->MouseButtonDown( aTransformedEvent );
	}
}

// ------------------------------------------------------------------------------

void SdrMediaWindow::MouseButtonUp( const MouseEvent& rMEvt )
{
	Window* pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	
	if( pWindow && getWindow() )
	{
		const MouseEvent aTransformedEvent( pWindow->ScreenToOutputPixel( getWindow()->OutputToScreenPixel( rMEvt.GetPosPixel() ) ),
									  		rMEvt.GetClicks(), rMEvt.GetMode(), rMEvt.GetButtons(), rMEvt.GetModifier() );
		
		pWindow->MouseButtonUp( aTransformedEvent );
	}
}

// ------------------------------------------------------------------------------

void SdrMediaWindow::KeyInput( const KeyEvent& rKEvt )
{
	Window* pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	
	if( pWindow )
		pWindow->KeyInput( rKEvt );
}

// ------------------------------------------------------------------------------

void SdrMediaWindow::KeyUp( const KeyEvent& rKEvt )
{
	Window* pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	
	if( pWindow )
		pWindow->KeyUp( rKEvt );
}

// ------------------------------------------------------------------------------

void SdrMediaWindow::Command( const CommandEvent& rCEvt )
{
	Window* pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	
	if( pWindow && getWindow() )
	{
		const CommandEvent aTransformedEvent( pWindow->ScreenToOutputPixel( getWindow()->OutputToScreenPixel( rCEvt.GetMousePosPixel() ) ),
									  		  rCEvt.GetCommand(), rCEvt.IsMouseEvent(), rCEvt.GetData() );
		
		pWindow->Command( aTransformedEvent );
	}
}

// ------------------------------------------------------------------------------

sal_Int8 SdrMediaWindow::AcceptDrop( const AcceptDropEvent& rEvt )
{
	Window* 	pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	sal_Int8	nRet = DND_ACTION_NONE;
	
	if( pWindow )
	{
		DropTargetHelper* pDropTargetHelper = dynamic_cast< DropTargetHelper* >( pWindow );
		
		if( pDropTargetHelper )
		{
			nRet = pDropTargetHelper->AcceptDrop( rEvt );
		}
	}
	
	return( nRet );
}

// ------------------------------------------------------------------------------

sal_Int8 SdrMediaWindow::ExecuteDrop( const ExecuteDropEvent& rEvt )
{
	Window* 	pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	sal_Int8	nRet = DND_ACTION_NONE;
	
	if( pWindow )
	{
		DropTargetHelper* pDropTargetHelper = dynamic_cast< DropTargetHelper* >( pWindow );
		
		if( pDropTargetHelper )
		{
			nRet = pDropTargetHelper->ExecuteDrop( rEvt );
		}
	}
	
	return( nRet );
}

// ------------------------------------------------------------------------------

void SdrMediaWindow::StartDrag( sal_Int8 nAction, const Point& rPosPixel )
{
	Window* pWindow = mrViewObjectContactOfSdrMediaObj.getWindow();
	
	if( pWindow )
	{
		DragSourceHelper* pDragSourceHelper = dynamic_cast< DragSourceHelper* >( pWindow );
		
		if( pDragSourceHelper )
		{
			pDragSourceHelper->StartDrag( nAction, rPosPixel );
		}
	}
}

} }
