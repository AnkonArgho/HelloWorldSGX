#include <stdio.h>
#include <string.h>

# define ENCLAVE_FILENAME "enclave.signed.so"

#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"

sgx_enclave_id_t global_eid = 0;

/* ocall functions (untrusted) */
void printHelloWorldFromOutside()
{
  printf("Hello World\n");
}

/* application entry */
int SGX_CDECL main(int argc, char *argv[])
{
  (void)(argc);
  (void)(argv);

  sgx_status_t ret = SGX_ERROR_UNEXPECTED;

  // initialize enclave
  ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
  if (ret != SGX_SUCCESS) {
    printf("Enclave init error\n");
    return -1;
  }
 
  // invoke trusted_func01();
  HelloWorldFromInside(global_eid);

  if (ret != SGX_SUCCESS) {
    printf("Enclave call error\n");
    return -1;
  }

  // destroy the enclave
  sgx_destroy_enclave(global_eid);

  return 0;
}
