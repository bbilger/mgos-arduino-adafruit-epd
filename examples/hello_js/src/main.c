/*
 * MIT License
 *
 * Copyright (c) 2019 Bjoern Bilger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>

#include "mgos_app.h"
#include "mgos_aepd.h"

static const uint8_t mgos_logo [] = {
	0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	0xc0, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x00,
	0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00,
	0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff,
	0xff, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
	0xe0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x07, 0xff, 0x9f, 0xfc, 0x7f, 0xf8, 0x00,
	0x0f, 0xff, 0x07, 0xf8, 0x3f, 0xfc, 0x00, 0x1f, 0xfe, 0x77, 0xfb, 0x9f, 0xfe, 0x00, 0x3f, 0xfe,
	0x73, 0xf3, 0x9f, 0xff, 0x00, 0x3f, 0xfe, 0x67, 0xf1, 0x9f, 0xff, 0x00, 0x7f, 0xfc, 0x07, 0xe0,
	0x3f, 0xff, 0x80, 0x7f, 0xf8, 0x1f, 0xc0, 0xff, 0xff, 0x80, 0xff, 0xf0, 0x7e, 0x03, 0xf0, 0xff,
	0xc0, 0xff, 0xe0, 0xfc, 0x07, 0xe2, 0x7f, 0xc0, 0xff, 0xc1, 0xfc, 0xcf, 0xe7, 0x7f, 0xc0, 0xff,
	0x83, 0xfc, 0xcf, 0xe7, 0x7f, 0xc0, 0xff, 0x07, 0xfc, 0x0f, 0xf0, 0x3f, 0xc0, 0xfe, 0x0f, 0xfe,
	0x1f, 0xf0, 0x1f, 0xc0, 0x7c, 0x1f, 0xff, 0xff, 0xff, 0x0f, 0x80, 0x78, 0x3f, 0xff, 0xff, 0xff,
	0x87, 0x80, 0x30, 0x7f, 0xff, 0xff, 0xff, 0xc3, 0x00, 0x20, 0xff, 0xff, 0xff, 0xff, 0xe1, 0x00,
	0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff,
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xff,
	0xff, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80,
	0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00,
	0x0f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xff,
	0xff, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0,
	0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00
};



const uint8_t *mgos_aepd_ex_get_logo(void) {
  return mgos_logo;
}

enum mgos_app_init_result mgos_app_init(void) {
  return MGOS_APP_INIT_SUCCESS;
}
