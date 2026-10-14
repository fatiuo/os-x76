#include "types.h"
#include "user.h"
#include"stat.h"

void test_deadlock() {
  // تعریف دو فرآیند و دو منبع
  int resource1 = 0;
  int resource2 = 1;
  
  // ایجاد اولین فرآیند
  if (fork() == 0) {
    // درخواست منبع 0
    if (requestresource(resource1) == 0) {
      printf(1, "Process 1 allocated resource 0.\n");

      // حالا در انتظار منبع 1
      if (requestresource(resource2) == -1) {
        printf(1, "Process 1 blocked while waiting for resource 1.\n");
      }
    } else {
      printf(1, "Process 1 could not acquire resource 0.\n");
    }
    
    exit();
  }

  // ایجاد دومین فرآیند
  if (fork() == 0) {
    // درخواست منبع 1
    if (requestresource(resource2) == 0) {
      printf(1, "Process 2 allocated resource 1.\n");

      // حالا در انتظار منبع 0
      if (requestresource(resource1) == -1) {
        printf(1, "Process 2 blocked while waiting for resource 0.\n");
      }
    } else {
      printf(1, "Process 2 could not acquire resource 1.\n");
    }
    
    exit();
  }

  // پدر منتظر می‌ماند تا فرآیندهای فرزند تمام شوند
  wait();
  wait();
}

int main(int argc, char *argv[]) {
  // شروع تست ددلاک
  printf(1, "Starting deadlock test...\n");
  test_deadlock();
  printf(1, "Deadlock test completed.\n");

  exit();
}
// #include"types.h"
// #include"user.h"
// #include"stat.h"
// Lock P2_Perm,P1_Perm;
// void p1(void* arg1,void* arg2){
//     REQUEST(0);
//     printf(0,"A\n");
//     REQUEST(0);
//     Lock_Release(&P2_Perm);
//     Lock_Acquire(&P1_Perm);
//     REQUEST(0);
//     printf(0,"C\n");
//     printf(0,"B\n");

//     exit();
// }

// void p2(void* arg1,void* arg2){
//     REQUEST(0);
//     Lock_Acquire(&P2_Perm);
//     printf(0,"F\n");
//     Lock_Release(&P1_Perm);
//     printf(0,"E\n");
//     REQUEST(0);
//     printf(0,"G\n");
//     exit();
// }
// int main(){
//     Lock_Init(&P2_Perm);
//     Lock_Init(&P1_Perm);
//     Lock_Acquire(&P2_Perm);
//     Lock_Acquire(&P1_Perm);
//     thread_create(&p1,(void*)0,(void*)0);
//     thread_create(&p2,(void*)0,(void*)0);
//     join(1);
//     join(2);
//     exit();
// }