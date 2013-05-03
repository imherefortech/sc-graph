#ifndef _test_h_
#define _test_h_

#include "prerequest.h"

#define PRINT_TEST_RESULT(res) if (res) printf("[OK]"); else printf("[ERROR]");
#define PRINT_SUBTEST(name) printf("\n\t\t > %s...", (name));

#define PREPARE_SUBTESTS()  bool result = true; bool sub_result = true;
#define RUN_SUBTEST(func, name) {  PRINT_SUBTEST(name); sub_result = func(); PRINT_TEST_RESULT(sub_result); result = result && sub_result; }
#define SUBTESTS_RESULT result

/*! Base interface for all tests
 */
class Test
{
public:
    virtual ~Test() {}

    //! Returns test name
    virtual const String& name() const = 0;

    /*! Prepare data for test
     * \return Returns false on error
     */
    virtual bool prepare() = 0;

    /*! Run test
     * \return Returns false on error
     */
    virtual bool run() = 0;

    //! Destroy garbage after test
    virtual void done() = 0;
};

#endif // _test_h_
