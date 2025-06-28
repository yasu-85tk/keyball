RGB_MATRIX_EFFECT(myef_mod_func)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
static bool myef_mod_func(effect_params_t* params) {

   RGB_MATRIX_USE_LIMITS(led_min, led_max);

   HSV hsv = rgb_matrix_config.hsv;
   RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv);
   hsv.h += rgb_matrix_config.speed;
   RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv);
   hsv.h += rgb_matrix_config.speed / 2;
   RGB rgb3 = rgb_matrix_hsv_to_rgb(hsv);
   hsv.h += rgb_matrix_config.speed / 3;
   RGB rgb4 = rgb_matrix_hsv_to_rgb(hsv);

   for (uint8_t i = led_min; i < led_max; i++) {
      RGB_MATRIX_TEST_LED_FLAGS();
      if (i == 45) {
          rgb_matrix_set_color(i, rgb4.r, rgb4.g, rgb4.b);
      } else if ((i % 13) == 6){
          rgb_matrix_set_color(i, rgb3.r, rgb3.g, rgb3.b);
      } else if ((i % 13) == 0 || (i % 13) == 12 || (i>=40 && i<=50)){
          rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
      } else {
          rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
      }
   }
   return rgb_matrix_check_finished_leds(led_max);

}
#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
