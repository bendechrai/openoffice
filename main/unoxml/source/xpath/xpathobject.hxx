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



#ifndef XPATH_XPATHOBJECT_HXX
#define XPATH_XPATHOBJECT_HXX

#include <boost/shared_ptr.hpp>

#include <libxml/tree.h>
#include <libxml/xpath.h>

#include <sal/types.h>
#include <rtl/ref.hxx>

#include <cppuhelper/implbase1.hxx>

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/xml/dom/XNodeList.hpp>
#include <com/sun/star/xml/xpath/XXPathObject.hpp>


using ::rtl::OUString;
using namespace com::sun::star::uno;
using namespace com::sun::star::xml::dom;
using namespace com::sun::star::xml::xpath;


namespace DOM {
    class CDocument;
}

namespace XPath
{
    class CXPathObject : public cppu::WeakImplHelper1< XXPathObject >
    {
    private:
        ::rtl::Reference< DOM::CDocument > const m_pDocument;
        ::osl::Mutex & m_rMutex;
        boost::shared_ptr<xmlXPathObject> const m_pXPathObj;
        XPathObjectType const m_XPathObjectType;

    public:
        CXPathObject( ::rtl::Reference<DOM::CDocument> const& pDocument,
            ::osl::Mutex & rMutex,
            ::boost::shared_ptr<xmlXPathObject> const& pXPathObj);

    /**
        get object type
    */
    virtual XPathObjectType SAL_CALL getObjectType() throw (RuntimeException);

    /**
        get the nodes from a nodelist type object
    */
    virtual Reference< XNodeList > SAL_CALL getNodeList()
        throw (RuntimeException);

     /**
        get value of a boolean object
     */
     virtual sal_Bool SAL_CALL getBoolean() throw (RuntimeException);

    /**
        get number as byte
    */
    virtual sal_Int8 SAL_CALL getByte() throw (RuntimeException);

    /**
        get number as short
    */
    virtual sal_Int16 SAL_CALL getShort() throw (RuntimeException);

    /**
        get number as long
    */
    virtual sal_Int32 SAL_CALL getLong() throw (RuntimeException);

    /**
        get number as hyper
    */
    virtual sal_Int64 SAL_CALL getHyper() throw (RuntimeException);

    /**
        get number as float
    */
    virtual float SAL_CALL getFloat() throw (RuntimeException);

    /**
        get number as double
    */
    virtual double SAL_CALL getDouble() throw (RuntimeException);

    /**
        get string value
    */
    virtual OUString SAL_CALL getString() throw (RuntimeException);

    };
}

#endif
