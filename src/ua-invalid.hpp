#ifndef __UA_INVALID_DATA_HPP__
#define __UA_INVALID_DATA_HPP__

#include <time.h>

#include <sofia-sip/nta.h>
#include <sofia-sip/sip.h>
#include <sofia-sip/nta_tport.h>
#include <sofia-sip/tport.h>

#include "drachtio.h"

namespace drachtio {

  class UaInvalidData {
    public: 
      UaInvalidData(const char* szUser, const char* szHost, int expires, tport_t* tp ) : m_tp(tp) {
        strncpy( m_szUser, szUser, URI_LEN - 1) ;
        strncpy( m_szHost, szHost, URI_LEN - 1) ;
        time(&m_expires) ;
        m_expires += expires ;
        tport_ref(m_tp) ;

      }
      ~UaInvalidData() {
        tport_unref(m_tp) ;
      }
      UaInvalidData& operator=( const UaInvalidData& ua ) {
        strncpy( m_szUser, ua.m_szUser, URI_LEN - 1) ;
        strncpy( m_szHost, ua.m_szHost, URI_LEN - 1) ;
        m_expires = ua.m_expires ;
        tport_ref(m_tp) ;   
        return *this ;       
      }

      void getUri( string& uri ) {
        uri = "" ;
        uri.append( m_szUser ) ;
        uri.append( "@" ) ;
        uri.append( m_szHost ) ;
      }
      tport_t* getTport(void) { return m_tp; }
      bool isExpired(void) {
        return m_expires < time(0) ;
      }
      void extendExpires(int expires) {
        m_expires = time(0) + expires ;
      }
    private:
      // not allowed
      UaInvalidData() {}

      char m_szUser[URI_LEN] ;
      char m_szHost[URI_LEN] ;
      time_t m_expires ;
      tport_t* m_tp ;
  } ;

}

#endif