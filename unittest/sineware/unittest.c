/**
 *   \file main.c
 *   \brief unit test sineware.c
 *
 *  Detailed description
 *
 */
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include <BCUnit/Basic.h>
#include <BCUnit/Console.h>
#include <BCUnit/BCUnit.h>
#include <BCUnit/TestDB.h>

#include "sinewave.h"

/* 测试获取y 的函数 */
void test_sineware_gety(void)
{
    double x = 1;
    double y = sinewave_get_y(x);
	int ret = 0;
	printf( "y=%f\n", y);
	if ( y > -0.01 && y < 0.01 ) {
		ret = 1;
	}

    CU_ASSERT_EQUAL(ret, 1);
}

/* 初始化suite */
int suite_success_init(void)
{
    return 0;
}

/* 清理suite */
int suite_success_clean(void)
{
    return 0;
}

CU_TestInfo testcase_sineware_gety[] = { { "test_sineware_gety",
                                           test_sineware_gety },
                                         CU_TEST_INFO_NULL };

//定义suite数组，包括多个suite，每个suite又会包括若干个测试方法。
CU_SuiteInfo suites[] = { { "test_sineware", suite_success_init,
                            suite_success_clean, NULL, NULL,
                            testcase_sineware_gety },
                          CU_SUITE_INFO_NULL };

/* 测试入口 */
void AddTests(void)
{
    assert(NULL != CU_get_registry());
    assert(!CU_is_test_running());

    if (CUE_SUCCESS != CU_register_suites(suites)) {
        exit(EXIT_FAILURE);
    }
}

/* 运行测试入口 */
int RunTest(void)
{
    if (CU_initialize_registry()) {
        fprintf(stderr, " Initialization of Test Registry failed. ");
        exit(EXIT_FAILURE);
    } else {
        AddTests();
        /**** Automated Mode *****************
                CU_set_output_filename("TestMax");
                CU_list_tests_to_file();
                CU_automated_run_tests();
                //************************************/
        /* CU_set_output_filename("TestMax"); */
        /* CU_list_tests_to_file(); */
        /* CU_automated_run_tests(); */

        /***** Basice Mode *******************
                CU_basic_set_mode(CU_BRM_VERBOSE);
                CU_basic_run_tests();
				//************************************/
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        /*****Console Mode ********************
                CU_console_run_tests();

                //************************************/
        /* CU_console_run_tests(); */

        /* CU_cleanup_registry(); */

        return CU_get_error();
    }
}

int main(int argc, char *argv[])
{
	RunTest();
    return 0;
}
