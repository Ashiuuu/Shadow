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
    cr_assert_null(1);
}
