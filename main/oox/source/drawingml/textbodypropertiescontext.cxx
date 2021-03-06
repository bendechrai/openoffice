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



#include "oox/drawingml/textbodypropertiescontext.hxx"

#include <com/sun/star/drawing/TextHorizontalAdjust.hpp>
#include <com/sun/star/text/ControlCharacter.hpp>
#include <com/sun/star/text/WritingMode.hpp>
#include <com/sun/star/drawing/TextVerticalAdjust.hpp>
#include <com/sun/star/drawing/TextHorizontalAdjust.hpp>
#include "oox/drawingml/textbodyproperties.hxx"
#include "oox/drawingml/drawingmltypes.hxx"
#include "oox/helper/attributelist.hxx"
#include "oox/helper/propertymap.hxx"

using ::rtl::OUString;
using namespace ::oox::core;
using namespace ::com::sun::star;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace drawingml {

// --------------------------------------------------------------------

// CT_TextBodyProperties
TextBodyPropertiesContext::TextBodyPropertiesContext( ContextHandler& rParent,
    const Reference< XFastAttributeList >& xAttributes, TextBodyProperties& rTextBodyProp )
: ContextHandler( rParent )
, mrTextBodyProp( rTextBodyProp )
{
    AttributeList aAttribs( xAttributes );

	// ST_TextWrappingType
    sal_Int32 nWrappingType = aAttribs.getToken( XML_wrap, XML_square );
    mrTextBodyProp.maPropertyMap[ PROP_TextWordWrap ] <<= static_cast< sal_Bool >( nWrappingType == XML_square );

	// ST_Coordinate
	OUString sValue;
	sValue = xAttributes->getOptionalValue( XML_lIns );
    if( sValue.getLength() ) {
	sal_Int32 nLeftInset = ( sValue.getLength() != 0 ? GetCoordinate(  sValue ) : 91440 / 360 );
	mrTextBodyProp.maPropertyMap[ PROP_TextLeftDistance ]  <<= static_cast< sal_Int32 >( nLeftInset );
    }
	sValue = xAttributes->getOptionalValue( XML_tIns );
    if( sValue.getLength() ) {
	sal_Int32 nTopInset  = ( sValue.getLength() != 0 ? GetCoordinate(  sValue ) : 91440 / 360 );
	mrTextBodyProp.maPropertyMap[ PROP_TextUpperDistance ] <<= static_cast< sal_Int32 >( nTopInset );
    }
	sValue = xAttributes->getOptionalValue( XML_rIns );
    if( sValue.getLength() ) {
	sal_Int32 nRightInset  = ( sValue.getLength() != 0 ? GetCoordinate(  sValue ) : 91440 / 360 );
	mrTextBodyProp.maPropertyMap[ PROP_TextRightDistance ] <<= static_cast< sal_Int32 >( nRightInset );
    }
	sValue = xAttributes->getOptionalValue( XML_bIns );
    if( sValue.getLength() ) {
	sal_Int32 nBottonInset = ( sValue.getLength() != 0 ? GetCoordinate(  sValue ) : 45720 / 360 );
	mrTextBodyProp.maPropertyMap[ PROP_TextLowerDistance ] <<= static_cast< sal_Int32 >( nBottonInset );
    }

	// ST_TextAnchoringType
	drawing::TextVerticalAdjust	eVA( drawing::TextVerticalAdjust_TOP );
	switch( xAttributes->getOptionalValueToken( XML_anchor, XML_t ) )
	{
		case XML_b :	eVA = drawing::TextVerticalAdjust_BOTTOM; break;
		case XML_dist :
		case XML_just :
		case XML_ctr :	eVA = drawing::TextVerticalAdjust_CENTER; break;
		default:
		case XML_t :	eVA = drawing::TextVerticalAdjust_TOP; break;
	}
	mrTextBodyProp.maPropertyMap[ PROP_TextVerticalAdjust ] <<= eVA;

    bool bAnchorCenter = aAttribs.getBool( XML_anchorCtr, false );
    if( bAnchorCenter )
	mrTextBodyProp.maPropertyMap[ PROP_TextHorizontalAdjust ] <<= 
	    TextHorizontalAdjust_CENTER;

//   bool bCompatLineSpacing = aAttribs.getBool( XML_compatLnSpc, false );
//   bool bForceAA = aAttribs.getBool( XML_forceAA, false );
//   bool bFromWordArt = aAttribs.getBool( XML_fromWordArt, false );

  // ST_TextHorzOverflowType
//   sal_Int32 nHorzOverflow = xAttributes->getOptionalValueToken( XML_horzOverflow, XML_overflow );
	// ST_TextVertOverflowType
//   sal_Int32 nVertOverflow =  xAttributes->getOptionalValueToken( XML_vertOverflow, XML_overflow );

	// ST_TextColumnCount
//   sal_Int32 nNumCol = aAttribs.getInteger( XML_numCol, 1 );

    // ST_Angle
    mrTextBodyProp.moRotation = aAttribs.getInteger( XML_rot );

//   bool bRtlCol = aAttribs.getBool( XML_rtlCol, false );
	// ST_PositiveCoordinate
//   sal_Int32 nSpcCol = aAttribs.getInteger( XML_spcCol, 0 );
//   bool bSpcFirstLastPara = aAttribs.getBool( XML_spcFirstLastPara, 0 );
//   bool bUpRight = aAttribs.getBool( XML_upright, 0 );

	// ST_TextVerticalType
    mrTextBodyProp.moVert = aAttribs.getToken( XML_vert );
    bool bRtl = aAttribs.getBool( XML_rtl, false );
    sal_Int32 tVert = mrTextBodyProp.moVert.get( XML_horz );
    if( tVert == XML_vert || tVert == XML_eaVert || tVert == XML_vert270 || tVert == XML_mongolianVert ) {
      mrTextBodyProp.maPropertyMap[ PROP_TextWritingMode ]
	<<= WritingMode_TB_RL;
      // workaround for TB_LR as using WritingMode2 doesn't work
    	if( !bAnchorCenter )
    	    mrTextBodyProp.maPropertyMap[ PROP_TextHorizontalAdjust ] <<= 
    		TextHorizontalAdjust_LEFT;
    } else
      mrTextBodyProp.maPropertyMap[ PROP_TextWritingMode ]
	<<= ( bRtl ? WritingMode_RL_TB : WritingMode_LR_TB );
}

// --------------------------------------------------------------------

void TextBodyPropertiesContext::endFastElement( sal_Int32 ) throw (SAXException, RuntimeException)
{
}

// --------------------------------------------------------------------

Reference< XFastContextHandler > TextBodyPropertiesContext::createFastChildContext( sal_Int32 aElementToken, const Reference< XFastAttributeList >& /*xAttributes*/) throw (SAXException, RuntimeException)
{
	Reference< XFastContextHandler > xRet;
	switch( aElementToken )
	{
			// Sequence
			case A_TOKEN( prstTxWarp ):		// CT_PresetTextShape
			case A_TOKEN( prot ):			// CT_TextProtectionProperty
				break;

			// EG_TextAutofit
			case A_TOKEN( noAutofit ):
                mrTextBodyProp.maPropertyMap[ PROP_TextAutoGrowHeight ] <<= false;   // CT_TextNoAutofit
				break;
			case A_TOKEN( normAutofit ):	// CT_TextNormalAutofit
                mrTextBodyProp.maPropertyMap[ PROP_TextFitToSize ] <<= true;
                mrTextBodyProp.maPropertyMap[ PROP_TextAutoGrowHeight ] <<= false;
                break;
			case A_TOKEN( spAutoFit ):
                mrTextBodyProp.maPropertyMap[ PROP_TextAutoGrowHeight ] <<= true;
				break;

			case A_TOKEN( scene3d ):		// CT_Scene3D

			// EG_Text3D
			case A_TOKEN( sp3d ):			// CT_Shape3D
			case A_TOKEN( flatTx ):			// CT_FlatText

				break;
	}

	return xRet;
}

// --------------------------------------------------------------------

} }

