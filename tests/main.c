#include "./unity.h"
#include "cwindcss.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <uthash.h>

struct str_int_hash_item {
  char *key;
  int value;
  UT_hash_handle hh;
};

void setUp(void) { cwind_init(); }

void tearDown(void) { cwind_destroy(); }

void test_cwind_extract_css_classes_should_return_unique_classes(void) {
  char *html =
      "<div class=\"flex justify-center items-center flex-col md:flex-row "
      "gap-1 h-min\">"
      "<img"
      "	src=\"/static/images/logo.webp\""
      "	class=\"w-[55px] rounded-md flex\""
      "/>"
      "<h1 class=\"text-3xl lg:text-2xl md:hidden lg:block\">DankMuzikk</h1>"
      "</div>";

  array *classes = cwind_extract_css_classes(html);

  struct str_int_hash_item *unique_classes = NULL;
  ARRAY_ITER(classes, class) {
    struct str_int_hash_item *item = NULL;

    HASH_FIND_STR(unique_classes, class.string, item);
    if (item == NULL) {
      item =
          (struct str_int_hash_item *)malloc(sizeof(struct str_int_hash_item));
      item->key = class.string;
      item->value = 1;
      HASH_ADD_STR(unique_classes, key, item);
    } else {
      item->value += 1;
    }
  }

  struct str_int_hash_item *item = NULL, *tmp = NULL;
  int i = 0;
  HASH_ITER(hh, unique_classes, item, tmp) {
    TEST_ASSERT_EQUAL_INT(1, item->value);
    HASH_DEL(unique_classes, item);
    free(item);
  }

  array_destroy(classes);
}

void test_extract_css_classes_should_return_empty_array_when_no_classes_are_provided(
    void) {
  array *classes = cwind_extract_css_classes("");
  TEST_ASSERT_EQUAL_INT(0, classes->len);
  array_destroy(classes);
}

void test_process_utility_classes_should_return_unique_css_classes_of_the_given_utility_classes(
    void) {
  char *html = ""
               "<div class=\"static\">"
               "  <p class=\"text-center intro p-1 p-[20px] pt-[69px] m-[12px] "
               "mt-[200px] pb-[420px] w-[12px]\">Welcome!</p>"
               "  <button class=\"btn btn-primary -p-[25px] float-left\">Click "
               "me</button>"
               "</div>";
  char *css = cwind_process_utility_classes(html);
  char *expected_css =
      ".static {position: static;} .p-\\[20px\\] {padding: 20px;} "
      ".pt-\\[69px\\] {padding-top: 69px;} "
      ".m-\\[12px\\] {margin: 12px;} .mt-\\[200px\\] {margin-top: 200px;} "
      ".pb-\\[420px\\] {padding-bottom: 420px;} .w-\\[12px\\] {width: 12px;} "
      ".-p-\\[25px\\] {padding: -25px;} .float-left {float: left;}";

  TEST_ASSERT_EQUAL_STRING(expected_css, css);
  free((void *)css);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_cwind_extract_css_classes_should_return_unique_classes);
  RUN_TEST(
      test_extract_css_classes_should_return_empty_array_when_no_classes_are_provided);
  RUN_TEST(
      test_process_utility_classes_should_return_unique_css_classes_of_the_given_utility_classes);
  return UNITY_END();
}
