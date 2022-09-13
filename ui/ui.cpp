#include "ui.h"

static lv_obj_t* background;
static lv_obj_t * meter;
static lv_obj_t* meter_label;
static lv_style_t bg_style;
static lv_style_t meter_style;
static lv_style_t meter_label_style;
static lv_color_t ventrac_red;
static lv_color_t ventrac_blue;
static lv_color_t ventrac_tan;

static void set_value(void* indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, (lv_meter_indicator_t * ) indic, v);
}

/**
 * A meter with multiple arcs
 */
void ui(void)
{
    /*================================================= Colors and Styles =======================*/
    // Ventrac colors
    ventrac_red = lv_color_hex(0xB50937);
    ventrac_blue = lv_color_hex(0x184271);
    ventrac_tan = lv_color_hex(0xC2B5A8);
    // Background style
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, ventrac_tan);
    lv_style_set_bg_opa(&bg_style, LV_OPA_100);
    lv_style_set_border_width(&bg_style, 0);
    lv_style_set_border_color(&bg_style, lv_color_black());
    // Meter style
    lv_style_init(&meter_style);
    lv_style_set_bg_color(&meter_style, ventrac_tan);
    lv_style_set_bg_opa(&meter_style, LV_OPA_100);
    lv_style_set_border_width(&meter_style, 4);
    lv_style_set_border_color(&meter_style, ventrac_blue);
    // Meter label style
    lv_style_init(&meter_label_style);
    lv_style_set_bg_color(&meter_label_style, ventrac_tan);
    lv_style_set_bg_opa(&meter_label_style, LV_OPA_100);
    lv_style_set_border_width(&meter_label_style, 0);
    lv_style_set_border_color(&meter_label_style, ventrac_blue);

    /*================================================= Background ===============================*/
    background = lv_obj_create(lv_scr_act());
    lv_obj_set_size(background, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
    lv_obj_add_style(background, &bg_style, 0);
    //lv_style_set_prop_meta(&style, LV_STYLE_TEXT_COLOR, LV_STYLE_PROP_META_INHERIT);


    /*================================================= Meter ====================================*/
    meter = lv_meter_create(background);
    meter_label = lv_label_create(meter);
    lv_obj_add_style(meter, &meter_style, 0);
    lv_obj_add_style(meter_label, &meter_label_style, 0);
    lv_obj_center(meter);
    lv_obj_center(meter_label);
    lv_obj_set_size(meter, 250, 250);
    //lv_obj_set_size(meter_label, 25, 25);
    /*Remove the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);
    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 51, 2, 6, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 10, 2, 18, lv_palette_main(LV_PALETTE_GREY), 20);
    lv_meter_set_scale_range(meter, scale, 0, 5000, 270, 133);
    /*Add a three arc indicator*/
    lv_meter_indicator_t * indic1 = lv_meter_add_arc(meter, scale, 10, ventrac_red, 0);
    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 5000);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_time(&a, 2000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_var(&a, indic1);
    lv_anim_start(&a);
    // Meter label
    lv_label_set_text_fmt(meter_label, "Engine RPM");
}
