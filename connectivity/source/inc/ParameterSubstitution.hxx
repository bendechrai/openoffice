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


#include "precompiled_connectivity.hxx"
#include <com/sun/star/util/XStringSubstitution.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/sdbc/XConnection.hpp>
#include <cppuhelper/implbase3.hxx>

namespace connectivity
{
    typedef ::cppu::WeakImplHelper3< ::com::sun::star::util::XStringSubstitution
                                    ,::com::sun::star::lang::XServiceInfo
                                    ,::com::sun::star::lang::XInitialization > ParameterSubstitution_BASE;
    class ParameterSubstitution : public ParameterSubstitution_BASE
    {
        ::osl::Mutex                                                                    m_aMutex;
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >    m_xContext;
        ::com::sun::star::uno::WeakReference< ::com::sun::star::sdbc::XConnection >     m_xConnection;

        ParameterSubstitution( const ParameterSubstitution& );
        ParameterSubstitution& operator=( const ParameterSubstitution& );
    public:
        
        static ::rtl::OUString getImplementationName_Static(  ) throw(::com::sun::star::uno::RuntimeException);
        static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_Static(  ) throw (::com::sun::star::uno::RuntimeException);
        static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > create( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >  & xContext);
    protected:
        ParameterSubstitution(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& _rxContext );
        virtual ~ParameterSubstitution(){}

        // XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw (::com::sun::star::uno::RuntimeException);
        // XInitialization
		virtual void SAL_CALL initialize( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aArguments ) throw(::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);

        // XStringSubstitution
        virtual ::rtl::OUString SAL_CALL substituteVariables( const ::rtl::OUString& aText, ::sal_Bool bSubstRequired ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::uno::RuntimeException);
        virtual ::rtl::OUString SAL_CALL reSubstituteVariables( const ::rtl::OUString& aText ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::rtl::OUString SAL_CALL getSubstituteVariableValue( const ::rtl::OUString& variable ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::uno::RuntimeException);
    };
// ==================================
} // connectivity
// ==================================
