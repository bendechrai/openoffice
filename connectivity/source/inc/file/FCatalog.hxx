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



#ifndef _CONNECTIVITY_FILE_CATALOG_HXX_
#define _CONNECTIVITY_FILE_CATALOG_HXX_

#include "connectivity/sdbcx/VCatalog.hxx"

#include "file/filedllapi.hxx"

namespace connectivity
{
	namespace file
	{
		class OConnection;
		class OOO_DLLPUBLIC_FILE SAL_NO_VTABLE OFileCatalog :
            public connectivity::sdbcx::OCatalog
		{
		protected:
			OConnection*										m_pConnection;

			/** builds the name which should be used to access the object later on in the collection.
				Will only be called in fillNames.
				@param	_xRow
					The current row from the resultset given to fillNames.
			*/
			virtual ::rtl::OUString buildName(	const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRow >& _xRow);

		public:
			virtual void refreshTables();
			virtual void refreshViews();
			virtual void refreshGroups();
			virtual void refreshUsers();

		public:
			OFileCatalog(OConnection* _pCon);
			OConnection*	getConnection() { return m_pConnection; }

			virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type & rType ) throw(::com::sun::star::uno::RuntimeException);
			// ::cppu::OComponentHelper
			virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes(  ) throw(::com::sun::star::uno::RuntimeException);
			virtual void SAL_CALL disposing(void);
		};
	}
}
#endif // _CONNECTIVITY_FILE_CATALOG_HXX_

