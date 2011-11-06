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

 
#ifndef _FILCMD_HXX_
#define _FILCMD_HXX_

#include <rtl/ustring.hxx>
#include <cppuhelper/weak.hxx>
#include <com/sun/star/uno/XInterface.hpp>
#include <com/sun/star/ucb/XCommandInfo.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>


namespace fileaccess {

	
	// forward
	class shell;
	
	
	class XCommandInfo_impl
		: public cppu::OWeakObject,
		  public com::sun::star::ucb::XCommandInfo
	{
	public:
		
		XCommandInfo_impl( shell* pMyShell );

		virtual ~XCommandInfo_impl();

		// XInterface
		virtual com::sun::star::uno::Any SAL_CALL
		queryInterface(
			const com::sun::star::uno::Type& aType )
			throw( com::sun::star::uno::RuntimeException);

		virtual void SAL_CALL
		acquire(
			void )
			throw();

		virtual void SAL_CALL
		release(
			void )
			throw();
		
		// XCommandInfo
		
		virtual com::sun::star::uno::Sequence< com::sun::star::ucb::CommandInfo > SAL_CALL
		getCommands(
			void )
			throw( com::sun::star::uno::RuntimeException);
		
		virtual com::sun::star::ucb::CommandInfo SAL_CALL
		getCommandInfoByName(
			const rtl::OUString& Name )
			throw( com::sun::star::ucb::UnsupportedCommandException,
				   com::sun::star::uno::RuntimeException);

		virtual com::sun::star::ucb::CommandInfo SAL_CALL
		getCommandInfoByHandle(
			sal_Int32 Handle )
			throw( com::sun::star::ucb::UnsupportedCommandException,
				   com::sun::star::uno::RuntimeException );

		virtual sal_Bool SAL_CALL
		hasCommandByName(
			const rtl::OUString& Name )
			throw( com::sun::star::uno::RuntimeException );

		virtual sal_Bool SAL_CALL
		hasCommandByHandle(
			sal_Int32 Handle )
			throw( com::sun::star::uno::RuntimeException );


	private:
		
		shell*                                                                  m_pMyShell;
		com::sun::star::uno::Reference< com::sun::star::ucb::XContentProvider > m_xProvider;
	};

}

#endif
