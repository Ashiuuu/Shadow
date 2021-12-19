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

Test(io, single_letters)
{
    struct INPUT *input = input_from_string("test");

    cr_assert_eq(input->current_char, 't');
    cr_assert_eq(input->next_char, 'e');

    pop_char(input);

    cr_assert_eq(input->current_char, 'e');
    cr_assert_eq(input->next_char, 's');

    free_input(input);
}

Test(io, word)
{
    struct INPUT *input = input_from_string("test");
    char *string = "test";
    
    for (size_t i = 0; i < 4; ++i)
    {
        cr_assert_eq(input->current_char, string[i]);
        pop_char(input);
    }

    free_input(input);
}

Test(io, double_eof)
{
    struct INPUT *input = input_from_string("t");

    cr_assert_eq(input->current_char, 't');
    cr_assert_eq(input->next_char, EOF);

    pop_char(input);

    cr_assert_eq(input->current_char, EOF);
    cr_assert_eq(input->next_char, EOF);  
}

int main(int argc, char *argv[]) {
    struct criterion_test_set *tests = criterion_initialize();

    int result = 0;
    if (criterion_handle_args(argc, argv, true))
        result = !criterion_run_all_tests(tests);

    criterion_finalize(tests);
    return result;
}
