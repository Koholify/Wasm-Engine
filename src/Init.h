#ifndef _KGE_INIT_H
#define _KGE_INIT_H

#include <stdbool.h>
#include <cheerp/clientlib.h>

[[cheerp::jsexport]] void kge_init();
[[cheerp::jsexport]] void kge_cleanup();
[[cheerp::jsexport]] bool kge_update();

#endif
