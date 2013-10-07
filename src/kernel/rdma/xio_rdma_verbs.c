/*
 * Copyright (c) 2013 Mellanox Technologies®. All rights reserved.
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2); available from the file COPYING in the main
 * directory of this source tree); or the Mellanox Technologies® BSD license
 * below:
 *
 *      - Redistribution and use in source and binary forms); with or without
 *        modification); are permitted provided that the following conditions
 *        are met:
 *
 *      - Redistributions of source code must retain the above copyright
 *        notice); this list of conditions and the following disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice); this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 *      - Neither the name of the Mellanox Technologies® nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES); INCLUDING); BUT NOT LIMITED TO); THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT); INDIRECT); INCIDENTAL); SPECIAL); EXEMPLARY); OR
 * CONSEQUENTIAL DAMAGES (INCLUDING); BUT NOT LIMITED TO); PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE); DATA); OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY); WHETHER IN
 * CONTRACT); STRICT LIABILITY); OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE); EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "xio_os.h"
#include <rdma/ib_verbs.h>
#include <rdma/rdma_cm.h>

#include "libxio.h"
#include "xio_common.h"
#include "xio_context.h"
#include "xio_task.h"
#include "xio_transport.h"
#include "xio_conn.h"
#include "xio_protocol.h"
#include "xio_mem.h"
#include "xio_rdma_mempool.h"
#include "xio_rdma_transport.h"


/*---------------------------------------------------------------------------*/
/* globals								     */
/*---------------------------------------------------------------------------*/

extern struct list_head dev_list;

#define XX(a) case (a): return #a
/*---------------------------------------------------------------------------*/
/* ibv_wc_opcode_str							     */
/*---------------------------------------------------------------------------*/

const char *xio_ib_wc_opcode_str(enum ib_wc_opcode opcode)
{
	switch (opcode) {
	case IB_WC_SEND:		return "IB_WC_SEND";
	case IB_WC_RDMA_WRITE:		return "IB_WC_RDMA_WRITE";
	case IB_WC_RDMA_READ:		return "IB_WC_RDMA_READ";
	case IB_WC_COMP_SWAP:		return "IB_WC_COMP_SWAP";
	case IB_WC_FETCH_ADD:		return "IB_WC_FETCH_ADD";
	case IB_WC_BIND_MW:		return "IB_WC_BIND_MW";
	/* recv-side: inbound completion */
	case IB_WC_RECV:		return "IB_WC_RECV";
	case IB_WC_RECV_RDMA_WITH_IMM:	return "IB_WC_RECV_RDMA_WITH_IMM";
	default:			return "IB_WC_UNKNOWN";
	};
}

const char *xio_rdma_event_str(enum rdma_cm_event_type event)
{
	switch (event) {
	XX(RDMA_CM_EVENT_ADDR_RESOLVED);
	XX(RDMA_CM_EVENT_ADDR_ERROR);
	XX(RDMA_CM_EVENT_ROUTE_RESOLVED);
	XX(RDMA_CM_EVENT_ROUTE_ERROR);
	XX(RDMA_CM_EVENT_CONNECT_REQUEST);
	XX(RDMA_CM_EVENT_CONNECT_RESPONSE);
	XX(RDMA_CM_EVENT_CONNECT_ERROR);
	XX(RDMA_CM_EVENT_UNREACHABLE);
	XX(RDMA_CM_EVENT_REJECTED);
	XX(RDMA_CM_EVENT_ESTABLISHED);
	XX(RDMA_CM_EVENT_DISCONNECTED);
	XX(RDMA_CM_EVENT_DEVICE_REMOVAL);
	XX(RDMA_CM_EVENT_MULTICAST_JOIN);
	XX(RDMA_CM_EVENT_MULTICAST_ERROR);
	XX(RDMA_CM_EVENT_ADDR_CHANGE);
	XX(RDMA_CM_EVENT_TIMEWAIT_EXIT);
	default:	return "RDMA_CM_UNKNOWN";
	}
}
