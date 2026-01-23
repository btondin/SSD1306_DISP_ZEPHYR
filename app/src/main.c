/*
 * SH1106 OLED Display Demo (LVGL 9.x)
 * Demonstrates: text, lines, arcs, bitmap image, and canvas pixel drawing
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <lvgl.h>
#include <string.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

#define DEMO_DURATION_MS 2000
#define SCREEN_WIDTH     128
#define SCREEN_HEIGHT    64

/* ─── Demo 1: Text ─────────────────────────────────────────── */
static void demo_text(void)
{
	lv_obj_t *scr = lv_screen_active();

	lv_obj_t *title = lv_label_create(scr);
	lv_label_set_text(title, "SH1106 Demo");
	lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0);
	lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 2);

	lv_obj_t *sub = lv_label_create(scr);
	lv_label_set_text(sub, "128x64 OLED");
	lv_obj_set_style_text_font(sub, &lv_font_unscii_8, 0);
	lv_obj_align(sub, LV_ALIGN_CENTER, 0, 4);

	lv_obj_t *footer = lv_label_create(scr);
	lv_label_set_text(footer, "Zephyr + LVGL");
	lv_obj_set_style_text_font(footer, &lv_font_unscii_8, 0);
	lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, -2);
}

/* ─── Demo 2: Lines ────────────────────────────────────────── */
static lv_point_precise_t line_points_triangle[] = {
	{64, 5}, {20, 58}, {108, 58}, {64, 5}
};

static lv_point_precise_t line_points_cross[] = {
	{0, 0}, {SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1}
};

static lv_point_precise_t line_points_cross2[] = {
	{SCREEN_WIDTH - 1, 0}, {0, SCREEN_HEIGHT - 1}
};

static void demo_lines(void)
{
	lv_obj_t *scr = lv_screen_active();

	static lv_style_t style_line;
	lv_style_init(&style_line);
	lv_style_set_line_width(&style_line, 1);
	lv_style_set_line_color(&style_line, lv_color_white());

	/* Triangle */
	lv_obj_t *tri = lv_line_create(scr);
	lv_line_set_points(tri, line_points_triangle, 4);
	lv_obj_add_style(tri, &style_line, 0);

	/* Diagonal cross */
	lv_obj_t *d1 = lv_line_create(scr);
	lv_line_set_points(d1, line_points_cross, 2);
	lv_obj_add_style(d1, &style_line, 0);

	lv_obj_t *d2 = lv_line_create(scr);
	lv_line_set_points(d2, line_points_cross2, 2);
	lv_obj_add_style(d2, &style_line, 0);
}

/* ─── Demo 3: Arc ──────────────────────────────────────────── */
static void demo_arc(void)
{
	lv_obj_t *scr = lv_screen_active();

	lv_obj_t *label = lv_label_create(scr);
	lv_label_set_text(label, "Arc");
	lv_obj_set_style_text_font(label, &lv_font_unscii_8, 0);
	lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 2);

	/* Large arc */
	lv_obj_t *arc = lv_arc_create(scr);
	lv_arc_set_range(arc, 0, 100);
	lv_arc_set_value(arc, 75);
	lv_arc_set_bg_angles(arc, 0, 270);
	lv_obj_set_size(arc, 50, 50);
	lv_obj_align(arc, LV_ALIGN_CENTER, -20, 6);
	lv_obj_remove_style(arc, NULL, LV_PART_KNOB);

	/* Small arc */
	lv_obj_t *arc2 = lv_arc_create(scr);
	lv_arc_set_range(arc2, 0, 100);
	lv_arc_set_value(arc2, 40);
	lv_arc_set_bg_angles(arc2, 0, 360);
	lv_obj_set_size(arc2, 30, 30);
	lv_obj_align(arc2, LV_ALIGN_CENTER, 35, 6);
	lv_obj_remove_style(arc2, NULL, LV_PART_KNOB);
}

/* ─── Demo 4: Bitmap Image ─────────────────────────────────── */

/* 32x32 smiley face bitmap (1-bit alpha, MSB first) */
static const uint8_t smiley_map[] = {
	0x00, 0x03, 0xC0, 0x00,
	0x00, 0x1F, 0xF8, 0x00,
	0x00, 0x7F, 0xFE, 0x00,
	0x00, 0xFF, 0xFF, 0x00,
	0x01, 0xFF, 0xFF, 0x80,
	0x03, 0xFF, 0xFF, 0xC0,
	0x07, 0xFF, 0xFF, 0xE0,
	0x0F, 0xFF, 0xFF, 0xF0,
	0x0F, 0xFF, 0xFF, 0xF0,
	0x1F, 0x9F, 0xF9, 0xF8,
	0x1F, 0x0F, 0xF0, 0xF8,
	0x3F, 0x0F, 0xF0, 0xFC,
	0x3F, 0x0F, 0xF0, 0xFC,
	0x3F, 0x9F, 0xF9, 0xFC,
	0x3F, 0xFF, 0xFF, 0xFC,
	0x3F, 0xFF, 0xFF, 0xFC,
	0x3F, 0xFF, 0xFF, 0xFC,
	0x3F, 0xFF, 0xFF, 0xFC,
	0x3F, 0xFF, 0xFF, 0xFC,
	0x3E, 0xFF, 0xFF, 0x7C,
	0x1E, 0x7F, 0xFE, 0x78,
	0x1F, 0x3F, 0xFC, 0xF8,
	0x0F, 0x9F, 0xF9, 0xF0,
	0x0F, 0xC0, 0x03, 0xF0,
	0x07, 0xF0, 0x0F, 0xE0,
	0x03, 0xFF, 0xFF, 0xC0,
	0x01, 0xFF, 0xFF, 0x80,
	0x00, 0xFF, 0xFF, 0x00,
	0x00, 0x7F, 0xFE, 0x00,
	0x00, 0x1F, 0xF8, 0x00,
	0x00, 0x03, 0xC0, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

static const lv_image_dsc_t smiley_img = {
	.header = {
		.magic = LV_IMAGE_HEADER_MAGIC,
		.cf = LV_COLOR_FORMAT_A1,
		.w = 32,
		.h = 32,
		.stride = 4,
	},
	.data_size = sizeof(smiley_map),
	.data = smiley_map,
};

static void demo_image(void)
{
	lv_obj_t *scr = lv_screen_active();

	lv_obj_t *label = lv_label_create(scr);
	lv_label_set_text(label, "Bitmap");
	lv_obj_set_style_text_font(label, &lv_font_unscii_8, 0);
	lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 2);

	lv_obj_t *img = lv_image_create(scr);
	lv_image_set_src(img, &smiley_img);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 6);
}

/* ─── Demo 5: Canvas pixel drawing ───────────────────────────── */
#define CANVAS_W 80
#define CANVAS_H 48
static uint8_t canvas_buf[LV_CANVAS_BUF_SIZE(CANVAS_W, CANVAS_H, 8, 1)];

static void canvas_draw_hline(lv_obj_t *canvas, int32_t x1, int32_t x2, int32_t y)
{
	for (int32_t x = x1; x <= x2; x++) {
		lv_canvas_set_px(canvas, x, y, lv_color_white(), LV_OPA_COVER);
	}
}

static void canvas_draw_vline(lv_obj_t *canvas, int32_t x, int32_t y1, int32_t y2)
{
	for (int32_t y = y1; y <= y2; y++) {
		lv_canvas_set_px(canvas, x, y, lv_color_white(), LV_OPA_COVER);
	}
}

static void demo_canvas(void)
{
	lv_obj_t *scr = lv_screen_active();

	lv_obj_t *canvas = lv_canvas_create(scr);
	lv_canvas_set_buffer(canvas, canvas_buf, CANVAS_W, CANVAS_H,
			     LV_COLOR_FORMAT_L8);
	lv_obj_align(canvas, LV_ALIGN_CENTER, 0, 0);

	/* Clear canvas to black */
	lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);

	/* Draw outer border */
	canvas_draw_hline(canvas, 0, CANVAS_W - 1, 0);
	canvas_draw_hline(canvas, 0, CANVAS_W - 1, CANVAS_H - 1);
	canvas_draw_vline(canvas, 0, 0, CANVAS_H - 1);
	canvas_draw_vline(canvas, CANVAS_W - 1, 0, CANVAS_H - 1);

	/* Draw inner rectangle */
	canvas_draw_hline(canvas, 8, CANVAS_W - 9, 8);
	canvas_draw_hline(canvas, 8, CANVAS_W - 9, CANVAS_H - 9);
	canvas_draw_vline(canvas, 8, 8, CANVAS_H - 9);
	canvas_draw_vline(canvas, CANVAS_W - 9, 8, CANVAS_H - 9);

	/* Draw an X inside the inner rectangle */
	int32_t inner_w = CANVAS_W - 18;
	int32_t inner_h = CANVAS_H - 18;

	for (int i = 0; i < inner_h; i++) {
		int32_t x = 9 + (i * inner_w) / inner_h;
		int32_t y = 9 + i;
		lv_canvas_set_px(canvas, x, y, lv_color_white(), LV_OPA_COVER);

		x = CANVAS_W - 10 - (i * inner_w) / inner_h;
		lv_canvas_set_px(canvas, x, y, lv_color_white(), LV_OPA_COVER);
	}

	/* Draw dot pattern in corners */
	for (int32_t dy = 2; dy <= 6; dy += 2) {
		for (int32_t dx = 2; dx <= 6; dx += 2) {
			lv_canvas_set_px(canvas, dx, dy,
					 lv_color_white(), LV_OPA_COVER);
			lv_canvas_set_px(canvas, CANVAS_W - 1 - dx, dy,
					 lv_color_white(), LV_OPA_COVER);
			lv_canvas_set_px(canvas, dx, CANVAS_H - 1 - dy,
					 lv_color_white(), LV_OPA_COVER);
			lv_canvas_set_px(canvas, CANVAS_W - 1 - dx, CANVAS_H - 1 - dy,
					 lv_color_white(), LV_OPA_COVER);
		}
	}
}

/* ─── Screen cleanup ───────────────────────────────────────── */
static void clear_screen(void)
{
	lv_obj_clean(lv_screen_active());
}

/* ─── Main ─────────────────────────────────────────────────── */
int main(void)
{
	const struct device *display_dev;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Display device not ready");
		return 0;
	}

	LOG_INF("SH1106 Display Demo started (LVGL 9.x)");

	lv_task_handler();
	display_blanking_off(display_dev);

	typedef void (*demo_fn)(void);
	static const demo_fn demos[] = {
		demo_text,
		demo_lines,
		demo_arc,
		demo_image,
		demo_canvas,
	};
	static const char *demo_names[] = {
		"Text", "Lines", "Arc", "Image", "Canvas"
	};
	const int num_demos = ARRAY_SIZE(demos);

	int current = 0;

	while (1) {
		LOG_INF("Demo %d/%d: %s", current + 1, num_demos,
			demo_names[current]);

		clear_screen();
		demos[current]();
		lv_task_handler();

		for (int t = 0; t < DEMO_DURATION_MS; t += 30) {
			lv_task_handler();
			k_sleep(K_MSEC(30));
		}

		current = (current + 1) % num_demos;
	}

	return 0;
}
