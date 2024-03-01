#ifndef _ASSERT_H_
#define _ASSERT_H_

namespace ASSERT {
    typedef int i32;
    typedef unsigned int u32;
#define FUNC_NAME(f) #f

    class Assert {
        private:
            i32 total_test;
            i32 pass_test;
            i32 fault_test;
            i32 success_test;
            long assert_total_time;
            long assert_func_time;
            long assert_total_start_time;
        public:
            Assert();
            ~Assert();
            void assert_coll(void (*func_test)());
            void begin_assert();
            void assert_true(bool expression);
            void assert_false(bool expression);
            void assert_null(void *);
            template <typename T, typename I> 
            void assert_exualse (T t, I i);
            void end_assert();
    };

}


#endif //_ASSERT_H_
