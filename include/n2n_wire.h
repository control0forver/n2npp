/**
 * (C) 2007-22 - ntop.org and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not see see <http://www.gnu.org/licenses/>
 *
 */

#if !defined( N2N_WIRE_H_ )
#define N2N_WIRE_H_

#include <stdlib.h>
#ifndef _MSC_VER
/* Not included in Visual Studio 2008 */
#include <stdint.h>
#endif

#ifndef _WIN32
#include <netinet/in.h>
#include <sys/socket.h> /* AF_INET and AF_INET6 */
#endif /* #ifndef _WIN32 */

#include "sn_selection.h"


int encode_uint8 (uint8_t * base,
                  size_t * idx,
                  const uint8_t v);

int decode_uint8 (uint8_t * out,
                  const uint8_t * base,
                  size_t * rem,
                  size_t * idx);

int encode_uint16 (uint8_t * base,
                   size_t * idx,
                   const uint16_t v);

int decode_uint16 (uint16_t * out,
                   const uint8_t * base,
                   size_t * rem,
                   size_t * idx);

int encode_uint32 (uint8_t * base,
                   size_t * idx,
                   const uint32_t v);

int decode_uint32 (uint32_t * out,
                   const uint8_t * base,
                   size_t * rem,
                   size_t * idx);

int encode_uint64 (uint8_t * base,
                   size_t * idx,
                   const uint64_t v);

int decode_uint64 (uint64_t * out,
                   const uint8_t * base,
                   size_t * rem,
                   size_t * idx);

int encode_buf (uint8_t * base,
                size_t * idx,
                const void * p,
                size_t s);

int decode_buf (uint8_t * out,
                size_t bufsize,
                const uint8_t * base,
                size_t * rem,
                size_t * idx);

int encode_mac (uint8_t * base,
                size_t * idx,
                const n2n_mac_t m);

int decode_mac (n2n_mac_t out,
                const uint8_t * base,
                size_t * rem,
                size_t * idx);

int encode_cookie (uint8_t * base,
                   size_t * idx,
                   const n2n_cookie_t c);

int decode_cookie (n2n_cookie_t * out,
                   const uint8_t * base,
                   size_t * rem,
                   size_t * idx);

int encode_common (uint8_t * base,
                   size_t * idx,
                   const n2n_common * common);

int decode_common (n2n_common * out,
                   const uint8_t * base,
                   size_t * rem,
                   size_t * idx);

int encode_sock (uint8_t * base,
                 size_t * idx,
                 const n2n_sock * sock);

int decode_sock (n2n_sock * sock,
                 const uint8_t * base,
                 size_t * rem,
                 size_t * idx);

// bugfix for https://github.com/ntop/n2n/issues/1029
// REVISIT: best to be removed with 4.0
int encode_sock_payload (uint8_t * base,
                         size_t * idx,
                         const n2n_sock * sock);

// bugfix for https://github.com/ntop/n2n/issues/1029
// REVISIT: best to be removed with 4.0
int decode_sock_payload (n2n_sock * sock,
                         const uint8_t * base,
                         size_t * rem,
                         size_t * idx);

int encode_REGISTER (uint8_t * base,
                     size_t * idx,
                     const n2n_common * common,
                     const n2n_REGISTER * reg);

int decode_REGISTER (n2n_REGISTER * pkt,
                     const n2n_common * cmn, /* info on how to interpret it */
                     const uint8_t * base,
                     size_t * rem,
                     size_t * idx);

int encode_REGISTER_SUPER (uint8_t * base,
                           size_t * idx,
                           const n2n_common * common,
                           const n2n_REGISTER_SUPER * reg);

int decode_REGISTER_SUPER (n2n_REGISTER_SUPER * pkt,
                           const n2n_common * cmn, /* info on how to interpret it */
                           const uint8_t * base,
                           size_t * rem,
                           size_t * idx);

int encode_UNREGISTER_SUPER (uint8_t *base,
                             size_t *idx,
                             const n2n_common *common,
                             const n2n_UNREGISTER_SUPER *unreg);

int decode_UNREGISTER_SUPER (n2n_UNREGISTER_SUPER *unreg,
                             const n2n_common *cmn, /* info on how to interpret it */
                             const uint8_t *base,
                             size_t *rem,
                             size_t *idx);

int encode_REGISTER_ACK (uint8_t * base,
                         size_t * idx,
                         const n2n_common * common,
                         const n2n_REGISTER_ACK * reg);

int decode_REGISTER_ACK (n2n_REGISTER_ACK * pkt,
                         const n2n_common * cmn, /* info on how to interpret it */
                         const uint8_t * base,
                         size_t * rem,
                         size_t * idx);

int encode_REGISTER_SUPER_ACK (uint8_t * base,
                               size_t * idx,
                               const n2n_common * cmn,
                               const n2n_REGISTER_SUPER_ACK * reg,
                               uint8_t * tmpbuf);

int decode_REGISTER_SUPER_ACK (n2n_REGISTER_SUPER_ACK * reg,
                               const n2n_common * cmn, /* info on how to interpret it */
                               const uint8_t * base,
                               size_t * rem,
                               size_t * idx,
                               uint8_t * tmpbuf);

int encode_REGISTER_SUPER_NAK (uint8_t * base,
                               size_t * idx,
                               const n2n_common * cmn,
                               const n2n_REGISTER_SUPER_NAK * nak);

int decode_REGISTER_SUPER_NAK (n2n_REGISTER_SUPER_NAK * nak,
                               const n2n_common * cmn, /* info on how to interpret it */
                               const uint8_t * base,
                               size_t * rem,
                               size_t * idx);

int fill_sockaddr (struct sockaddr * addr,
                   size_t addrlen,
                   const n2n_sock * sock);

int fill_n2nsock (n2n_sock* sock,
                  const struct sockaddr* sa);

int encode_PACKET (uint8_t * base,
                   size_t * idx,
                   const n2n_common * common,
                   const n2n_PACKET * pkt);

int decode_PACKET (n2n_PACKET * pkt,
                   const n2n_common * cmn, /* info on how to interpret it */
                   const uint8_t * base,
                   size_t * rem,
                   size_t * idx);

int encode_PEER_INFO (uint8_t * base,
                      size_t * idx,
                      const n2n_common * common,
                      const n2n_PEER_INFO * pkt);

int decode_PEER_INFO (n2n_PEER_INFO * pkt,
                      const n2n_common * cmn, /* info on how to interpret it */
                      const uint8_t * base,
                      size_t * rem,
                      size_t * idx);

int encode_QUERY_PEER (uint8_t * base,
                       size_t * idx,
                       const n2n_common * common,
                       const n2n_QUERY_PEER * pkt);

int decode_QUERY_PEER (n2n_QUERY_PEER * pkt,
                       const n2n_common * cmn, /* info on how to interpret it */
                       const uint8_t * base,
                       size_t * rem,
                       size_t * idx);

#endif /* #if !defined( N2N_WIRE_H_ ) */
