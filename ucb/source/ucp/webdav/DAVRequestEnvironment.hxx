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


#ifndef _DAVREQUESTENVIRONMENT_HXX_
#define _DAVREQUESTENVIRONMENT_HXX_

#include <vector>
#include <rtl/ref.hxx>
#include "DAVAuthListener.hxx"

namespace webdav_ucp
{
    typedef std::pair< rtl::OUString, rtl::OUString > DAVRequestHeader;
    typedef std::vector< DAVRequestHeader > DAVRequestHeaders;

struct DAVRequestEnvironment
{
    rtl::OUString m_aRequestURI;
    rtl::Reference< DAVAuthListener >     m_xAuthListener;
//    rtl::Reference< DAVStatusListener >   m_xStatusListener;
//    rtl::Reference< DAVProgressListener > m_xStatusListener;
    DAVRequestHeaders                     m_aRequestHeaders;
    uno::Reference< ucb::XCommandEnvironment > m_xEnv;

DAVRequestEnvironment( const rtl::OUString & rRequestURI,
                           const rtl::Reference< DAVAuthListener > & xListener,
                           const DAVRequestHeaders & rRequestHeaders,
                           const uno::Reference< ucb::XCommandEnvironment > & xEnv)
    : m_aRequestURI( rRequestURI ), 
      m_xAuthListener( xListener ),
      m_aRequestHeaders( rRequestHeaders ),
      m_xEnv( xEnv ){}

    DAVRequestEnvironment() {}
};

} // namespace webdav_ucp

#endif // _DAVREQUESTENVIRONMENT_HXX_
