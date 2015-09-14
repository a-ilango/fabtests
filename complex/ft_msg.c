/*
 * Copyright (c) 2013-2015 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under the BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AWV
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <shared.h>
#include "fabtest.h"


static int ft_post_recv(void)
{
	struct fi_msg msg;
	int ret;

	switch (test_info.class_function) {
	case FT_FUNC_SENDV:
		ft_format_iov(ft_rx.iov, ft.iov_array[ft_rx.iov_iter],
				ft_rx.buf, ft_rx.msg_size);
		ret = fi_recvv(ft_rx.ep, ft_rx.iov, ft_rx.iov_desc,
				ft.iov_array[ft_rx.iov_iter], ft_rx.addr, &rx_ctx);
		ft_next_iov_cnt(&ft_rx, fabric_info->rx_attr->iov_limit);
		break;
	case FT_FUNC_SENDMSG:
		ft_format_iov(ft_rx.iov, ft.iov_array[ft_rx.iov_iter],
				ft_rx.buf, ft_rx.msg_size);
		msg.msg_iov = ft_rx.iov;
		msg.desc = ft_rx.iov_desc;
		msg.iov_count = ft.iov_array[ft_rx.iov_iter];
		msg.addr = ft_rx.addr;
		msg.context = &rx_ctx;
		msg.data = 0;
		ret = fi_recvmsg(ft_rx.ep, &msg, 0);
		ft_next_iov_cnt(&ft_rx, fabric_info->rx_attr->iov_limit);
		break;
	default:
		ret = fi_recv(ft_rx.ep, ft_rx.buf, ft_rx.msg_size,
				ft_rx.memdesc, ft_rx.addr, &rx_ctx);
		break;
	}

	return ret;
}

static int ft_post_trecv(void)
{
	struct fi_msg_tagged msg;
	int ret;

	switch (test_info.class_function) {
	case FT_FUNC_SENDV:
		ft_format_iov(ft_rx.iov, ft.iov_array[ft_rx.iov_iter],
				ft_rx.buf, ft_rx.msg_size);
		ret = fi_trecvv(ft_rx.ep, ft_rx.iov, ft_rx.iov_desc,
				ft.iov_array[ft_rx.iov_iter], ft_rx.addr,
				ft_rx.tag, 0, &rx_ctx);
		ft_next_iov_cnt(&ft_rx, fabric_info->rx_attr->iov_limit);
		break;
	case FT_FUNC_SENDMSG:
		ft_format_iov(ft_rx.iov, ft.iov_array[ft_rx.iov_iter],
				ft_rx.buf, ft_rx.msg_size);
		msg.msg_iov = ft_rx.iov;
		msg.desc = ft_rx.iov_desc;
		msg.iov_count = ft.iov_array[ft_rx.iov_iter];
		msg.addr = ft_rx.addr;
		msg.tag = ft_rx.tag;
		msg.ignore = 0;
		msg.context = &rx_ctx;
		ret = fi_trecvmsg(ft_rx.ep, &msg, 0);
		ft_next_iov_cnt(&ft_rx, fabric_info->rx_attr->iov_limit);
		break;
	default:
		ret = fi_trecv(ft_rx.ep, ft_rx.buf, ft_rx.msg_size,
				ft_rx.memdesc, ft_rx.addr, ft_rx.tag, 0, &rx_ctx);
		break;
	}
	return ret;
}

static int ft_post_send(void)
{
	struct fi_msg msg;
	int ret;

	switch (test_info.class_function) {
	case FT_FUNC_SENDV:
		ft_format_iov(ft_tx.iov, ft.iov_array[ft_tx.iov_iter],
				ft_tx.buf, ft_tx.msg_size);
		ret = fi_sendv(ft_tx.ep, ft_tx.iov, ft_tx.iov_desc,
				ft.iov_array[ft_tx.iov_iter], ft_tx.addr, &tx_ctx);
		ft_next_iov_cnt(&ft_tx, fabric_info->tx_attr->iov_limit);
		break;
	case FT_FUNC_SENDMSG:
		ft_format_iov(ft_tx.iov, ft.iov_array[ft_tx.iov_iter],
				ft_tx.buf, ft_tx.msg_size);
		msg.msg_iov = ft_tx.iov;
		msg.desc = ft_tx.iov_desc;
		msg.iov_count = ft.iov_array[ft_tx.iov_iter];
		msg.addr = ft_tx.addr;
		msg.context = &tx_ctx;
		msg.data = 0;
		ret = fi_sendmsg(ft_tx.ep, &msg, 0);
		ft_next_iov_cnt(&ft_tx, fabric_info->tx_attr->iov_limit);
		break;
	default:
		ret = fi_send(ft_tx.ep, ft_tx.buf, ft_tx.msg_size,
				ft_tx.memdesc, ft_tx.addr, &tx_ctx);
		break;
	}

	return ret;
}

static int ft_post_tsend(void)
{
	struct fi_msg_tagged msg;
	int ret;

	switch (test_info.class_function) {
	case FT_FUNC_SENDV:
		ft_format_iov(ft_tx.iov, ft.iov_array[ft_tx.iov_iter],
				ft_tx.buf, ft_tx.msg_size);
		ret = fi_tsendv(ft_tx.ep, ft_tx.iov, ft_tx.iov_desc,
				ft.iov_array[ft_tx.iov_iter], ft_tx.addr,
				ft_tx.tag, &tx_ctx);
		ft_next_iov_cnt(&ft_tx, fabric_info->tx_attr->iov_limit);
		break;
	case FT_FUNC_SENDMSG:
		ft_format_iov(ft_tx.iov, ft.iov_array[ft_tx.iov_iter],
				ft_tx.buf, ft_tx.msg_size);
		msg.msg_iov = ft_tx.iov;
		msg.desc = ft_tx.iov_desc;
		msg.iov_count = ft.iov_array[ft_tx.iov_iter];
		msg.addr = ft_tx.addr;
		msg.tag = ft_tx.tag;
		msg.context = &tx_ctx;
		msg.data = 0;
		ret = fi_tsendmsg(ft_tx.ep, &msg, 0);
		ft_next_iov_cnt(&ft_tx, fabric_info->tx_attr->iov_limit);
		break;
	default:
		ret = fi_tsend(ft_tx.ep, ft_tx.buf, ft_tx.msg_size,
				ft_tx.memdesc, ft_tx.addr, ft_tx.tag, &tx_ctx);
		break;
	}
	return ret;
}

int ft_post_recv_bufs(void)
{
	int ret;

	for (; ft_rx.credits; ft_rx.credits--) {
		if (test_info.caps & FI_MSG) {
			ret = ft_post_recv();
		} else {
			ret = ft_post_trecv();
			if (!ret)
				ft_rx.tag++;
		}
		if (ret) {
			if (ret == -FI_EAGAIN)
				break;
			FT_PRINTERR("recv", ret);
			return ret;
		}
	}
	return 0;
}

int ft_recv_msg(void)
{
	int credits, ret;

	if (ft_rx.credits > (ft_rx.max_credits >> 1)) {
		ret = ft_post_recv_bufs();
		if (ret)
			return ret;
	}

	credits = ft_rx.credits;
	do {
		ret = ft_comp_rx(FT_COMP_TO);
		if (ret)
			return ret;
	} while (credits == ft_rx.credits);

	return 0;
}

int ft_send_msg(void)
{
	int ret;

	while (!ft_tx.credits) {
		ret = ft_comp_tx(FT_COMP_TO);
		if (ret)
			return ret;
	}

	ft_tx.credits--;
	if (test_info.caps & FI_MSG) {
		ret = ft_post_send();
	} else {
		ret = ft_post_tsend();
		if (!ret)
			ft_tx.tag++;
	}
	if (ret) {
		FT_PRINTERR("send", ret);
		return ret;
	}

	if (!ft_tx.credits) {
		ret = ft_comp_tx(0);
		if (ret)
			return ret;
	}

	return 0;
}

int ft_send_dgram(void)
{
	int ret;

	*(uint8_t*) ft_tx.buf = ft_tx.seqno++;
	ret = ft_send_msg();
	return ret;
}

int ft_send_dgram_flood(void)
{
	int i, ret = 0;

	ft_tx.seqno = 0;
	*(uint8_t*) ft_tx.buf = 0;
	for (i = 0; i < ft.xfer_iter - 1; i++) {
		ret = ft_send_msg();
		if (ret)
			break;
	}

	return ret;
}

int ft_recv_dgram(void)
{
	int credits, ret;

	do {
		if (ft_rx.credits > (ft_rx.max_credits >> 1)) {
			ret = ft_post_recv_bufs();
			if (ret)
				return ret;
		}

		credits = ft_rx.credits;

		ret = ft_comp_rx(FT_DGRAM_POLL_TO);
		if ((credits != ft_rx.credits) &&
		    (*(uint8_t *) ft_rx.buf == ft_rx.seqno)) {
			ft_rx.seqno++;
			return 0;
		}
	} while (!ret);

	return (ret == -FI_EAGAIN) ? -FI_ETIMEDOUT : ret;
}

int ft_recv_dgram_flood(size_t *recv_cnt)
{
	int ret;
	size_t cnt = 0;

	do {
		ret = ft_post_recv_bufs();
		if (ret)
			break;

		ret = ft_comp_rx(0);
		cnt += ft_rx.credits;

	} while (!ret && (*(uint8_t *) ft_rx.buf != (uint8_t) ~0));

	*recv_cnt = cnt;
	return ret;
}

int ft_sendrecv_dgram(void)
{
	int ret, try;

	for (try = 0; try < 1000; try++) {
		ret = ft_send_dgram();
		if (ret)
			return ret;

		ret = ft_recv_dgram();
		if (ret != -FI_ETIMEDOUT)
			break;

		/* resend */
		if (test_info.caps & FI_TAGGED)
			ft_tx.tag--;
		ft_tx.seqno--;
	}

	return ret;
}
