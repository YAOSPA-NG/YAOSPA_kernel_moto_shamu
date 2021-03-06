/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#undef TRACE_SYSTEM
#define TRACE_SYSTEM rmnet_data
#define TRACE_INCLUDE_FILE rmnet_data_trace

#if !defined(_TRACE_MSM_LOW_POWER_H_) || defined(TRACE_HEADER_MULTI_READ)
#define _RMNET_DATA_TRACE_H_

#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/tracepoint.h>

DECLARE_EVENT_CLASS(rmnet_handler_template,

	TP_PROTO(struct sk_buff *skb),

	TP_ARGS(skb),

	TP_STRUCT__entry(
		__field(void *, skbaddr)
		__field(unsigned int, len)
		__string(name, skb->dev->name)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->len = skb->len;
		__assign_str(name, skb->dev->name);
	),

	TP_printk("dev=%s skbaddr=%p len=%u",
		__get_str(name), __entry->skbaddr, __entry->len)
)

DEFINE_EVENT(rmnet_handler_template, rmnet_egress_handler,

	TP_PROTO(struct sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(rmnet_handler_template, rmnet_ingress_handler,

	TP_PROTO(struct sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(rmnet_handler_template, rmnet_vnd_start_xmit,

	TP_PROTO(struct sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(rmnet_handler_template, __rmnet_deliver_skb,

	TP_PROTO(struct sk_buff *skb),

	TP_ARGS(skb)
);

TRACE_EVENT(rmnet_map_checksum_downlink_packet,

	TP_PROTO(struct sk_buff *skb, int ckresult),

	TP_ARGS(skb, ckresult),

	TP_STRUCT__entry(
		__string(name, skb->dev->name)
		__field(int, res)
	),

	TP_fast_assign(
		__assign_str(name, skb->dev->name);
		__entry->res = ckresult;
	),

	TP_printk("DL checksum on dev=%s, res: %d",
		__get_str(name), __entry->res)
)

TRACE_EVENT(rmnet_map_checksum_uplink_packet,

	TP_PROTO(struct net_device *dev, int ckresult),

	TP_ARGS(dev, ckresult),

	TP_STRUCT__entry(
		__string(name, dev->name)
		__field(int, res)
	),

	TP_fast_assign(
		__assign_str(name, dev->name);
		__entry->res = ckresult;
	),

	TP_printk("UL checksum on dev=%s, res: %d",
		__get_str(name), __entry->res)
)

#endif /* _RMNET_DATA_TRACE_H_ */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#include <trace/define_trace.h>

