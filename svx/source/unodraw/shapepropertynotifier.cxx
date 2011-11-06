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

#include "svx/shapepropertynotifier.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/beans/XPropertySet.hpp>
/** === end UNO includes === **/

#include <comphelper/stl_types.hxx>
#include <cppuhelper/interfacecontainer.hxx>
#include <cppuhelper/weak.hxx>
#include <tools/diagnose_ex.h>

#include <hash_map>

namespace
{

    struct ShapePropertyHash
    {
        size_t operator()( ::svx::ShapeProperty __x ) const
        {
            return size_t( __x );
        }
    };
}

//........................................................................
namespace svx
{
//........................................................................

	/** === begin UNO using === **/
	using ::com::sun::star::uno::Reference;
	using ::com::sun::star::uno::XInterface;
	using ::com::sun::star::uno::UNO_QUERY;
	using ::com::sun::star::uno::UNO_QUERY_THROW;
	using ::com::sun::star::uno::UNO_SET_THROW;
	using ::com::sun::star::uno::Exception;
	using ::com::sun::star::uno::RuntimeException;
	using ::com::sun::star::uno::Any;
	using ::com::sun::star::uno::makeAny;
	using ::com::sun::star::uno::Sequence;
	using ::com::sun::star::uno::Type;
    using ::com::sun::star::beans::PropertyChangeEvent;
    using ::com::sun::star::beans::XPropertyChangeListener;
    using ::com::sun::star::lang::EventObject;
    using ::com::sun::star::beans::XPropertySet;
	/** === end UNO using === **/

    typedef ::std::hash_map< ShapeProperty, PPropertyValueProvider, ShapePropertyHash  >    PropertyProviders;

    typedef ::cppu::OMultiTypeInterfaceContainerHelperVar   <   ::rtl::OUString
                                                            ,   ::comphelper::UStringHash
                                                            ,   ::comphelper::UStringEqual
                                                            >   PropertyChangeListenerContainer;

    //====================================================================
	//= IPropertyValueProvider
	//====================================================================
    IPropertyValueProvider::~IPropertyValueProvider()
    {
    }

    //====================================================================
	//= PropertyChangeNotifier_Data
	//====================================================================
    struct PropertyChangeNotifier_Data
    {
        ::cppu::OWeakObject&            m_rContext;
        PropertyProviders               m_aProviders;
        PropertyChangeListenerContainer m_aPropertyChangeListeners;

        PropertyChangeNotifier_Data( ::cppu::OWeakObject& _rContext, ::osl::Mutex& _rMutex )
            :m_rContext( _rContext )
            ,m_aPropertyChangeListeners( _rMutex )
        {
        }
    };
	//====================================================================
	//= PropertyValueProvider
	//====================================================================
	//--------------------------------------------------------------------
    ::rtl::OUString PropertyValueProvider::getPropertyName() const
    {
        return m_sPropertyName;
    }

	//--------------------------------------------------------------------
    void PropertyValueProvider::getCurrentValue( Any& _out_rValue ) const
    {
        Reference< XPropertySet > xContextProps( const_cast< PropertyValueProvider* >( this )->m_rContext, UNO_QUERY_THROW );
        _out_rValue = xContextProps->getPropertyValue( getPropertyName() );
    }

	//====================================================================
	//= PropertyChangeNotifier
	//====================================================================
	//--------------------------------------------------------------------
    PropertyChangeNotifier::PropertyChangeNotifier( ::cppu::OWeakObject& _rOwner, ::osl::Mutex& _rMutex )
        :m_pData( new PropertyChangeNotifier_Data( _rOwner, _rMutex ) )
    {
    }

	//--------------------------------------------------------------------
    PropertyChangeNotifier::~PropertyChangeNotifier()
    {
    }

	//--------------------------------------------------------------------
    void PropertyChangeNotifier::registerProvider( const ShapeProperty _eProperty, const PPropertyValueProvider _pProvider )
    {
        ENSURE_OR_THROW( _eProperty != eInvalidShapeProperty, "Illegal ShapeProperty value!" );
        ENSURE_OR_THROW( !!_pProvider, "NULL factory not allowed." );

        OSL_ENSURE( m_pData->m_aProviders.find( _eProperty ) == m_pData->m_aProviders.end(),
            "PropertyChangeNotifier::registerProvider: factory for this ID already present!" );

        m_pData->m_aProviders[ _eProperty ] = _pProvider;
    }

	//--------------------------------------------------------------------
    void PropertyChangeNotifier::notifyPropertyChange( const ShapeProperty _eProperty ) const
    {
        ENSURE_OR_THROW( _eProperty != eInvalidShapeProperty, "Illegal ShapeProperty value!" );

        PropertyProviders::const_iterator provPos = m_pData->m_aProviders.find( _eProperty );
        OSL_ENSURE( provPos != m_pData->m_aProviders.end(), "PropertyChangeNotifier::notifyPropertyChange: no factory!" );
        if ( provPos == m_pData->m_aProviders.end() )
            return;

        ::rtl::OUString sPropertyName( provPos->second->getPropertyName() );

        ::cppu::OInterfaceContainerHelper* pPropListeners = m_pData->m_aPropertyChangeListeners.getContainer( sPropertyName );
        ::cppu::OInterfaceContainerHelper* pAllListeners = m_pData->m_aPropertyChangeListeners.getContainer( ::rtl::OUString() );
	    if ( !pPropListeners && !pAllListeners )
            return;

        try
        {
            PropertyChangeEvent aEvent;
            aEvent.Source = m_pData->m_rContext;
            // Handle/OldValue not supported
            aEvent.PropertyName = provPos->second->getPropertyName();
            provPos->second->getCurrentValue( aEvent.NewValue );

            if ( pPropListeners )
                pPropListeners->notifyEach( &XPropertyChangeListener::propertyChange, aEvent );
            if ( pAllListeners )
                pAllListeners->notifyEach( &XPropertyChangeListener::propertyChange, aEvent );
        }
        catch( const Exception& )
        {
        	DBG_UNHANDLED_EXCEPTION();
        }
    }

	//--------------------------------------------------------------------
    void PropertyChangeNotifier::addPropertyChangeListener( const ::rtl::OUString& _rPropertyName, const Reference< XPropertyChangeListener >& _rxListener )
    {
        m_pData->m_aPropertyChangeListeners.addInterface( _rPropertyName, _rxListener );
    }

	//--------------------------------------------------------------------
    void PropertyChangeNotifier::removePropertyChangeListener( const ::rtl::OUString& _rPropertyName, const Reference< XPropertyChangeListener >& _rxListener )
    {
        m_pData->m_aPropertyChangeListeners.removeInterface( _rPropertyName, _rxListener );
    }

	//--------------------------------------------------------------------
    void PropertyChangeNotifier::disposing()
    {
        EventObject aEvent;
        aEvent.Source = m_pData->m_rContext;
        m_pData->m_aPropertyChangeListeners.disposeAndClear( aEvent );
    }

//........................................................................
} // namespace svx
//........................................................................
