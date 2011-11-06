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



#ifndef CONNECTIVITY_LOCALREF_HXX
#define CONNECTIVITY_LOCALREF_HXX

/** === begin UNO includes === **/
/** === end UNO includes === **/

#include <jvmaccess/virtualmachine.hxx>

//........................................................................
namespace connectivity { namespace jdbc
{
//........................................................................

	//====================================================================
	//= LocalRef
	//====================================================================
    /** helper class to hold a local ref to a JNI object

        Note that this class never actually calls NewLocalRef. It is assumed that all objects
        passed are already acquired with a local ref (as it usually is the case if you obtain
        the object from an JNI method).
    */
    template< typename T >
    class LocalRef
    {
    public:
        explicit LocalRef( JNIEnv& environment )
            :m_environment( environment )
            ,m_object( NULL )
        {
        }

        LocalRef( JNIEnv& environment, T object )
            :m_environment( environment )
            ,m_object( object )
        {
        }

        ~LocalRef()
        {
            reset();
        }

        T release()
        {
            T t = m_object;
            m_object = NULL;
            return t;
        }

        void set( T object ) { reset(); m_object = object; }

        void reset()
        {
            if ( m_object != NULL )
            {
                m_environment.DeleteLocalRef( m_object );
                m_object = NULL;
            }
        }

        JNIEnv& env() const { return m_environment; }
        T       get() const { return m_object; }
        bool    is()  const { return m_object != NULL; }

    private:
        LocalRef(LocalRef &); // not defined
        void operator =(LocalRef &); // not defined

    protected:
        JNIEnv& m_environment;
        T       m_object;
    };

//........................................................................
} } // namespace connectivity::jdbc
//........................................................................

#endif // CONNECTIVITY_LOCALREF_HXX
