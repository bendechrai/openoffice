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



#ifndef _CONNECTIVITY_FLAT_EDATABASEMETADATA_HXX_
#define _CONNECTIVITY_FLAT_EDATABASEMETADATA_HXX_

#include "file/FDatabaseMetaData.hxx"

namespace connectivity
{
	namespace flat
	{
		//**************************************************************
		//************ Class: java.sql.DatabaseMetaDataDate
		//**************************************************************

		class OFlatDatabaseMetaData :	public file::ODatabaseMetaData
		{
            virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet > impl_getTypeInfo_throw();
        protected:
            virtual ~OFlatDatabaseMetaData();
		public:
			OFlatDatabaseMetaData(file::OConnection* _pCon);

			virtual ::rtl::OUString SAL_CALL getURL(  ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
			virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet > SAL_CALL getColumns( const ::com::sun::star::uno::Any& catalog, const ::rtl::OUString& schemaPattern, const ::rtl::OUString& tableNamePattern, const ::rtl::OUString& columnNamePattern ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
		};
	}
}
#endif // _CONNECTIVITY_FLAT_ODATABASEMETADATA_HXX_

