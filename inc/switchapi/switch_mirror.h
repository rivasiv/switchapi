/*
Copyright 2013-present Barefoot Networks, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _switch_mirror_h
#define _switch_mirror_h

#include "switch_base_types.h"
#include "switch_handle.h"
#include "switch_tunnel.h"
#include "model_flags.h"
#ifdef BMV2
#include "pd/pd_mirroring.h"
#else
#include "p4_sim/mirroring.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
/**
*   @defgroup Mirror Mirroring API
*  API functions define and manipulate Access lists
*  @{
*/
// begin of MIRROR API

/** Mirror ID */
typedef unsigned int switch_mirror_id_t;

/** Mirror Session type */
typedef enum {
    SWITCH_MIRROR_SESSION_TYPE_SIMPLE,               /**< Simple Mirror session */
    SWITCH_MIRROR_SESSION_TYPE_TRUNCATE,             /**< Truncate packet in session */
    SWITCH_MIRROR_SESSION_TYPE_COALESCE              /**< Coalesce mirrorred packets */
} switch_mirror_session_type_t;

/** Mirror type */
typedef enum {
    SWITCH_MIRROR_TYPE_NONE = 0,
    SWITCH_MIRROR_TYPE_LOCAL = 1,                     /**< Local mirror */
    SWITCH_MIRROR_TYPE_REMOTE = 2,                    /**< Remote mirror */
    SWITCH_MIRROR_TYPE_ENHANCED_REMOTE = 3            /**< ERSpan mirror */
} switch_mirror_type_t;

/** Mirror API information */
typedef struct switch_api_mirror_info_ {
    switch_mirror_type_t mirror_type;                 /**< mirror type */
    switch_mirror_id_t session_id;                    /**< mirror session id */
    switch_mirror_session_type_t session_type;        /**< mirror session type */
    switch_handle_t egress_port;                      /**< egress port */
    switch_direction_t direction;                     /**< direction */
    switch_cos_t cos;                                 /**< traffic class */
    switch_vlan_t vlan_id;                            /**< vlan id */
    uint16_t vlan_tpid;                               /**< vlan tag protocol */
    uint8_t vlan_priority;                            /**< vlan priority */
    bool tunnel_create;                               /**< tunnel create */
    bool vlan_create;                                 /**< vlan create */
    switch_encap_type_t encap_type;                   /**< tunnel encap type */
    switch_tunnel_info_t tunnel_info;                 /**< tunnel info */
    switch_mac_addr_t src_mac;                        /**< soource mac */
    switch_mac_addr_t dst_mac;                        /**< destination mac */
    uint32_t max_pkt_len;                             /**< max packet length */
    switch_handle_t nhop_handle;                      /**< nexthop handle */
    bool enable;                                      /**< enable mirror */
} switch_api_mirror_info_t;

/**
* ID for cpu mirror session
*/
#define SWITCH_CPU_MIRROR_SESSION_ID 250

/**
* ID for negative mirror session
*/
#define SWITCH_NEGATIVE_MIRROR_SESSION_ID  1015

/**
 Create a mirror sesion
 @param device device on which to create mirror session
 @param api_mirror_info parameters of mirror session
*/

switch_handle_t switch_api_mirror_session_create(switch_device_t device,
                                                 switch_api_mirror_info_t *api_mirror_info);

/**
 Update a mirror sesion
 @param device device on which to create mirror session
 @param mirror_handle mirror handle
 @param api_mirror_info parameters of mirror session
*/
switch_status_t switch_api_mirror_session_update(switch_device_t device,
                                                 switch_handle_t mirror_handle,
                                                 switch_api_mirror_info_t *api_mirror_info);
/**
 delete the mirror session
 @param device device
 @param mirror_handle mirror handle
*/
switch_status_t switch_api_mirror_session_delete(switch_device_t device,
                                             switch_handle_t mirror_handle);

/**
 create mirror nexthop
 @param device device
 @param mirror_handle mirror handle
 @param nhop_hdl nexthop handle
 */
switch_status_t switch_mirror_nhop_create(switch_device_t device,
                                          switch_handle_t mirror_handle,
                                          switch_handle_t nhop_hdl);

/**
 delete mirror nexthop
 @param device device
 @param mirror_handle mirror handle
 */
switch_status_t switch_mirror_nhop_delete(switch_device_t device,
                                          switch_handle_t mirror_handle);

/** @} */ // end of ACL API

#ifdef __cplusplus
}
#endif

#endif
