/*
 * Samsung HDMI Physical interface driver
 *
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Author: Ayoung Sim <a.sim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <uapi/linux/v4l2-dv-timings.h>
#include "hdmi.h"

static const u8 hdmiphy_conf27[32] = {
	0x01, 0x51, 0x22, 0x51, 0x08, 0xfc, 0x88, 0x46,
	0x72, 0x50, 0x24, 0x0c, 0x24, 0x0F, 0x7C, 0xA5,
	0xD4, 0x2B, 0x87, 0x00, 0x00, 0x04, 0x00, 0x30,
	0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x00,
};

static const u8 hdmiphy_conf27_027[32] = {
	0x01, 0x51, 0x22, 0x51, 0x08, 0xFC, 0x88, 0x46,
	0x72, 0x50, 0x24, 0x0C, 0x24, 0x0F, 0x7C, 0xA5,
	0xD4, 0x2B, 0x87, 0x00, 0x00, 0x04, 0x00, 0x30,
	0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x01, 0x00,
};

static const u8 hdmiphy_conf74_175[32] = {
	0x01, 0x51, 0x1F, 0x10, 0x5B, 0xEF, 0x88, 0x41,
	0x53, 0x51, 0x24, 0x0C, 0x24, 0x0F, 0x7C, 0xA5,
	0xD4, 0x2B, 0x87, 0x00, 0x00, 0x04, 0x00, 0x30,
	0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x01, 0x80,
};

static const u8 hdmiphy_conf74_25[32] = {
	0x01, 0x51, 0x1F, 0x10, 0x40, 0xF8, 0x88, 0xC1,
	0x52, 0x51, 0x24, 0x0C, 0x24, 0x0F, 0x7C, 0xA5,
	0xD4, 0x2B, 0x87, 0x00, 0x00, 0x04, 0x00, 0x30,
	0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x01, 0x00,
};

static const u8 hdmiphy_conf148_352[32] = {
	0x01, 0x51, 0x2E, 0x02, 0x40, 0x34, 0x88, 0xC2,
	0x6E, 0x53, 0x44, 0x94, 0x27, 0x0F, 0x7C, 0xA0,
	0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
	0x0A, 0x10, 0x01, 0x01, 0x48, 0x4A, 0x01, 0x00,
};

static const u8 hdmiphy_conf148_5[32] = {
	0x01, 0x51, 0x1f, 0x00, 0x40, 0xf8, 0x88, 0xc1,
	0x52, 0x52, 0x24, 0x0c, 0x24, 0x0f, 0x7c, 0xa5,
	0xd4, 0x2b, 0x87, 0x00, 0x00, 0x04, 0x00, 0x30,
	0x08, 0x10, 0x01, 0x01, 0x48, 0x4a, 0x01, 0x00,
};

static const u8 hdmiphy_conf297[32] = {
	0x01, 0x51, 0x3E, 0x05, 0x40, 0xF0, 0x88, 0xC2,
	0x52, 0x53, 0x44, 0x9C, 0x27, 0x0F, 0x7C, 0xA0,
	0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
	0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x01, 0x80,
};

const struct hdmiphy_conf hdmiphy_conf[] = {
	{ V4L2_DV_BT_CEA_720X480P59_94, hdmiphy_conf27 },
	{ V4L2_DV_BT_CEA_720X576P50, hdmiphy_conf27 },
	{ V4L2_DV_BT_CEA_1280X720P50, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1280X720P60, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080I50, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080I60, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080P24, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080P25, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080P30, hdmiphy_conf74_175 },
	{ V4L2_DV_BT_CEA_1920X1080P50, hdmiphy_conf148_5 },
	{ V4L2_DV_BT_CEA_1920X1080P60, hdmiphy_conf148_5 },
	{ V4L2_DV_BT_CEA_3840X2160P24, hdmiphy_conf297 },
	{ V4L2_DV_BT_CEA_1280X720P60_SB_HALF, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1280X720P60_TB, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1280X720P50_SB_HALF, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1280X720P50_TB, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080P24_FP, hdmiphy_conf148_5 },
	{ V4L2_DV_BT_CEA_1920X1080P24_SB_HALF, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080P24_TB, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080I60_SB_HALF, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080I50_SB_HALF, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080P60_SB_HALF, hdmiphy_conf148_5 },
	{ V4L2_DV_BT_CEA_1920X1080P60_TB, hdmiphy_conf148_5 },
	{ V4L2_DV_BT_CEA_1920X1080P30_SB_HALF, hdmiphy_conf74_25 },
	{ V4L2_DV_BT_CEA_1920X1080P30_TB, hdmiphy_conf74_25 },
};

const int hdmiphy_conf_cnt = ARRAY_SIZE(hdmiphy_conf);
