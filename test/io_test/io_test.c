#include <criterion/criterion.h>
#include "io.h"

/*Test(Io_Test, No_String)
  {
  string_to_stream("");
  }*/

/*Test(Io_test, "Simple String")
  {
  FILE *stream = string_to_stream("Hello World");
  cr_assert_str_not_empty(fgetc(stream));
  cr_assert_str_eq(fgetc(stream), 'e');
  }*/

Test(Sample, test_is_null)
{
    cr_assert_null(NULL);
}

int main(int argc, char *argv[]) {
    struct criterion_test_set *tests = criterion_initialize();

    int result = 0;
    if (criterion_handle_args(argc, argv, true))
        result = !criterion_run_all_tests(tests);

    criterion_finalize(tests);
    return result;
}
